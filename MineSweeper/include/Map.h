
#ifndef MAP_H
#define MAP_H
#define BOOM -1
#define HIDE '-'
#include "../Value.h"
class Map
{
	public:
		Map();

		void PrintMap();
		void PrintMap(OpenPointType res);

		int length();

		OpenPointType OpenPoint(int x, int y);
	private:
		int map[9][9];
		bool is_open[9][9];

		int open_number;//记录未打开的点
		const int map_size;
};
#endif //MAP_H
