#include "trie.h"
#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>

Trie::Trie() {
	_root = new Node("");
}

bool Trie::_isEmpty(Node* root) { 
	return root->next.empty();
}

Trie::Node* Trie::_insert(Node *root, std::string str) {
	SearchResult *sr = _search(root, str);
	root = sr->n;

	if(!sr->found) {
		std::stringstream ss(sr->str);

		while(ss >> str) {
			Node *n = new Node(str);
			root->next[str] = n;
			root = n;
		}
	}

	return root;
}

Trie::SearchResult* Trie::_search(Node *root, std::string str) {
	SearchResult *sr = new SearchResult(str);
	sr->n = root;
	
	std::size_t pos = str.find_first_of(" ");
	
	if(pos != std::string::npos) {
		std::string str1 = str.substr(0, pos);
		
		if(str1 != "" && root->next.find(str1) != root->next.end()) {
			sr->found = true;
			sr->str = str.substr(pos + 1);
			sr->n = root->next[str1];
			sr = _search(sr->n, sr->str);
		}
	} else {
		if(str != "" && root->next.find(str) != root->next.end()) {
			sr->found = true;
			sr->str = "";
			sr->n = root->next[str];
		}
	}

	return sr;
}

void Trie::_insertNgrams(Node *root, std::string filename, int n) {
	std::ifstream inp(filename);
	
	if(!inp) {
		std::cout << "Failed to open file.\n";
	} else {
		std::string str;
		while(std::getline(inp, str)) {
			int i = 0;
			std::stringstream ss(str);
			std::string s = "";
			
			while(i < n) {
				std::string temp;
				ss >> temp;
				s += temp + " ";
				i += 1;
			}

			s = s.substr(0, s.length() - 1);

			Node *n = _insert(root, s);
			
			while(ss >> s) {
				Node *ns = new Node(s);
				if(n->next.find(s) == n->next.end())
				n->next[s] = ns;
			}
		}
	}
}

std::set<std::string> Trie::_suggest(Node *root, std::string str) {
	SearchResult *sr = _search(root, str);
	std::set<std::string> ret;

	if(sr->found) {
		Node *curr = sr->n;
		std::cout << "Suggest: " << curr->data << '\n';
		for(auto p : curr->next) {
			ret.insert(p.first);
		}
	}
	return ret;
}

void Trie::_deleteTrie(Node* root) {
	free(root);
}

Trie::~Trie() {
}
