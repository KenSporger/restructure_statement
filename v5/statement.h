#ifndef _STATEMENTV5_H
#define _STATEMENTV5_H

#include "../types.h"
#include "createStatementData.h"

std::string statement(const Invoice &invoices, const Plays &plays);
std::string htmlStatement(const Invoice &invoices, const Plays &plays);

#endif
