#pragma once
#include "Flight.h"
#include <vector>

class station
{
	std::vector<flight> flights_;

public:
	station() = default;
	station(station const &a) = delete;
	station(station&&) = delete;

	flight operator[](unsigned int);
	void sort_by_date();
	void book_ticket(unsigned int);
	friend std::ostream& operator<< (std::ostream&, const station&);
	friend std::istream& operator>> (std::istream&, station&);
	std::vector<flight>::iterator begin();
	std::vector<flight>::iterator end();
};

std::ostream& operator<< (std::ostream&, const station&);
std::istream& operator>> (std::istream&, station&);