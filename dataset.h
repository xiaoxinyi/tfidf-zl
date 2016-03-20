#ifndef ZL_DATASET_H__
#define ZL_DATASET_H__ 

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;

class Document;

class Corpus {
public:
	int vocab_size_;
	string corpus_file_name_;
	string vocab_dict_file_name_;
	unordered_map<string, int> word_to_id_dict_;
	vector<Document> docs_vec_;


	Corpus(string corpus_file_name, string vocab_dict_file_name);
	bool load_vocab_dict();
	void write_docs();
	void write_vocabulary_dictionary();
	void load_tfidf_corpus();
};

class Document {
public:
	string doc_file_name_;
	unordered_map<int, int> word_to_count_;
	int doc_length_;

	Document(string file_name, Corpus& corpus);
	Document() {}
	void load_raw_text(Corpus& corpus);
	void process_raw_text(string text, Corpus& corpus);
	void write_doc(ofstream& ofs);
	

};

#endif