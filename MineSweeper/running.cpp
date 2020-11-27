#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include "include/Map.h"
int running()
{
	Map map;
	int input[2];
	GameStatus status = Rest;
	OpenPointType open_result;
	time_t now_time;
	struct tm* start_time;
	time(&now_time);
	start_time = localtime(&now_time);
	while (status != Lost && status != Win)
	{
		if (status == Rest)
			status = Doing;
		system("cls");
		map.PrintMap();

		open_result = Number;
		std::cout << "Pos(x, y)>>>> ";
        std::cin >> input[0] >> input[1];
        if (input[0] <= 0 || input[0] > map.length() || input[1] <= 0 || input[1] > map.length())
        {
            open_result = Error;
        }

        if(open_result != Error)
            open_result = map.OpenPoint(input[0]-1, input[1]- 1);
		if (open_result == Boom)
		{
			status = Lost;
			system("cls");
			map.PrintMap(open_result);
			std::cout << "You lost!" << std::endl;
			break;
		}
		else if (open_result == win)
		{
			status = Win;
			std::cout << "You Win!" << std::endl;
			break;
		}
	}
	time_t t;
	struct tm* end_time;
	time(&t);
	end_time = localtime(&t);

	int game_time = 0;
	game_time += abs(start_time->tm_hour - end_time->tm_hour) * 60 * 60;
	if (start_time->tm_hour != end_time->tm_hour)
	{
		if (start_time->tm_sec != 0)
		{
			game_time += 60 - start_time->tm_sec;
			start_time->tm_sec = 0;
			start_time->tm_min ++;
			if (start_time->tm_min == 60)
			{
				start_time->tm_min = 0;
				start_time->tm_hour++;
			}
		}
		if (start_time->tm_min != 0)
		{
			game_time += 60 - start_time->tm_min;
			start_time->tm_min = 0;
			start_time->tm_hour++;
		}
		game_time += abs(start_time->tm_min - end_time->tm_min) * 60;
		if (end_time->tm_sec != 0)
			game_time += end_time->tm_sec;
		if (end_time->tm_min != 0)
			game_time += end_time->tm_min * 60;
	}
	std::cout << "Use time(s): " << game_time << std::endl;
	system("pause");
	return 0;
}
