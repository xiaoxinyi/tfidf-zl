#include <iostream>
#include "dataset.h"
using namespace std;

int main() {
	Corpus corpus("corpus.txt", "vocabulary-dict.txt");
	Document doc1("shenzhen1.txt", corpus);
	Document doc2("shenzhen2.txt", corpus);

	cout << doc1.doc_length_ << endl;
	cout << doc2.doc_length_ << endl;
	corpus.write_docs();
	corpus.write_vocabulary_dictionary();
	return 0;
}