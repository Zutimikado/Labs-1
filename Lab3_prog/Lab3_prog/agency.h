#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

#pragma warning(disable : 4996)

struct agent
{
	char name[30];
	unsigned int left;
	unsigned int total;
	tm time;

	agent& operator=(const agent& a);
	bool operator>(const agent& a);
};

class agency
{
public:
	agent *ag;
	int count = 0;

public:
	agency(unsigned int);
	virtual ~agency();

	void append(const char*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	agent operator[](int);
	int num();
	void sortdate();
	void sortname();
	void book(unsigned int, unsigned int);
	void readfile();
	friend std::ostream& operator<< (std::ostream& out, const agency& a);
	friend std::ostream& operator<< (std::ostream& out, const agent& a);
};

std::ostream& operator<< (std::ostream& out, const agency& a);
std::ostream& operator<< (std::ostream& out, const agent& a);
std::istream& operator>> (std::istream& in, agency& a);