#include <STC89C5xRC.H>

#include "TCRT5000.h"
#include "L298N.h"

/*
	global vars
*/

#define INIT 0
#define GO 1
#define STOP_W5S 2
#define GO_2 3
#define SLOW 4
#define GO_3 5
#define STOP 6

unsigned int real_pwm = 0;
unsigned int real_wtime = 0;
unsigned char channel_sum = 0;
unsigned char stage = 0;

unsigned char D0_r = 0;
unsigned char D1_r = 0;
unsigned char D2_r = 0;
unsigned char D3_r = 0;
unsigned char D4_r = 0;
unsigned char D5_r = 0;

void Timer0Init(void) // 1us@12.000MHz
{
	AUXR &= 0x7F; // 定时器时钟12T模式
	TMOD &= 0xF0; // 设置定时器模式

	TL0 = 0xFF; // 设置定时初始值
	TH0 = 0xFF; // 设置定时初始值
	TF0 = 0;	// 清除TF0标志

	ET0 = 1;

	TR0 = 1; // 定时器0开始计时
}

void UartInit(void) // 9600bps@12.000MHz
{
	PCON &= 0x7F; // 波特率不倍速
	SCON = 0x50;  // 8位数据,可变波特率
	AUXR &= 0xBF; // 定时器时钟12T模式
	AUXR &= 0xFE; // 串口1选择定时器1为波特率发生器
	TMOD &= 0x0F; // 设置定时器模式
	TMOD |= 0x20; // 设置定时器模式
	TL1 = 0xFD;	  // 设置定时初始值
	TH1 = 0xFD;	  // 设置定时重载值
	ET1 = 0;	  // 禁止定时器%d中断
	TR1 = 1;	  // 定时器1开始计时

	ES = 1;
}

void serviceUART() interrupt 4
{
	// 接收到数据，RI被置1
	if (RI == 1)
	{
		if (SBUF == 'A')
			stage = GO;
		else if (SBUF == 'S')
			stage = STOP;
		RI = 0; // 软件方法将RI置0
	}
	// 发送完毕，TI被置1
	if (TI == 1)
	{
		//......
		TI = 0; // 软件方法将TI置0
	}
}

void serviceTimer0() interrupt 1
{
	real_pwm = (real_pwm + 1) % 1000;
	if (stage == STOP_W5S)
	{
		if (real_pwm == 999)
		{
			real_wtime++;
		}
		if (real_wtime == 5000)
		{
			real_wtime = 0;
			stage++;
		}
	}
}

void main()
{

	UartInit();
	Timer0Init();

	EA = 1;

	stage = GO;
	
	while (1)
	{
		channel_sum = (unsigned char)D0 +
					  (unsigned char)D1 +
					  (unsigned char)D2 +
					  (unsigned char)D3 +
					  (unsigned char)D4 +
					  (unsigned char)D5;

					  
		if (channel_sum > 0)
		{
			D0_r = D0;
			D1_r = D1;
			D2_r = D2;
			D3_r = D3;
			D4_r = D4;
			D5_r = D5;
		}

		if (channel_sum > 3)
		{
			stage++;
			continue;
		}

		if (stage == STOP || stage == STOP_W5S)
		{
			left_side(120);
			right_side(120);
			continue;
		}

		if (D0_r == 1) // 左1压
		{
			if (real_pwm > 400)
			{
				right_side(1);
				left_side(0);
			}
			else
			{
				right_side(120);
				left_side(120);
			}
			continue;
		}

		if (D5_r == 1) // 右1压
		{
			if (real_pwm > 400)
			{
				left_side(1);
				right_side(0);
			}
			else
			{
				left_side(120);
				right_side(120);
			}
			continue;
		}

		if (D4_r == 1) // 右2压
		{
			if (real_pwm > 400)
			{
				left_side(1);
				right_side(0);
			}
			else
			{
				left_side(120);
				right_side(120);
			}
			continue;
		}

		if (D1_r == 1) // 左2压
		{
			if (real_pwm > 400)
			{
				right_side(1);
				left_side(0);
			}
			else
			{
				right_side(120);
				left_side(120);
			}
			continue;
		}

		if (D2_r == 1 && D3_r == 1)
		{
			if (stage == SLOW)
			{
				if (real_pwm > 100)
				{
					left_side(1);
					right_side(1);
				}
				else
				{
					left_side(0);
					right_side(0);
				}
			}
			else
			{
				left_side(1);
				right_side(1);
			}
			continue;
		}

		if (D2_r == 1)
		{
			if (stage == SLOW)
			{
				if (real_pwm > 100)
				{
					left_side(1);
					right_side(1);
				}
				else
				{
					left_side(0);
					right_side(0);
				}
			}
			else
			{
				if (real_pwm > 100)
				{
					left_side(1);
					right_side(1);
				}
				else
				{
					left_side(120);
					right_side(1);
				}
			}
			continue;
		}

		if (D3_r == 1)
		{
			if (stage == SLOW)
			{
				if (real_pwm > 100)
				{
					left_side(1);
					right_side(1);
				}
				else
				{
					left_side(0);
					right_side(0);
				}
			}
			else
			{
				if (real_pwm > 100)
				{
					left_side(1);
					right_side(1);
				}
				else
				{
					left_side(1);
					right_side(120);
				}
			}
			continue;
		}
	}
}