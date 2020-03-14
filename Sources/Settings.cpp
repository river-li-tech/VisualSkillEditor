#include "stdafx.h"
#include "Dict.h"
#include "Settings.h"

SettingsData::SettingsData()
{
    _configs.clear();
}

void SettingsData::resetConfig()
{
    _configs.clear();
}

void SettingsData::readConfig(const QJsonObject &content)
{
    resetConfig();
    QJsonObject::const_iterator it;
    for (it = content.begin(); it != content.end(); it++) {
        QString key = it.key();
        QString value = it.value().toString();
        addConfig(key, value);
    }
}

QString SettingsData::toPlainText()
{
    QJsonObject rootObj;
    QMap<QString, QString>::const_iterator it;
    for (it = _configs.begin(); it != _configs.end(); it++) {
        rootObj[it.key()] = it.value();
    }

    QJsonDocument doc(rootObj);
    return QString::fromUtf8(doc.toJson());
}

void SettingsData::addConfig(const QString &name, const QString &value)
{
    if (!_configs.contains(name)) {
        _configs.insert(name, value);
    } else {
        _configs[name] = value;
    }
}

QString SettingsData::getConfig(const QString &name)
{
    if (_configs.contains(name)) {
        return _configs[name];
    }
    return "";
}

bool SettingsData::hasConfig(const QString &name)
{
    return _configs.contains(name);
}

Settings::Settings()
{
    _defalut_settins.resetConfig();
    _user_settins.resetConfig();
}

void Settings::readSettings()
{
    //default
    QString dftCfgPath = gSettings->getDefaultConfigPath();
    QFile dftCfgFile(dftCfgPath);
    if (!dftCfgFile.open(QFile::ReadOnly)) {
        qWarning("load config file error.file(%s)", ctr(dftCfgPath));
        dftCfgFile.close();
        return;
    }

    QByteArray dftAllData = dftCfgFile.readAll();
    QJsonParseError dft_json_error;
    QJsonDocument dftJsonDoc(QJsonDocument::fromJson(dftAllData, &dft_json_error));
    if (dft_json_error.error != QJsonParseError::NoError) {
        qWarning("load,json error!");
        dftCfgFile.close();
        return;
    }
    QJsonObject dftRootObj = dftJsonDoc.object();
    _defalut_settins.readConfig(dftRootObj);
    dftCfgFile.close();

    //user
    QString userCfgPath = gSettings->getUserConfigPath();
    QFile userCfgFile(userCfgPath);
    if (!userCfgFile.open(QFile::ReadOnly)) {
        qWarning("load config file error.file(%s)", ctr(userCfgPath));
        userCfgFile.close();
        return;
    }

    QByteArray usrAllData = userCfgFile.readAll();
    QJsonParseError usr_json_error;
    QJsonDocument usrJsonDoc(QJsonDocument::fromJson(usrAllData, &usr_json_error));
    if (usr_json_error.error != QJsonParseError::NoError) {
        qWarning("load,json error!");
        userCfgFile.close();
        return;
    }
    QJsonObject usrRootObj = usrJsonDoc.object();
    _user_settins.readConfig(usrRootObj);
    userCfgFile.close();
}

void Settings::writeSettings()
{
    //user
    QString userCfgPath = gSettings->getUserConfigPath();
    QFile userCfgFile(userCfgPath);
    if (!userCfgFile.open(QFile::WriteOnly)) {
        qWarning("save user config error.file(%s)", ctr(userCfgPath));
        userCfgFile.close();
        return;
    }
    QTextStream stream(&userCfgFile);
    QString content = _user_settins.toPlainText();
    stream << content;
    userCfgFile.close();
}

QString Settings::getDefaultConfigPath()
{
    return QString("%0/Config/default.json").arg(QDir::currentPath());
}

QString Settings::getUserConfigPath()
{
    return QString("%0/Config/user.json").arg(QDir::currentPath());
}

void Settings::setShowIcons(bool val)
{
    _user_settins.addConfig("show_icons", val ? "1" : "0");
}

bool Settings::isShowIcons()
{
    if (_user_settins.hasConfig("show_icons")) {
        return _user_settins.getConfig("show_icons") == "1";
    }
    if (_defalut_settins.hasConfig("show_icons")) {
        return _defalut_settins.getConfig("show_icons") == "1";
    }
    return false;
}

void Settings::setSerialTxt(bool val)
{
    _user_settins.addConfig("serial_txt", val ? "1" : "0");
}

bool Settings::isSerialTxt()
{
    if (_user_settins.hasConfig("serial_txt")) {
        return _user_settins.getConfig("serial_txt") == "1";
    }
    if (_defalut_settins.hasConfig("serial_txt")) {
        return _defalut_settins.getConfig("serial_txt") == "1";
    }
    return false;
}

QString Settings::getCustomSkillInstDir()
{
    if (_user_settins.hasConfig("custom_skill_inst_dir")) {
        return _user_settins.getConfig("custom_skill_inst_dir");
    }
    if (_defalut_settins.hasConfig("custom_skill_inst_dir")) {
        return _defalut_settins.getConfig("custom_skill_inst_dir");
    }
    return "";
}

QString Settings::getCustomSkillGfxDir()
{
    if (_user_settins.hasConfig("custom_skill_gfx_dir")) {
        return _user_settins.getConfig("custom_skill_gfx_dir");
    }
    if (_defalut_settins.hasConfig("custom_skill_gfx_dir")) {
        return _defalut_settins.getConfig("custom_skill_gfx_dir");
    }
    return "";
}
QString Settings::getCustomSkillScriptDir()
{
    if (_user_settins.hasConfig("custom_skill_script_dir")) {
        return _user_settins.getConfig("custom_skill_script_dir");
    }
    if (_defalut_settins.hasConfig("custom_skill_script_dir")) {
        return _defalut_settins.getConfig("custom_skill_script_dir");
    }
    return "";
}
