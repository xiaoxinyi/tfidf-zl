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
	
	return 0;
}