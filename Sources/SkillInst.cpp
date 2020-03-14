#include "stdafx.h"
#include "Dict.h"
#include "SkillInst.h"

///////////////////////////////////////////////////////////////////////////
SkillInstData::SkillInstData()
: _id(_INVALID_ID), _desc(""), _logicFile(""), _isClientSkill(_INVALID_ID),
_isSelected(false), _parent(nullptr)
{
    for (int idx = 0; idx < SKILLINST_LOGIC_PARAM_COUNT; idx++) {
        _params[idx] = _INVALID_ID;
    }
}

bool SkillInstData::load(const QStringList& datas)
{
    if (datas.length() < SKILLINST_LOGIC_PARAM_COUNT + 2) {
        return false;
    }

    _id = datas[0].toInt();
    _desc = datas[1];
    _isClientSkill = datas[2].toInt();
    _logicFile = datas[3];

    for (int idx = 0; idx < SKILLINST_LOGIC_PARAM_COUNT; idx++) {
        _params[idx] = datas[idx + 4].toInt();
    }

    return true;
}

bool SkillInstData::save(QStringList& datas)
{
    datas.append(QString::number(_id));
    datas.append(_desc);
    datas.append(QString::number(_isClientSkill));
    datas.append(_logicFile);

    for (int idx = 0; idx < SKILLINST_LOGIC_PARAM_COUNT; idx++) {
        datas.append(QString::number(_params[idx]));
    }
    return true;
}

void SkillInstData::notify(SkillNotifyReason reason)
{
    if (_parent != nullptr) {
        emit _parent->dataChanged(*this, reason);
    }
}

///////////////////////////////////////////////////////////////////////////
SkillInst::SkillInst(QObject *parent)
: QObject(parent), _curFilePath(""), _info("")
{
    _headers.clear();
    _types.clear();
    _descs.clear();
    _datas.clear();
}

bool SkillInst::loadFile(const QString& fileName)
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
        SkillInstDataPtr pdata = SkillInstDataPtr::create();
        pdata->setParent(this);
        QStringList datas = sContent.split("	");
        if (pdata->load(datas)) {
            _datas.push_back(pdata);
        } else {
            qWarning("parse data content error.content(%s)", ctr(sContent));
        }
    }
    this->notify(SkillNotifyReason::R_SKILLINST_LOAD);
    return true;
}

bool SkillInst::saveFile(const QString& fileName)
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
        SkillInstDataPtr pdata = _datas.at(idx);
        if (pdata != nullptr) {
            QStringList list;
            pdata->save(list);
            saveLine(stream, list);
        }
    }
    this->notify(SkillNotifyReason::R_SKILLINST_SAVE);
    return true;
}

void SkillInst::notify(SkillNotifyReason reason)
{
    emit this->instChanged(*this, reason);
}

void SkillInst::notify(SkillInstData& data, SkillNotifyReason reason)
{
    emit this->dataChanged(data, reason);
}

void SkillInst::clear()
{
    _headers.clear();
    _types.clear();
    _descs.clear();
    _datas.clear();
    this->notify(SkillNotifyReason::R_SKILLINST_CLEAR);
}

bool SkillInst::addData(SkillInstDataPtr data)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillInstDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == data->getId()) {
            qWarning("addData same error.id(%d)", data->getId());
            return false;
        }
    }
    _datas.push_back(data);
    this->notify(SkillNotifyReason::R_SKILLINST_LOAD);
    return true;
}

void SkillInst::removeData(int id)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillInstDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == id) {
            _datas.removeAt(idx);
            this->notify(SkillNotifyReason::R_SKILLINST_LOAD);
            break;
        }
    }
}

int SkillInst::getMaxId()
{
    int maxId = -1;
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillInstDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() > maxId) {
            maxId = tdata->getId();
        }
    }
    return maxId;
}

SkillInstDataPtr SkillInst::getData(int id)
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillInstDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->getId() == id) {
            return tdata;
        }
    }
    return SkillInstDataPtr();
}

SkillInstDataPtr SkillInst::getCurData()
{
    for (int idx = 0; idx < this->_datas.length(); idx++) {
        SkillInstDataPtr tdata = _datas.at(idx);
        if (tdata != nullptr && tdata->isSelected()) {
            return tdata;
        }
    }
    return SkillInstDataPtr();
}

void SkillInst::saveLine(QTextStream& stream, const QStringList& list)
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
SkillInstDataPtr getInstData(int id)
{
    if (gSkillInst != nullptr) {
        return gSkillInst->getData(id);
    }
    return SkillInstDataPtr();
}

SkillInstDataPtr getCurInstData()
{
    if (gSkillInst != nullptr) {
        return gSkillInst->getCurData();
    }
    return SkillInstDataPtr();
}

double getInstDataParamByIdx(int logicIdx)
{
    SkillInstDataPtr cfgPtr = getCurInstData();
    if (cfgPtr == nullptr) {
        return _INVALID_ID;
    }
    return cfgPtr->getLogicParamByIdx(logicIdx - 1);
}

void setInstDataParamByIdx(int refIdx, int num)
{
    SkillInstDataPtr cfgPtr = getCurInstData();
    if (cfgPtr == nullptr) {
        return;
    }
    if (refIdx > 0) {
        cfgPtr->setLogicParamByIdx(refIdx - 1, num);
    }
}

