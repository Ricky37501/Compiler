#include "Analyse.h"
#include <fstream>
#include<iostream>
#include "Word.h"
using namespace std;


Analyse::Analyse(const char * filename):
mSize(0),
mFlag(true)
{
	ifstream in(filename, ifstream::binary);
	in.seekg(0,ifstream::end);
	mSize = static_cast<int>(in.tellg());
	in.seekg(0, ifstream::beg);
	mProgram = new char[mSize];
	in.read(mProgram, mSize);
}

Analyse::Analyse() :
	mProgram(nullptr),
	mSize(0),
	mFlag(true)
{
}


Analyse::~Analyse()
{
}

void Analyse::testOutput()
{
	cout << "读取源程序：" << endl;
	for(int i=0;i<mSize;i++){
		cout << mProgram[i];
	}
	cout << endl;
	cout << endl;
}

bool Analyse::isLetter(const char &ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}

bool Analyse::isString(const char &)
{
	return false;
}

bool Analyse::isNumber(const char &ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool Analyse::isOperator(const char & ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '!' || ch == '|' || ch == '&')
		return true;
	else 
		return false;
}

bool Analyse::isDelimiter(const char & ch)
{
	if (ch == '(' || ch == ')' || ch == ';' || ch == '{' || ch == '}')
		return true;
	else
		return false;
}

bool Analyse::isNomeaning(const char &ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') 
		return true;
	else 
		return false;
}

bool Analyse::isKeyword(string s)
{
	for (int i = 0;i < 9;i++) {
		if (mKeyWord[i] == s) {
			return true;
		}
	}
	return false;
}

#ifndef DESIGN
void Analyse::doS(vector<Word>::iterator& i)
{
	//cout << "doS 执行" << endl;
	if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		if (++i == mWords.end()) {
			mFlag = false;
			return;
		}
		if (i->getValue() == "=") {
			if (++i == mWords.end()) {
				mFlag = false;
				return;
			}
			doE(i);
		}
		else {
			cout << "ERROR: 缺少赋值符号‘=’" << endl;
			mFlag = false;
		}
	}
	else {
		cout << "ERROR: 左值应为变量" << endl;
		mFlag = false;
	}

	if (i == mWords.end()) {
		cout << "ERROR: 缺少 ‘ ; ’" << endl;
		mFlag = false;
	}
	else if (i->getValue() != ";") {
		cout << "ERROR: 存在余缀字符 或 没有以 ‘ ; ’作为语句终止符" << endl;
		mFlag = false;
	}
	//cout << "doS 返回" << endl;
}

void Analyse::doE(vector<Word>::iterator& i)
{
	//cout << "doE 执行" << endl;
	if (mFlag == false) {
		return;
	}
	if (i->getValue() == "(" || i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		doT(i);
		doE_(i);
	}
	else {
		cout << "ERROR: 非法表达式！" << endl;
		mFlag = false;
	}
	//cout << "doE 返回" << endl;
}

void Analyse::doE_(vector<Word>::iterator& i)
{
	//cout << "doE' 执行" << endl;
	if (mFlag == false) {
		return;
	}

	if (i->getValue() == "+" || i->getValue() == "-") {
		if (++i == mWords.end()) {
			cout << "ERROR: 语句不完整! " << endl;
			mFlag = false;
			return;
		}
		doT(i);
		doE_(i);
	}

	else if (i->getValue() == ")" || i->getValue() == ";") {
		return;
	}
	//cout << "doE' 返回" << endl;
}

void Analyse::doT(vector<Word>::iterator& i)
{
	//cout << "doT 执行" << endl;
	if (mFlag == false) {
		return;
	}
	if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT || i->getValue() == "(") {
		doF(i);
		doT_(i);
	}
	//cout << "doT 返回" << endl;
}

