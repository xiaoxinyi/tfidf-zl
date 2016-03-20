#include <iostream>

#include "dataset.h"
using namespace std;

int main() {
	Corpus corpus;
	vector<string> filenames = {"shenzhen1.txt",
															"shenzhen2.txt"};

	CorpusUtils::ReadCorpusInput(corpus, filenames);
	CorpusUtils::WriteCorpusOutput(corpus, "corpus.txt");
	CorpusUtils::WriteVocabularyOutput(corpus, "vocabulary.txt");

	cout << "there are " << corpus.getDocuments() << " documents in corpus" << endl;
	cout << "vacabulary size : " << corpus.getVocabSize() << endl;
	cout << "total word number :" << corpus.getWordNo() << endl;

	CorpusUtils::CheckSum(corpus);
	return 0;
}