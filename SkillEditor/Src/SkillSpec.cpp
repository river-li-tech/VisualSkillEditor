#include "stdafx.h"
#include "SkillSpec.h"

//////////////////////////////////////////////////////////////////////////
SkillSpecEnumValue::SkillSpecEnumValue()
: _name(""), _data(""), _value(_INVALID_ID)
{
    for (int idx = 0; idx < C_INT_ARG_COUNT; idx++) {
        _intArgs[idx] = _INVALID_ID;
    }
    for (int idx = 0; idx < C_STR_ARG_COUNT; idx++) {
        _strArgs[idx] = "";
    }
}

bool SkillSpecEnumValue::fromXml(const QDomElement& curNode, int instId)
{
    _name = curNode.attribute("name", _name);
    _data = curNode.attribute("data", _data);

    for (int idx = 1; idx <= C_INT_ARG_COUNT; idx++) {
        _intArgs[idx - 1] = curNode.attribute(QString("intarg%1").arg(idx), "-1").toInt();
    }
    for (int idx = 1; idx <= C_STR_ARG_COUNT; idx++) {
        _strArgs[idx - 1] = curNode.attribute(QString("strarg%1").arg(idx), "");
    }
    if (curNode.text() != "") {
        _value = curNode.text().toInt();
    }
    return true;
}

int SkillSpecEnumValue::getIntArg(int idx) const
{
    if (idx > 0 && idx <= C_INT_ARG_COUNT) {
        return _intArgs[idx - 1];
    }
    return _INVALID_ID;
}

QString SkillSpecEnumValue::getStrArg(int idx) const
{
    if (idx > 0 && idx <= C_STR_ARG_COUNT) {
        return _strArgs[idx - 1];
    }
    return "";
}

//////////////////////////////////////////////////////////////////////////
SkillSpecEnum::SkillSpecEnum()
: _id(""), _isCheck(false)
{
    _values.clear();
}

