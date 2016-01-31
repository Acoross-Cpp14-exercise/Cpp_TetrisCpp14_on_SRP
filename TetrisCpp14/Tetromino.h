#ifndef _TETRISCPP14_TETROMINO_H
#define _TETRISCPP14_TETROMINO_H

#include <iostream>

#include <./geodata.h>

namespace acoross {
namespace tetris {

enum class Directions : int
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

enum class TetrominoType : int
{
	LONG = 0,
	RECT,
	LEFTUP,
	RIGHTUP,
	MAX
};

// 4���� ������� �����Ǵ� ������ Ŭ����.
// �� Ŭ������ ��� API �� �� Ŭ������ �����͸� ��ȭ��Ű�� ���� ������.
class Tetromino
{
public:
	static const int TetrominoBlockCount = 4;

	using Tetri_t = Point[TetrominoBlockCount];

	const Point TetrominoDefines[(int)TetrominoType::MAX][(int)Directions::MAX][TetrominoBlockCount]
	{	//LONG
		Point(-1,0),Point(0,0),Point(1,0),Point(2,0),
		Point(0,-1),Point(0,0),Point(0,1),Point(0,2),
		Point(-1,0),Point(0,0),Point(1,0),Point(2,0),
		Point(0,-2),Point(0,-1),Point(0,0),Point(0,1),
		//RECT
		Point(0,-1),Point(1,-1),Point(0,0),Point(1,0),
		Point(0,-1),Point(1,-1),Point(0,0),Point(1,0),
		Point(0,-1),Point(1,-1),Point(0,0),Point(1,0),
		Point(0,-1),Point(1,-1),Point(0,0),Point(1,0),
		//LEFTUP
		Point(-1,-1),Point(-1,0),Point(0,0),Point(1,0),
		Point(0,-1),Point(1,-1),Point(0,0),Point(0,1),
		Point(-1,0),Point(0,0),Point(1,0),Point(1,1),
		Point(0,-1),Point(0,0),Point(0,1),Point(-1,1),
		//RIGHTUP
		Point(-1,0),Point(0,0),Point(1,0),Point(1,-1),
		Point(0,-1),Point(0,0),Point(0,1),Point(1,1),
		Point(-1,0),Point(0,0),Point(1,0),Point(-1,1),
		Point(-1,-1),Point(0,-1),Point(0,0),Point(0,1)
	};

	Tetromino(TetrominoType type)
		: tetromino_type_(type)
		, direction_(Directions::UP)
	{}
	~Tetromino()
	{
		std::cout << "dtor!" << std::endl;
	}

	void Rotate(bool bClockwise)
	{
		int dir = (int)direction_;
		if (bClockwise)
			dir = (dir + 1);
		else
			dir = (dir + 3);

		dir = dir % (int)Directions::MAX;
		direction_ = (Directions)dir;
	}

	void SetDirection(Directions dir)
	{
		direction_ = dir;
	}

	const Tetri_t& GetBlock() const
	{
		return TetrominoDefines[(int)tetromino_type_][(int)direction_];
	}

private:
	const TetrominoType tetromino_type_;
	Directions direction_;
};

} //namespace tetris
} //namespace acoross
#endif //_TETRISCPP14_TETROMINO_H