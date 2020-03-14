#include "stdafx.h"
#include "Dict.h"
#include "Utils.h"
#include "SkillSpec.h"

long Utils::getCurTime()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}
