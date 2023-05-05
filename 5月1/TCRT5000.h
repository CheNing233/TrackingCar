#ifndef __TCRT5000__
#define __TCRT5000__

// @brief 六个模块的数字输出线
//#define D0 P00
#define D1 P01
#define D2 P02
#define D3 P03
#define D4 P04
//#define D5 P05

// @brief 六个模块的权重
#define D0_WEIGHT -3
#define D1_WEIGHT -2
#define D2_WEIGHT -1
#define D3_WEIGHT 1
#define D4_WEIGHT 2
#define D5_WEIGHT 3

signed char get_deflection_weight();

#endif