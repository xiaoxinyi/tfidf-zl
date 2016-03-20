#ifndef ZL_DATASET_H__
#define ZL_DATASET_H__ 

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;

// Document contains term_no, total word count,
// count of each word.
class Document {
public:
	Document();

	unordered_map<int, int>& getMutableWordCounts() {
	 return word_counts_; 
	}
	int getWordCount(int word_id);
	void updateWordCount(int word_id, int update = 1);

	int getTermNo() const { return term_no_; }
	void setTermNo(int term_no) { term_no_ = term_no; }

	int getWordNo() const { return word_no_; }
	void setWordNo(int word_no) { word_no_ = word_no; }
	void updateWordNo(int update) { word_no_ += update; }
private:
	// Distinct word number.
	int term_no_;

	// Total word count.
	int word_no_;

	// Word count.
	unordered_map<int, int> word_counts_;
};

class Corpus;

class DocumentUtils {
public:
	// Read filename in to document.
	// Record information to corpus.
	static void ReadDocumentInput(Document& document,
																const string& filename,
																Corpus& corpus);

	static void WriteDocumentOutput(Document& document,
																	ofstream& ofs);
};

// Corpus contains vocabulary size, the total word number,
// ids for each word, all the documents.
class Corpus {
public:
	Corpus();

	Corpus(const Corpus& from) = delete;
	Corpus& operator=(const Corpus& from) = delete;

	int getVocabSize() const { return vocab_size_; }
	void setVocabSize(const int& vocab_size) { vocab_size_ = vocab_size; }
	void updateVocabSize(const int& update) { vocab_size_ += update; }

	int getWordNo() const { return word_no_; }
	void setWordNo(const int& word_no) { word_no_ = word_no; }
	void updateWordNo(int update) { word_no_ += update; }

	unordered_map<string, int>& getMutableWordIds() { return word_ids_; }
	void setWordId(string& word, int id) { word_ids_[word] = id; }
	int getWordId(const string& word);

	void addDocument(Document&& document) { documents_.emplace_back(move(document)); }
	void setDocuments(vector<Document>&& documents) { documents_ = move(documents); }
	int getDocuments() const { return documents_.size(); }
	Document& getMutableDocument(int i) { return documents_[i]; }

private:
	// Distinct word number.
	int vocab_size_;

	// Total word number.
	int word_no_;

	// Word map id.
	unordered_map<string, int> word_ids_;

	// Documents in corpus.
	vector<Document> documents_;
};

class CorpusUtils {
public:
	// Update corpus's vocabulary size, word number,
	// and word ids.
	static void UpdateCorpusFromWord(Corpus& corpus, 
																	 string& word,
																	 int& word_id);
	// Read files into corpus.
	static void ReadCorpusInput(Corpus& corpus,
															vector<string>& filenames);

	static void WriteCorpusOutput(Corpus& corpus, 
																const string& filename);

	static void WriteVocabularyOutput(Corpus& corpus,
																		const string& filename);

	static void CheckSum(Corpus& corpus);
};

#endif