bool SkillSpecEnum::fromXml(const QDomElement& curNode, int instId)
{
    _id = curNode.attribute("id", _id).toLower();
    if (curNode.hasAttribute("ischeck")) {
        _isCheck = curNode.attribute("ischeck", "0").toLower() == "1";
    }

    QDomNodeList nodes = curNode.childNodes();
    if (nodes.length() > 0) {
        for (int idx = 0; idx < nodes.length(); idx++) {
            QDomElement& node = nodes.at(idx).toElement();
            SkillSpecEnumValuePtr nodePtr = SkillSpecEnumValuePtr::create();
            nodePtr->fromXml(node.toElement(), true);
            this->_values.push_back(nodePtr);
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
SkillSpecLimit::SkillSpecLimit()
: _mincls(_INVALID_ID), _maxcls(_INVALID_ID), _desc("")
{
}

bool SkillSpecLimit::fromXml(const QDomElement& curNode, int instId)
{
    _mincls = curNode.attribute("mincls", "-1").toInt();
    _maxcls = curNode.attribute("maxcls", "-1").toInt();
    _desc = curNode.attribute("desc", _desc);
    return true;
}

void SkillSpecLimit::mergeLimit(const SkillSpecLimit& limit)
{
    if (limit._mincls != _INVALID_ID) {
        this->_mincls = limit._mincls;
    }
    if (limit._maxcls != _INVALID_ID) {
        this->_maxcls = limit._maxcls;
    }
    if (!limit._desc.isEmpty()) {
        this->_desc = limit._desc;
    }
}

//////////////////////////////////////////////////////////////////////////
SkillSpecNodeParam::SkillSpecNodeParam()
: _name("NoName"), _title("NoTitle"), _desc(""), _type(""), _default(""),
_min(""), _max(""), _isNeeded(false)
{
}

bool SkillSpecNodeParam::fromXml(const QDomElement& curNode, int instId)
{
    _name = curNode.nodeName();
    _title = curNode.attribute("title", _title);
    _desc = curNode.attribute("desc", _title);
    if (curNode.hasAttribute("type")) {
        _type = curNode.attribute("type", _type).toLower();
    }
    if (curNode.hasAttribute("default")) {
        _default = curNode.attribute("default", _default).toLower();
    }
    if (curNode.hasAttribute("min")) {
        _min = curNode.attribute("min", _min).toLower();
    }
    if (curNode.hasAttribute("max")) {
        _max = curNode.attribute("max", _max).toLower();
    }
    if (curNode.hasAttribute("isneed")) {
        _isNeeded = curNode.attribute("isneed", "0") == "1";
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
SkillSpecNode::SkillSpecNode()
: _id(""), _name(""), _title(""), _desc(""), _format(""), _nodeType(_INVALID_ID),
_code(_INVALID_ID), _public(_INVALID_ID), _limit(SkillSpecLimitPtr::create())
{
    _params.clear();
}

bool SkillSpecNode::fromXml(const QDomElement& curNode, int instId)
{
    _name = curNode.nodeName();
    _id = curNode.attribute("id", _id).toLower();
    _title = curNode.attribute("title", "Miss Title");
    _desc = curNode.attribute("desc", _title);
    _format = curNode.attribute("format", _format).toLower();
    _nodeType = curNode.attribute("nodetype", "-1").toInt();
    _code = curNode.attribute("code", "-1").toInt();
    _public = curNode.attribute("public", "-1").toInt();

    QDomNodeList nodes = curNode.childNodes();
    if (nodes.length() > 0) {
        for (int idx = 0; idx < nodes.length(); idx++) {
            QDomElement& node = nodes.at(idx).toElement();
            SkillSpecNodeParamPtr nodePtr = SkillSpecNodeParamPtr::create();
            nodePtr->fromXml(node.toElement(), true);
            this->_params.push_back(nodePtr);
        }
    }
    return true;
}
SkillSpecNodeParamPtr SkillSpecNode::getParam(const QString& name) const
{
    for (int idx = 0; idx < _params.length(); idx++) {
        if (_params[idx]->getName() == name) {
            return _params[idx];
        }
    }
    return SkillSpecNodeParamPtr();
}

//////////////////////////////////////////////////////////////////////////
SkillSpec::SkillSpec()
: _curFilePath("")
{
    _nodes.clear();
    _enums.clear();
}

bool SkillSpec::load(const QString & fileName)
{
    QFile file(fileName);
    if (!file.exists()) {
        qWarning() << "load skill spec file not exists, fileName:" << fileName;
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "load skill spec file error, fileName:" << fileName;
        return false;
    }

    this->_curFilePath = fileName;
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "load skill spec file xml error, fileName:" << fileName;
        file.close();
        return false;
    }
    QDomElement rootObj = doc.documentElement();
    this->fromXml(rootObj, true);

    file.close();
    return true;
}

void SkillSpec::clear()
{
    _curFilePath = "";
    _nodes.clear();
    _enums.clear();
}

bool SkillSpec::fromXml(const QDomElement& curNode, int instId)
{
    //enums
    QDomNodeList enumsNode = curNode.elementsByTagName("Enums");
    if (enumsNode.length() > 0) {
        for (int idx = 0; idx < enumsNode.length(); idx++) {
            QDomNode& enums = enumsNode.at(idx);
            QDomNodeList enumList = enums.toElement().elementsByTagName("enum");
            if (enumList.length() > 0) {
                for (int idx2 = 0; idx2 < enumList.length(); idx2++) {
                    QDomNode& node = enumList.at(idx2);
                    SkillSpecEnumPtr nodePtr = SkillSpecEnumPtr::create();
                    nodePtr->fromXml(node.toElement(), true);
                    this->_enums.insert(nodePtr->getId(), nodePtr);
                }
            }
        }
    }
    //skills
    QDomNodeList skillsNode = curNode.elementsByTagName("Skills");
    if (skillsNode.length() > 0) {
        for (int idx = 0; idx < skillsNode.length(); idx++) {
            QDomNode& skills = skillsNode.at(idx);
            parseNodes(skills, "skill");
        }
    }
    //sections
    QDomNodeList sectionsNode = curNode.elementsByTagName("Sections");
    if (sectionsNode.length() > 0) {
        for (int idx = 0; idx < sectionsNode.length(); idx++) {
            QDomNode& sections = sectionsNode.at(idx);
            parseNodes(sections, "section");
        }
    }
    //conds
    QDomNodeList condsNode = curNode.elementsByTagName("Conds");
    if (condsNode.length() > 0) {
        for (int idx = 0; idx < condsNode.length(); idx++) {
            QDomNode& conds = condsNode.at(idx);
            parseNodes(conds, "cond");
        }
    }
    //actions
    QDomNodeList actionsNode = curNode.elementsByTagName("Actions");
    if (actionsNode.length() > 0) {
        for (int idx = 0; idx < actionsNode.length(); idx++) {
            QDomNode& actions = actionsNode.at(idx);
            parseNodes(actions, "action");
        }
    }
    //排序便于在下拉列表中选择
    return true;
}

SkillSpecNodePtr SkillSpec::getNode(const QString& id) const
{
    for (int idx = 0; idx < _nodes.length(); idx++) {
        if (_nodes[idx]->getId() == id) {
            return _nodes[idx];
        }
    }
    return SkillSpecNodePtr();
}

SkillSpecEnumPtr SkillSpec::getEnum(const QString& id) const
{
    if (_enums.contains(id)) {
        return _enums[id];
    }
    return SkillSpecEnumPtr();
}

void SkillSpec::parseNodes(const QDomNode& curNode, const QString& tagName)
{
    //解析限制描述组(公共的)
    SkillSpecLimitPtr limit = SkillSpecLimitPtr::create();
    QDomNodeList limitList = curNode.toElement().elementsByTagName("limit");
    if (limitList.length() > 0) {
        for (int idx2 = 0; idx2 < limitList.length(); idx2++) {
            QDomNode& node = limitList.at(idx2);
            SkillSpecLimitPtr nodePtr = SkillSpecLimitPtr::create();
            nodePtr->fromXml(node.toElement(), true);
            limit->mergeLimit(*nodePtr);
        }
    }
    //解析节点组
    QDomNodeList nodeList = curNode.toElement().elementsByTagName(tagName);
    if (nodeList.length() > 0) {
        for (int idx2 = 0; idx2 < nodeList.length(); idx2++) {
            QDomNode& node = nodeList.at(idx2);
            SkillSpecNodePtr nodePtr = SkillSpecNodePtr::create();
            nodePtr->fromXml(node.toElement(), true);
            nodePtr->getLimit()->mergeLimit(*limit);
            this->_nodes.push_back(nodePtr);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
SkillSpecNodePtr getSpecNode(const QString& nodeId)
{
    if (gSkillSpec == nullptr) {
        return SkillSpecNodePtr();
    }
    return gSkillSpec->getNode(nodeId);
}

SkillSpecNodeParamPtr getSpecNodeParam(const QString& nodeId, const QString& paramName)
{
    SkillSpecNodePtr pnode = getSpecNode(nodeId);
    if (pnode == nullptr) {
        return SkillSpecNodeParamPtr();
    }
    return pnode->getParam(paramName);
}

SkillSpecEnumPtr getSpecEnum(const QString& enumId)
{
    if (gSkillSpec == nullptr) {
        return SkillSpecEnumPtr();
    }
    return gSkillSpec->getEnum(enumId);
}

SkillSpecLimitPtr getSpecNodeLimit(const QString& nodeId)
{
    SkillSpecNodePtr specNode = getSpecNode(nodeId);
    if (specNode != nullptr) {
        return specNode->getLimit();
    }
    return SkillSpecLimitPtr();
}

QString getSpecNodeName(const QString& id)
{
    SkillSpecNodePtr specRecord = getSpecNode(id);
    if (specRecord != nullptr) {
        return specRecord->getName();
    }
    return "unknown";
}

int getSpecNodeType(const QString& id)
{
    SkillSpecNodePtr specRecord = getSpecNode(id);
    if (specRecord != nullptr) {
        return specRecord->getNodeType();
    }
    return -1;
}

int getSpecNodeCode(const QString& id)
{
    SkillSpecNodePtr specRecord = getSpecNode(id);
    if (specRecord != nullptr) {
        return specRecord->getCode();
    }
    return -1;
}

int getSpecNodePublic(const QString& id)
{
    SkillSpecNodePtr specRecord = getSpecNode(id);
    if (specRecord != nullptr) {
        return specRecord->getPublicType();
    }
    return -1;
}

bool compareNodesLessThan(SkillSpecNodePtr lhs, SkillSpecNodePtr rhs)
{
    return lhs->getTitle() < rhs->getTitle();
}

QString getIconName(const QString& nodeId)
{
    SkillSpecNodePtr node_ptr = getSpecNode(nodeId);
    SkillSpecEnumPtr enum_ptr = getSpecEnum(SKILLPARAM_ENUM_NODETYPE_NAME);
    if (node_ptr != nullptr && enum_ptr != nullptr) {
        SkillSpecEnumValuePtr value_ptr = enum_ptr->getValue(node_ptr->getNodeType());
        if (value_ptr != nullptr) {
            return value_ptr->getData();
        }
    }
    return ":/icons/Icons/node.png";
}

void getSpecNodeListByType(QList<SkillSpecNodePtr>& list, int nodeType, int publicType)
{
    //提取到列表中
    int nIdx = 0;
    QList<SkillSpecNodePtr>::iterator iter = gSkillSpec->nodesBegin();
    while (iter != gSkillSpec->nodesEnd()) {
        SkillSpecNodePtr nodePtr = *iter;
        if (nodePtr != nullptr 
            && nodePtr->getNodeType() == nodeType
            && (nodePtr->getPublicType() & publicType) != 0) {
            list.append(nodePtr);
            nIdx++;
        }
        iter++;
    }

    //按名称排序
    //qSort(sortList.begin(), sortList.end(), compareNodesLessThan);
}

int getSpecActionCode(const QString& nodeId)
{
    SkillSpecNodePtr nodePtr = getSpecNode(nodeId);
    if (nodePtr)  {
        return nodePtr->getCode();
    }
    return _INVALID_ID;
}