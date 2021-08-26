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

double totalAmount(const Invoice &invoices, const Plays &plays)
{
	double result = 0;
	for (auto perf : invoices.performances)
	{
		result += amountFor(perf, plays.at(perf.playID));
	}
	return result;
}

int totalVolumeCredits(const Invoice &invoices, const Plays &plays)
{
	int result = 0;
	for (auto perf : invoices.performances)
	{
		result += volumeCreditsFor(perf, plays.at(perf.playID));
	}
	return result;
}

string renderPlainText(const StatementData& data)
{
	string result = "Statement for " + data.customer + "\n";

	for (auto perf : data.performances)
	{
		result += " " + perf.play.name + ": " + usd(perf.amount) + "(" + to_string(perf.audience) + " seats)\n";
	}

	result += "Amount owed is " + usd(data.totalAmount) + "\n";
	result += "You earned " + to_string(data.totalVolumeCredits) + " credits\n";

	return result;
}

StatementPerf enrichPerformance(const Performance & perf, const Plays &plays)
{
	StatementPerf result(perf);
	result.play = plays.at(perf.playID);
	result.amount = amountFor(perf, plays.at(perf.playID));
	result.volumeCredits = volumeCreditsFor(perf, plays.at(perf.playID));
	return result;
}

StatementData createStatementData(const Invoice &invoices, const Plays &plays)
{
	StatementData result;
	result.customer = invoices.customer;
	for (auto perf : invoices.performances) result.performances.push_back(enrichPerformance(perf, plays));
	result.totalAmount = totalAmount(invoices, plays);
	result.totalVolumeCredits = totalVolumeCredits(invoices, plays);
	return result;
}

string statement(const Invoice &invoices, const Plays &plays)
{
	return renderPlainText(createStatementData(invoices, plays));
}