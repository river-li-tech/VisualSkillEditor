#pragma once
#include <QMap>

///////////////////////////////////////////////////////////////////////
class SettingsData
{
public:
    SettingsData();
    void resetConfig();
    void readConfig(const QJsonObject &content);
    QString toPlainText();

    void addConfig(const QString &name, const QString &value);
    QString getConfig(const QString &name);
    bool hasConfig(const QString &name);

public:
    QMap<QString, QString> _configs;
};

///////////////////////////////////////////////////////////////////////

class Settings
{
public:
    Settings();

    void readSettings();
    void writeSettings();

    SettingsData &getDefalutSettings() { return _defalut_settins; }
    SettingsData &getUserSettings() { return _user_settins; }

public:
    void setShowIcons(bool val);
    bool isShowIcons();

    void setSerialTxt(bool val);
    bool isSerialTxt();

    QString getCustomSkillInstDir();
    QString getCustomSkillGfxDir();
    QString getCustomSkillScriptDir();

private:
    QString getDefaultConfigPath();
    QString getUserConfigPath();

private:
    SettingsData    _defalut_settins;
    SettingsData    _user_settins;
};
