#include "main.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}


Data* Cache::read(int addr) {
    Node *root = s_engine->Foundingroot;
    for(int i = 0; i < count; i++){
            if(rp->heap[i]->addr == addr){
                rp->ch[i] += 1;   
                
                int j;
                for(j = 0; j < count; j++){
                    if(s_engine->a[j]->addr == addr){
                        break;
                    }
                }
                Node *newnode = new Node;
                newnode->pro = new Elem(addr, s_engine->a[j]->data, s_engine->a[j]->sync);
                rp->DeleteHeap(i);
                
                root = s_engine->Deletenode(root, s_engine->a[j]->addr);     
                s_engine->Foundingroot = root;
 
                s_engine->a[j] = newnode->pro;
                rp->Add(newnode->pro);  
                root = s_engine->AddNode(addr, root, newnode);
                
                // for(int m = 0; m < count; m++){
                //     cout<<m<<" " << rp->heap[m]->data->getValue() <<" ";
                // }
                // cout <<endl;
                // for(int k = 0; k < count; k++){
                //     cout<<k<<" " << rp->ch[k] <<" ";
                // }
                return newnode->pro->data;
            }
        }
        
    return NULL;
}


Elem* Cache::put(int addr, Data* cont) {
    
    Node *root = s_engine->Foundingroot;    
    Elem *delNode;
    int j;
    bool del = 0;
    if(count == 0){
        root->pro = new Elem(addr, cont, 1);
        s_engine->a[count] = root->pro;
        rp->Add(root->pro);  
        return NULL;
    }
    else if(count == size){
        for(j = 0; j < count; j++){
                    if(s_engine->a[j]->addr == rp->heap[0]->addr){
                        del = 1;
                        delNode = s_engine->a[j];
                        break;
                    }
                }
        root = s_engine->Deletenode(root, rp->heap[0]->addr);
        s_engine->Foundingroot = root;
        rp->DeleteHeap(0);

    }
        // for(int m = 0; m < count; m++){
        //             cout<<m<<" " << rp->heap[m]->data->getValue() <<" ";
        //         }
        //         cout <<endl;
        //         for(int k = 0; k < count; k++){
        //             cout<<k<<" " << rp->ch[k] <<" ";
        //         }
        //         cout <<endl;
        Node *newnode = new Node;
        newnode->pro = new Elem(addr, cont, 1);
        root = s_engine->AddNode(addr, root, newnode);
        
        rp->Add(newnode->pro);  
        if(del){
                s_engine->a[j] = newnode->pro;
                return delNode;
        }
        else{
                s_engine->a[count-1] = newnode->pro;
                // cout << rp->heap[0]->data->getValue() <<"0 ";
        }
        

    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    
    Node *root = s_engine->Foundingroot; 
    if(count == 0){
        
        root->pro = new Elem(addr, cont, 0);
        s_engine->a[count] = root->pro;
        rp->Add(s_engine->a[count]);  
        return NULL;
    }
    else{
        
        for(int i = 0; i < count; i++){
            
            if(rp->heap[i]->addr == addr){
                
                rp->ch[i] += 1;   
                int j;
                for(j = 0; j < count; j++){
                    if(s_engine->a[j]->addr == addr){
                        break;
                    }
                }
                
                rp->DeleteHeap(i);
                
                root = s_engine->Deletenode(root, s_engine->a[j]->addr);
                s_engine->Foundingroot = root;
                Node *newnode = new Node;
                newnode->pro = new Elem(addr, cont, 0);
                s_engine->a[j] = newnode->pro;
                rp->Add(newnode->pro);  
                root = s_engine->AddNode(addr, root, newnode);
                
                return NULL;
            }
        }
        int j;
        bool del = 0;
        Elem *delNode;
        if(count == size){
            //s_engine->Deletenode(root, a[])
            
                for(j = 0; j < count; j++){
                    if(s_engine->a[j]->addr == rp->heap[0]->addr){
                        del = 1;
                        delNode = s_engine->a[j];
                        break;
                    }
                }
            root = s_engine->Deletenode(root, rp->heap[0]->addr);

            rp->DeleteHeap(0);

        }
            Node *newnode = new Node;
            newnode->pro = new Elem(addr, cont, 0);
            root = s_engine->AddNode(addr, root, newnode);
            rp->Add(newnode->pro);  
            if(del){
                s_engine->a[j] = newnode->pro;
                return delNode;
            }
            else{
                s_engine->a[count-1] = newnode->pro;
            }

    }
    return NULL;
}
void Cache::printRP() {
    for(int i = 0; i < count; i++ ){
        rp->heap[i]->print();
    }
}
void Cache::printSE() {
    // s_engine->Foundingroot->pro->print();
    Node *root = s_engine->Foundingroot;
   
    cout <<"Print BST in inorder:"<<endl;
    s_engine->InOrder(s_engine->Foundingroot);
    cout <<"Print BST in preorder:"<<endl;
    s_engine->PreOrder(s_engine->Foundingroot);
    
}

void Cache::printLP() {
    //cout << 1;
}
