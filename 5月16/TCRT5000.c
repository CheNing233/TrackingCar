#include <STC89C5xRC.H>

#include "TCRT5000.H"

unsigned char backup_action = GO_STR;

unsigned char get_action()
{
		
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

	if ((D0 == 1 || D1 == 1) && (D4 == 1 || D5 == 1))
	{
		return X;
	}

	if (D2 == 1 && D3 == 1){
		backup_action = GO_STR;
		return GO_STR;
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

}