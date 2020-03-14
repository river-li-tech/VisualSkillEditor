#include "stdafx.h"
#include <QtWidgets/QApplication>

#include "SkillEditor.h"
#include "SkillInst.h"
#include "SkillGfx.h"
#include "SkillScript.h"
#include "SkillSpec.h"
#include "Settings.h"
#include "Log.h"
#include "Dict.h"
#include "Utils.h"

extern QApplication * gApp;
extern SkillEditor * gSkillEditor;
extern SkillInst * gSkillInst;
extern SkillSpec* gSkillSpec;
extern Settings * gSettings;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(SkillEditor);
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);

    LogInit("Log/Log.txt");

    //create app
    gApp = new QApplication(argc, argv);
    QCoreApplication::setOrganizationName("ProjectA");
    QCoreApplication::setApplicationName("Skill Editor");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    //load chinese default.
    QTranslator translator;
    if (translator.load("../I18N/zh")) {
        qApp->installTranslator(&translator);
    }

    //create global data
    gDict = new Dict();
    gSkillInst = new SkillInst(nullptr);
    gSkillInst->clear();
    gSkillGfx = new SkillGfx(nullptr);
    gSkillGfx ->clear();
    gSkillScript = new SkillScript();
    gSkillScript->clear();
    gSkillSpec = new SkillSpec();
    gSkillSpec->clear();
    gSkillSpec->load(SKILLSPEC_FILE_PATH);
    gSettings = new Settings();
    gSettings->readSettings();

    // startup dialog or file
    int ret = 0;
    gSkillEditor = new SkillEditor();
    gSkillEditor->show();
    if (ENABLE_STARTUP_LOAD_FILE) {
        gSkillEditor->loadWorkspace();
    }
    ret = gApp->exec();

    return ret;
}
