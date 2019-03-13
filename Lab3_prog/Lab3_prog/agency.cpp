#include "agency.h"

agency::agency(unsigned int size)
{
	count = 0;
	ag = new agent[size];
}

agency::~agency()
{
	count = 0;
	delete[] ag;
}


void agency::append(const char *name, unsigned int const total, int const year, int const month, int const day, int const hour, int const minute)
{
	this->ag[count].total = total;
	this->ag[count].left = total;
	strcpy(this->ag[count].name, name);
	ag[count].time.tm_sec = 0;
	ag[count].time.tm_min = minute;
	ag[count].time.tm_hour = hour;
	ag[count].time.tm_mday = day;
	ag[count].time.tm_mon = month;
	ag[count].time.tm_year = year;
	count++;
}