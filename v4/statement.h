#ifndef _STATEMENTV4_H
#define _STATEMENTV4_H

#include "../types.h"

struct StatementPerf : public Performance
{
	StatementPerf(const Performance& perf)
		:Performance(perf) {}
	Play play;
	double amount;
	int volumeCredits;
};

struct StatementData
{
	int totalVolumeCredits;
	double totalAmount;
	std::string customer;
	std::vector<StatementPerf> performances;
};

std::string statement(const Invoice &invoices, const Plays &plays);

#endif
