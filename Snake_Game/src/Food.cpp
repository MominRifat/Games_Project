#include "Food.h"

Food::Food()
{
    gen_food();
}
void Food::gen_food()
{
    pos.X = (rand() % WIDTH - 1)+2;
    pos.Y = (rand() % HEIGHT - 1)+2;
}
COORD Food::get_pos()
{
    return pos;
}
