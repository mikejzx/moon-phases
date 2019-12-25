
/*
	This program calculates the lunar phase on the given date.
	Reference: https://www.subsystems.us/uploads/9/8/9/4/98948044/moonphase.pdf

	Stages:
	- 0, New Moon        (0.000 - 0.125)
	- 1, Waxing Crescent (0.125 - 0.250)
	- 2, First Quarter   (0.250 - 0.375)
	- 3, Waxing Gibbous  (0.375 - 0.500)

	- 4, Full Moon       (0.500 - 0.625)
	- 5, Waning Gibbous  (0.625 - 0.750)
	- 6, Last Quarter    (0.750 - 0.875)
	- 7, Waning Crescent (0.875 - 1.00f)
*/

// Includes
#include <iostream>
#include <math.h>
#include <string.h>

// Local Includes.
#include "./moon_ascii.h"

// Function prototypes.
float julian_day(int, int, int);

// Entry-point
int main (int argc, char* argv[])
{
	// This is the beginning date we use. It was a new moon on this day.
	float nmoon = julian_day(2000, 1, 6);

	// Get the date from command line args.
	if (argc < 4)
	{
		std::cout << "Usage: lunar <day> <month> <year>" << std::endl;
		return 0;
	}
	bool southhemi = true;
	if (argc > 4)
	{
		// Check if Northern Hemisphere flag.
		if (strcmp(argv[4], "--north") == 0)
		{
			southhemi = false;
		}	
	}

	// Get command line args.
	int d = std::stoi(argv[1]);
	int m = std::stoi(argv[2]);
	int y = std::stoi(argv[3]);
	
	std::cout << "Approximate lunar phase for date " << d << "." << m << "." << y  << " :"<< std::endl;

	// Calculate days since new moon from Julian day.
	float jd = julian_day(y, m, d);
	float diff = jd - nmoon;
	float newmoons = diff / 29.530588853f;
	float norm = newmoons - int(newmoons);
	float daysincyc = norm * 29.530588853f;
	
	std::cout << daysincyc << " days since New Moon" << std::endl;

	// Names of each phase.
	const char* phases[] = {
		"New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbous", 
		"Full Moon", "Waning Gibbous", "Third Quarter", "Waning Crescent"
	};

	// Calculate phase index.
	unsigned phase = (int)round(norm * 7.0f);
	
	// Print out the phase name.
	std::cout << "The Moon phase is " << phases[phase] << std::endl;
	
	// Flip for Southern hemisphere.
	if (southhemi)
	{
		phase = 8 - phase;
		if (phase == 8) { phase = 0; }
		std::cout << "The following would be visible from the Southern hemisphere:";
	}
	else 
	{
		std::cout << "The following would be visible from the Northern hemisphere:";
	}

	// Print ASCII
	std::cout << ascii_art_phases[phase]  << std::endl;

	return 0;
}

// Get the Julian Day of the date.
float julian_day(int y, int m, int d)
{
	// If month is Jan or Feb, subtract 1 from year, and add 12 to month.
	if (m < 3)
	{
		--y;
		m += 12;
	}
	
	int a = y / 100;
	int b = a / 4;
	int c = 2 - a + b;
	int e = int(365.25f * (y + 4716.0f));
	int f = int(30.6001f * (m + 1.0f));
	
	return c + d + e + f - 1524.5f;
}
