#include <STC89C5xRC.H>

#include "TCRT5000.H"

ACTION_t get_action()
{
	static ACTION_t backup_action;
	char sum = (unsigned char)D0 +\
		(unsigned char)D1 +\
			(unsigned char)D2 +\
				(unsigned char)D3 +\
					(unsigned char)D4 +\
						(unsigned char)D5;

	if (sum < 1) // 全部悬空时，返回上一个状态
	{
		return backup_action;
	}

	if (sum > 2) // 大于两传感器时，降速判断
	{
		return backup_action;
	}

	if (D0 == 1) // 左1压，右2空
	{
		backup_action = TURN_LEFT;
		return TURN_LEFT;
	}

	if (D1 == 1) // 左2压，右2空
	{
		backup_action = TURN_LEFT;
		return TURN_LEFT;
	}

	if (D2 == 1) // 左三右三同压或单压
	{
		backup_action = GO_STR;
		return GO_STR;
	}
	
	if (D3 == 1)
	{
		backup_action = GO_STR;
		return GO_STR;
	}

	if (D4 == 1) // 右2压，左2空
	{
		backup_action = TRUN_RIGHT;
		return TRUN_RIGHT;
	}

	if (D5 == 1) // 右1压，左2空
	{
		backup_action = TRUN_RIGHT;
		return TRUN_RIGHT;
	}

	return backup_action;
}