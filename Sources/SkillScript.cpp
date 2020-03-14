#include "stdafx.h"
#include "define.h"
#include "SkillScript.h"
#include "SkillInst.h"
#include "SkillSpec.h"
#include "Utils.h"
#include "Dict.h"
#include "Settings.h"

//////////////////////////////////////////////////////////////////////////
SkillScriptRefInfo::SkillScriptRefInfo()
: _name(""), _id(_INVALID_ID), _info(""), _isSelected(false)
{
}

bool SkillScriptRefInfo::fromXml(const QDomElement& curNode, int scriptId)
{
    _name = curNode.nodeName();
    _id = curNode.attribute("id", "0").toInt();
    _info = curNode.attribute("info", _info);
    return true;
}

bool SkillScriptRefInfo::toXml(QDomDocument& doc, QDomElement& curNode, bool deep)
{
    if (_id < 0 || _info.isEmpty()) {
        return true;
    }
    curNode.setAttribute("id", QString::number(this->_id));
    curNode.setAttribute("info", _info);
    return true;
}

bool SkillScriptRefInfo::toStreamXml(QXmlStreamWriter& writer, bool deep)
{
    if (_id < 0 || _info.isEmpty()) {
        return true;
    }

    writer.writeAttribute("id", QString::number(this->_id));
    writer.writeAttribute("info", _info);
    return true;
}

void SkillScriptRefInfo::clone(SkillScriptRefInfoPtr ptr)
{
    this->_name = ptr->_name;
    this->_id = ptr->_id;
    this->_info = ptr->_info;
}

//////////////////////////////////////////////////////////////////////////
SkillScriptNodeParam::SkillScriptNodeParam()
: _name(""), _type(_INVALID_ID), _number(_INVALID_ID), _string(""), _ref(0),
_parent(nullptr), _isEmit(false)
{
}

bool SkillScriptNodeParam::fromXml(const QDomAttr& curNode, int scriptId)
{
    QString key = curNode.name().toLower();
    QString val = curNode.value().toLower();

    _name = key;
    if (isStringTxt(val)) {
        this->_type = SkillScriptNodeParam::STRING;
        this->_string = val.right(val.length() - 1);
    } else if (isRefTxt(val)) {
        this->_type = SkillScriptNodeParam::REFERENCE;
        this->_ref = val.right(val.length() - 1).toDouble() + 1;
        this->_number = getInstDataParamByIdx(this->_ref);
    } else {
        this->_type = SkillScriptNodeParam::NUMBER;
        this->_number = val.toDouble();
    }
    return true;
}

bool SkillScriptNodeParam::toXml(QDomDocument& doc, QDomElement & curNode, bool deep)
{
    if (!isModified()) {
        return true;
    }
    if (this->_type == SkillScriptNodeParam::STRING) {
        curNode.setAttribute(_name, QString("#") + this->_string);
    } else if (this->_type == SkillScriptNodeParam::REFERENCE) {
        curNode.setAttribute(_name, QString("%") + QString::number(this->_ref - 1));
    } else if (this->_type == SkillScriptNodeParam::NUMBER) {
        curNode.setAttribute(_name, this->_number);
    }
    return true;
}

bool SkillScriptNodeParam::toStreamXml(QXmlStreamWriter& writer, bool deep)
{
    if (!isModified()) {
        return true;
    }
    if (this->_type == SkillScriptNodeParam::STRING) {
        writer.writeAttribute(_name, QString("#") + this->_string);
    } else if (this->_type == SkillScriptNodeParam::REFERENCE) {
        writer.writeAttribute(_name, QString("%") + QString::number(this->_ref - 1));
    } else if (this->_type == SkillScriptNodeParam::NUMBER) {
        writer.writeAttribute(_name, QString::number(this->_number));
    }
    return true;
}

void SkillScriptNodeParam::notify(SkillNotifyReason reason)
{
    if (_isEmit && _parent != nullptr && _parent->getScript() != nullptr) {
        emit _parent->getScript()->paramChanged(*this, reason);
    }
}

void SkillScriptNodeParam::clone(const SkillScriptNodeParam& param)
{
    this->_name = param._name;
    this->_type = param._type;
    this->_number = param._number;
    this->_ref = param._ref;
    this->_string = param._string;
}

void SkillScriptNodeParam::setName(const QString& name)
{
    if (_name != name) {
        _name = name;
        this->notify(SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_NAME);
    }
}

void SkillScriptNodeParam::setAsString(const QString& str)
{
    _type = SkillScriptNodeParam::STRING;
    _ref = 0;
    _number = _INVALID_ID;
    _string = str;
    this->notify(SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_STRING);
}

