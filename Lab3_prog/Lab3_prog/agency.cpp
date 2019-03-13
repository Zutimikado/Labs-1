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


void agency::append(const char *name, unsigned int const total, unsigned int const year, unsigned int const month, unsigned int const day, unsigned int const hour, unsigned int const minute)
{
	this->ag[count].total = total;
	this->ag[count].left = total;
	strcpy(this->ag[count].name, name);
	ag[count].time.tm_sec = 0;
	ag[count].time.tm_min = minute;
	ag[count].time.tm_hour = hour;
	ag[count].time.tm_mday = day;
	ag[count].time.tm_mon = month - 1;
	ag[count].time.tm_year = year - 1900;
	count++;
}

agent agency::operator[](int i)
{
	return this->ag[i];
}


std::ostream& operator<< (std::ostream& out, const agency& a)
{
	int i = 0;
	
	for (i = 0; i < a.count; i++)
	{
		out << a.ag[i].name << ": " << std::put_time(&a.ag[i].time, "%c") << "; " << a.ag[i].left << "/" << a.ag[i].total << std::endl;
	}

	return out;
}

std::ostream& operator<< (std::ostream& out, const agent& a)
{
	out << a.name << ": " << std::put_time(&a.time, "%c") << "; " << a.left << "/" << a.total << std::endl;

	return out;
}

std::istream& operator>> (std::istream& in, agency& a)
{
	char str[100];
	unsigned int total = 0, year = 0, month = 0, day = 0, hour = 0, minute = 0;
	
	std::cout << "Enter the name: ";
	in >> str;
	std::cout << "Enter the number of tickets: ";
	in >> total;
	std::cout << "Enter the date(year/month/day/hour/minute): ";
	in >> year;
	in >> month;
	in >> day;
	in >> hour;
	in >> minute;

	a.append(str, total, year, month, day, hour, minute);

	return in;
}