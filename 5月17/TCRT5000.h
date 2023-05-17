#ifndef __TCRT5000__
#define __TCRT5000__

// @brief 六个模块的数字输出线
#define D0 P07
#define D1 P06
#define D2 P05
#define D3 P04
#define D4 P03
#define D5 P02

 #define   GO_STR 0
#define	TURN_LEFT_SMALL 1
 #define  TURN_LEFT  2 
 #define   TURN_RIGHT 3
#define	TURN_RIGHT_SMALL 4
	#define X 5

unsigned char get_action();

#endif