#include "statement.h"

using namespace std;

string usd(double num)
{
	char temp[20];
	sprintf_s(temp, 20, "%.2lf", num / 100);
	return "$" + string(temp);
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

string renderHtml(const StatementData& data)
{
	string result = "<h1>Statement for " + data.customer + "<h1>\n";
	result += "<table>\n";
	result += "<tr><th>play</th><th>seats</th><th>cost</th></tr>";
	for (auto perf : data.performances)
	{
		result += "<tr><td>" + perf.play.name + "</td><td>" + to_string(perf.audience) + "</td>";
		result += "<td>" + usd(perf.amount) + "</td></tr>\n";
	}
	result += "</table>\n";

	result += "<p>Amount owed is <em>" + usd(data.totalAmount) + "</em></p>\n";
	result += "<p>You earned <em>" + to_string(data.totalVolumeCredits) + "</em> credits</p>\n";

	return result;
}

string statement(const Invoice &invoices, const Plays &plays)
{
	return renderPlainText(createStatementData(invoices, plays));
}

string htmlStatement(const Invoice &invoices, const Plays &plays)
{
	return renderHtml(createStatementData(invoices, plays));
}