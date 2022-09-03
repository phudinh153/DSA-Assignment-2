#ifndef CACHE_H
#define CACHE_H

#include "main.h"
int size = MAXSIZE;
int count = 0;
class Node{
    public:
        Node *left, *right;
        Elem *pro; //property
    Node(){
        left = nullptr;
        right = nullptr;
    }
};

class ReplacementPolicy {
    public:
    
    int *ch = new int[size];    //count for heap
    
    Elem **heap = new Elem*[size];
    virtual ~ReplacementPolicy() = default;
    virtual void DeleteHeap(int pos) = 0;
    virtual void Add(Elem *d) = 0;

};

class SearchEngine {
    public:
    
    Elem** a = new Elem*[size];
    Node *Foundingroot = new Node;
	virtual ~SearchEngine() = default;
    virtual Node *SearchNode(int ad, Node *root) = 0;
    virtual Node *AddNode(int ad, Node *root, Node *newnode) = 0;
    virtual Node *Deletenode(Node *root, int key) = 0;
    virtual void PrintInOrder() = 0;
    virtual void PrintPreOrder() = 0;
};

class MFU : public ReplacementPolicy {
    //TODO
};

class LFU : public ReplacementPolicy {
    public:
    LFU(){
        for(int i = 0; i < size; i++){
        ch[i] = 0;
    }
    }
    ~LFU(){
        delete[] heap;
        delete ch;    
    }
void ReHeapup(int pos){
    int posParent = (pos - 1) / 2;
    //cout << "posParent: " << posParent<<endl;
    //cout << "ch: "<<ch[posParent]<<endl;
    while(ch[pos] < ch[posParent] && posParent >= 0){
        swap(heap[pos], heap[posParent]);
        swap(ch[pos], ch[posParent]);
        //if((pos - 1) / 2 >= 0){
            pos = posParent;
            posParent = (pos - 1) / 2;
        //}
    }
}

void ReHeapdown(int pos){
    int posCL = 2*pos + 1;
    int posCR = 2*pos + 2;
    
    while(posCL < count || posCR < count){
        if(posCL < count && posCR < count){
            if(ch[posCL] <= ch[posCR] && ch[pos] >= ch[posCL]){
                swap(heap[pos], heap[posCL]);
                swap(ch[pos], ch[posCL]);
                pos = posCL;
            }
            else if(ch[posCL] > ch[posCR] && ch[pos] >= ch[posCR]){
                swap(heap[pos], heap[posCR]);
                swap(ch[pos], ch[posCR]);
                pos = posCR;
            }
            else{
                break;
            }
        } 
        else if(posCL >= count && ch[pos] >= ch[posCR]){
            swap(heap[pos], heap[posCR]);
            swap(ch[pos], ch[posCR]);
            pos = posCR;
        } 
        else if(posCR >= count && ch[pos] >= ch[posCL]){
            swap(heap[pos], heap[posCL]);
            swap(ch[pos], ch[posCL]);
            pos = posCL;
        }
        else{
            break;
        }
        posCL = 2*pos + 1;
        posCR = 2*pos + 2;
    }
}

void DeleteHeap(int pos){
    swap(heap[pos], heap[count-1]);
    swap(ch[pos], ch[count-1]);
    count--;
    ReHeapdown(pos);
    
    for(int i = 0; i < count; i++){
        ReHeapup(i);
    }
}

void Add(Elem *d){
    heap[count] = d;
    ReHeapup(count);
    count++;
       
}

};
class MFRU: public ReplacementPolicy {
    //TODO
};

class LFRU: public ReplacementPolicy {
    //TODO
};

class BST : public SearchEngine {
    public:
    ~BST(){
        delete[] a;
    }
    void PrintInOrder(){
        cout <<"Print BST in inorder:"<<endl;
        inOrder(this->Foundingroot);
    }
    void inOrder(Node *root){
        if(root){
            inOrder(root->left);
            root->pro->print();
		    inOrder(root->right);
        }
    }

    void PrintPreOrder(){
        cout <<"Print BST in preorder:"<<endl;
        preOrder(this->Foundingroot);
    }
    void preOrder(Node *root){
        if(root){
            preOrder(root->left);
            root->pro->print();
		    preOrder(root->right);
        }
    }

    Node *SearchNode(int ad, Node *root){
        if(root){
            if(root->pro->addr == ad){          
                    return root;      
            }
            else if(root->pro->addr > ad) {     
                return SearchNode(ad, root->left);
                }
            else if(root->pro->addr < ad) {
                return SearchNode(ad, root->right);
                }
            }
            return nullptr;
            
        }
    Node *AddNode(int ad, Node *root, Node *newnode){
            if(root == nullptr){
                    return newnode;      
            }
            else {
                if(root->pro->addr > ad) {     
                root->left = AddNode(ad, root->left, newnode);
                }
                else if(root->pro->addr < ad) {
                root->right = AddNode(ad, root->right, newnode);
                }
                return root;
            }
        }
    Node* Deletenode(Node *root, int key){
    if(root->pro->addr > key) root->left = Deletenode(root->left, key);
    else if(root->pro->addr < key) root->right = Deletenode(root->right, key);
    else{
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
        else if(root->left == nullptr){
            Node *p = root;
            root = root->right;
            delete p;
            p = nullptr;
    
        }
        else if(root->right == nullptr){
            Node *p = root;
            root = root->left;
            delete p;
            p = nullptr;
    
        }
        else{
            Node *p = root->right;
            while(p->left != nullptr){
                p = p->left;
            }
            root->pro = p->pro;
            root->right = Deletenode(root->right, p->pro->addr);
        }
    }

    return root;

}
};
#endif