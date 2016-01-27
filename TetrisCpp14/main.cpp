#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <array>

namespace acoross {
namespace tetris {

struct Point
{
	int x, y;
};

enum class Directions : int
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

// 4개의 블록으로 구성되는 데이터 클래스.
// 이 클래스의 모든 API 는 이 클래스의 데이터를 변화시키기 위해 동작함.
class Tetromino
{
public:
	enum class TetrominoType : int
	{
		LONG = 0,
		RECT,
		LEFTUP,
		RIGHTUP,
		MAX
	};
	
	static const int TetrominoBlockCount = 4;

	const Point TetrominoDefines[(int)TetrominoType::MAX][(int)Directions::MAX][TetrominoBlockCount]
	{ {0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 }
	};

	Tetromino(TetrominoType type)
		: tetromino_type_(type)
		, direction_(Directions::UP)
	{}
	~Tetromino(){}

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

	const Point* GetBlock() const
	{	
		return TetrominoDefines[(int)tetromino_type_][(int)direction_];
	}

private:
	const TetrominoType tetromino_type_;
	Directions direction_;
};

//template <size_t x, size_t y>
//class TetrisBoard 
//{
//public:
//	void SetTeromino(Tetromino& tetro);
//
//	void RotateTeromino(Tetromino& tetro) const;
//
//	void MoveTetromino(Tetromino& tetro, int input) const;
//
//private:
//	int board_[y][x];
//};

class ScreenOut
{
public:
	void Draw(){}
};

void GameLoop()
{
	//TetrisBoard<10, 20> board;
	ScreenOut screen;

	auto t_last = std::chrono::high_resolution_clock::now();

	// 60fps
	for (;;)
	{
		auto t_now = std::chrono::high_resolution_clock::now();
		auto t_delta_ms = std::chrono::duration<double, std::milli>(t_now - t_last).count();
		t_last = t_now;

		std::cout << t_delta_ms << std::endl;
		
		// get input
		int input = 0;

		// modify game data
		//board.Update(input);

		// draw screen
		screen.Draw();

		
		std::this_thread::sleep_for(std::chrono::milliseconds(13));
	}
}

} //namespace tetris
} //namespace acoross


int main(int argc, char* argv[])
{
	acoross::tetris::GameLoop();

	return 0;
}
