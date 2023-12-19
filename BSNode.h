#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        T elem;
        BSNode<T>* left;
        BSNode<T>* right;
        BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr){
            new BSNode<T>(elem, left, right);
        }
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
            out << "BSNode Elemento: " << bsn.elem << ", Izq: " << bsn.left << ", Der: " << bsn.right << std::endl;
            return out;
        }
};

#endif