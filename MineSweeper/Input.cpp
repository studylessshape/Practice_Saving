#ifndef INPUT_CPP
#define INPUT_CPP
#include <iostream>
#include "include/Map.h"
enum InputResult
{
	Null,
	Invalid,
	Valid,
};//�ж�������
//��������
InputResult InputReceive(int out[2], int range);//��������ĺ���

InputResult InputReceive(int out[2], int range)
{
	std::cin >> out[0] >> out[1];
	if (out[0] <= 0 || out[0] > range || out[1] <= 0 || out[1] > range)
	{
		return Invalid;
	}
	return Valid;
}
#endif