void Analyse::doT_(vector<Word>::iterator& i)
{
	//cout << "doT' 执行" << endl;
	if (mFlag == false) {
		return;
	}
	if (i->getValue() == "*" || i->getValue() == "/") {
		if (++i == mWords.end()) {
			mFlag = false;
			return;
		}
		doF(i);
		doT_(i);
	}
	else if (i->getValue() == "+" || i->getValue() == "-" || i->getValue() == ")" || i->getValue() == ";") {
		return;
	}
	else {
		cout << "ERROR: 算式不规范！" << endl;
		mFlag = false;
	}
	//cout << "doT' 返回" << endl;
}

void Analyse::doF(vector<Word>::iterator& i)
{
	//cout << "doF 执行" << endl;
	if (mFlag == false) {
		return;
	}

	if (i->getValue() == "(") {
		if (++i == mWords.end())
		{
			cout << "ERROR: 语句不完整！" << endl;
			mFlag = false;
			return;
		}
		doE(i);
		if (i == mWords.end()) {
			cout << "ERROR: 缺少 ‘)’ " << endl;
			mFlag = false;
			return;
		}
		if (i->getValue() == ")") {
			i++;
			return;
		}
		else {
			cout << "ERROR: 应在 '" << i->getValue() << " '前添加 ' ) ' " << endl;
			mFlag = false;
			return;
		}
	}
	else if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		i++;
	}
	else {
		cout << "ERROR: 出错了" << endl;
		mFlag = false;
	}
	//cout << "doF 返回" << endl;
}
#else
void Analyse::doS(vector<Word>::iterator& i) {
	if (i->getValue() == "while" && (i + 1)->getValue() == "(") {
		i += 2;
		doA(i);
	}
	else {
		cout << "单词while拼写错误或者缺少左括号！" << endl;
		mFlag = false;
		return;
	}
	if (i->getValue() == ")" && (i + 1)->getValue() == "{") {
		i += 2;
		doB(i);
	}
	else {
		cout << "缺少右括号“（”或者缺少左花括号“{”！" << endl;
		mFlag = false;
		return;
	}
}

void Analyse::doA(vector<Word>::iterator& i) {
	string tempD;
	string tempC1;
	string tempC2;
	doC(i, tempC1);
	doD(i, tempD);
	doC(i, tempC2);

	mSiyuanshi[mSiyuanshiNum].op = tempD;
	mSiyuanshi[mSiyuanshiNum].arg1 = tempC1;
	mSiyuanshi[mSiyuanshiNum].arg2 = tempC2;
	mSiyuanshi[mSiyuanshiNum].result = "T" + to_string(mSiyuanshiNum + 1);
	mSiyuanshiNum++;

	mSiyuanshi[mSiyuanshiNum].op = "Jump";
	mJumpType = mSiyuanshiNum;
	mSiyuanshiNum++;
}

void Analyse::doD(vector<Word>::iterator& i, string& tempD) {
	tempD = i->getValue();
	i++;
}

void Analyse::doB(vector<Word>::iterator& i) {
	string tempC;
	string tempResult, tempDengyu;
	if (i->getType() == Word::Type::IDENTIFIER) {
		tempResult = i->getValue();
		i++;
	}
	else {
		return;
	}
	if (i->getValue() == "=") {
		tempDengyu = i->getValue();
		i++;
	}
	else {
		return;
	}
	doC(i, tempC);
	mSiyuanshi[mSiyuanshiNum].op = tempDengyu;
	mSiyuanshi[mSiyuanshiNum].arg1 = tempC;
	mSiyuanshi[mSiyuanshiNum].result = tempResult;
	mSiyuanshiNum++;

	mSiyuanshi[mSiyuanshiNum].op = "Jump";
	mSiyuanshi[mSiyuanshiNum].result = "0";// to_string(JumpType);
	mSiyuanshiNum++;

	mSiyuanshi[mJumpType].result = to_string(mSiyuanshiNum);
}

