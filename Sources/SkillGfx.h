/************************************************************************/
/*
@file:SkillGfx.h
@author:LRiver.2019.10.25
@desc:载入SkillGfx.txt文件
/************************************************************************/

#pragma once
#include "stdafx.h"
#include "define.h"

///////////////////////////////////////////////////////////////////////////
class SkillGfxData : public QObject
{
    Q_OBJECT
public:
    enum DATACOLUMN
    {
        COLUMN_ID,
        COLUMN_DESC,
        COLUMN_LOGIC,
    };

public:
    SkillGfxData();
    bool load(const QStringList& datas);
    bool save(QStringList& datas);

public:
    int getId() const { return _id; }
    void setId(int val)
    {
        if (val != _id) {
            _id = val;
        }
    }

    const QString& getDesc() const { return _desc; }
    void setDesc(const QString& val)
    {
        if (val != _desc) {
            _desc = val;
        }
    }

    const QString& getName() const { return _name; }
    void setName(const QString& val)
    {
        if (val != _desc) {
            _name = val;
        }
    }

    int getInstId() const { return _instId; }
    void setInstId(int val)
    {
        if (val != _id) {
            _instId = val;
        }
    }

    int getActionId() const { return _actionId; }
    void setActionId(int val)
    {
        if (val != _id) {
            _actionId = val;
        }
    }

    int getParamCount() const { return SKILLGFX_LOGIC_PARAM_COUNT; }
    int getParamByIdx(int idx) const
    {
        if (idx >= 0 && idx < SKILLGFX_LOGIC_PARAM_COUNT) {
            return _params[idx];
        }
        return _INVALID_ID;
    }
    void setParamByIdx(int idx, int val)
    {
        if (idx >= 0 && idx < SKILLGFX_LOGIC_PARAM_COUNT) {
            if (val != _params[idx]) {
                _params[idx] = val;
            }
        }
    }

    int getIsRefCount() const { return SKILLGFX_LOGIC_PARAM_COUNT; }
    int getIsRefByIdx(int idx) const
    {
        if (idx >= 0 && idx < SKILLGFX_LOGIC_PARAM_COUNT) {
            return _isref[idx];
        }
        return _INVALID_ID;
    }
    void setIsRefByIdx(int idx, int val)
    {
        if (idx >= 0 && idx < SKILLGFX_LOGIC_PARAM_COUNT) {
            if (val != _isref[idx]) {
                _isref[idx] = val;
            }
        }
    }
public:
    bool getParent() const { return _parent; }
    void setParent(SkillGfx* parent) { _parent = parent; }

private:
    int             _id;
    QString         _desc;
    QString         _name;
    int             _instId;
    int             _actionId;
    int             _isref[SKILLGFX_LOGIC_PARAM_COUNT];
    int             _params[SKILLGFX_LOGIC_PARAM_COUNT];

    SkillGfx*       _parent;
};
using SkillGfxDataPtr = QSharedPointer<SkillGfxData>;

///////////////////////////////////////////////////////////////////////////
class SkillGfx : public QObject
{
    Q_OBJECT
public:
    SkillGfx(QObject *parent);

public:
    void clear();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void notify(SkillNotifyReason reason);
    void notify(SkillGfxData& data, SkillNotifyReason reason);

public:
    void addData(SkillGfxDataPtr data);
    int insertData(int posidx, SkillGfxDataPtr data);
    void removeData(int id);
    SkillGfxDataPtr getData(int id);
    const QList<SkillGfxDataPtr>& getDatas() const { return _datas; }

public:
    void setFilePath(QString file) { this->_curFilePath = file; }
    QString getFilePath() const { return this->_curFilePath; }
    QString getFileName() const { return QFileInfo(this->_curFilePath).fileName(); }
    QString getRelFileName(QString dir) const { return QDir(dir).relativeFilePath(getFilePath()); }
    QString getFileSuffix() const { return QFileInfo(this->_curFilePath).suffix(); }
    QString getFileDir() const { return QFileInfo(this->_curFilePath).absolutePath(); }

signals:
    void tableChanged(const SkillGfx& pool, SkillNotifyReason reason);
    void dataChanged(const SkillGfxData& data, SkillNotifyReason reason);

private:
    void saveLine(QTextStream& stream, const QStringList& list);

private:
    QStringList                 _headers;
    QStringList                 _types;
    QString                     _info;
    QStringList                 _descs;
    QList<SkillGfxDataPtr>      _datas;

    QString                     _curFilePath;
};

///////////////////////////////////////////////////////////////////////////
//获取实例数据
SkillGfxDataPtr getGfxData(int id);
