#include <STC89C5xRC.H>

#include "TCRT5000.H"

// @brief 0 直走；1 左触发；-1右触发
signed char get_deflection_weight()
{

	static signed char backup = 0;

	if (D2 == 1)
	{
		backup = 0;
		return 0;
	}
	if (D3 == 1)
	{
		backup = 0;
		return 0;
	}

	if (D1 == 1)
	{
		backup = 1;
		return 1;
	}
	if (D4 == 1)
	{
		backup = -1;
		return -1;
	}

	return backup;
}
