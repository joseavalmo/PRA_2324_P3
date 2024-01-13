#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> class BSTree{

	private:
		int nelem;
		BSNode<T> *root;

		BSNode<T>* search(BSNode<T>*n, T e) const{
			if(n == nullptr) 
				throw runtime_error("El elemento no se ha encontrado");
			else if(e < n->elem) return search(n->left, e);
			else if(e > n->elem) return search(n->right, e);
			else return n;
		}

		BSNode<T>* insert(BSNode<T>*& n, T e){
    			if (n == nullptr) {
        			n = new BSNode<T>(e, nullptr, nullptr);
        			this->nelem++;
        			return n;
    			}else if (e > n->elem) {
        			return insert(n->right, e);
    			}else if (e < n->elem) {
        			return insert(n->left, e);
    			}else {
        			throw runtime_error("El elemento está ya en el arbol");
    			}
		}		

		
		void print_inorder(ostream &out, BSNode<T> *n){
			if(n == nullptr) return;
			print_inorder(out, n->left);
			out << " ";
			out << *n;
			out << " ";
			print_inorder(out, n->right);
			out << " ";
		}
		
		/*function inorden(n, P):
    if n != null then
        inorden(n.first_descendant(), P)
        P(n)
        foreach d in sorted(n.remaining_descendants()) do
            inorden(d, P)
        done
    end*/

		BSNode<T>* remove(BSNode<T>*& n, T e){
		    if (n == nullptr){
			throw runtime_error("No existe el nodo");
		    }

		    if (e > n->elem){
			n->right = remove(n->right, e);
		    }else if (e < n->elem) {
			n->left = remove(n->left, e);
		    }else{
			if (n->left != nullptr && n->right != nullptr){
			    T maxLeft = max(n->left);
			    n->elem = maxLeft;
			    n->left = remove(n->left, maxLeft);
			}else{
			    BSNode<T>* temp = n;
			    n = (n->left != nullptr) ? n->left : n->right;
			    delete temp;
			    nelem--;
			}
		    }

		    return n;
		}	

		T max(BSNode<T>* n)const{

			if(n == nullptr) 
				throw runtime_error("El nodo no existe");
			BSNode<T>* aux = n;

			if(aux->right != nullptr) 
				return max(aux->right);
			else 
				return aux->elem;
		}

		BSNode<T>* remove_max(BSNode<T>* n){
			
			if(n->right != nullptr) 
				return remove_max(n->right);
			else 
				return n->left;
		}

		void delete_cascade(BSNode<T>*n){
			if(n == nullptr) return;
			delete_cascade(n->left);
			delete_cascade(n->right);
			delete n;
		}

		void opAdd(BSTree<T>& aT, BSNode<T>*n){
                        try{
				if(n != nullptr){
					aT.insert(n->elem);
					opAdd(aT, n->left);
					opAdd(aT, n->right);
				}
                        }catch(std::runtime_error &e){
                        }
                }


		/* function preorden(n, P){
		   if n != null
		   P(n)
		   foreach d in sorted(n.desdendants()) do
		   	preorden(d, P)
		   	donde
		   return*/



	public:
		BSTree(){
			nelem = 0;
			root = nullptr;
		}

		~BSTree(){
			delete_cascade(root);		
		}

		int size() const{
			return nelem;
		}

		T search(T e){
			BSNode<T>* res = search(root, e);
			return res->elem;			
		}

		T operator[](T e) const{
			return search(e);
		}

		void insert(T e){
			insert(root, e);
		}

		friend ostream&operator<<(ostream &out, BSTree<T> &bst){
			bst.print_inorder(out, bst.root);
			return out;
		}


		friend BSTree<T>operator+(const BSTree<T> &bt1, const BSTree<T> &bt2){
			BSTree<T> narbol;
			narbol.opAdd(narbol, bt1.root);
			narbol.opAdd(narbol, bt2.root);
			return narbol;
		}

		void remove(T e){
			remove(root, e);
		}

};


#endif
