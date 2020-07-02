#include "stdafx.h"
#include "Dict.h"
#include "SkillGfx.h"

///////////////////////////////////////////////////////////////////////////
SkillGfxData::SkillGfxData()
: _id(_INVALID_ID), _desc(""), _name(""),
_instId(_INVALID_ID), _actionId(_INVALID_ID), 
_parent(nullptr)
{
    for (int idx = 0; idx < SKILLGFX_LOGIC_PARAM_COUNT; idx++) {
        _params[idx] = _INVALID_ID;
    }
    for (int idx = 0; idx < SKILLGFX_LOGIC_PARAM_COUNT; idx++) {
        _isref[idx] = _INVALID_ID;
    }
}

bool SkillGfxData::load(const QStringList& datas)
{
    if (datas.length() < SKILLGFX_LOGIC_PARAM_COUNT + 2) {
        return false;
    }

    _id = datas[0].toInt();
    _desc = datas[1];
    _name = datas[2];
    _instId = datas[3].toInt();
    _actionId = datas[4].toInt();

    for (int idx = 0; idx < SKILLGFX_LOGIC_PARAM_COUNT; idx++) {
        _isref[idx] = datas[5 + 2 * idx].toInt();
        _params[idx] = datas[5 + 2 * idx + 1].toInt();
    }

    return true;
}

bool SkillGfxData::save(QStringList& datas)
{
    datas.append(QString::number(_id));
    datas.append(_desc);
    datas.append(_name);
    datas.append(QString::number(_instId));
    datas.append(QString::number(_actionId));

    for (int idx = 0; idx < SKILLGFX_LOGIC_PARAM_COUNT; idx++) {
        datas.append(QString::number(_isref[idx]));
        datas.append(QString::number(_params[idx]));
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
SkillGfx::SkillGfx(QObject *parent)
: QObject(parent), _curFilePath(""), _info("")
{
    _headers.clear();
    _types.clear();
    _descs.clear();
    _datas.clear();
}

bool SkillGfx::loadFile(const QString& fileName)
{
    QFile sprFile(fileName);
    if (!sprFile.exists()) {
        qWarning() << "load skill inst file not exists, fileName:" << fileName;
        return false;
    }
    if (!sprFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("load skill inst file error, fileName(%s)", ctr(fileName));
        return false;
    }

    this->_curFilePath = fileName;

    //文件头
    QTextStream stream(&sprFile);
    _headers = stream.readLine().split("	");
    _types = stream.readLine().split("	");
    _info = stream.readLine();
    _descs = stream.readLine().split("	");

    //解析内容
    while (!stream.atEnd()) {
        QString sContent = stream.readLine();
        //#标记为注释
        if (sContent.startsWith("#")) {
            continue;
        }

        //解析行
        SkillGfxDataPtr pdata = SkillGfxDataPtr::create();
        pdata->setParent(this);
        QStringList datas = sContent.split("	");
        if (pdata->load(datas)) {
            _datas.push_back(pdata);
        } else {
            qWarning("parse data content error.content(%s)", ctr(sContent));
        }
    }
    this->notify(SkillNotifyReason::R_SKILLGFX_LOAD);
    return true;
}

bool SkillGfx::saveFile(const QString& fileName)
{
    QFile sprFile(fileName);
    if (!sprFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("save skill inst file error, fileName(%s)", ctr(fileName));
        return false;
    }

    this->_curFilePath = fileName;

    //写入文件头
    QTextStream stream(&sprFile);
    saveLine(stream, _headers);
    saveLine(stream, _types);
    stream << _info << endl;
    saveLine(stream, _descs);

    //写入内容
    for (int idx = 0; idx < _datas.length(); idx++) {
        SkillGfxDataPtr pdata = _datas.at(idx);
        if (pdata != nullptr) {
            QStringList list;
            pdata->save(list);
            saveLine(stream, list);
        }
    }
    this->notify(SkillNotifyReason::R_SKILLGFX_SAVE);
    return true;
}

void SkillGfx::notify(SkillNotifyReason reason)
{
    emit this->tableChanged(*this, reason);
}

void SkillGfx::notify(SkillGfxData& data, SkillNotifyReason reason)
{
    emit this->dataChanged(data, reason);
}

void SkillGfx::clear()
{
    _headers.clear();
    _types.clear();
    _descs.clear();
    _datas.clear();
    this->notify(SkillNotifyReason::R_SKILLGFX_CLEAR);
}

void SkillGfx::addData(SkillGfxDataPtr data)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillGfxDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == data->getId()) {
            qWarning("addData same error.id(%d)", data->getId());
            return;
        }
    }
    _datas.push_back(data);
    this->notify(*data, SkillNotifyReason::R_SKILLGFX_LOAD);
}

int SkillGfx::insertData(int posidx, SkillGfxDataPtr data)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillGfxDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == data->getId()) {
            qWarning("addData same error.id(%d)", data->getId());
            return posidx;
        }
    }
    _datas.insert(posidx, data);
    this->notify(*data, SkillNotifyReason::R_SKILLGFX_LOAD);
    return ++posidx;
}

void SkillGfx::removeData(int id)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillGfxDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == id) {
            _datas.removeAt(idx);
            this->notify(*tdata, SkillNotifyReason::R_SKILLGFX_REMOVE_DATA);
            break;
        }
    }
}

SkillGfxDataPtr SkillGfx::getData(int id)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillGfxDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == id) {
            return tdata;
        }
    }
    return SkillGfxDataPtr();
}

void SkillGfx::saveLine(QTextStream& stream, const QStringList& list)
{
    for (int idx = 0; idx < list.length(); idx++) {
        stream << list.at(idx);
        if (idx != list.length() - 1) {
            stream << "	";
        }
    }
    stream << endl;
}

///////////////////////////////////////////////////////////////////////////
SkillGfxDataPtr getInstData(int id)
{
    if (gSkillGfx != nullptr) {
        return gSkillGfx->getData(id);
    }
    return SkillGfxDataPtr();
}