void SkillScriptNodeParam::setAsRefNum(double num)
{
    _type = SkillScriptNodeParam::REFERENCE;
    _string = "";
    bool bNofityRef = false;
    if (_number != num) {
        _number = num;
        this->notify(SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_REF_NUMBER);
    }
}

void SkillScriptNodeParam::setAsRefIdx(int refIdx)
{
    _type = SkillScriptNodeParam::REFERENCE;
    _string = "";
    if (_ref != refIdx) {
        _ref = refIdx;
        this->notify(SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_REF);
    }
}
bool SkillScriptNodeParam::isRefTxt(const QString& val)
{
    return val.length() >= 1 && val.startsWith("%");
}

bool SkillScriptNodeParam::isStringTxt(const QString& val)
{
    return val.length() >= 1 && val.startsWith("#");
}

QString SkillScriptNodeParam::getDisplayData() const
{
    if (isRef()) {
        return QString("%1(%%2)").arg(_number).arg(_ref);
    } else if (isString()) {
        return _string;
    } else if (isNumber()) {
        return QString::number(_number);
    }
    return "";
}

QString SkillScriptNodeParam::getParentNodeId() const
{
    if (_parent != nullptr) {
        return _parent->getId();
    }
    return "";
}

bool SkillScriptNodeParam::isModified() const
{
    if (_parent == nullptr) {
        return true;
    }
    SkillSpecNodeParamPtr argPtr = getSpecNodeParam(_parent->getId(), _name);
    if (argPtr != nullptr) {
        if (isRef()) {
            return true;
        } else if (isString()) {
            return (QString("#") + this->_string) != argPtr->getDefault();
        } else if (isNumber()) {
            return QString::number(_number) != argPtr->getDefault();
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
SkillScriptNode::SkillScriptNode(SkillScript *script)
: _name(""), _id(""), _autoId(_INVALID_ID), _script(script), _parent(nullptr),
_treeItem(nullptr), _isEmit(false), _isInValid(false), _info(""),
_isExpand(true), _isSelected(false), _jump(nullptr)
{
    _nodes.clear();
    _params.clear();
}
SkillScriptNode::~SkillScriptNode()
{
    _nodes.clear();
    _params.clear();
    _treeItem = nullptr;
    _parent = nullptr;
    _script = nullptr;
}

bool SkillScriptNode::fromXml(const QDomElement& curNode, int scriptId)
{
    _name = curNode.nodeName();
    _id = curNode.attribute("id", _id).toLower();
    _info = curNode.attribute("info", _info);

    //fill default params
    fillScriptNodeParams(*this);
    //parse attributes
    QDomNamedNodeMap attrs = curNode.attributes();
    if (attrs.length() > 0) {
        for (int idx = 0; idx < attrs.length(); idx++) {
            QDomNode& node = attrs.item(idx);
            if (node.toAttr().name() == "id") {
                continue;
            }
            if (node.toAttr().name() == "info") {
                continue;
            }
            SkillSpecNodeParamPtr specNodeParam = getSpecNodeParam(_id, node.toAttr().name());
            if (specNodeParam == nullptr) {
                continue;//凡是不在SkillSpec.xml中的属性，全部不读入
            }
            SkillScriptNodeParamPtr nodePtr = SkillScriptNodeParamPtr::create();
            nodePtr->fromXml(node.toAttr(), scriptId);
            this->addParam(nodePtr);
        }
    }

    //parse child nodes
    QDomNodeList nodes = curNode.childNodes();
    if (nodes.length() > 0) {
        for (int idx = 0; idx < nodes.length(); idx++) {
            QDomNode& node = nodes.at(idx);
            if (node.nodeName() == SKILLSCRIPT_REFINFOS_TAG_NAME) {
                continue;;
            }
            SkillSpecNodePtr specNode = getSpecNode(_id);
            if (specNode == nullptr) {
                continue;//凡是不在SkillSpec.xml中的节点，全部不读入
            }
            SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(_script);
            nodePtr->fromXml(node.toElement(), scriptId);
            this->addNode(nodePtr);
        }
    }

    return true;
}

bool SkillScriptNode::toXml(QDomDocument& doc, QDomElement & curNode, bool deep)
{
    //属性
    curNode.setAttribute("id", this->_id);
    if (this->_info.length() > 0) {
        curNode.setAttribute("info", this->_info);
    }
    for (int idx = 0; idx < this->_params.length(); idx++) {
        SkillScriptNodeParamPtr ptr = this->_params.at(idx);
        if (ptr != nullptr && ptr->getName() != "id") {
            ptr->toXml(doc, curNode, true);
        }
    }

    //子节点
    for (int idx = 0; idx < this->_nodes.length(); idx++) {
        SkillScriptNodePtr ptr = this->_nodes.at(idx);
        if (ptr != nullptr) {
            QDomElement node = doc.createElement(ptr->getName());
            curNode.appendChild(node);
            ptr->toXml(doc, node, true);
        }
    }

    return true;
}

bool SkillScriptNode::toStreamXml(QXmlStreamWriter& writer, bool deep)
{
    //属性
    writer.writeAttribute("id", this->_id);
    if (this->_info.length() > 0) {
        writer.writeAttribute("info", this->_info);
    }
    for (int idx = 0; idx < this->_params.length(); idx++) {
        SkillScriptNodeParamPtr ptr = this->_params.at(idx);
        if (ptr != nullptr && ptr->getName() != "id") {
            ptr->toStreamXml(writer, true);
        }
    }

    //子节点
    for (int idx = 0; idx < this->_nodes.length(); idx++) {
        SkillScriptNodePtr ptr = this->_nodes.at(idx);
        if (ptr != nullptr) {
            writer.writeStartElement(ptr->getName());
            ptr->toStreamXml(writer, true);
            writer.writeEndElement();
        }
    }

    return true;
}

bool SkillScriptNode::toTree(QTreeWidgetItem* curNode) const
{
    //子节点
    for (int idx = 0; idx < this->_nodes.length(); idx++) {
        SkillScriptNodePtr ptr = this->_nodes.at(idx);
        if (ptr != nullptr) {
            QTreeWidgetItem *node = new QTreeWidgetItem(curNode);
            ptr->toTree(node);
            node->setText(0, formatScriptNodeTitle(*ptr));
            node->setToolTip(0, formatScriptNodeToolTip(*ptr));
        }
    }
    _treeItem = curNode;
    //设置外观
    if (gSettings->isShowIcons()) {
        QString iconPath = getIconName(this->getId());
        if (!iconPath.isEmpty()) {
            curNode->setIcon(0, QIcon(iconPath));
        }
    }
    SkillSpecNodePtr specRecord = getSpecNode(_id);
    if (specRecord != nullptr && specRecord->getNodeType() == SKILLSPEC_TOOL_NODE_TYPE) {
        curNode->setBackground(0, QBrush(QColor(SKILLNODE_TOOL_BACKGROUND_COLOR)));
    }
    curNode->setExpanded(_isExpand);
    //curNode->setSelected(_isSelected);

    //关联SkillNode指针
    SkillScriptNodeUserData userData;
    userData._skillNode = const_cast<SkillScriptNode*>(this);
    curNode->setData(0, Qt::UserRole + 1, QVariant::fromValue(userData));

    return true;
}

void SkillScriptNode::updateTree()
{
    if (_treeItem != nullptr) {
        _treeItem->setText(0, formatScriptNodeTitle(*this));
    }
}

void SkillScriptNode::notify(SkillNotifyReason reason)
{
    if (_isEmit && _script != nullptr) {
        emit _script->nodeChanged(*this, reason);
    }
}

void SkillScriptNode::setId(const QString& id)
{
    if (_id != id) {
        _id = id;
        _name = getSpecNodeName(this->getId());
        _params.clear();
        _info = "";
        this->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ID);
    }
}

SkillScriptNodePtr SkillScriptNode::getNode(int idx)
{
    if (idx >= 0 && idx < _nodes.length()) {
        return _nodes[idx];
    }
    return SkillScriptNodePtr();
}

SkillScriptNodePtr SkillScriptNode::getChildNode(const QString& nodeId)
{
    for (int idx = 0; idx < _nodes.length(); idx++) {
        SkillScriptNodePtr ptr = _nodes.at(idx);
        if (ptr != nullptr && ptr->getId() == nodeId) {
            return ptr;
        }
    }
    return SkillScriptNodePtr();
}

void SkillScriptNode::addNode(SkillScriptNodePtr node, int idx)
{
    if (idx < 0) {
        _nodes.push_back(node);
    } else {
        _nodes.insert(idx, node);
    }
    fillScriptNodeParams(*node);
    node->setParent(this);
    node->setIsEmit(true);
    node->_isInValid = false;
    node->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ADD_NODE);
}

void SkillScriptNode::removeNode(SkillScriptNode* node)
{
    for (int idx = 0; idx < _nodes.length(); idx++) {
        SkillScriptNodePtr ptr = _nodes.at(idx);
        if (ptr.data() == node) {
            _nodes.removeAt(idx);
            node->_isInValid = true;
            ptr->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_REMOVE_NODE);
            ptr->setIsEmit(false);
        }
    }
}

