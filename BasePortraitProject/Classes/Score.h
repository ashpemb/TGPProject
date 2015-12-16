#ifndef Score_h
#define Score_h
#include <stdio.h>

using namespace std;

class Score
{
public:
	~Score();
	static Score* sharedScore();

	
	
	int getScore();
	void setScore();
	void updateScore(int amount);

private:
	Score();
	static Score* instance;
	int score = 0;
};
#endif /* Score_h */