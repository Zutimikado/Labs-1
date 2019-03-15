#include "agency.h"

agent& agent::operator=(const agent& a)
{
	this->time = a.time;
	this->left = a.left;
	strcpy(this->name, a.name);
	this->total = a.total;
	return *this;
}

bool agent::operator>(const agent& a)
{
	if (this->time.tm_year > a.time.tm_year)
	{
		return true;
	}
	else if (this->time.tm_year == a.time.tm_year)
	{
		if (this->time.tm_mon > a.time.tm_mon)
		{
			return true;
		}
		else if (this->time.tm_mon == a.time.tm_mon)
		{
			if (this->time.tm_mday > a.time.tm_mday)
			{
				return true;
			}
			else if (this->time.tm_mday == a.time.tm_mday)
			{
				if (this->time.tm_hour > a.time.tm_hour)
				{
					return true;
				}
				else if (this->time.tm_hour == a.time.tm_hour)
				{
					if (this->time.tm_min > a.time.tm_min)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

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


void agency::append(const char *name, unsigned int const total, unsigned int left, unsigned int const year, unsigned int const month, unsigned int const day, unsigned int const hour, unsigned int const minute)
{
	ag[count].total = total;
	ag[count].left = left;
	strcpy(ag[count].name, name);
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

int agency::num()
{
	return this->count;
}

void agency::sortdate()
{
	int i = 0, j = 0;

	for (i = count - 1; i >= 1; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (ag[j] > ag[j + 1])
			{
				agent ag1 = ag[j];
				ag[j] = ag[j + 1];
				ag[j + 1] = ag1;
			}
		}
	}
}

void agency::sortname()
{
	int i = 0, j = 0, k = 0;

	for (i = count - 1; i >= 1; i--)
	{
		for (j = 0; j < i; j++)
		{
			while (ag[j].name[k] != '\0' || ag[j + 1].name[k] != '\0')
			{
				if (ag[j].name[k] > ag[j + 1].name[k])
				{
					agent ag1 = ag[j];
					ag[j] = ag[j + 1];
					ag[j + 1] = ag1;
					break;
				}
				else if (ag[j].name[k] == ag[j + 1].name[k])
				{
					k++;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void agency::book(unsigned int ind, unsigned int num)
{
	try
	{
		if (ag[ind - 1].left < num)
		{
			throw std::exception("There aren't enough tickets");
		}
		ag[ind - 1].left -= num;
		std::cout << "Tickets successfully booked!" << std::endl;
	}
	catch (std::exception &err)
	{
		std::cout << err.what() << std::endl;
	}
}

void agency::readfile()
{
	std::ifstream fin("agent.csv");
	char str[100], str1[100], name[20];
	int i = 0, j = 0, total = 0, left = 0, year = 0, month = 0, day = 0, hour = 0, minute = 0;

	while (!fin.eof())
	{
		fin.getline(str, 100);

		i = 0;
		j = 0;

		while (str[j] != ';')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		strcpy(name, str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != ';')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		total = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != ';')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		left = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != '-')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		year = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != '-')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		month = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != ' ')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		day = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != ':')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		j++;
		str1[i] = '\0';
		hour = atoi(str1);
		strcpy(str1, "");

		i = 0;
		while (str[j] != '\0')
		{
			str1[i] = str[j];
			i++;
			j++;
		}
		str1[i] = '\0';
		minute = atoi(str1);
		strcpy(str1, "");

		strcpy(str, "");
		this->append(name, total, left, year, month, day, hour, minute);
	}
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
	unsigned int total = 0, left = 0, year = 0, month = 0, day = 0, hour = 0, minute = 0;
	
	std::cout << "Enter the name: ";
	in >> str;
	std::cout << "Enter the number of tickets: ";
	in >> total;
	std::cout << "Enter the number of remaining tickets: ";
	in >> left;
	std::cout << "Enter the date(year/month/day/hour/minute): ";
	in >> year;
	in >> month;
	in >> day;
	in >> hour;
	in >> minute;

	a.append(str, total, left, year, month, day, hour, minute);

	return in;
}