void Analyse::doC(vector<Word>::iterator& i, string& tempC) {
	string tempE;
	queue<string> tempG;

	int temp = 0;
	doE(i, tempE);
	doG(i, tempG);

	if (!tempG.empty()) {
		while (!tempG.empty()) {
			if (temp == 0) {
				mSiyuanshi[mSiyuanshiNum].arg1 = tempE;
				mSiyuanshi[mSiyuanshiNum].op = tempG.front();
				tempG.pop();
				mSiyuanshi[mSiyuanshiNum].arg2 = tempG.front();
				tempG.pop();
				mSiyuanshi[mSiyuanshiNum].result = "T" + to_string(mSiyuanshiNum + 1);
				mSiyuanshiNum++;
				temp++;
			}
			else {
				mSiyuanshi[mSiyuanshiNum].arg1 = mSiyuanshi[mSiyuanshiNum - 1].result;
				mSiyuanshi[mSiyuanshiNum].op = tempG.front();
				tempG.pop();
				mSiyuanshi[mSiyuanshiNum].arg2 = tempG.front();
				tempG.pop();
				mSiyuanshi[mSiyuanshiNum].result = "T" + to_string(mSiyuanshiNum + 1);
				mSiyuanshiNum++;
				temp++;
			}
		}
		tempC = mSiyuanshi[mSiyuanshiNum - 1].result;
	}
	else {
		tempC = tempE;
	}
}

void Analyse::doE(vector<Word>::iterator& i, string& tempE) {
	string tempF;
	doF(i, tempF);

	queue<string> tempH;
	doH(i, tempH);
	int temp = 0;
	if (!tempH.empty()) {
		while (!tempH.empty()) {
			if (temp == 0) {
				mSiyuanshi[mSiyuanshiNum].arg1 = tempF;
				mSiyuanshi[mSiyuanshiNum].op = tempH.front();
				tempH.pop();
				mSiyuanshi[mSiyuanshiNum].arg2 = tempH.front();
				tempH.pop();
				mSiyuanshi[mSiyuanshiNum].result = "T" + to_string(mSiyuanshiNum + 1);
				mSiyuanshiNum++;
				temp++;
			}
			else {
				mSiyuanshi[mSiyuanshiNum].arg1 = mSiyuanshi[mSiyuanshiNum - 1].result;
				mSiyuanshi[mSiyuanshiNum].op = tempH.front();
				tempH.pop();
				mSiyuanshi[mSiyuanshiNum].arg2 = tempH.front();
				tempH.pop();
				mSiyuanshi[mSiyuanshiNum].result = "T" + to_string(mSiyuanshiNum + 1);
				mSiyuanshiNum++;
				temp++;
			}
		}
		tempE = mSiyuanshi[mSiyuanshiNum - 1].result;
	}
	else {
		tempE = tempF;
	}
}

void Analyse::doG(vector<Word>::iterator& i, queue<string>& tempG) {

	if (i->getValue() == "+" || i->getValue() == "-") {
		//cout << word[nowword].oneword << "\t正确！" << endl;

		tempG.push(i->getValue());

		i++;
		string tempE;
		doE(i, tempE);
		tempG.push(tempE);

		doG(i, tempG);

		return;
	}
	else
		return;
}

void Analyse::doF(vector<Word>::iterator& i, string& tempF) {
	if (i->getValue() == "(") {
		//cout << word[nowword].oneword << "\t正确！" << endl;
		string tempC;
		i++;
		doC(i, tempC);
		if (i->getValue() != ")") {
			cout << "错误：没输入右括号！" << endl;
			mFlag = false;
			return;
		}
		else {
			//cout << word[nowword].oneword << "\t正确！" << endl;
			tempF = tempC;
			i++;
		}

	}
	else if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		//cout << word[nowword].oneword << "\t正确！" << endl;

		tempF = i->getValue();

		i++;
	}
	else {

		cout << "错误：" << (i - 1)->getType() << "：" << (i - 1)->getValue() << " 的后面不能接 " << i->getType() << "：" << i->getValue() << endl;
		mFlag = false;
		i++;
		doF(i, tempF);
	}
}

