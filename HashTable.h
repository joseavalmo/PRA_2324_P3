#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

using namespace std;

template <typename V> class HashTable : public Dict<V>{
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		int h(string key){
			int res = 0;
			for(int i = 0; i<key.size(); i++){
				res += key[i]%max;
			}
			return res%max;
		}
	public:

		HashTable(int size){
			this->n = 0;
			this->max = size;
			table = new ListLinked<TableEntry<V>>[size];
		}
		
		~HashTable(){
			delete[] table;
		}

		V search(string key)override{
			//cout << "Entra en search" << endl;
			int index = h(key);
			//cout << index << endl << table[index].size() << endl;
			for(int i = 0; i<table[index].size(); i++){
				if(table[index].get(i).key == key)return table[index].get(i).value;				
			}

			throw runtime_error("Key '" + key + "' not found!");
		}

		void insert(string key, V value)override{
			
			//cout << "Entramos en insert" << endl;

			try{
				search(key);
				//cout << "Elemento encontrado" << endl;

			} catch (const runtime_error& e){
				TableEntry<V> newEntry(key, value);
				table[h(key)].prepend(newEntry);
				n++;
				//cout << "Elemento añadido" << endl;
				return;		
			}

			throw runtime_error("Key '" + key + "' already exists!");
		}

		V remove(string key)override{
			int index = h(key);
			for(int i = 0; i<table[index].size(); i++){
				if(table[index].get(i).key == key){
					V res = table[index].get(i).value;
					table[index].remove(i);
					n--;
					return res;
				}
			}
			throw runtime_error("Elemento no existe");
		}

		int entries()override{
			return n;
		}

		int capacity(){
			return this->max;
		}

		friend ostream&operator<<(ostream &out, HashTable<V> &th){
			out << "HashTable [entries: " << th.entries() << ", capacity: " << th.capacity() << "]" << endl;
			cout << "==============" << endl << endl;

			for(int i = 0; i<th.capacity(); i++){
				cout << "== Cubeta " << i << " ==" << endl << endl;
				cout << "List => [";
				for(int j = 0; j<th.table[i].size(); j++){
					if(j == 0) cout << endl;
					out << th.table[i].get(j);
				}
				cout << "]" << endl << endl;
			}
			out << "==============" << endl;
			return out;
		}

		V operator[](string key){
			V res = search(key);
			return res;
		}

};


#endif