/************************************************************************/
/*
@file:SkillSpec.h
@author:LRiver.2019.10.25
@desc:载入技能描述文件(Bin/Config/SkillSpec.xml)
<Spec>                                              ---class SkillSpec
<Enums>
<enum id="enum.bool">
<value name="false">0</value>           ---class SkillSpecEnumValue
<value name="true">1</value>            ---class SkillSpecEnumValue
</enum>
</Enums>
<Sections>
<section id="onstart">                      ---class SkillNode
<title desc="段落：开始触发"/>           ---class SkillNodeParam
<desc desc="段落：开始触发"/>            ---class SkillNodeParam
</section>
</Sections>
<Conds>
<cond id="hasimpact">                       ---class SkillNode
<title desc="条件：是否拥有impact"/>     ---class SkillNodeParam
<desc desc="条件：检查角色..."/>         ---class SkillNodeParam
</cond>
</Conds>
<Actions>
<action id="select">                        ---class SkillNode
<title desc="指令：选择分支"/>           ---class SkillNodeParam
<desc desc="指令：用于表示..."/>         ---class SkillNodeParam
</action>
</Actions>
</Spec>
*/
/************************************************************************/

#pragma once
#include "stdafx.h"
#include "define.h"

//////////////////////////////////////////////////////////////////////////
class SkillSpecEnumValue
{
public:
    SkillSpecEnumValue();
    bool fromXml(const QDomElement& curNode, int instId);

public:
    QString getName() const { return _name; }
    int getValue() const { return _value; }
    QString getData() const { return _data; }

    int getIntArg(int idx) const;
    QString getStrArg(int idx) const;

private:
    QString     _name;
    int         _value;
    QString     _data;

    static const int C_INT_ARG_COUNT = 3;
    static const int C_STR_ARG_COUNT = 3;

    int         _intArgs[C_INT_ARG_COUNT];
    QString     _strArgs[C_STR_ARG_COUNT];
};
using SkillSpecEnumValuePtr = QSharedPointer<SkillSpecEnumValue>;

//////////////////////////////////////////////////////////////////////////
class SkillSpecEnum
{
public:
    SkillSpecEnum();
    bool fromXml(const QDomElement& curNode, int instId);

public:
    QString getId() const { return _id; }
    bool isCheck() const { return _isCheck; }
    SkillSpecEnumValuePtr getValue(int value) const
    {
        for (int idx = 0; idx < _values.length(); idx++) {
            if (_values[idx]->getValue() == value) {
                return _values[idx];
            }
        }
        return SkillSpecEnumValuePtr();
    }
    const QList<SkillSpecEnumValuePtr>& getValues() const
    {
        return _values;
    }

private:
    QString                                     _id;
    bool                                        _isCheck;
    QList<SkillSpecEnumValuePtr>                _values;
};
using SkillSpecEnumPtr = QSharedPointer<SkillSpecEnum>;

//////////////////////////////////////////////////////////////////////////
class SkillSpecLimit
{
public:
    SkillSpecLimit();
    bool fromXml(const QDomElement& curNode, int instId);
    void mergeLimit(const SkillSpecLimit& limit);

public:
    int getMinCls() const { return _mincls; }
    int getMaxCls() const { return _maxcls; }
    QString getDesc() const { return _desc; }

private:
    int         _mincls;
    int         _maxcls;
    QString     _desc;
};
using SkillSpecLimitPtr = QSharedPointer<SkillSpecLimit>;

//////////////////////////////////////////////////////////////////////////
class SkillSpecNodeParam
{
public:
    SkillSpecNodeParam();
    bool fromXml(const QDomElement& curNode, int instId);

public:
    QString getName() const { return _name; }
    QString getTitle() const { return _title; }
    QString getDesc() const { return _desc; }
    QString getType() const { return _type; }
    QString getDefault() const { return _default; }
    QString getMin() const { return _min; }
    QString getMax() const { return _max; }
    bool getIsNeed() const { return _isNeeded; }

private:
    QString     _name;
    QString     _title;
    QString     _desc;
    QString     _type;
    QString     _default;
    QString     _min;
    QString     _max;
    bool        _isNeeded;
};
using SkillSpecNodeParamPtr = QSharedPointer<SkillSpecNodeParam>;

//////////////////////////////////////////////////////////////////////////
class SkillSpecNode
{
public:
    using SpecNodeParamPtrList = QList<SkillSpecNodeParamPtr>;

public:
    SkillSpecNode();
    bool fromXml(const QDomElement& curNode, int instId);

public:
    QString getId() const { return _id; }
    QString getName() const { return _name; }
    QString getTitle() const { return _title; }
    QString getDesc() const { return _desc; }
    QString getFormat() const { return _format; }
    int getNodeType() const { return _nodeType; }
    int getPublicType() const { return _public; }
    int getCode() const { return _code; }
    SkillSpecNodeParamPtr getParam(const QString& name) const;
    SpecNodeParamPtrList& getParams() { return _params; }

    SkillSpecLimitPtr getLimit() const { return _limit; }

private:
    QString                 _id;
    QString                 _name;
    QString                 _title;
    QString                 _desc;
    QString                 _format;
    int                     _nodeType;
    int                     _code;
    int                     _public;
    SpecNodeParamPtrList    _params;
    SkillSpecLimitPtr       _limit;
};
using SkillSpecNodePtr = QSharedPointer<SkillSpecNode>;

//////////////////////////////////////////////////////////////////////////
class SkillSpec : public QObject
{
    Q_OBJECT

public:
    using SpecNodeList = QList<SkillSpecNodePtr>;
    using SpecEnumMap = QMap<QString, SkillSpecEnumPtr>;
    using SpecLimitList = QList<SkillSpecLimitPtr>;

public:
    SkillSpec();
    void clear();
    bool load(const QString & fileName);
    bool fromXml(const QDomElement& curNode, int instId);

public:
    QString getFilePath() const { return _curFilePath; }
    SkillSpecNodePtr getNode(const QString& id) const;
    SpecNodeList::iterator nodesBegin() { return _nodes.begin(); }
    SpecNodeList::iterator nodesEnd() { return _nodes.end(); }
    SkillSpecEnumPtr getEnum(const QString& id) const;

private:
    void parseNodes(const QDomNode& node, const QString& tagName);

private:
    QString             _curFilePath;
    SpecNodeList        _nodes;
    SpecEnumMap         _enums;
};

///////////////////////////////////////////////////////////////////////////
//根据id获取节点
SkillSpecNodePtr getSpecNode(const QString& nodeId);
//根据id和参数名获取节点参数
SkillSpecNodeParamPtr getSpecNodeParam(const QString& nodeId, const QString& paramName);
//根据id获取枚举
SkillSpecEnumPtr getSpecEnum(const QString& enumId);
//根据id获取节点
SkillSpecLimitPtr getSpecNodeLimit(const QString& nodeId);
//根据节点id获取其名字
QString getSpecNodeName(const QString& id);
//根据节点id获取其节点类型
int getSpecNodeType(const QString& id);
//根据节点id获取其编码
int getSpecNodeCode(const QString& id);
//根据节点id获取其开放范围
int getSpecNodePublic(const QString& id);
//节点按名称排序器
bool compareNodesLessThan(SkillSpecNodePtr lhs, SkillSpecNodePtr rhs);
//通过enum.nodetype获取icon路径
QString getIconName(const QString& nodeId);
//通过节点类型和开放性获取列表
void getSpecNodeListByType(QList<SkillSpecNodePtr>& list, int nodeType, int publicType);
//获取指令编码值
int getSpecActionCode(const QString& nodeId);