void Analyse::doH(vector<Word>::iterator& i, queue<string>& tempH) {
	if (i->getValue() == "*" || i->getValue() == "/") {
		//cout << word[nowword].oneword << "\t正确！" << endl;

		tempH.push(i->getValue());
		i++;

		string tempF;
		doF(i, tempF);

		tempH.push(tempF);

		doH(i, tempH);
		return;
	}
	else
		return;
}
#endif // !DESIGN


void Analyse::LexicalAnalysis()
{
	bool end = false;
	int count = 0;
	int mode = 0; //0：扫描   1：发现字串   2：记录常量数字   3：记录标识符或关键字  4：记录引号引起的常量字符串  5：记录运算符或界符  
	Word w;
	string value = "";
	while (true) {
		switch (mode){
			case 0: {
				if (!isNomeaning(mProgram[count])) {
					mode = 1; //发现字串
				}
				else {
					count++;
				}
				break;
			}
			case 1: {
				if (isNumber(mProgram[count])) {
					mode = 2;//常量数字
				}
				else if (isLetter(mProgram[count])) {
					mode = 3;//是标识符或关键字
				}
				else if (mProgram[count] == '"') {
					mode = 4;//是常量字符串
					count++;
				}
				else {
					mode = 5;//是运算符或界符
				}
				break;
			}
			case 2: {
				if (!isNumber(mProgram[count]) ){
					mode = 0; //扫描
					w.set(Word::CONSTANT, value);
					mWords.push_back(w);
					value = "";
				}
				else {
					value += mProgram[count];
					count++;
				}
				break;
			}
			case 3: {//标识符或关键字
				if (!isLetter(mProgram[count]) &&!isNumber(mProgram[count])) {
					mode = 0; //扫描
					if (isKeyword(value)) {
						w.set(Word::KEYWORD, value);
					}
					else {
						w.set(Word::IDENTIFIER, value);
					}
					mWords.push_back(w);
					value = "";
				}
				else {
					value += mProgram[count];
					count++;
				}
				break;
			}
			case 4: {//常量字符串
				if (mProgram[count] == '"') {
					w.set(Word::CONSTANT, value);
					mWords.push_back(w);
					value = "";
					count++;
					mode = 0;
				}
				else {
					value += mProgram[count];
					count++;
				}
				break;
			}
			case 5: {//界符
				value += mProgram[count];
				if (isDelimiter(mProgram[count])) {
					w.set(Word::DELIMITER, value);
				}
				else {
					w.set(Word::OPERATOR, value);
				}
				mWords.push_back(w);
				value = "";
				count++;
				mode = 0;//扫描
				break;
			}
		}//switch
		if (count >= mSize) {
			break;
		}
	}//while
}

void Analyse::GrammaticalAnalysis()
{
	auto iterator = mWords.begin();
#ifndef DESIGN
	while (iterator->getValue() != "=") {
		iterator++;
	}
	iterator--;
	doS(iterator);
	if (mFlag) {
		cout << "赋值语句语法正确" << endl;
	}
	else {
		cout << "赋值语句语法错误" << endl;
	}
#else
	while (iterator->getValue() != "while") {
		iterator++;
	}
	doS(iterator);
	iterator--;
	if (mFlag) {
		cout << "while循环语句语法正确" << endl;
	}
	else {
		cout << "while循环语句语法错误" << endl;
	}
	cout << "四元式：" << endl;
	for (int i = 0; i <= mSiyuanshiNum; i++) {
		cout << i << "\t" << mSiyuanshi[i].op << "\t　" << mSiyuanshi[i].arg1 << "\t　" << mSiyuanshi[i].arg2 << "\t　" << mSiyuanshi[i].result << endl;
	}
#endif // !DESIGN
}
