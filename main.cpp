#include<iostream>
#include<vector>
#include "Analyse.h"
#include"Word.h"
using namespace std;

int main() {
	Analyse a("program.txt");
	a.testOutput();
	a.LexicalAnalysis();
	
	cout << "�ʷ�����������£�" << endl;
	for (vector<Word>::iterator i = a.mWords.begin();i != a.mWords.end();i++) {
		i->printType();
		cout  << i->getValue() << endl;
	}
	cout << endl;

	cout << "ִ���﷨������" << endl;
	a.GrammaticalAnalysis();

	system("pause");
	return 0;
}