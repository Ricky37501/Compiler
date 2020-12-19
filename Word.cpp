#include "Word.h"
#include <iostream>
using namespace std;

Word::Word() :mType(NONE),mValue(""){

}

Word::~Word(){

}

void Word::set(Type type, string value)
{
	mType = type;
	mValue = value;
}

void Word::printType()
{
	switch (mType)
	{
	case CONSTANT:
		cout << "常量："  ;
		break;	
	case OPERATOR:
		cout << "运算符："  ;
		break;	
	case DELIMITER:
		cout << "界符："  ;
		break;	
	case IDENTIFIER:
		cout << "标识符："  ;	
		break;
	case KEYWORD:
		cout << "关键字："  ;
		break;
	default:
		break;
	}

}

Word::Type Word::getType()
{
	return mType;
}

string Word::getValue()
{
	return mValue;
}
