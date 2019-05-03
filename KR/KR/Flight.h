#pragma once
#include <string>

struct flight
{
	std::string start_city;
	std::string end_city;
	tm start_time;
	tm end_time;
	unsigned int remaining_ticket;
	unsigned int capasity;
};