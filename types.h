#ifndef _TYPES_H
#define _TYPES_H

#include<string>
#include<vector>
#include<map>

// 剧团剧目数据
struct Play
{
	std::string name;
	std::string type;
};

typedef std::map<std::string, Play> Plays;

// 一场演出数据
struct Performance
{
	std::string playID;
	int audience;
};

// 总账单数据
struct Invoice
{
	std::string customer;
	std::vector<Performance> performances;
};

#endif

