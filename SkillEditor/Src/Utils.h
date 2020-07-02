/************************************************************************/
/*
@file:Utils.h
@author:LRiver.2019.10.25
@desc:Utils
*/
/************************************************************************/

#pragma once
#include "stdafx.h"

class Utils
{
public:
    //获取当前时间
    static long getCurTime();

    //将字符串转化为数值
    template<typename T>
    static T transRangeValue(const QString& str, T dft);
};

//将字符串转化为数值
template<typename T>
T Utils::transRangeValue(const QString& str, T dft)
{
    bool isOk = false;
    if (std::is_same<T, int>::value) {
        int ret = str.toInt(&isOk);
        if (isOk) {
            return ret;
        } else {
            return dft;
        }
    } else if (std::is_same<T, double>::value) {
        int ret = str.toDouble(&isOk);
        if (isOk) {
            return ret;
        } else {
            return dft;
        }
    } else if (std::is_same<T, float>::value) {
        int ret = str.toFloat(&isOk);
        if (isOk) {
            return ret;
        } else {
            return dft;
        }
    } else if (std::is_same<T, long>::value) {
        int ret = str.toLong(&isOk);
        if (isOk) {
            return ret;
        } else {
            return dft;
        }
    }
    return dft;
}

