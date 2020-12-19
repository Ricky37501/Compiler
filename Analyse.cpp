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
	cout << "��ȡԴ����" << endl;
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
	//cout << "doS ִ��" << endl;
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
			cout << "ERROR: ȱ�ٸ�ֵ���š�=��" << endl;
			mFlag = false;
		}
	}
	else {
		cout << "ERROR: ��ֵӦΪ����" << endl;
		mFlag = false;
	}

	if (i == mWords.end()) {
		cout << "ERROR: ȱ�� �� ; ��" << endl;
		mFlag = false;
	}
	else if (i->getValue() != ";") {
		cout << "ERROR: ������׺�ַ� �� û���� �� ; ����Ϊ�����ֹ��" << endl;
		mFlag = false;
	}
	//cout << "doS ����" << endl;
}

void Analyse::doE(vector<Word>::iterator& i)
{
	//cout << "doE ִ��" << endl;
	if (mFlag == false) {
		return;
	}
	if (i->getValue() == "(" || i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		doT(i);
		doE_(i);
	}
	else {
		cout << "ERROR: �Ƿ����ʽ��" << endl;
		mFlag = false;
	}
	//cout << "doE ����" << endl;
}

void Analyse::doE_(vector<Word>::iterator& i)
{
	//cout << "doE' ִ��" << endl;
	if (mFlag == false) {
		return;
	}

	if (i->getValue() == "+" || i->getValue() == "-") {
		if (++i == mWords.end()) {
			cout << "ERROR: ��䲻����! " << endl;
			mFlag = false;
			return;
		}
		doT(i);
		doE_(i);
	}

	else if (i->getValue() == ")" || i->getValue() == ";") {
		return;
	}
	//cout << "doE' ����" << endl;
}

void Analyse::doT(vector<Word>::iterator& i)
{
	//cout << "doT ִ��" << endl;
	if (mFlag == false) {
		return;
	}
	if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT || i->getValue() == "(") {
		doF(i);
		doT_(i);
	}
	//cout << "doT ����" << endl;
}

void Analyse::doT_(vector<Word>::iterator& i)
{
	//cout << "doT' ִ��" << endl;
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
		cout << "ERROR: ��ʽ���淶��" << endl;
		mFlag = false;
	}
	//cout << "doT' ����" << endl;
}

void Analyse::doF(vector<Word>::iterator& i)
{
	//cout << "doF ִ��" << endl;
	if (mFlag == false) {
		return;
	}

	if (i->getValue() == "(") {
		if (++i == mWords.end())
		{
			cout << "ERROR: ��䲻������" << endl;
			mFlag = false;
			return;
		}
		doE(i);
		if (i == mWords.end()) {
			cout << "ERROR: ȱ�� ��)�� " << endl;
			mFlag = false;
			return;
		}
		if (i->getValue() == ")") {
			i++;
			return;
		}
		else {
			cout << "ERROR: Ӧ�� '" << i->getValue() << " 'ǰ��� ' ) ' " << endl;
			mFlag = false;
			return;
		}
	}
	else if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		i++;
	}
	else {
		cout << "ERROR: ������" << endl;
		mFlag = false;
	}
	//cout << "doF ����" << endl;
}
#else
void Analyse::doS(vector<Word>::iterator& i) {
	if (i->getValue() == "while" && (i + 1)->getValue() == "(") {
		i += 2;
		doA(i);
	}
	else {
		cout << "����whileƴд�������ȱ�������ţ�" << endl;
		mFlag = false;
		return;
	}
	if (i->getValue() == ")" && (i + 1)->getValue() == "{") {
		i += 2;
		doB(i);
	}
	else {
		cout << "ȱ�������š���������ȱ�������š�{����" << endl;
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
		//cout << word[nowword].oneword << "\t��ȷ��" << endl;

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
		//cout << word[nowword].oneword << "\t��ȷ��" << endl;
		string tempC;
		i++;
		doC(i, tempC);
		if (i->getValue() != ")") {
			cout << "����û���������ţ�" << endl;
			mFlag = false;
			return;
		}
		else {
			//cout << word[nowword].oneword << "\t��ȷ��" << endl;
			tempF = tempC;
			i++;
		}

	}
	else if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		//cout << word[nowword].oneword << "\t��ȷ��" << endl;

		tempF = i->getValue();

		i++;
	}
	else {

		cout << "����" << (i - 1)->getType() << "��" << (i - 1)->getValue() << " �ĺ��治�ܽ� " << i->getType() << "��" << i->getValue() << endl;
		mFlag = false;
		i++;
		doF(i, tempF);
	}
}

void Analyse::doH(vector<Word>::iterator& i, queue<string>& tempH) {
	if (i->getValue() == "*" || i->getValue() == "/") {
		//cout << word[nowword].oneword << "\t��ȷ��" << endl;

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
	int mode = 0; //0��ɨ��   1�������ִ�   2����¼��������   3����¼��ʶ����ؼ���  4����¼��������ĳ����ַ���  5����¼���������  
	Word w;
	string value = "";
	while (true) {
		switch (mode){
			case 0: {
				if (!isNomeaning(mProgram[count])) {
					mode = 1; //�����ִ�
				}
				else {
					count++;
				}
				break;
			}
			case 1: {
				if (isNumber(mProgram[count])) {
					mode = 2;//��������
				}
				else if (isLetter(mProgram[count])) {
					mode = 3;//�Ǳ�ʶ����ؼ���
				}
				else if (mProgram[count] == '"') {
					mode = 4;//�ǳ����ַ���
					count++;
				}
				else {
					mode = 5;//�����������
				}
				break;
			}
			case 2: {
				if (!isNumber(mProgram[count]) ){
					mode = 0; //ɨ��
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
			case 3: {//��ʶ����ؼ���
				if (!isLetter(mProgram[count]) &&!isNumber(mProgram[count])) {
					mode = 0; //ɨ��
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
			case 4: {//�����ַ���
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
			case 5: {//���
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
				mode = 0;//ɨ��
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
		cout << "��ֵ����﷨��ȷ" << endl;
	}
	else {
		cout << "��ֵ����﷨����" << endl;
	}
#else
	while (iterator->getValue() != "while") {
		iterator++;
	}
	doS(iterator);
	iterator--;
	if (mFlag) {
		cout << "whileѭ������﷨��ȷ" << endl;
	}
	else {
		cout << "whileѭ������﷨����" << endl;
	}
	cout << "��Ԫʽ��" << endl;
	for (int i = 0; i <= mSiyuanshiNum; i++) {
		cout << i << "\t" << mSiyuanshi[i].op << "\t��" << mSiyuanshi[i].arg1 << "\t��" << mSiyuanshi[i].arg2 << "\t��" << mSiyuanshi[i].result << endl;
	}
#endif // !DESIGN
}
