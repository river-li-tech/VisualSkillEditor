/************************************************************************/
/*
@file:SkillScript.h
@author:LRiver.2019.10.25
@desc:载入技能xml文件
*/
/************************************************************************/

#pragma once
#include "stdafx.h"
#include "define.h"

class SkillScriptNodeParam;
class SkillScriptNode;
class SkillScript;
class SkillScriptRefInfo;

using SkillScriptNodeParamPtr = QSharedPointer<SkillScriptNodeParam>;
using SkillScriptNodeParamPtrList = QList<SkillScriptNodeParamPtr>;
using SkillScriptNodePtr = QSharedPointer<SkillScriptNode>;
using SkillScriptNodePtrList = QList<SkillScriptNodePtr>;
using SkillScriptRefInfoPtr = QSharedPointer<SkillScriptRefInfo>;

//////////////////////////////////////////////////////////////////////////
struct SkillScriptNodeUserData : public QObjectUserData
{
    SkillScriptNodeUserData() : _skillNode(nullptr) {}
    SkillScriptNode* _skillNode;
};
Q_DECLARE_METATYPE(SkillScriptNodeUserData);

class SkillScriptRefInfo : public QObject
{
    Q_OBJECT
public:
    SkillScriptRefInfo();
    bool fromXml(const QDomElement& curNode, int scriptId);
    bool toXml(QDomDocument& doc, QDomElement& curNode, bool deep);
    bool toStreamXml(QXmlStreamWriter& writer, bool deep);
    void clone(SkillScriptRefInfoPtr ptr);

public:
    QString getName() const { return _name; }
    void setName(const QString& name) { _name = name; }

    int getId() const { return _id; }
    void setId(int id) { _id = id; }

    QString getInfo() const { return _info; };
    void setInfo(const QString str) { _info = str; };

    bool isSelected() const { return _isSelected; }
    void setSelected(bool val) { _isSelected = val; }

private:
    QString             _name;
    int                 _id;
    QString             _info;

    bool                _isSelected;
};

//////////////////////////////////////////////////////////////////////////
class SkillScriptNodeParam : public QObject
{
    Q_OBJECT
public:
    enum
    {
        INVALID,
        NUMBER,
        STRING,
        REFERENCE,
    };
public:
    SkillScriptNodeParam();
    bool fromXml(const QDomAttr& curNode, int scriptId);
    bool toXml(QDomDocument& doc, QDomElement& curNode, bool deep);
    bool toStreamXml(QXmlStreamWriter& writer, bool deep);
    void notify(SkillNotifyReason reason);
    void clone(const SkillScriptNodeParam& param);

public:
    bool isRef() const { return _type == SkillScriptNodeParam::REFERENCE; }
    bool isString() const { return _type == SkillScriptNodeParam::STRING; }
    bool isNumber() const { return _type == SkillScriptNodeParam::NUMBER; }

public:
    int getType() const { return _type; }

    QString getName() const { return _name; }
    void setName(const QString& name);

    QString getString() const { return _string; }
    void setAsString(const QString& str);

    template<typename T>
    T getNumber() const { return static_cast<T>(_number); }
    template<typename T>
    void setAsNumber(T num)
    {
        double tNum = static_cast<double>(num);
        if (_type != SkillScriptNodeParam::NUMBER
            || _ref != 0
            || _string != ""
            || _number != tNum) {
            _type = SkillScriptNodeParam::NUMBER;
            //setInstDataParamByIdx(_ref, -1);
            _ref = 0;
            _string = "";
            _number = static_cast<double>(num);
            this->notify(SkillNotifyReason::R_SKILLSCRIPTNODEPARAM_PARAM_NUMBER);
        }
    }

    int getRef() const { return _ref; }
    void setAsRefNum(double num);
    void setAsRefIdx(int refIdx);

    void setIsEmit(bool isEmit) { _isEmit = isEmit; }
    bool isEmit() { return _isEmit; }

    SkillScriptNode* getParent() const { return _parent; }
    void setParent(SkillScriptNode* node) { _parent = node; }

    QString getDisplayData() const;
    QString getParentNodeId() const;

public:
    bool isRefTxt(const QString& val);
    bool isStringTxt(const QString& val);
    bool isModified() const;

private:
    QString             _name;
    int                 _type;
    double              _number;
    QString             _string;
    int                 _ref;

    SkillScriptNode*    _parent;
    bool                _isEmit;
};

//////////////////////////////////////////////////////////////////////////
class SkillScriptNode : public QObject
{
    Q_OBJECT

    friend QString formatScriptNodeTitle(const SkillScriptNode& node);
    friend QString formatScriptNodeToolTip(const SkillScriptNode& node);

public:
    SkillScriptNode(SkillScript *script);
    ~SkillScriptNode();

public:
    bool fromXml(const QDomElement& curNode, int scriptId);
    bool toXml(QDomDocument& doc, QDomElement& curNode, bool deep);
    bool toStreamXml(QXmlStreamWriter& writer, bool deep);
    bool toTree(QTreeWidgetItem* parent) const;
    void updateTree();
    void notify(SkillNotifyReason reason);

public:
    QString getName() const { return _name; }

    QString getId() const { return _id; }
    void setId(const QString& id);

    int getAutoId() const { return _autoId; }
    void setAutoId(int autoId) { _autoId = autoId; }

    void setInfo(const QString& val) { _info = val; }
    QString getInfo() const { return _info; }

