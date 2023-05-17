#include <STC89C5xRC.H>
#include "L298N.h"

// AC反转，BD正转

void left_side(unsigned char isback)
{
	if(isback == 0)
	{
		// 反
		// @brief 左前轮转向控制位
		UPPER_LEFT_A = 1;
		UPPER_LEFT_B = 0;
		// @brief 左后轮转向控制位
		LOWER_LEFT_A = 1;
		LOWER_LEFT_B = 0;
		return;
	}
	else if(isback == 1)
	{
		// 正
		// @brief 左前轮转向控制位
		UPPER_LEFT_A = 0;
		UPPER_LEFT_B = 1;
		// @brief 左后轮转向控制位
		LOWER_LEFT_A = 0;
		LOWER_LEFT_B = 1;
		return;
	}
	// stop
	// @brief 左前轮转向控制位
	UPPER_LEFT_A = 0;
	UPPER_LEFT_B = 0;
	// @brief 左后轮转向控制位
	LOWER_LEFT_A = 0;
	LOWER_LEFT_B = 0;
}

void right_side(unsigned char isback)
{
	if(isback == 0)
	{
		// 反
		// @brief 左前轮转向控制位
		UPPER_RIGHT_A = 1;
		UPPER_RIGHT_B = 0;
		// @brief 左后轮转向控制位
		LOWER_RIGHT_A = 1;
		LOWER_RIGHT_B = 0;
		return;
	}
	else if(isback == 1)
	{
		// 正
		// @brief 左前轮转向控制位
		UPPER_RIGHT_A = 0;
		UPPER_RIGHT_B = 1;
		// @brief 左后轮转向控制位
		LOWER_RIGHT_A = 0;
		LOWER_RIGHT_B = 1;
		return;
	}
	// stop
	// @brief 左前轮转向控制位
	UPPER_RIGHT_A = 0;
	UPPER_RIGHT_B = 0;
	// @brief 左后轮转向控制位
	LOWER_RIGHT_A = 0;
	LOWER_RIGHT_B = 0;
}
