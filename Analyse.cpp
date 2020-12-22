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
		if (mFlag == false || i == mWords.end()) {
			mFlag = false;
			return;
		}
	}
	else {
		cout << "ERROR:�Ƿ��ؼ��� �� ȱʧ��(��" << endl;
		mFlag = false;
		return;
	}
	if (i->getValue() == ")" && (i + 1)->getValue() == "{") {
		i += 2;
		doB(i);
		if (mFlag == false || i==mWords.end()) {
			mFlag = false;
			return;
		}
	}
	else {
		cout << " ERROR : ȱ�١�������{��" << endl;
		mFlag = false;
		return;
	}
	if (i->getValue() != "}" ) {
		cout << "ERROR : ȱ�١�}��" << endl;
		mFlag = false;
	}
}

void Analyse::doA(vector<Word>::iterator& i) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	string op_R;
	string arg_1;
	string arg_2;
	doE(i, arg_1);
	doR(i, op_R);
	doE(i, arg_2);

	m4[m4Num].op = "jump"+op_R;
	m4[m4Num].arg1 = arg_1;
	m4[m4Num].arg2 = arg_2;
	mJumpOccupy2 = m4Num;
	m4Num++;
	m4[m4Num].op = "jump";
	mJumpOccupy1 = m4Num;
	m4Num++;
}

void Analyse::doR(vector<Word>::iterator& i, string& op_R) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	if (i->getValue() == "<" || i->getValue() == ">"){
		op_R = i->getValue();
		i++;
	}
	else {
		mFlag = false;
		cout << "ERROR : �Ƿ���ϵ�����" << endl;
	}
}

void Analyse::doB(vector<Word>::iterator& i) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	string id_E;
	string id;
	if (i->getType() == Word::Type::IDENTIFIER) {
		id = i->getValue();
		i++;
	}
	else {
		mFlag = false;
		cout << "ERROR : ��ֵ�����ӦΪ�ɸı����ֵ" << endl;
		return;
	}
	if (i->getValue() == "=") {
		i++;
	}
	else {
		mFlag = false;
		cout << "ERROR : ȱ�ٸ�ֵ�� "<<endl;
		return;
	}
	doE(i, id_E);
	if (i->getValue() == ";") {
		i++;
	}
	else {
		mFlag = false;
		cout << "ERROR : ȱ�� ��;��" << endl;
		return;
	}
	m4[mJumpOccupy2].result = to_string(m4Num-1);
	m4[m4Num].op = "=";
	m4[m4Num].arg1 = id_E;
	m4[m4Num].result = id;
	m4Num++;

	m4[m4Num].op = "jump";
	m4[m4Num].result = "0";
	m4Num++;

	m4[mJumpOccupy1].result = to_string(m4Num);
}

void Analyse::doE(vector<Word>::iterator& i, string& id_E) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	string id_T;
	queue<string> expr_E_;
	if (i->getValue() == "(" || i->getType() == Word::IDENTIFIER) {
		doT(i, id_T);
		doE_(i, expr_E_);
		bool isFirst = true;
		if (!expr_E_.empty()) {
			while (!expr_E_.empty()) {
				if (isFirst) { //  id_T   op   arg   T?
					isFirst = false;
					m4[m4Num].arg1 = id_T;
					m4[m4Num].op = expr_E_.front();
					expr_E_.pop();
					m4[m4Num].arg2 = expr_E_.front();
					expr_E_.pop();
					m4[m4Num].result = "t" + to_string(m4Num);
					m4Num++;
				}
				else {  //  T?  op  arg  T??
					m4[m4Num].arg1 = m4[m4Num - 1].result;
					m4[m4Num].op = expr_E_.front();
					expr_E_.pop();
					m4[m4Num].arg2 = expr_E_.front();
					expr_E_.pop();
					m4[m4Num].result = "t" + to_string(m4Num);
					m4Num++;
				}
			}
			id_E = m4[m4Num - 1].result;
		}
		else {
			id_E = id_T;
		}
	}
	else {
		mFlag = false;
		cout << "ERROR : �Ƿ����ʽ" << endl;
	}
}

