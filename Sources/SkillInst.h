/************************************************************************/
/*
@file:SkillInst.h
@author:LRiver.2019.10.25
@desc:载入SkillInst.txt文件
---------------------------------------------------------
|   Id  | Desc  | Logic |Param01|Param02|Param03|Param04|           
---------------------------------------------------------
|       |       |       |       |       |       |       |       --SkillInstData
---------------------------------------------------------
|       |       |       |       |       |       |       |       --SkillInstData
---------------------------------------------------------
*/
/************************************************************************/

#pragma once
#include "stdafx.h"
#include "define.h"

///////////////////////////////////////////////////////////////////////////
class SkillInstData : public QObject
{
    Q_OBJECT
public:
    enum DATACOLUMN
    {
        COLUMN_ID,
        COLUMN_DESC,
        COLUMN_ISCLIENTSKILL,
        COLUMN_LOGIC,
    };

public:
    SkillInstData();
    bool load(const QStringList& datas);
    bool save(QStringList& datas);
    void notify(SkillNotifyReason reason);

public:
    int getId() const { return _id; }
    void setId(int val)
    {
        if (val != _id) {
            _id = val;
            this->notify(SkillNotifyReason::R_SKILLINSTDATA_ID);
        }
    }

    const QString& getDesc() const { return _desc; }
    void setDesc(const QString& val)
    {
        if (val != _desc) {
            _desc = val;
            this->notify(SkillNotifyReason::R_SKILLINSTDATA_DESC);
        }
    }

    const QString& getLogicFile() const { return _logicFile; }
    void setLogicFile(const QString& val)
    {
        if (val != _logicFile) {
            _logicFile = val;
            this->notify(SkillNotifyReason::R_SKILLINSTDATA_LOGIC);
        }
    }

    const int getIsClientSkill() const { return _isClientSkill; }
    void setIsClientSkill(int val)
    {
        if (val != _isClientSkill) {
            _isClientSkill = val;
            this->notify(SkillNotifyReason::R_SKILLINSTDATA_ISCLIENTSKILL);
        }
    }

    int getLogicParamCount() const { return SKILLINST_LOGIC_PARAM_COUNT; }
    int getLogicParamByIdx(int idx) const
    {
        if (idx >= 0 && idx < SKILLINST_LOGIC_PARAM_COUNT) {
            return _params[idx];
        }
        return _INVALID_ID;
    }
    void setLogicParamByIdx(int idx, int val)
    {
        if (idx >= 0 && idx < SKILLINST_LOGIC_PARAM_COUNT) {
            if (val != _params[idx]) {
                _params[idx] = val;
                this->notify(SkillNotifyReason::R_SKILLINSTDATA_PARAMS);
            }
        }
    }

public:
    bool isSelected() const { return _isSelected; }
    void setSelected(bool val)
    {
        if (val != _isSelected) {
            _isSelected = val;
            this->notify(SkillNotifyReason::R_SKILLINSTDATA_SELECTION);
        }
    }

    bool getParent() const { return _parent; }
    void setParent(SkillInst* parent) { _parent = parent; }

private:
    int             _id;
    QString         _desc;
    QString         _logicFile;
    int             _isClientSkill;
    int             _params[SKILLINST_LOGIC_PARAM_COUNT];

    bool            _isSelected;
    SkillInst*      _parent;
};
using SkillInstDataPtr = QSharedPointer<SkillInstData>;

///////////////////////////////////////////////////////////////////////////
class SkillInst : public QObject
{
    Q_OBJECT
public:
    SkillInst(QObject *parent);

public:
    void clear();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void notify(SkillNotifyReason reason);
    void notify(SkillInstData& data, SkillNotifyReason reason);

public:
    bool addData(SkillInstDataPtr data);
    void removeData(int id);
    int getMaxId();
    SkillInstDataPtr getData(int id);
    SkillInstDataPtr getCurData();
    const QList<SkillInstDataPtr>& getDatas() const { return _datas; }

public:
    void setFilePath(QString file) { this->_curFilePath = file; }
    QString getFilePath() const { return this->_curFilePath; }
    QString getFileName() const { return QFileInfo(this->_curFilePath).fileName(); }
    QString getFileSuffix() const { return QFileInfo(this->_curFilePath).suffix(); }
    QString getFileDir() const { return QFileInfo(this->_curFilePath).absolutePath(); }

signals:
    void instChanged(const SkillInst& pool, SkillNotifyReason reason);
    void dataChanged(const SkillInstData& data, SkillNotifyReason reason);

private:
    void saveLine(QTextStream& stream, const QStringList& list);

private:
    QStringList                 _headers;
    QStringList                 _types;
    QString                     _info;
    QStringList                 _descs;
    QList<SkillInstDataPtr>     _datas;

    QString                     _curFilePath;
};

///////////////////////////////////////////////////////////////////////////
//获取实例数据
SkillInstDataPtr getInstData(int id);
//获取当前实例数据
SkillInstDataPtr getCurInstData();

//根据索引读取当前SkillInst中的LogicParam的值
double getInstDataParamByIdx(int logicIdx);
//根据索引写入当前SkillInst中LogicParam的值
void setInstDataParamByIdx(int refIdx, int num);
