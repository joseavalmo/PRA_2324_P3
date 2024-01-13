#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V> class BSTreeDict: public Dict<V>{
	private:
		BSTree<TableEntry<V>>* tree;
	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>;
		}

		~BSTreeDict(){
			delete tree;	
		}

		void insert(string key, V value) override{
			TableEntry<V> *aux = new TableEntry<V>(key, value);
			tree->insert(*aux);
			delete aux;
		}

		V search(string key) override{
			return tree->search(key).value;
		}

		V remove(string key) override{
			V val = tree->search(key).value;
			tree->remove(key);
			return val;
		}

		int entries() override{
			return tree->size();
		}

		friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
			out << *bs.tree;
			return out;
		}

		V operator[](string key){
			return search(key);
		}
};

#endif