void Analyse::doE_(vector<Word>::iterator& i, queue<string>& expr_E_) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	if (i->getValue() == "+" || i->getValue() == "-") {
		expr_E_.push(i->getValue());
		i++;
		string id_T;
		doT(i, id_T);
		expr_E_.push(id_T);
		doE_(i, expr_E_);
		return;
	}
	else if (i->getValue() == ")" || i->getValue() == "<" || i->getValue() == ">" || i->getValue() == "}" || i->getValue() == ";") {
		return;
	}
	else {
		mFlag = false;
		return;
	}
}

void Analyse::doT(vector<Word>::iterator& i, string& id_T) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	if (i->getValue() == "(" || i->getType() == Word::IDENTIFIER || i->getType()==Word::CONSTANT) {
		string id_F;
		doF(i, id_F);
		queue<string> expr_T_;
		doT_(i, expr_T_);

		bool isFirst = true;
		//ƴ��id_F��expr_T_
		if (!expr_T_.empty()) {
			while (!expr_T_.empty()) {
				if (isFirst) { // id_F  op  arg  T?
					isFirst = false;
					m4[m4Num].arg1 = id_F;
					m4[m4Num].op = expr_T_.front();
					expr_T_.pop();
					m4[m4Num].arg2 = expr_T_.front();
					expr_T_.pop();
					m4[m4Num].result = "t" + to_string(m4Num);
					m4Num++;
					//temp++;
				}
				else {         // T?  op  arg2  T??
					m4[m4Num].arg1 = m4[m4Num - 1].result;
					m4[m4Num].op = expr_T_.front();
					expr_T_.pop();
					m4[m4Num].arg2 = expr_T_.front();
					expr_T_.pop();
					m4[m4Num].result = "t" + to_string(m4Num);
					m4Num++;
					//temp++;
				}
			}
			id_T = m4[m4Num - 1].result;
		}
		//expr_T_Ϊ��
		else {
			id_T = id_F;
		}
	}
	else {
		mFlag = false;
		cout << "ERROR : �Ƿ����ʽ" << endl;
		return;
	}
}

void Analyse::doT_(vector<Word>::iterator& i, queue<string>& id_T_) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	if (i->getValue() == "*" || i->getValue() == "/") {
		id_T_.push(i->getValue());
		i++;
		string id_F;
		doF(i, id_F);
		id_T_.push(id_F);
		doT_(i, id_T_);
		return;
	}
	else if (i->getValue() =="+" || i->getValue() == "-" || i->getValue() == ")" || i->getValue() == ">" || i->getValue() == "<" || i->getValue() == "}" || i->getValue() == ";") {
		return;
	}
	else {
		mFlag = false;
		return;
	}
}

void Analyse::doF(vector<Word>::iterator& i, string& id_F) {
	if (mFlag == false || i == mWords.end()) {
		mFlag = false;
		return;
	}
	if (i->getValue() == "(") {
		string id_E;
		i++;
		doE(i, id_E);
		if (i->getValue() != ")") {
			cout << "ERROR : ȱ�� ��" << endl;
			mFlag = false;
			return;
		}
		else {
			id_F = id_E;
			i++;
		}
	}
	else if (i->getType() == Word::Type::IDENTIFIER || i->getType() == Word::Type::CONSTANT) {
		id_F = i->getValue();
		i++;
	}
	else {
		cout << "ERROR : " << (i - 1)->getType() << "��" << (i - 1)->getValue() << " �ĺ��治�ܽ� " << i->getType() << "��" << i->getValue() << endl;
		mFlag = false;
		//i++;
		//doF(i, tempF);
		return;
	}
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
	if (mFlag) {
		cout << "\n-----------------��Ԫʽ----------------" << endl;
		for (int i = 0; i <= m4Num; i++) {
			cout << i << "\t" << m4[i].op << "\t��" << m4[i].arg1 << "\t��" << m4[i].arg2 << "\t��" << m4[i].result << endl;
		}
	}
#endif // !DESIGN
}
