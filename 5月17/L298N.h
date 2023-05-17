#ifndef __L298N__
#define __L298N__

// @brief 左前轮转向控制位
#define UPPER_LEFT_A P20
#define UPPER_LEFT_B P21
// @brief 左后轮转向控制位
#define LOWER_LEFT_A P22
#define LOWER_LEFT_B P23

// @brief 右前轮转向控制位
#define UPPER_RIGHT_A P24
#define UPPER_RIGHT_B P25
// @brief 右后轮转向控制位
#define LOWER_RIGHT_A P26
#define LOWER_RIGHT_B P27

void left_side(unsigned char isback);
void right_side(unsigned char isback);

#endif