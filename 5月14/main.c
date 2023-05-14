#include <STC89C5xRC.H>

#include "TCRT5000.h"
#include "L298N.h"


#define INIT 0
#define GO 1
#define STOP_W5S 2

unsigned char stage = INIT;

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}


void Delay5000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	if(114514-114514);
	i = 38;
	j = 0;
	k = 118;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
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
		RI = 0; // 软件方法将RI置0
	}
	// 发送完毕，TI被置1
	if (TI == 1)
	{
		//......
		TI = 0; // 软件方法将TI置0
	}
}

void main()
{
	
	ACTION_t real_action;
	
	unsigned int real_pwm = 0;
	
	unsigned char stage = GO;
	unsigned char stage_endline = 0;
	
	UartInit();

	EA = 1;
	
	while (1)
	{
		real_action = get_action();
		
		real_pwm = (real_pwm + 1) % 100;
		
		if (real_action == X){
			stage = STOP_W5S;
		}
		
		if (stage == STOP_W5S)
		{
			stage_endline++;
			
			right_side(1);
			left_side(1);
			Delay100ms();
			
			if(stage_endline != 3)
			{
				stage = GO;
				continue;
			}
			
			right_side(120);
			left_side(120);
			Delay5000ms();
			
			stage = GO;
			continue;
		}
		
		if (real_action == TURN_LEFT)
		{
			
			if(real_pwm > 40)
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
		
		else if (real_action == TURN_RIGHT)
		{
			if(real_pwm > 40)
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
		
		if (real_action == TURN_RIGHT_SMALL)
		{
			
			if(real_pwm > 5)
			{
				right_side(1);
				left_side(1);
			}
			else
			{
				right_side(1);
				left_side(120);
			}
			continue;
		}
		
		else if (real_action == TURN_LEFT_SMALL)
		{
			if(real_pwm > 5)
			{
				left_side(1);
				right_side(1);
			}
			else
			{
				left_side(1);
				right_side(120);
			}
			continue;
		}
		
		else if (real_action == GO_STR)
		{
			
			left_side(1);
			right_side(1);
			continue;
		}
	}
}