#ifndef _TETRISCPP14_GEODATA_H
#define _TETRISCPP14_GEODATA_H

#include <iostream>
#include <string>

#include <./geodata.h>

namespace acoross {
namespace tetris {

class ScreenBuffer
{
public:
	static const int SizX{ 10 };
	static const int SizY{ 20 };

	using buffer_array_t = char[SizY][SizX];

	ScreenBuffer()
	{
		Initialize();
	}

	void Initialize()
	{
		::memset(blocks_, 0, sizeof(blocks_));
	}

	template<size_t N>
	void DrawFrom(const Point(&points)[N], char val)
	{
		for (auto& p : points)
		{
			DrawFrom(p, val);
		}
	}

	void DrawFrom(const buffer_array_t& buf)
	{
		for (int y = 0; y < SizY; ++y)
		{
			for (int x = 0; x < SizX; ++x)
			{
				if (buf[y][x] != 0)
				{
					blocks_[y][x] = buf[y][x];
				}
			}
			std::cout << std::endl;
		}
	}

	template<size_t N>
	void DrawFrom(const Point& pos, const Point(&points)[N], char val)
	{
		for (auto& p : points)
		{
			DrawFrom(Point(pos.x + p.x, pos.y + p.y), val);
		}
	}

	void DrawFrom(const Point& point, char val)
	{
		if (point.x < 0 || point.x >= SizX)
			return;

		if (point.y < 0 || point.y >= SizY)
			return;

		blocks_[point.y][point.x] = val;
	}

	void DrawToScreen()
	{
		std::string output;
		for (int y = 0; y < SizY; ++y)
		{
			for (int x = 0; x < SizX; ++x)
			{
				if (blocks_[y][x] == 0)
				{
					output.append("_ ");
					//std::cout << "_ ";
				}
				else
				{
					output.append("@ ");
					//std::cout << "@ ";
				}
			}
			output.append("\n");
			//std::cout << std::endl;
		}

		//std::cout << output;
		printf("%s", output.c_str());
	}

	const buffer_array_t& GetBuffer() const
	{
		return blocks_;
	}

	int GetBlockAt(const Point& point) const
	{
		if (point.x < 0 || point.x >= SizX)
			return -1;

		if (point.y < 0 || point.y >= SizY)
			return -1;

		return blocks_[point.y][point.x];
	}

private:
	char blocks_[SizY][SizX];
};

} //namespace tetris
} //namespace acoross

#endif //_TETRISCPP14_GEODATA_H