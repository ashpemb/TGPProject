#include "Score.h"

Score::Score()
{
	score = 1;
}


Score::~Score()
{

}

int Score::getScore()
{
	return score;
}

void Score::updateScore(int amount)
{
	score = score + amount;
}