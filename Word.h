#pragma once
#include <string>
using namespace std;

class Word
{
public:
	Word();
	~Word();

	enum Type {
		DELIMITER,//���
		OPERATOR,//�����
		KEYWORD,//�ؼ���
		IDENTIFIER,//��ʶ��
		CONSTANT,//����
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

