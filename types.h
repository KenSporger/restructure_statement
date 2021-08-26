#ifndef _TYPES_H
#define _TYPES_H

#include<string>
#include<vector>
#include<map>

// ���ž�Ŀ����
struct Play
{
	std::string name;
	std::string type;
};

typedef std::map<std::string, Play> Plays;

// һ���ݳ�����
struct Performance
{
	std::string playID;
	int audience;
};

// ���˵�����
struct Invoice
{
	std::string customer;
	std::vector<Performance> performances;
};

#endif

