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

	if (sum > 2) // 大于两传感器
	{
		return X;
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

	if (D2 == 1)
	{
		backup_action = TURN_LEFT_SMALL;
		return TURN_LEFT_SMALL;
	}
	
	if (D3 == 1)
	{
		backup_action = TURN_RIGHT_SMALL;
		return TURN_RIGHT_SMALL;
	}

	if (D4 == 1) // 右2压，左2空
	{
		backup_action = TURN_RIGHT;
		return TURN_RIGHT;
	}

	if (D5 == 1) // 右1压，左2空
	{
		backup_action = TURN_RIGHT;
		return TURN_RIGHT;
	}

	return backup_action;
}