#pragma once
#include <string>
using namespace std;

class Word
{
public:
	Word();
	~Word();

	enum Type {
		DELIMITER,//界符
		OPERATOR,//运算符
		KEYWORD,//关键字
		IDENTIFIER,//标识符
		CONSTANT,//常数
		NONE
	};
	void set(Word::Type, string);
	void printType();
	Type getType();
	string getValue();
private:
	Type mType;
	string mValue;
};

