#include "StartLevelSetting.h"
#include "../CTestLevel.h"

CLevel& StartLevelSetting()
{
	CLevel& buf = *new CTestLevel();

	return buf;
}