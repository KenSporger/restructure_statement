#include<iostream>
#include "v5/statement.h"
#include "types.h"

using namespace std;

int main()
{

	// ≤‚ ‘ ˝æ›
	Plays plays = {
		{ "hamlet",{ "Hamlet", "tragedy" } },
		{ "as-like",{ "As You Like It", "comedy" } },
		{ "othello",{ "Othello", "tragedy" } }
	};

	Invoice invoices;
	invoices.customer = "BigGo";
	invoices.performances.push_back({ "hamlet", 55 });
	invoices.performances.push_back({ "as-like", 35 });
	invoices.performances.push_back({"othello", 40 });

	cout << statement(invoices, plays);
	return 0;
}