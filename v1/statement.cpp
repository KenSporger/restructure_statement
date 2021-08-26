#include "statement.h"
#include<algorithm>

using namespace std;

string statement(const Invoice &invoices, const Plays &plays)
{
	double totalAmount = 0;
	int volumeCredits = 0;
	string result = "Statement for " + invoices.customer + "\n";

	auto format = [](double num)->string {
		char temp[20];
		sprintf_s(temp, 20, "%.2lf", num);
		return "$" + string(temp);
	};

	for (auto perf : invoices.performances)
	{
		const Play play = plays.at(perf.playID);
		double thisAmount = 0;

		if (play.type == "tragedy")
		{
			thisAmount = 40000;
			if (perf.audience > 30)
			{
				thisAmount += 1000 * (perf.audience - 30);
			}
		}
		else if (play.type == "comedy")
		{
			thisAmount = 30000;
			if (perf.audience > 20)
			{
				thisAmount += 10000 + 500 * (perf.audience - 20);
			}
			thisAmount += 300 * perf.audience;
		}
		else
		{
			throw("unknown type: " + play.type);
		}

		volumeCredits += max(perf.audience - 30, 0);
		if (play.type == "comedy") volumeCredits += (int)floor(perf.audience / 5);

		result += " " + play.name + ": " + format(thisAmount / 100) + "(" + to_string(perf.audience) + " seats)\n";
		totalAmount += thisAmount;
	}

	result += "Amount owed is " + format(totalAmount / 100) + "\n";
	result += "You earned " + to_string(volumeCredits) + " credits\n";

	return result;
}
