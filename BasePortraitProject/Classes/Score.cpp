#include "Score.h"

Score* Score::instance = NULL;

Score* Score::sharedScore()
{
	if (instance == NULL)
	{
		instance = new Score();
	}
	return instance;
}

Score::Score()
{
	score = 0;
}


Score::~Score()
{

}

int Score::getScore()
{
	return score;
}

void Score::setScore()
{
	score = 0;
}

void Score::updateScore(int amount)
{
	score = score + amount;
}