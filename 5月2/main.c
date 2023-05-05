#include <STC89C5xRC.H>

#include "TCRT5000.h"
#include "L298N.h"



void main()
{
	
	ACTION_t real_action;
	
	unsigned int real_pwm = 0;
	
	
	while (1)
	{
		real_action = get_action();
		
		real_pwm = (real_pwm + 1) % 100;
		
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
		
		else if (real_action == TRUN_RIGHT)
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
		
		/*else if (real_action == GO_STR)
		{
			left_side(1);
			right_side(1);
			continue;
		}
		*/
		else if (real_action == GO_STR)
		{
			if(real_pwm > 10)
			{
				left_side(1);
				right_side(1);
			}
			else
			{
				left_side(0);
				right_side(0);
			}
			continue;
		}
	}
}