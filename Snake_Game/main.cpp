#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <vector>
#include "Snake.h"
#include "Food.h"

#define WIDTH 50
#define HEIGHT 25

using namespace std;

Snake snake({WIDTH / 2, HEIGHT / 2}, 1);
Food food;
int score;
bool is_paused = false;

void board()
{
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();
    vector<COORD> snake_body = snake.get_body();
    cout << "SCORE = " << score << "\n\n";
    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1)
            {
                cout << "#";
            }
            else if (i == snake_pos.Y && j + 1 == snake_pos.X)
            {
                cout << "O";
            }
            else if (i == food_pos.Y && j + 1 == food_pos.X)
            {
                cout << "F";
            }
            else
            {
                bool isBodyPart = false;
                for (int k = 0; k < snake_body.size(); k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X)
                    {
                        cout << "o";
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                {
                    cout << " ";
                }
            }
        }
        cout << "#\n";
    }
}

int main()
{
    score = 0;
    srand(static_cast<unsigned int>(time(NULL)));
    food.gen_food();
    bool game_over = false;

    while (!game_over)
    {
        if (!is_paused)
        {
            board();
            if (kbhit())
            {
                switch (getch())
                {
                    case '5': snake.change_dir('u'); break;
                    case '1': snake.change_dir('l'); break;
                    case '2': snake.change_dir('d'); break;
                    case '3': snake.change_dir('r'); break;
                    case 'p': is_paused = !is_paused; break;
                }
            }

            if (snake.eaten(food.get_pos()))
            {
                food.gen_food();
                snake.grow();
                score += 10;
            }

            if (snake.collided())
            {
                game_over = true;
            }

            snake.move_snake();
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

            Sleep(100);
        }
        else
        {
            if (kbhit())
            {
                switch (getch())
                {
                    case 'p': is_paused = !is_paused; break;
                }
            }
            Sleep(100);
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}
