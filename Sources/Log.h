/************************************************************************/
/* 
@file:Log.h
@author:LRiver.2019.10.25
@desc:Log
*/
/************************************************************************/

#pragma once
#include "stdafx.h"
//初始化
bool LogInit(const QString & path);
//释放
void LogRelease();
//日志处理
void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