void SkillScriptNode::moveNode(SkillScriptNode* node, bool up)
{
    SkillScriptNodePtr ptr = asNodePtr(node);
    int idx = getNodeIdx(node);
    if (ptr != nullptr && idx >= 0) {
        bool isNotify = false;
        if (up) {
            if (idx >= 1) {
                _nodes.removeAt(idx);
                _nodes.insert(idx - 1, ptr);
                isNotify = true;
            }
        } else {
            if (idx == _nodes.length() - 1) {
                _nodes.removeAt(idx);
                _nodes.push_back(ptr);
                isNotify = true;
            } else if (idx < _nodes.length() - 1) {
                _nodes.removeAt(idx);
                _nodes.insert(idx + 1, ptr);
                isNotify = true;
            }
        }

        if (isNotify) {
            ptr->setIsEmit(true);
            ptr->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_MOVE_NODE);
        }
    }
}

SkillScriptNode* SkillScriptNode::getNextNeibour()
{
    if (_parent != nullptr) {
        int idx = getNodeIdx(this);
        if (idx >= 0 && idx < _parent->getNodesLength() - 1) {
            return _parent->getNode(idx + 1).data();
        } else {
            return _parent;
        }
    }
    return nullptr;
}

SkillScriptNode* SkillScriptNode::getPrevNeibour()
{
    if (_parent != nullptr) {
        int idx = getNodeIdx(this);
        if (idx >= 1) {
            return _parent->getNode(idx - 1).data();
        } else {
            return _parent;
        }
    }
    return nullptr;
}

