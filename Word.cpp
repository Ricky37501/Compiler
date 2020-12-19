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
		cout << "������"  ;
		break;	
	case OPERATOR:
		cout << "�������"  ;
		break;	
	case DELIMITER:
		cout << "�����"  ;
		break;	
	case IDENTIFIER:
		cout << "��ʶ����"  ;	
		break;
	case KEYWORD:
		cout << "�ؼ��֣�"  ;
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
