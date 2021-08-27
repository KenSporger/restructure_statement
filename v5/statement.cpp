#include "statement.h"
#include<algorithm>

using namespace std;

double amountFor(const StatementPerf &data)
{
	double result = 0;
	if (data.play.type == "tragedy")
	{
		result = 40000;
		if (data.audience > 30)
		{
			result += 1000 * (data.audience - 30);
		}
	}
	else if (data.play.type == "comedy")
	{
		result = 30000;
		if (data.audience > 20)
		{
			result += 10000 + 500 * (data.audience - 20);
		}
		result += 300 * data.audience;
	}
	else
	{
		throw("unknown type: " + data.play.type);
	}
	return result;
}


int volumeCreditsFor(const StatementPerf &data)
{
	int result = 0;
	result += max(data.audience - 30, 0);
	if (data.play.type == "comedy") result += (int)floor(data.audience / 5);
	return result;
}

string usd(double num)
{
	char temp[20];
	sprintf_s(temp, 20, "%.2lf", num / 100);
	return "$" + string(temp);
}

double totalAmount(const StatementData &data)
{
	double result = 0;
	for (auto perf : data.performances)
	{
		result += perf.amount;
	}
	return result;
}

int totalVolumeCredits(const StatementData &data)
{
	int result = 0;
	for (auto perf : data.performances)
	{
		result += perf.volumeCredits;
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
	result.amount = amountFor(result);
	result.volumeCredits = volumeCreditsFor(result);
	return result;
}

StatementData createStatementData(const Invoice &invoices, const Plays &plays)
{
	StatementData result;
	result.customer = invoices.customer;
	for (auto perf : invoices.performances) result.performances.push_back(enrichPerformance(perf, plays));
	result.totalAmount = totalAmount(result);
	result.totalVolumeCredits = totalVolumeCredits(result);
	return result;
}

string statement(const Invoice &invoices, const Plays &plays)
{
	return renderPlainText(createStatementData(invoices, plays));
}