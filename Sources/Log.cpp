#include "stdafx.h"
#include "Dict.h"
#include "Log.h"

QFile * gLogFile = NULL;
char * _msgHead[] = {
    "[Debug]",
    "[Warn ]",
    "[Error]",
    "[Fatal]",
    "[Info ]"
};

bool LogInit(const QString & path)
{
    gLogFile = new QFile(path);
    QString dirPath = QFileInfo(path).absolutePath();
    QDir dir(dirPath);
    if (!dir.exists()) {
        dir.mkdir(dirPath);
    }

    if (!gLogFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qWarning("open log file error.file(%s)", ctr(path));
        return false;
    }
    qInstallMessageHandler(LogHandler);
    qInfo("------------------------start----------------------------");
    return true;
}

void LogRelease()
{
    if (gLogFile != NULL) {
        gLogFile->close();
        SAFE_DELETE(gLogFile);
    }
}

void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString ctxInfo = QString("File:(%0) Line:(%1)").arg(context.file).arg(context.line);
    QString dateInfo = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString message = QString(" %0[%1]:%2 <%3>").arg(_msgHead[type]).arg(dateInfo).arg(msg).arg(ctxInfo);

    if (gLogFile != NULL) {
        QTextStream stream(gLogFile);
        stream << message << endl;
        stream.flush();
        gLogFile->flush();
    } else {
        fprintf(stderr, "%s\n", message.toStdString());
    }
}
