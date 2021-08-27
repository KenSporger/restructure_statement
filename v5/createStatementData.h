#ifndef _STATEMENTDATAV5_H
#define _STATEMENTDATAV5_H

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

StatementData createStatementData(const Invoice &invoices, const Plays &plays);

#endif
