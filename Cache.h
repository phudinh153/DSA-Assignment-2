#ifndef CACHE_H
#define CACHE_H

#include "main.h"

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
    int ch[5] ={0, 0, 0, 0, 0};    //count for heap

    virtual ~ReplacementPolicy() = default;



};

class SearchEngine {
    public:
    int count = 0;
    Elem** a = new Elem*[5];
    Node *Foundingroot = new Node;
	virtual ~SearchEngine() = default;
    virtual Node *SearchNode(int ad, Node *root) = 0;
    virtual Node *AddNode(int ad, Node *root, Node *newnode) = 0;
    virtual Node *Deletenode(Node *root, int key) = 0;
};

class MFU : public ReplacementPolicy {
    //TODO
};

class LFU : public ReplacementPolicy {
    public:


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
    void PrintInOrder(Node *root){
        cout <<"Print BST in inorder:"<<endl;
        inOrder(root);
    }
    void inOrder(Node *root){
        if(root){
            inOrder(root->left);
            root->pro->print();
		    inOrder(root->right);
        }
    }

    void PrintPreOrder(Node *root){
        cout <<"Print BST in preorder:"<<endl;
        preOrder(root);
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