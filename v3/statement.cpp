#include "statement.h"
#include<algorithm>

using namespace std;

double amountFor(const Performance &perf, const Play &play)
{
	double result = 0;
	if (play.type == "tragedy")
	{
		result = 40000;
		if (perf.audience > 30)
		{
			result += 1000 * (perf.audience - 30);
		}
	}
	else if (play.type == "comedy")
	{
		result = 30000;
		if (perf.audience > 20)
		{
			result += 10000 + 500 * (perf.audience - 20);
		}
		result += 300 * perf.audience;
	}
	else
	{
		throw("unknown type: " + play.type);
	}
	return result;
}

int volumeCreditsFor(const Performance &perf, const Play &play)
{
	int result = 0;
	result += max(perf.audience - 30, 0);
	if (play.type == "comedy") result += (int)floor(perf.audience / 5);
	return result;
}

string usd(double num)
{
	char temp[20];
	sprintf_s(temp, 20, "%.2lf", num / 100);
	return "$" + string(temp);
}

string statement(const Invoice &invoices, const Plays &plays)
{
	double totalAmount = 0;
	int volumeCredits = 0;
	string result = "Statement for " + invoices.customer + "\n";

	for (auto perf : invoices.performances)
	{
		const Play play = plays.at(perf.playID);
		
		double thisAmount = amountFor(perf, play);

		volumeCredits += volumeCreditsFor(perf, play);

		result += " " + play.name + ": " + usd(thisAmount) + "(" + to_string(perf.audience) + " seats)\n";
		totalAmount += thisAmount;
	}

	result += "Amount owed is " + usd(totalAmount) + "\n";
	result += "You earned " + to_string(volumeCredits) + " credits\n";

	return result;
}