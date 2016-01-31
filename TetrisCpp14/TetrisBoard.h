#ifndef _TETRISCPP14_TETRISBOARD_H
#define _TETRISCPP14_TETRISBOARD_H

#include <./screenbuffer.h>
#include <./Tetromino.h>

namespace acoross {
namespace tetris {

class TetrisBoard
{
public:
	explicit TetrisBoard()
	{
		for (int y = 0; y < ScreenBuffer::SizY; ++y)
		{
			for (int x = 0; x < ScreenBuffer::SizX; ++x)
			{
				if (x == 0 || x == ScreenBuffer::SizX - 1 || y == ScreenBuffer::SizY - 1)
				{
					buffer_.DrawFrom(Point(x, y), 1);
				}
			}
		}
	}

	void SetTetromino(const Point& pos, const Tetromino& tm)
	{
		buffer_.DrawFrom(pos, tm.GetBlock(), 1);
	}

	bool CanBeHere(const Point& pos, const Tetromino& tm) const
	{
		for (const auto& p : tm.GetBlock())
		{
			if (buffer_.GetBlockAt(Point(pos.x + p.x, pos.y + p.y)) > 0)
				return false;
		}

		return true;
	}

	const ScreenBuffer::buffer_array_t& GetRawBuffer() const
	{
		return buffer_.GetBuffer();
	}

private:
	ScreenBuffer buffer_;
};

} //namespace tetris
} //namespace acoross

#endif //_TETRISCPP14_TETRISBOARD_H