#include <iostream>

#include "dataset.h"
using namespace std;

const bool UNIQUE = true;

int main() {
	Corpus corpus;
	vector<string> filenames = {"shenzhen1.txt",
															"shenzhen2.txt"};

	// Read raw text from filenames.
	CorpusUtils::ReadCorpusInput(corpus, filenames);

	// UNIQUE decide ouput document distinct number of word or total word count.
	CorpusUtils::WriteCorpusOutput(corpus, "corpus.txt", UNIQUE);

	// Write vocabulary into file.
	CorpusUtils::WriteVocabularyOutput(corpus, "vocabulary.txt");

	cout << "there are " << corpus.getDocuments() << " documents in corpus" << endl;
	cout << "vacabulary size : " << corpus.getVocabSize() << endl;
	cout << "total word number :" << corpus.getWordNo() << endl;

	CorpusUtils::CheckSum(corpus);
	return 0;
}