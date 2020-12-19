#pragma once
#include<string>
#include<vector>
#include<queue>
using namespace std;
class Word;

#define DESIGN

class Analyse
{
public:
	//��ȡԴ�����ļ�����ȡ�����ַ���
	Analyse(const char*);
	Analyse();
	~Analyse();
	//��������Դ����
	void testOutput();

	bool isLetter(const char&);//��ĸ
	bool isString(const char&);//�����ַ���
	bool isNumber(const char&);//����
	bool isOperator(const char&);//�����
	bool isDelimiter(const char&);//���
	bool isNomeaning(const char&);//�ո��س�
	bool isKeyword(string);//�ؼ���

#ifndef DESIGN
	//�����ķ���
	//first(E)=first(T)=first(F)={ i , ( }
	//first(E')={+, -, ��}
	//first(T')={*, /, ��}
	//follow(E)=follow(E')={ ) }
	//follow(T)=follow(T')={+, - , )}
	//follow(F)={+,/}

	//select��S��i = E��={ i }
	//select��E��TE�䣩={ i , ( }
	//select��E'->-TE�� | +TE' ��={ + , - }
	//select��E'->�ţ�={ ) }
	//select��T��FT�䣩={ i , ( }
	//select��T���* FT�� | /FT' ��={* , /}
	//select��T����ţ�={+,-, )}
	//select��F��(E) | i��={ ( , i }

	//���ս���������
	//S��i=E
	void doS(vector<Word>::iterator& i);
	//E��TE��
	void doE(vector<Word>::iterator& i);
	//E���-TE�� | +TE' | ��
	void doE_(vector<Word>::iterator& i);
	//T��FT��
	void doT(vector<Word>::iterator& i);
	//T���*FT�� | /FT' |  ��
	void doT_(vector<Word>::iterator& i);
	//F��(E) | i
	void doF(vector<Word>::iterator& i);
#else
	//��Ԫʽ��OPΪ��������result=arg1+arg2;
	struct Siyuanshi {
		string op;
		string arg1;
		string arg2;
		string result;
	};
	Siyuanshi mSiyuanshi[100];
	int mSiyuanshiNum = 0;//��Ԫʽ����
	int mJumpType = 0;

	//S->while(A){B}
	void doS(vector<Word>::iterator& i);
	//A->CDC
	void doA(vector<Word>::iterator& i);
	//D->���ȹ�ϵ
	void doD(vector<Word>::iterator& i, string& tempD);
	//B->i=C;						//B->i=E
	void doB(vector<Word>::iterator& i);
	//C-> EG						//E->TE'
	void doC(vector<Word>::iterator& i, string& tempC);
	//E -> FH						//T->FT'
	void doE(vector<Word>::iterator& i, string& tempE);
	//G -> +EG | -EG | ��		//E' -> +TE' | -TE' | ��
	void doG(vector<Word>::iterator& i, queue<string>& tempG);
	//F -> (C) | i | n				//F -> (E) | i 
	void doF(vector<Word>::iterator& i, string& tempF);
	//H -> *FH | /FH | ��		//T' -> *FT' | /FT' | ��
	void doH(vector<Word>::iterator& i, queue<string>& tempH);
#endif // DESIGN

	//ִ�дʷ�����
	void LexicalAnalysis();
	//ִ���﷨����
	void GrammaticalAnalysis();

	vector<Word> mWords;//��ŵ���
private:

	string mKeyWord[9] = {"int","double","float","void","return","if","for","while","else"};//���ùؼ���
	char* mProgram;//Դ����
	int mSize;//Դ���򳤶�
	bool mFlag;//�﷨������ȷ���
};

