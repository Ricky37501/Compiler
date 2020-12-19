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
	//读取源程序文件，获取代码字符串
	Analyse(const char*);
	Analyse();
	~Analyse();
	//输出读入的源程序
	void testOutput();

	bool isLetter(const char&);//字母
	bool isString(const char&);//常量字符串
	bool isNumber(const char&);//数字
	bool isOperator(const char&);//运算符
	bool isDelimiter(const char&);//界符
	bool isNomeaning(const char&);//空格或回车
	bool isKeyword(string);//关键字

#ifndef DESIGN
	//分析文法：
	//first(E)=first(T)=first(F)={ i , ( }
	//first(E')={+, -, ε}
	//first(T')={*, /, ε}
	//follow(E)=follow(E')={ ) }
	//follow(T)=follow(T')={+, - , )}
	//follow(F)={+,/}

	//select（S→i = E）={ i }
	//select（E→TE′）={ i , ( }
	//select（E'->-TE′ | +TE' ）={ + , - }
	//select（E'->ε）={ ) }
	//select（T→FT′）={ i , ( }
	//select（T′→* FT′ | /FT' ）={* , /}
	//select（T′→ε）={+,-, )}
	//select（F→(E) | i）={ ( , i }

	//非终结符处理程序
	//S→i=E
	void doS(vector<Word>::iterator& i);
	//E→TE′
	void doE(vector<Word>::iterator& i);
	//E′→-TE′ | +TE' | ε
	void doE_(vector<Word>::iterator& i);
	//T→FT′
	void doT(vector<Word>::iterator& i);
	//T′→*FT′ | /FT' |  ε
	void doT_(vector<Word>::iterator& i);
	//F→(E) | i
	void doF(vector<Word>::iterator& i);
#else
	//四元式：OP为操作符，result=arg1+arg2;
	struct Siyuanshi {
		string op;
		string arg1;
		string arg2;
		string result;
	};
	Siyuanshi mSiyuanshi[100];
	int mSiyuanshiNum = 0;//四元式个数
	int mJumpType = 0;

	//S->while(A){B}
	void doS(vector<Word>::iterator& i);
	//A->CDC
	void doA(vector<Word>::iterator& i);
	//D->优先关系
	void doD(vector<Word>::iterator& i, string& tempD);
	//B->i=C;						//B->i=E
	void doB(vector<Word>::iterator& i);
	//C-> EG						//E->TE'
	void doC(vector<Word>::iterator& i, string& tempC);
	//E -> FH						//T->FT'
	void doE(vector<Word>::iterator& i, string& tempE);
	//G -> +EG | -EG | ε		//E' -> +TE' | -TE' | ε
	void doG(vector<Word>::iterator& i, queue<string>& tempG);
	//F -> (C) | i | n				//F -> (E) | i 
	void doF(vector<Word>::iterator& i, string& tempF);
	//H -> *FH | /FH | ε		//T' -> *FT' | /FT' | ε
	void doH(vector<Word>::iterator& i, queue<string>& tempH);
#endif // DESIGN

	//执行词法分析
	void LexicalAnalysis();
	//执行语法分析
	void GrammaticalAnalysis();

	vector<Word> mWords;//存放单词
private:

	string mKeyWord[9] = {"int","double","float","void","return","if","for","while","else"};//设置关键字
	char* mProgram;//源程序
	int mSize;//源程序长度
	bool mFlag;//语法分析正确与否
};

