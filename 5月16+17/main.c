#include <STC89C5xRC.H>

#include "TCRT5000.h"
#include "L298N.h"

#define ONLY_GO 0
#define GO 1
#define STOP_W5S 2

unsigned char stage = ONLY_GO;
unsigned char start_stopline = 0;
unsigned int start_protect = 1000;

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	
	ET0 = 1;
}

unsigned int t0cnt = 0;
unsigned char t0ok = 0;
void serviceTimer0() interrupt 1
{
	
	if(t0cnt > 0){
		t0cnt--;
	}
	else{
		t0ok = 1;
		TR0 = 0;
	}
		
}

void t0start(unsigned int time){
	
	t0ok = 0;
	t0cnt = time;
	TR0 = 1;
	
}


void main()
{
	
	unsigned char real_action;
	unsigned char backup_action;
	
	unsigned int real_pwm = 0;

	stage = ONLY_GO;
	
	Timer0Init();
	EA = 1;
	
	while (1)
	{
		backup_action = real_action;
		
		if(stage == ONLY_GO){
			start_protect--;
		}
		
		if(!start_protect){
			stage = GO;
		}
		
		real_action = get_action();
		
		real_pwm = (real_pwm + 1) % 100;
		
		if (real_action == X){
			
			if (backup_action != X )
				start_stopline = (start_stopline + 1) % 2;
			
			if (start_stopline == 1 && stage == GO){
				
				t0start(20);
				
				left_side(1);
				right_side(1);
				
				while(!t0ok);
				
				t0start(550);
				
				right_side(120);
				left_side(120);
				
				while(!t0ok);
				
				stage = GO;
				continue;
			}
			else{
				t0start(3);
				right_side(1);
				left_side(1);
				
				while(!t0ok);
				continue;
			}
		}
		
		if (real_action == TURN_LEFT)
		{
			
			if(real_pwm > 50)
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
		
		if (real_action == TURN_RIGHT)
		{
			if(real_pwm > 50)
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
			
			if(real_pwm > 20)
			{
				right_side(1);
				left_side(1);
			}
			else
			{
				right_side(120);
				left_side(1);
			}
			continue;
		}
		
		if (real_action == TURN_LEFT_SMALL)
		{
			if(real_pwm > 20)
			{
				left_side(1);
				right_side(1);
			}
			else
			{
				left_side(120);
				right_side(1);
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