SkillScriptNode* SkillScriptNode::getNeibour()
{
    if (_parent != nullptr) {
        int idx = getNodeIdx(this);
        if (idx >= 1) {
            return _parent->getNode(idx - 1).data();
        } else if (idx >= 0 && idx < _parent->getNodesLength() - 1) {
            return _parent->getNode(idx + 1).data();
        } else {
            return _parent;
        }
    }
    return nullptr;
}

SkillScriptNode* SkillScriptNode::getPrevBrother()
{
    if (_parent != nullptr) {
        int idx = getNodeIdx(this);
        if (idx >= 1) {
            return _parent->getNode(idx - 1).data();
        }
    }
    return nullptr;
}

void SkillScriptNode::setSelected(bool val)
{
    _isSelected = val;
    if (_treeItem != nullptr) {
        if (_isSelected) {
            _treeItem->setBackground(0, QBrush(QColor(SKILLNODE_SELECTED_BACKGROUND_COLOR)));
        } else {
            SkillSpecNodePtr specRecord = getSpecNode(_id);
            if (specRecord != nullptr && specRecord->getNodeType() == SKILLSPEC_TOOL_NODE_TYPE) {
                _treeItem->setBackground(0, QBrush(QColor(SKILLNODE_TOOL_BACKGROUND_COLOR)));
            } else {
                _treeItem->setBackground(0, QBrush(QColor(SKILLNODE_DEFAULT_BACKGROUND_COLOR)));
            }
        }
    }
}

SkillScriptNode* SkillScriptNode::getSelectedNode()
{
    if (this->isSelected()) {
        return this;
    }
    QList<SkillScriptNode*> list;
    if (this->getSelectedNodes(list)) {
        return list.front();
    } else {
        return nullptr;
    }
}

bool SkillScriptNode::getSelectedNodes(QList<SkillScriptNode*>& list)
{
    if (this->isSelected()) {
        list.append(this);
    }

    const SkillScriptNodePtrList& nodes = this->getNodes();
    for (int idx = 0; idx < nodes.length(); idx++) {
        SkillScriptNodePtr ptr = nodes.at(idx);
        if (ptr != nullptr) {
            ptr->getSelectedNodes(list);
        }
    }
    return list.length() > 0;
}

void SkillScriptNode::setSelectedNodes(QList<SkillScriptNode*>& list)
{
    for (int idx = 0; idx < list.length(); idx++) {
        SkillScriptNode* ptr = list.at(idx);
        if (ptr != nullptr) {
            ptr->setSelected(true);
        }
    }
}

SkillScriptNodeParamPtr SkillScriptNode::getParam(const QString& name) const
{
    for (int idx = 0; idx < this->_params.length(); idx++) {
        SkillScriptNodeParamPtr ptr = this->_params.at(idx);
        if (ptr != nullptr && ptr->getName() == name) {
            return ptr;
        }
    }
    return SkillScriptNodeParamPtr();
}

void SkillScriptNode::addParam(SkillScriptNodeParamPtr param)
{
    for (int idx = 0; idx < this->_params.length(); idx++) {
        SkillScriptNodeParamPtr ptr = this->_params.at(idx);
        if (ptr != nullptr && ptr->getName() == param->getName()) {
            ptr->clone(*param);
            param->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ADD_PARAM);
            //添加后再支持发送信号
            param->setIsEmit(true);
            return;
        }
    }
    //不存在，直接添加
    _params.push_back(param);
    param->setParent(this);
    param->notify(SkillNotifyReason::R_SKILLSCRIPTNODE_ADD_PARAM);
    //添加后再支持发送信号
    param->setIsEmit(true);
}

