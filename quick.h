#pragma once
#include <vector>
#include <mutex>
#include <thread>

/*
	The approach:

	We find the lowest number with the highest multiplicative persistence for each number of decimals.
	We start at one decimal, results in 0
	At 2, we find 77 with an mp of 4.

	Here are some things to speed up the process:
	1) We only test numbers with "increasing" digits, so 123, we don't test 312 (same mp) since we know that 123 < 312.
	2) For each decimal, we start with the winner of the last with an appended decimal of 1. This way, we don't do the same checks twice.
	So for winner 77 we start with 177 in the next round. This might be mathematically off but we still find the true numbers for mp < 11.
	I guess it's a valid performance improvement then.
*/

/*
	Talking about programming styles, this is absolute rubbish. An evening project for a bit of fun. Please don't judge.
*/

/*
	We represent numbers as a vector of digits in the decimal system.
	This is used to skip conversions between a base-2 number and the decimal representation
	used to calculate the "multiplicative number" of a base-10 number.
	With uint64_t, we are also limited to 2^64 numbers, < 20 decimal places.

	DecimalNumber n, n[0] is the first digit with, n[1] is the second.
	So number is n[0] * 10^0 + n[1] * 10^1 + ... n[i] * 10^i
*/

using Digit = uint16_t;
using DecimalNumber = std::vector<Digit>;

// base of system
static const Digit Base = 10;

// converst number to a string, it uses the hex appraoch when you change the base to something != 10
inline std::string toText(const DecimalNumber  &buf)
{
	// this only works with 
	std::string text;
	for (int i = buf.size()-1; i>= 0; i--)
	{
		char c = '?';
		auto digit = buf[i];
		if ((0 <= digit) && (digit <= 9))
		{
			c = '0' + digit;
		}
		else if ((10 <= digit) && (digit <= 36))
		{
			c = 'A' + digit-10;
		}

		text.push_back(c);
	}
	return text;
}

// reduces a number multiplicatively, so for 235, we get 2*3*5 = 30
// reduces inplace to prevent unnecessary allocations
inline void reduceMul(std::vector<Digit> &buf)
{
	// multiplication fo decimal numbers
	// as taught in pirmary school
	for (int i = 0; i < buf.size(); i++)
	{
		Digit digit = buf[i];
		
		buf[i] = (i == 0);

		if(digit == 0) 
		{
			buf[0] = 0;
			buf.resize(1);
			return;
		}

		int remainder = 0;
		for (int k = 0; k <= i; k++)
		{
			Digit &d = buf[k];
			auto prod = d  * digit + remainder;
			remainder = prod / Base;

			d = prod - Base * remainder;
		}
	}

	// shrink the buffer to the necessary number of digits
	for (int i = buf.size()-1; i >= 0 ; i--)
	{
		if (buf[i] != 0)
		{
			buf.resize(i+1);
			return;
		}
	}

	buf.resize(0);
	return;
}

// calculate the multiplicative persistence of a number n
inline int mulPers(DecimalNumber num)
{

	int its = 0;
	while (num.size() > 1)
	{
		reduceMul(num);
		its++;
	}

	return its;
}


/*
	takes a Number num, iterates through all 1-9 digits at decimal place decimal,
	if the multiplicative persistence of any of those resulting numbers is higher then stored in "winnerMP", we update
	winnerMP with the mul pers of the number and store the number in "winner"
*/
inline void iterateRangeRec(DecimalNumber & num, DecimalNumber &winner, int &winnerMP, unsigned int decimal)
{
	Digit curDigit = num[decimal];

	Digit minDigit = (decimal == (num.size() - 1)) ? 1 : num[decimal + 1];

	minDigit = std::max(curDigit, minDigit);

	if (decimal > 0)
	{
		for (Digit i = minDigit; i < Base; i++)
		{
			num[decimal] = i;
			iterateRangeRec(num, winner, winnerMP, decimal - 1);
		}

		num[decimal] = 1;
	}
	else
	{
		for (Digit i = minDigit; i < Base; i++)
		{
			num[decimal] = i;
			int mp = mulPers(num);

			if (mp > winnerMP)
			{
				winner = num;
				winnerMP = mp;
			}
		}

		num[decimal] = 1;
	}
}

// iterates through any number with "numDecimals" decimal places to get the lowest number with the highest multiplicative persistence
// prints the highest MP
inline DecimalNumber findHighestMP(DecimalNumber start)
{
	DecimalNumber winner;
	int winnerMP = -1;

	// init a number to [111 ... 1] with numDecimals digits
	DecimalNumber num = start;
	int numDecimals = num.size();

	iterateRangeRec(num, winner, winnerMP, numDecimals-1);

	return winner;
}

// quick since this version was faster then the brute force "test every number" version.
// goes through every number of digits, starting with 1, and prints the winner.
inline void findQuick()
{
	TicToc tic;
	int order = 0;
	DecimalNumber winner = { 1 };
	while (true)
	{
		winner = findHighestMP(winner);

		auto time = tic.tocMS();
		std::cout << "10E" << winner.size() - 1 << ": Winner is " << toText(winner) << " with " << mulPers(winner) << " steps (" << time << "ms)" << std::endl;
		

		winner.push_back(1); // add one digit
		order++;
	}
}