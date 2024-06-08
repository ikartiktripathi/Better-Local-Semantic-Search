#ifndef _TRIE_H_
#define _TRIE_H_

#include<set>
#include<map>
#include<string>

class Trie {
	private:
		struct Node {
			std::string data;
			std::map<std::string, Node*> next;

			Node(std::string str) : data(str) {}
		};

		struct SearchResult {
			bool found;
			std::string str;
			Node *n;

			SearchResult(std::string s) : found(false), str(s), n(NULL) {}
		};

		Node* _root;
		void _insertNgrams(Node*, std::string, int n);
		Node* _insert(Node*, std::string);
		void _remove(Node*, std::string);
		void _deleteTrie(Node*);
		SearchResult* _search(Node*, std::string);
		bool _isEmpty(Node*);
		std::set<std::string> _suggest(Node*, std::string);

	public:
		Trie();
		~Trie();

		void insertNgrams(std::string filename, int n) {
			_insertNgrams(_root, filename, n);
		}

		void insert(std::string str) {
			Node *n = _insert(_root, str);
		}
		
		void remove(std::string str) { _remove(_root, str); }
		void deleteTrie() { _deleteTrie(_root); }
		
		bool search(std::string str) { 
			SearchResult *sr = _search(_root, str);
			return sr->found;
		}
		
		bool isEmpty() { return _isEmpty(_root); }
		std::set<std::string> suggest(std::string str) { return _suggest(_root, str); }
};


#endif
