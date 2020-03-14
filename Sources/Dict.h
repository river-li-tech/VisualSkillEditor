/************************************************************************/
/* 
@file:Dict.h
@author:LRiver
@desc:string dictionary for i18n
*/
/************************************************************************/

#pragma once
#include <QObject>
#include <QString>

class Dict
{
public:
    QString DEFAULT_UNSAVED_PATH = QObject::tr("UnSaved");// QStringLiteral("/未保存");    // LogicParam列数量
    QString PROG_NAME = QObject::tr("SkillEditor");// QStringLiteral("技能编辑器");    // LogicParam列数量
    QString TXT_NEW_FILE = QObject::tr("New File");//QStringLiteral("新建文件");    // LogicParam列数量
    QString TXT_OPEN_FILE = QObject::tr("Open File");//QStringLiteral("打开文件");    // LogicParam列数量
    QString TXT_SAVE_FILE_FAILED = QObject::tr("Failed to write file:\n%1");//QStringLiteral("写入文件失败\n%1");    // LogicParam列数量
    QString TXT_OPEN_FILE_FAILED = QObject::tr("Failed to open file:\n%1");//QStringLiteral("打开文件失败\n%1");    // LogicParam列数量
    QString TXT_SAVE_FILE_SUCCESS = QObject::tr("Write file successfully");//QStringLiteral("写入文件成功");    // LogicParam列数量
    QString TXT_OPEN_FILE_SUCCESS = QObject::tr("Open file successfully.");//QStringLiteral("打开文件成功");    // LogicParam列数量
    QString TXT_ASK_SAVE_MODIFIED = QObject::tr("Do you need to save changes?");//QStringLiteral("是否保存修改?");    // LogicParam列数量
    QString TXT_EXCEED_INFO_MAX_COUNT = QObject::tr("Remarks cannot exceed %1!");//QStringLiteral("是否保存修改?");    // LogicParam列数量
    QString TXT_CHECK_IS_REF = QObject::tr("Is Ref");//QStringLiteral("是否保存修改?");    // LogicParam列数量

    QString TXT_SKILL_INST_SAME_ID = QObject::tr("Same Id is NOT allowed!");//QStringLiteral("ID不允许重复");    // LogicParam列数量
    QString TXT_SKILL_INST_DELETE_SCRIPT = QObject::tr("Do you need delete script?");//QStringLiteral("是否需要删除脚本文件?");    // LogicParam列数量
    QString TXT_SKILL_INST_ISCLIENT_ERROR = QObject::tr("Only -1/0/1 available!");//QStringLiteral("ID不允许重复");    // LogicParam列数量

    QString TXT_ADD_CHILD_NODE_FAILED = QObject::tr("Add child node failed.\nNode type error.");//QStringLiteral("是否保存修改?");    // LogicParam列数量
    QString TXT_MOVE_NODE_FAILED = QObject::tr("Move node failed.\nNode type error.");//QStringLiteral("是否保存修改?");    // LogicParam列数量
    QString TXT_PASTE_NODE_FAILED = QObject::tr("Paste node failed.\nNode type error.");//QStringLiteral("是否保存修改?");    // LogicParam列数量

    QString TXT_ALL_SAVED = QObject::tr("All Saved!");//QStringLiteral("全部保存!");    // LogicParam列数量

    QString TXT_LOAD_CONFIG_FAILED = QObject::tr("load config file error.");
    QString TXT_SETTING_DIALOG_TITLE = QObject::tr("Settings");
    QString TXT_SETTING_DIALOG_ASK_SAVED = QObject::tr("User Settings changed, apply?");
};
