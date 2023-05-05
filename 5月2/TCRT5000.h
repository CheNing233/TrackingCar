#ifndef __TCRT5000__
#define __TCRT5000__

// @brief 六个模块的数字输出线
#define D0 P17
#define D1 P16
#define D2 P15
#define D3 P14
#define D4 P13
#define D5 P12

typedef enum
{
    TURN_LEFT,
    GO_STR,
    TRUN_RIGHT,
    SLOW_DOWN
} ACTION_t;

ACTION_t get_action();

#endif