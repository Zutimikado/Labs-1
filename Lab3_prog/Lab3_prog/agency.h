#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>

#pragma warning(disable : 4996)

struct agent
{
	char name[120];
	unsigned int left;
	unsigned int total;
	tm time;
};

class agency
{
	agent *ag;
	int count = 0;

public:
	agency(unsigned int);
	virtual  ~agency();

	void append(const char*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	friend std::ostream& operator<< (std::ostream& out, const agency& a);
};

std::ostream& operator<< (std::ostream& out, const agency& a);
std::istream& operator>> (std::istream& in, agency& a);