bool SkillScriptNode::containParam(const QString& name) const
{
    for (int idx = 0; idx < this->_params.length(); idx++) {
        SkillScriptNodeParamPtr ptr = this->_params.at(idx);
        if (ptr != nullptr && ptr->getName() == name) {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////
SkillScript::SkillScript()
: SkillScriptNode(this), _curFilePath("")
{
    _nodes.clear();
}

bool SkillScript::loadFile(const QString & fileName)
{
    QFile file(fileName);
    if (!file.exists()) {
        qWarning() << "load skill script file not exists, fileName:" << fileName;
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "load skill script file error, fileName:" << fileName;
        return false;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "load skill script file xml error, fileName:" << fileName;
        file.close();
        return false;
    }

    this->_curFilePath = fileName;

    QDomElement rootObj = doc.documentElement();
    this->fromXml(rootObj, true);
    this->loadInfosfromXml(rootObj, true);

    file.close();

    fillBasicNodes();
    emit this->scriptChanged(*this, SkillNotifyReason::R_SKILLSCRIPT_LOAD);
    return true;
}

bool SkillScript::saveFile(const QString & fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    this->_curFilePath = fileName;
    fillBasicNodes();

#ifdef _SAVE_XML_BY_DOM
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement(this->getName());
    doc.appendChild(root);
    this->toXml(doc, root, true);
    this->saveInfosToXml(rootObj);

    doc.save(QTextStream(&file), 4);
#else
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    //nodes
    writer.writeStartElement(this->getName());
    this->toStreamXml(writer, true);
    //infos
    writer.writeStartElement(SKILLSCRIPT_REFINFOS_TAG_NAME);
    this->saveInfosToStreamXml(writer, true);
    writer.writeEndElement();

    writer.writeEndElement();

    writer.writeEndDocument();
    file.close();
#endif // _SAVE_XML_BY_DOM

    file.close();
    emit this->scriptChanged(*this, SkillNotifyReason::R_SKILLSCRIPT_SAVE);
    return true;
}

void SkillScript::clear()
{
    _name = "";
    _id = "";
    _autoId = _INVALID_ID;
    _nodes.clear();
    _params.clear();

    _curFilePath = "";
    _refs.clear();
    _isEmit = false;

    emit this->scriptChanged(*this, SkillNotifyReason::R_SKILLSCRIPT_CLEAR);
}

void SkillScript::setRef(SkillScriptRefInfoPtr ptr)
{
    SkillScriptRefInfoPtr ref = getRef(ptr->getId());
    if (ref != nullptr) {
        ref->clone(ptr);
    }
}

SkillScriptRefInfoPtr SkillScript::getRef(int id)
{
    for (int idx = 0; idx < this->_refs.length(); idx++) {
        SkillScriptRefInfoPtr tdata = _refs.at(idx);
        if (tdata != nullptr && tdata->getId() == id) {
            return tdata;
        }
    }
    return SkillScriptRefInfoPtr();
}

SkillScriptRefInfoPtr SkillScript::getSelectedRef()
{
    for (int idx = 0; idx < this->_refs.length(); idx++) {
        SkillScriptRefInfoPtr tdata = _refs.at(idx);
        if (tdata != nullptr && tdata->isSelected()) {
            return tdata;
        }
    }
    return SkillScriptRefInfoPtr();
}

void SkillScript::unselectAllRef()
{
    for (int idx = 0; idx < this->_refs.length(); idx++) {
        SkillScriptRefInfoPtr tdata = _refs.at(idx);
        if (tdata != nullptr && tdata->isSelected()) {
            tdata->setSelected(false);
        }
    }
}

void SkillScript::fillBasicNodes()
{
    if (_name.isEmpty()) {
        _name = "skill";
        _id = SKILLSCRIPT_SKILL_ID_DEFAULT;

        SkillScriptNodePtr sectionPtr = SkillScriptNodePtr::create(_script);
        sectionPtr->setId(SKILLSCRIPT_ADD_SKILL_SECTION_ID);
        this->addNode(sectionPtr);
    }
}

void SkillScript::fillScriptRefs()
{
    for (int idx = 0; idx < SKILLINST_LOGIC_PARAM_COUNT; idx++) {
        SkillScriptRefInfoPtr nodePtr = SkillScriptRefInfoPtr::create();
        nodePtr->setId(idx);
        nodePtr->setName("info");
        this->_refs.push_back(nodePtr);
    }
}

bool SkillScript::loadInfosfromXml(const QDomElement& curNode, int scriptId)
{
    //添加默认数据，便于后续逻辑访问数据
    fillScriptRefs();
    //解析节点组
    QDomNodeList rootNodes = curNode.toElement().elementsByTagName(SKILLSCRIPT_REFINFOS_TAG_NAME);
    for (int ridx = 0; ridx < rootNodes.length(); ridx++) {
        QDomNode& rootNode = rootNodes.at(ridx);
        QDomNodeList nodeList = rootNode.toElement().elementsByTagName(SKILLSCRIPT_REFINFO_TAG_NAME);
        for (int idx = 0; idx < nodeList.length(); idx++) {
            QDomNode& node = nodeList.at(idx);
            SkillScriptRefInfoPtr nodePtr = SkillScriptRefInfoPtr::create();
            nodePtr->fromXml(node.toElement(), true);
            this->setRef(nodePtr);
        }
    }
    return true;
}

bool SkillScript::saveInfosToXml(QDomDocument& doc, QDomElement& curNode, bool deep)
{
    for (int idx = 0; idx < this->_refs.length(); idx++) {
        SkillScriptRefInfoPtr ptr = this->_refs.at(idx);
        if (ptr != nullptr) {
            QDomElement node = doc.createElement(ptr->getName());
            curNode.appendChild(node);
            ptr->toXml(doc, node, true);
        }
    }
    return true;
}

bool SkillScript::saveInfosToStreamXml(QXmlStreamWriter& writer, bool deep)
{
    for (int idx = 0; idx < this->_refs.length(); idx++) {
        SkillScriptRefInfoPtr ptr = this->_refs.at(idx);
        if (ptr != nullptr && !ptr->getInfo().isEmpty()) {
            writer.writeStartElement(ptr->getName());
            ptr->toStreamXml(writer, true);
            writer.writeEndElement();
        }
    }
    return true;
}

QString formatScriptNodeTitle(const SkillScriptNode& node)
{
    QString result = node._id;

    SkillSpecNodePtr specRecord = getSpecNode(node._id);
    if (specRecord == nullptr) {
        return result;
    }

    if (specRecord->getNodeType() == SKILLSPEC_TOOL_NODE_TYPE) {
        result = "";
        //格式化数据
        QString specFormat = specRecord->getFormat();
        if (specFormat.length() > 0) {
            QStringList specFormatList = specFormat.split(":");
            for (int idx = 0; idx < specFormatList.length(); idx++) {
                QString specArgFormat = specFormatList[idx];
                SkillSpecNodeParamPtr specArg = specRecord->getParam(specArgFormat);
                SkillScriptNodeParamPtr paramPtr = node.getParam(specArgFormat);
                if (specArg != nullptr && paramPtr != nullptr) {
                    if (paramPtr->isModified()) {
                        result += specArg->getTitle() + ":" + paramPtr->getDisplayData() + " ";
                    }
                } else {
                    result += specArgFormat + " ";
                }
            }
        }
    } else {
        //格式化基础描述
        result = QString::fromLocal8Bit("%1").arg(specRecord->getTitle());

        //格式化数据
        QString specFormat = specRecord->getFormat();
        if (specFormat.length() > 0) {
            result += " [";
            QStringList specFormatList = specFormat.split(":");
            for (int idx = 0; idx < specFormatList.length(); idx++) {
                QString specArgFormat = specFormatList[idx];
                SkillSpecNodeParamPtr specArg = specRecord->getParam(specArgFormat);
                SkillScriptNodeParamPtr paramPtr = node.getParam(specArgFormat);
                if (specArg != nullptr && paramPtr != nullptr) {
                    if (paramPtr->isModified()) {
                        result += specArg->getTitle() + ":" + paramPtr->getDisplayData() + " ";
                    }
                } else {
                    result += specArgFormat + " ";
                }
            }
            result += "]";
        }
    }

    return result;
}

QString formatScriptNodeToolTip(const SkillScriptNode& node)
{
    SkillSpecNodePtr specRecord = getSpecNode(node._id);
    if (specRecord != nullptr) {
        return specRecord->getDesc();
    }
    return "";
}

void fillScriptNodeParams(SkillScriptNode& node)
{
    SkillSpecNodePtr recordPtr = getSpecNode(node.getId());
    if (recordPtr != nullptr) {
        SkillSpecNode::SpecNodeParamPtrList& paramList = recordPtr->getParams();
        for (int idx = 0; idx < paramList.length(); idx++) {
            SkillSpecNodeParamPtr argPtr = paramList.at(idx);
            if (!node.containParam(argPtr->getName()) && argPtr != nullptr) {
                if (argPtr->getType() == "enum.string") {
                    SkillScriptNodeParamPtr ptr = SkillScriptNodeParamPtr::create();
                    ptr->setName(argPtr->getName());
                    QString dftVal = argPtr->getDefault();
                    ptr->setAsString(dftVal.length() >= 1 ? dftVal.right(dftVal.length() - 1) : dftVal);
                    node.addParam(ptr);
                } else {
                    SkillScriptNodeParamPtr ptr = SkillScriptNodeParamPtr::create();
                    ptr->setName(argPtr->getName());
                    ptr->setAsNumber(argPtr->getDefault().toDouble());
                    node.addParam(ptr);
                }
            }
        }
    }
}

void setNodeParamValue(SkillScriptNode& node, const QString& name, double num)
{
    SkillScriptNodeParamPtr paramPtr = node.getParam(name);
    if (paramPtr != nullptr) {
        paramPtr->setAsNumber<double>(num);
    }
}

bool node2Xml(SkillScriptNode& node, QDomDocument& doc)
{
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement(node.getName());
    doc.appendChild(root);
    return node.toXml(doc, root, true);
}

bool xml2Node(QDomDocument& doc, SkillScriptNode& node)
{
    QDomElement rootObj = doc.documentElement();
    return node.fromXml(rootObj, true);
}

bool xmlTxt2Node(const QString& content, SkillScriptNode& node)
{
    QDomDocument doc;
    if (!doc.setContent(content)) {
        return false;
    }
    return xml2Node(doc, node);
}

SkillScriptNodePtr asNodePtr(SkillScriptNode* node)
{
    SkillScriptNode* parent = node->getParent();
    if (parent != nullptr) {
        const SkillScriptNodePtrList& nodes = parent->getNodes();
        for (int idx = 0; idx < nodes.length(); idx++) {
            SkillScriptNodePtr ptr = nodes.at(idx);
            if (ptr.data() == node) {
                return ptr;
            }
        }
    }
    return SkillScriptNodePtr();
}

int getNodeIdx(SkillScriptNode* node)
{
    SkillScriptNode* parent = node->getParent();
    if (parent != nullptr) {
        const SkillScriptNodePtrList& nodes = parent->getNodes();
        for (int idx = 0; idx < nodes.length(); idx++) {
            SkillScriptNodePtr ptr = nodes.at(idx);
            if (ptr.data() == node) {
                return idx;
            }
        }
    }
    return -1;
}

int getNodeCls(const SkillScriptNode& node)
{
    SkillScriptNode* parent = node.getParent();
    if (parent != nullptr && parent != &node) {
        return getNodeCls(*parent) + 1;
    }
    return 0;
}

int getNodePublicByParents(const SkillScriptNode& node)
{
    int selfPublic = 0xFFFF;// getSpecNodePublic(node.getId());
    const SkillScriptNode* curNode = &node;
    while (curNode != nullptr) {
        const SkillScriptNode* parent = curNode->getParent();
        if (parent == nullptr || parent == curNode) {
            break;
        }
        selfPublic &= getSpecNodePublic(parent->getId());
        curNode = parent;
    }
    return selfPublic;
}

bool checkNodeClsLimit(const SkillScriptNode& node, int targetLevel)
{
    SkillSpecLimitPtr limit = getSpecNodeLimit(node.getId());
    if (limit != nullptr) {
        if (limit->getMinCls() != _INVALID_ID
            && targetLevel < limit->getMinCls()) {
            return false;
        }
        if (limit->getMaxCls() != _INVALID_ID
            && targetLevel > limit->getMaxCls()) {
            return false;
        }
    }
    return true;
}

void applyScriptRefData(int refIdx, double num, SkillScriptNode* parent)
{
    if (parent == nullptr) {
        return;
    }

    const SkillScriptNodePtrList& nodes = parent->getNodes();
    for (int idx = 0; idx < nodes.length(); idx++) {
        SkillScriptNodePtr node = nodes.at(idx);
        if (node != nullptr) {
            const SkillScriptNodeParamPtrList& paramList = node->getParams();
            for (int pidx = 0; pidx < paramList.length(); pidx++) {
                SkillScriptNodeParamPtr paramPtr = paramList.at(pidx);
                if (paramPtr != nullptr && paramPtr->isRef() && paramPtr->getRef() == refIdx) {
                    paramPtr->setAsRefNum(num);
                }
            }
            //递归调用
            applyScriptRefData(refIdx, num, node.data());
        }
    }
}

bool serializeNode(SkillScriptNodePtr nodePtr, SkillScriptNodePtr nextNodePtr, QList<SkillScriptNodePtr>& list)
{
    if (nodePtr->getName() == "cond") {
        return true;
    }
    SkillSpecNodePtr specRecord = getSpecNode(nodePtr->getId());
    if (specRecord != nullptr && specRecord->getNodeType() == SKILLSPEC_TOOL_NODE_TYPE) {
        return true;
    }

    const SkillScriptNodePtrList& childNodes = nodePtr->getNodes();
    SkillScriptNodePtr childNextNodePtr = nextNodePtr;

    if (childNodes.length() > 0 && nodePtr->getId() == "loop") {
        //判断为true时跳转到循环起始点
        SkillScriptNodePtr jumpNode = createJumpNode(childNodes.first(), JumpCondType::TYPE_LOOP_TRUE);
        list.push_back(jumpNode);
        //更新loop值
        SkillScriptNodePtr opNode = createOpState(OpStateType::OP_LOOP);
        list.push_back(opNode);
    }

    for (int idx = childNodes.length() - 1; idx >= 0; idx--) {
        SkillScriptNodePtr childNode = childNodes.at(idx);
        if (childNode != nullptr) {
            if (nodePtr->getId() == "select") {
                //无条件跳转到结束点
                SkillScriptNodePtr jumpNode = createJumpNode(nextNodePtr, JumpCondType::TYPE_NONE);
                list.push_back(jumpNode);
            }
            serializeNode(childNode, childNextNodePtr, list);
            childNextNodePtr = childNode;
        }
    }

    if (nodePtr->getId() == "if") {
        //判断为false时执行跳转
        SkillScriptNodePtr jumpNode = createJumpNode(nextNodePtr, JumpCondType::TYPE_IF_FALSE);
        list.push_back(jumpNode);
        //增加测试节点
        SkillScriptNodePtr testNode = createIfNode(nodePtr);
        list.push_back(testNode);
    } else if (nodePtr->getId() == "loop") {
        //判断为false时执行跳转
        SkillScriptNodePtr jumpNode = createJumpNode(nextNodePtr, JumpCondType::TYPE_LOOP_FALSE);
        list.push_back(jumpNode);
        list.push_back(nodePtr);
    } else {
        list.push_back(nodePtr);
    }
    return true;
}

SkillScriptNodePtr createOpState(int opType)
{
    SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
    nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_OPSTATE_ID);
    fillScriptNodeParams(*nodePtr);
    SkillScriptNodeParamPtr condParam = nodePtr->getParam("state");
    if (condParam != nullptr) {
        condParam->setAsNumber(opType);
    }
    return nodePtr;
}

SkillScriptNodePtr createIfNode(SkillScriptNodePtr ifNodePtr)
{
    SkillScriptNodePtr nodePtr = ifNodePtr;
    fillScriptNodeParams(*nodePtr);
    const SkillScriptNodePtrList& nodes = ifNodePtr->getNodes();
    int condIdx = 0;
    for (int idx = 0; idx < nodes.length(); idx++) {
        SkillScriptNodePtr childNode = nodes.at(idx);
        if (childNode != nullptr && childNode->getName() == "cond") {
            //condtype
            setNodeParamValue(*nodePtr, QString("condtype%0").arg(condIdx), getSpecNodeCode(childNode->getId()));
            //condlink
            SkillScriptNodeParamPtr condLinkParam = childNode->getParam("link");
            if (condLinkParam != nullptr) {
                setNodeParamValue(*nodePtr, QString("condlink%0").arg(condIdx), condLinkParam->getNumber<double>());
            }
            //condvalue
            const SkillScriptNodeParamPtrList& valueParams = childNode->getParams();
            int condValueIdx = 0;
            for (int jdx = 1; jdx < valueParams.length(); jdx++) {
                SkillScriptNodeParamPtr valueParamPtr = valueParams.at(jdx);
                if (valueParamPtr != nullptr) {
                    setNodeParamValue(*nodePtr, QString("condvalue%0_%1").arg(condIdx).arg(condValueIdx), valueParamPtr->getNumber<double>());
                    condValueIdx++;
                }
            }
            condIdx++;
        }
    }
    return nodePtr;
}

SkillScriptNodePtr createJumpNode(SkillScriptNodePtr jumpNodePtr, int condState)
{
    SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
    nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_JUMP_ID);
    nodePtr->setJump(jumpNodePtr);
    fillScriptNodeParams(*nodePtr);
    SkillScriptNodeParamPtr condParam = nodePtr->getParam("cond");
    if (condParam != nullptr) {
        condParam->setAsNumber(condState);
    }
    return nodePtr;
}

SkillScriptNodePtr createEndNode()
{
    SkillScriptNodePtr nodePtr = SkillScriptNodePtr::create(gSkillScript);
    nodePtr->setId(SKILLSCRIPT_ADD_SKILL_NODE_END_ID);
    fillScriptNodeParams(*nodePtr);
    return nodePtr;
}

void linkNode(SkillScriptNodePtr nodePtr)
{
    if (nodePtr->getId() == "jump") {
        SkillScriptNodeParamPtr addrParam = nodePtr->getParam("addr");
        if (addrParam != nullptr && nodePtr->getJump() != nullptr) {
            addrParam->setAsNumber(nodePtr->getJump()->getAutoId());
        }
    }
}

