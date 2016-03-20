#include "dataset.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;

Corpus::Corpus(string corpus_file_name, string vocab_dict_file_name) :vocab_size_(0), corpus_file_name_(corpus_file_name), vocab_dict_file_name_(vocab_dict_file_name) {
	if (load_vocab_dict()) {
		cout << "Vocabulary dictionary is loaded." << endl;
	} else {
		cout << "Fail to load vacabulary dictionary." << endl;
	}
}

// read word-id file into word_to_di_dict_
bool Corpus::load_vocab_dict() {
	
	int num_line = 0;

	ifstream ifs(vocab_dict_file_name_);
	if (ifs.is_open()) {
		regex e("([[:w:]])+:([[:d:]]+)");  // regex match word:id for each line
		smatch sm;
		string line;
		
		while (getline(ifs, line)) {
			++num_line;
			regex_match(line, sm, e);
			if (sm.size() == 3) {
				word_to_id_dict_[sm[1].str()] = atoi(sm[2].str().c_str());
			} else {
				cout <<	"line " << num_line << " cannot match the pattern." << endl;
			}
		}
	} else {
		cout << "cannot open " << vocab_dict_file_name_ << endl;
		return false;
	}
	ifs.close();

	// set vocab_size_
	vocab_size_ = word_to_id_dict_.size();

	return true;
}

/**
 * file format 
 * length of document id:counts id:count ...
 */
void Corpus::write_docs(){
	ofstream ofs(corpus_file_name_);
	if (ofs.is_open()){
		for (auto& doc : docs_vec_) {
			doc.write_doc(ofs);
		}	
	} else {
		cout << corpus_file_name_ << " cannot be opened" << endl;
	}
	
	ofs.close();
}

void Corpus::write_vocabulary_dictionary() {
	ofstream ofs(vocab_dict_file_name_);
	if (ofs.is_open()) {
		for (auto p : word_to_id_dict_) {
			ofs << p.first << ":" << p.second << endl;
		}
	}
	ofs.close();
}

void Corpus::load_tfidf_corpus() {
	ifstream ifs(corpus_file_name_);
	//int temp = vocab_size_;
	vector<Document> docs_vec;
	if (ifs.is_open()) {
		string line;
		regex e_length("([[:d:]]+)");  // match doc_length
		regex e("([[:d:]]+):([[:d:]]+)");  // match word_id:word_count
		while (getline(ifs, line)) {
			smatch sm;
			docs_vec.emplace_back(Document());
			Document& doc = docs_vec.back();

			// set doc_length_
			if (regex_search(line, sm, e_length)) {
				if (sm.size() == 2) {
					doc.doc_length_ = atoi(sm[1].str().c_str());
				}
			} else {
				cout << "Corpus format error, lack document's length. " << endl;
			}

			// fill in word_count_
			line = sm.suffix().str();
			while (regex_search(line, sm, e)) {
				if (sm.size() == 3) {
					int word_id = atoi(sm[1].str().c_str());
					int word_count = atoi(sm[2].str().c_str());

					doc.word_to_count_[word_id] = word_count;
				}
			}
		}
	} else {
		cout << "cannot open " << corpus_file_name_ << endl;
	}
	ifs.close();

	docs_vec_.swap(docs_vec);
}
// end of Corpus definition 

// class Document definitioin
Document::Document(string doc_file_name, Corpus& corpus) {
	doc_file_name_ = doc_file_name;
	doc_length_ = 0;
	load_raw_text(corpus);
	
}

// load raw text to word_to_count_, word_to_id_dict_
void Document::load_raw_text(Corpus& corpus) {

	ifstream ifs(doc_file_name_);
	
	if (ifs.is_open()) {
		string line;

		while (getline(ifs, line)) {
			process_raw_text(line, corpus);
		}
	} else {
		cout << "cannot open " << doc_file_name_ << endl;
		return;
	}

	ifs.close();

	doc_length_ = word_to_count_.size();
	corpus.docs_vec_.emplace_back(*this);
}

// put word into word_to_count_, word_to_id_dict_
void Document::process_raw_text(string text, Corpus& corpus) {
	unordered_map<string, int>& word_to_id_dict_ = corpus.word_to_id_dict_;

	if (!text.empty()) {
		regex e("([[:alpha:]]+)");  // regex match character-form word
		smatch sm;
		while (regex_search(text, sm, e)) {  // search "words" in text one by one 
			if (sm.size() == 2) {
				string word = sm[1].str();
				// convert all character in word to lower
				transform(begin(word), end(word), begin(word), ::tolower);
				// put word into word_to_id_dict_
				if (word_to_id_dict_.find(word) == end(word_to_id_dict_)) {
					word_to_id_dict_[word] = corpus.vocab_size_++; 

				} 

				int word_id = word_to_id_dict_[word];

				// put word into word_to_count_
				if (word_to_count_.find(word_id) == end(word_to_count_)) {
					word_to_count_[word_id] = 1;
					// increase doc_length_
					// ++doc_length_;
				} else {
					++word_to_count_[word_id];
				}

				
			}

			text = sm.suffix().str();
		}
	}
}

/**
 * file format 
 * length of document id:counts id:count ...
 */
void Document::write_doc(ofstream& ofs) {
	ofs << doc_length_;
	for (auto p : word_to_count_) {
		ofs << " " << p.first << ":" << p.second;
	}
	ofs << endl;
}

// end of Document definition