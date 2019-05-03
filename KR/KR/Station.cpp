#include "Flight.h"
#include "Station.h"
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

flight station::operator[](const unsigned int index)
{
	return flights_[index];
}

void station::book_ticket(const unsigned int index)
{
	if (flights_[index].remaining_ticket > 0)
	{
		flights_[index].remaining_ticket--;
	}
	else
	{
		throw std::exception("Tickets are over!");
	}
}

void station::sort_by_date()
{
	std::sort(flights_.begin(), flights_.end(), [](flight e1, flight e2) -> bool
	{
		return mktime(&(e1.start_time)) < mktime(&(e2.start_time));
	});
}

std::vector<flight>::iterator station::begin()
{
	return flights_.begin();
}

std::vector<flight>::iterator station::end()
{
	return flights_.end();
}

std::istream& operator>>(std::istream& in, station& a)
{
	std::string line;
	std::getline(in, line);

	std::string subs[6];

	for (auto i = 0; i < 5; i++)
	{
		const auto pos = line.find(';');
		subs[i] = line.substr(0, pos);
		line.erase(0, pos + 1);
	}
	subs[5] = line;

	flight f;
	f.start_city = subs[0];
	f.end_city = subs[2];
	f.capasity = std::stoi(subs[4]);
	f.remaining_ticket = std::stoi(subs[5]);
	std::stringstream ss1(subs[1]);
	ss1 >> std::get_time(&(f.start_time), "%Y-%m-%d %H:%M");
	std::stringstream ss2(subs[3]);
	ss2 >> std::get_time(&(f.end_time), "%Y-%m-%d %H:%M");

	a.flights_.push_back(f);

	return in;
}

std::ostream& operator<<(std::ostream& out, station const& a)
{
	for (const flight& f : a.flights_)
	{
		out << f.start_city << " to " << f.end_city << "; " << std::put_time(&(f.start_time), "%b %d %Y %H:%M") << " - " << std::put_time(&(f.end_time), "%b %d %Y %H:%M") << "; " << f.remaining_ticket << "/" << f.capasity << "\n";
	}
	return out;
}
