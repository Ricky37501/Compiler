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
	//first(S)={ i }
	//first(E)=first(T)=first(F)={ i , ( }
	//first(E')={+, -, ��}
	//first(T')={*, /, ��}
	//follow(S)={ # }
	//follow(E)=follow(E')={ ), # }
	//follow(T)=follow(T')={+, - , ) , #}
	//follow(F)={+, / , ), #}

	//select��S��i = E��={ i }
	//select��E��TE�䣩={ i , ( }
	//select��E'��-TE�� | +TE' ��={ + , - }
	//select��E'->�ţ�={ ) ,# }
	//select��T��FT�䣩={ i , ( }
	//select��T���* FT�� | /FT' ��={* , /}
	//select��T����ţ�={+,-, ) , #}
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
	//�����ķ�:
	//first(S)={ while }
	//first(A)=first(E)=first(T)=first(F)={ ( , i } 
	//first(D)={ <,> }
	//first(B) = { i }
	//first(E')={+, -, ��}
	//first(T')={*, /, ��}
	//follow(S)={ # }
	//follow(A)={ ) }
	//follow(D) = { (��i }
	//follow(B)={ } }
	//follow(E)=follow(E')={  ) ,<,>, } }
	//follow(T)=follow(T')={ +,-, ) , <,>, } }
	//follow(F)={ *, / ,+, - , ) , <,>, }}

	//select(S��while(A){B})={ while( }
	//select (A��EDE)={ ( , i }
	//select (R��< | >)={ <,> }
	//select (B��i=E)={ i }
	//select (E��TE')={ ( , i }

	//select (E' �� +TE')={ + }
	//select (E' ��| -TE')={ - }
	//select (E' �� ��)={ ) ,<,>, }, ; }

	//select (T��FT')={ (, i }

	//select (T���  /FT')={ / }
	//select (T���*FT' ')={ * }
	//select (T�����)={ +,-, ) , <,>, } , ; }

	//select (F�� i��={ i}
	//select (F��(E)��={ ( }

	//S->while(A){B}
	void doS(vector<Word>::iterator& i);
	//A��ERE
	void doA(vector<Word>::iterator& i);
	//R��< | >
	void doR(vector<Word>::iterator& i, string& tempR);
	//B��i=E
	void doB(vector<Word>::iterator& i);
	//E��TE'
	void doE(vector<Word>::iterator& i, string& tempC);
	//T��FT'
	void doT(vector<Word>::iterator& i, string& tempT);
	//E' �� +TE' | -TE' | ��
	void doE_(vector<Word>::iterator& i, queue<string>& tempE_);
	//F �� (E) | i 
	void doF(vector<Word>::iterator& i, string& tempF);
	//T' �� *FT' | /FT' | ��
	void doT_(vector<Word>::iterator& i, queue<string>& tempT);
#endif // DESIGN

	//ִ�дʷ�����
	void LexicalAnalysis();
	//ִ���﷨����
	void GrammaticalAnalysis();

	//��Ԫʽ��OPΪ��������result=arg1+arg2;
	struct Siyuanshi {
		string op;
		string arg1;
		string arg2;
		string result;
	};
	Siyuanshi m4[100];
	int m4Num = 0;//��Ԫʽ����
	//��¼����λ��
	//��¼ִ�������ת��λ��
	int mJumpOccupy1 = 0;
	//��¼����A��ת��λ��
	int mJumpOccupy2 = 0;

	vector<Word> mWords;//��ŵ���
private:
	string mKeyWord[9] = {"int","double","float","void","return","if","for","while","else"};//���ùؼ���
	char* mProgram;//Դ����
	int mSize;//Դ���򳤶�
	bool mFlag;//�﷨������ȷ���
};

