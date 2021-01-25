#include <climits>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template <std::size_t B>
class BPtree {
    struct Node {
        bool IS_LEAF{};
        deque<int> key;
        int size{};
        deque<Node*> ptr;
        Node(){
          //key.resize(0);
          ptr.resize(B+1);
        }
//        explicit Node() {
//        key.resize(grado_);
//          ptr.resize(B+1);
//        }
        friend ostream &operator<<(ostream &os, const Node &node) {
          for (int i = 0; &node && i < node.key.size(); ++i) {
            os << "keys: " << node.key[i] << " ";
          }
          return os;
        }
    };
    //int grado_;
    int keySize;
    int childrenSize;
    Node* root;
    void insertInternal(int, Node*, Node*);
    Node* findParent(Node*, Node*);

public:
    //BPtree() {
      //root = nullptr;
    //}
    BPtree() {
      this->keySize = B;
      this->childrenSize = B + 1;
      this->root = nullptr;
    }

    void traversalSearch(int valor, Node* &cursor) {
      while (cursor->IS_LEAF == false) {
        for (int i = 0; i < cursor->size; i++) {
          if (valor < cursor->key[i]) {
            cursor = cursor->ptr[i];
            break;
          }
          if (i == cursor->size - 1) {
            cursor = cursor->ptr[i + 1];
            break;
          }
        }
      }
    }

    bool search(int valor) {
      Node* cursor = root;
      traversalSearch(valor, cursor);
      for (int i = 0; i < cursor->size; i++) {
        if (cursor->key[i] == valor) {
          return true;
        }
      }
      return false;
    }

    void setVariable(Node* &pNode, int uValor, int uIte, Node* prevNode, Node* nextNode) {
      pNode->key.insert(pNode->key.begin()+uIte, uValor);
      pNode->ptr[pNode->key.size()] = nextNode;
      pNode->ptr[pNode->key.size()-1] = prevNode;
    }

    void insert(int valor) {
      // insertar en la raiz primera clave
      if (root == nullptr) {
        root = new Node;
        root->key.push_back(valor);
        root->IS_LEAF = true;
      }
      else {
        Node* cursor = root;
        Node* parent;
        traversalSearch(valor, cursor);

        //buscar e insertar claves en un nodo
        if (cursor->key.size() < keySize) {
          int i = 0;
          for (; valor > cursor->key[i] && i < cursor->key.size(); i++);

          for (int j = cursor->key.size(); j > i; j--) {
            cursor->key[j] = cursor->key[j-1];
          }
          if (cursor->key[i] == valor) {
            return;
          }
          setVariable(cursor, valor, i, nullptr,  cursor->ptr[cursor->key.size()-1]);
        }
        else {
          Node* newLeaf = new Node;
          int* virtualNode = new int[childrenSize];

          for (int i = 0; i < keySize; ++i) {
            virtualNode[i] = cursor->key[i];
          }
          // i es parte del iterador clave
          int i=0, j;
          for (; valor>virtualNode[i] && i<keySize; i++);
          for (int k = childrenSize; k > i; k--) {
            virtualNode[k] = virtualNode[k-1];
          }
        }
      }
    }
};

int main() {
  BPtree<2> aquelArbolitoDondeEstaEscrito;
  aquelArbolitoDondeEstaEscrito.insert(5);
  aquelArbolitoDondeEstaEscrito.insert(5);
  aquelArbolitoDondeEstaEscrito.insert(15);
  aquelArbolitoDondeEstaEscrito.search(7);
  return 0;
}