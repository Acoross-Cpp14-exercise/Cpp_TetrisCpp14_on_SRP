#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <array>
#include <conio.h>



#include <./screenbuffer.h>
#include <./TetrisBoard.h>

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_SPACE = 32;

void GameLoop()
{
	using namespace acoross;
	using namespace acoross::tetris;

	TetrisBoard tetris_board;
	ScreenBuffer screen_buffer;
	
	TetrominoType type = TetrominoType::LONG;
	auto tm_ptr = std::make_unique<Tetromino>(type);

	const Point start_pos(3, 1);
	Point tetromino_pos = start_pos;

	for (;;)
	{
		char input = 0;

		switch ((input = _getch())) {
		case KEY_UP:
			{
				tm_ptr->Rotate(true);

				Point togo = tetromino_pos;
				while (!tetris_board.CanBeHere(togo, *tm_ptr))
				{
					--togo.y;
				}
				tetromino_pos = togo;
			}
			break;
		case KEY_DOWN:
			{
				Point togo(tetromino_pos.x, tetromino_pos.y + 1);
				if (tetris_board.CanBeHere(togo, *tm_ptr))
				{
					tetromino_pos = togo;
				}
			}
			break;
		case KEY_LEFT:
			{
				Point togo(tetromino_pos.x -1, tetromino_pos.y);
				if (tetris_board.CanBeHere(togo, *tm_ptr))
				{
					tetromino_pos = togo;
				}
			}
			break;
		case KEY_RIGHT:
			{
				Point togo(tetromino_pos.x + 1, tetromino_pos.y);
				if (tetris_board.CanBeHere(togo, *tm_ptr))
				{
					tetromino_pos = togo;
				}
			}
			break;
		case KEY_SPACE:
			{
				Point togo = tetromino_pos;
				while (tetris_board.CanBeHere(togo, *tm_ptr))
				{
					tetromino_pos = togo;
					++togo.y;
				}

				tetris_board.SetTetromino(tetromino_pos, *tm_ptr);
				tetromino_pos = start_pos;

				int typeint = (int)type;
				++typeint;
				typeint %= (int)TetrominoType::MAX;
				type = (TetrominoType)typeint;

				tm_ptr.reset(new Tetromino(type));
			}
			break;
		default:
			break;
		}
		
		screen_buffer.Initialize();
		screen_buffer.DrawFrom(tetris_board.GetRawBuffer());
		screen_buffer.DrawFrom(tetromino_pos, tm_ptr->GetBlock(), 1);

		system("cls");
		screen_buffer.DrawToScreen();
	}
}

int main(int argc, char* argv[])
{
	GameLoop();

	return 0;
}
