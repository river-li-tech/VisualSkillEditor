///////////////////////////////////////////////////////////////////////////
//cpp headers
#include <limits>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
//qt modules
#include <QObject>
#include <QtWidgets>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QList>
#include <QMap>
#include <QtMath>
#include <QtAlgorithms>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QDomNode>
#include <QMessageBox>
#include <QLoggingCategory>
#include <QIODevice>
#include <QStringList>
#include <QXmlStreamWriter>
using QTableWidgetItemPtr = QSharedPointer<QTableWidgetItem>;

///////////////////////////////////////////////////////////////////////////
#define  SAFE_DELETE(p) if(p) {delete p;p = nullptr;}

#define  SAFE_DELETE_CONTAINER(iter)\
while (iter.hasNext()) { \
    delete iter.next(); \
}

#define ctr(s) s.toStdString().c_str()
#define _INVALID_ID -1

///////////////////////////////////////////////////////////////////////////
class QApplication;
extern QApplication * gApp;

class SkillEditor;
extern SkillEditor * gSkillEditor;

class SkillInst;
extern SkillInst * gSkillInst;

class SkillGfx;
extern SkillGfx * gSkillGfx;

class SkillScript;
extern SkillScript * gSkillScript;

class SkillSpec;
extern SkillSpec * gSkillSpec;

class Dict;
extern Dict* gDict;

class Settings;
extern Settings * gSettings;

