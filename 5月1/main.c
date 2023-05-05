#include <STC89C5xRC.H>

#include "TCRT5000.h"
#include "L298N.h"

// @brief 偏转权
signed char deflection_weight = 0;

void INTinit()
{

	EA = 1;
}

void Timer0Init(void) // 1微秒@11.0592MHz
{
	AUXR &= 0x7F; // 定时器时钟12T模式
	TMOD &= 0xF0; // 设置定时器模式
	TMOD |= 0x02; // 设置定时器模式
	TL0 = 0xFF;	  // 设置定时初始值
	TH0 = 0xFF;	  // 设置定时重载值
	TF0 = 0;	  // 清除TF0标志
	TR0 = 1;	  // 定时器0开始计时

	ET0 = 1;
}

void Timer0Service() interrupt 1
{
	if (deflection_weight == 0)
	{
		// @brief 左前轮转向控制位
		UPPER_LEFT_A = 0;
		UPPER_LEFT_B = 1;
		// @brief 左后轮转向控制位
		LOWER_LEFT_A = 0;
		LOWER_LEFT_B = 1;

		// @brief 右前轮转向控制位
		UPPER_RIGHT_A = 0;
		UPPER_RIGHT_B = 1;
		// @brief 右后轮转向控制位
		LOWER_RIGHT_A = 0;
		LOWER_RIGHT_B = 1;
	}
	else if (deflection_weight == -1)
	{
		// @brief 左前轮转向控制位
		UPPER_LEFT_A = 1;
		UPPER_LEFT_B = 0;
		// @brief 左后轮转向控制位
		LOWER_LEFT_A = 1;
		LOWER_LEFT_B = 0;

		// @brief 右前轮转向控制位
		UPPER_RIGHT_A = 0;
		UPPER_RIGHT_B = 1;
		// @brief 右后轮转向控制位
		LOWER_RIGHT_A = 0;
		LOWER_RIGHT_B = 1;
	}
	else if (deflection_weight == 1)
	{
		// @brief 左前轮转向控制位
		UPPER_LEFT_A = 0;
		UPPER_LEFT_B = 1;
		// @brief 左后轮转向控制位
		LOWER_LEFT_A = 0;
		LOWER_LEFT_B = 1;

		// @brief 右前轮转向控制位
		UPPER_RIGHT_A = 1;
		UPPER_RIGHT_B = 0;
		// @brief 右后轮转向控制位
		LOWER_RIGHT_A = 1;
		LOWER_RIGHT_B = 0;
	}
}

void main()
{
	// 初始化
	Timer0Init();
	INTinit();

	// 获取偏转权
	while (1)
	{
		deflection_weight = get_deflection_weight();
	}
}