    const SkillScriptNodeParamPtrList& getParams() const { return _params; }
    SkillScriptNodeParamPtr getParam(const QString& name) const;
    void addParam(SkillScriptNodeParamPtr param);
    bool containParam(const QString& name) const;

public:
    SkillScriptNodePtr getNode(int idx);
    SkillScriptNodePtr getChildNode(const QString& nodeId);
    const SkillScriptNodePtrList& getNodes() const { return _nodes; }
    int getNodesLength() const { return _nodes.length(); }

    SkillScriptNode* getNextNeibour();
    SkillScriptNode* getPrevNeibour();
    SkillScriptNode* getNeibour();
    SkillScriptNode* getPrevBrother();

public:
    void addNode(SkillScriptNodePtr node, int idx = -1);
    void removeNode(SkillScriptNode* node);
    void moveNode(SkillScriptNode* node, bool up);

public:
    void setIsEmit(bool isEmit) { _isEmit = isEmit; }
    bool isEmit() { return _isEmit; }

    SkillScriptNode* getParent() const { return _parent; }
    void setParent(SkillScriptNode* node) { _parent = node; }

    SkillScript* getScript() const { return _script; }
    QTreeWidgetItem * getTreeItem() const { return _treeItem; }
    bool isInvalid() { return _isInValid; }

    bool isExpand() const { return _isExpand; }
    void setExpand(bool val) { _isExpand = val; }
    bool isSelected() const { return _isSelected; }
    void setSelected(bool val);

    SkillScriptNodePtr getJump() const { return _jump; }
    void setJump(SkillScriptNodePtr jump) { _jump = jump; }

public:
    SkillScriptNode* getSelectedNode();
    bool getSelectedNodes(QList<SkillScriptNode*>& list);
    void setSelectedNodes(QList<SkillScriptNode*>& list);

protected:
    QString                         _name;
    QString                         _id;
    int                             _autoId;
    SkillScriptNodePtrList          _nodes;
    SkillScriptNodeParamPtrList     _params;
    QString                         _info;

    SkillScript *                   _script;
    SkillScriptNode *               _parent;
    bool                            _isEmit;
    mutable QTreeWidgetItem *       _treeItem;
    bool                            _isInValid;
    bool                            _isExpand;
    bool                            _isSelected;
    SkillScriptNodePtr              _jump;
};

//////////////////////////////////////////////////////////////////////////
class SkillScript : public SkillScriptNode
{
    Q_OBJECT
public:
    SkillScript();
    void clear();
    bool loadFile(const QString & fileName);
    bool saveFile(const QString & fileName);

public:
    QString getFilePath() const { return this->_curFilePath; }
    QString getFileName() const { return QFileInfo(this->_curFilePath).fileName(); }
    QString getRelFileName(QString dir) const { return QDir(dir).relativeFilePath(getFilePath()); }
    QString getFileSuffix() const { return QFileInfo(this->_curFilePath).suffix(); }
    QString getFileDir() const { return QFileInfo(this->_curFilePath).absolutePath(); }

signals:
    void scriptChanged(const SkillScript& script, SkillNotifyReason reason);
    void nodeChanged(const SkillScriptNode& node, SkillNotifyReason reason);
    void paramChanged(const SkillScriptNodeParam& param, SkillNotifyReason reason);

public:
    void setRef(SkillScriptRefInfoPtr ptr);
    SkillScriptRefInfoPtr getRef(int id);
    SkillScriptRefInfoPtr getSelectedRef();
    void unselectAllRef();

private:
    void fillBasicNodes();
    void fillScriptRefs();

    bool loadInfosfromXml(const QDomElement& curNode, int scriptId);
    bool saveInfosToXml(QDomDocument& doc, QDomElement& curNode, bool deep);
    bool saveInfosToStreamXml(QXmlStreamWriter& writer, bool deep);

private:
    QString                         _curFilePath;
    QList<SkillScriptRefInfoPtr>    _refs;
};

//////////////////////////////////////////////////////////////////////////
//格式化节点的描述文本
QString formatScriptNodeTitle(const SkillScriptNode& node);
//格式化节点的提示文本
QString formatScriptNodeToolTip(const SkillScriptNode& node);

//填充Node的默认Params
void fillScriptNodeParams(SkillScriptNode& node);
void setNodeParamValue(SkillScriptNode& node, const QString& name, double num);

//将节点保存为XmlDocument
bool node2Xml(SkillScriptNode& node, QDomDocument& doc);
//将XmlDocument解析为SkillNode
bool xml2Node(QDomDocument& doc, SkillScriptNode& node);
//将XmlDocument文本解析为SkillNode
bool xmlTxt2Node(const QString& content, SkillScriptNode& node);

//从裸指针获取智能指针
SkillScriptNodePtr asNodePtr(SkillScriptNode* node);
//获取其在父节点中的序号
int getNodeIdx(SkillScriptNode* node);

//获取节点在树中的层级
int getNodeCls(const SkillScriptNode& node);
//获取节点在树中的开放性
int getNodePublicByParents(const SkillScriptNode& node);
//验证节点层级
bool checkNodeClsLimit(const SkillScriptNode& node, int targetLevel);
//更新索引数据
void applyScriptRefData(int refIdx, double num, SkillScriptNode* parent);

//序列化节点为顺序数组
bool serializeNode(SkillScriptNodePtr nodePtr, SkillScriptNodePtr nextNodePtr, QList<SkillScriptNodePtr>& list);
SkillScriptNodePtr createOpState(int opType);
SkillScriptNodePtr createIfNode(SkillScriptNodePtr ifNodePtr);
SkillScriptNodePtr createJumpNode(SkillScriptNodePtr jumpNodePtr, int condState);
SkillScriptNodePtr createEndNode();
void linkNode(SkillScriptNodePtr nodePtr);
