#include "main.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}


Data* Cache::read(int addr) {
    // Node *root = s_engine->Foundingroot;
    // Node *found = s_engine->SearchNode(addr, root);
    // if(found){ 
    //         //updatecountofRP

    //     //heapify
        
    //     return found->pro->data;
    // }
    for(int i = 0; i < 5; i++){
        if(s_engine->a[i]->addr == addr){
            rp->ch[i] += 1;     
            return s_engine->a[i]->data;
        }
    }
    return NULL;
}



Elem* Cache::put(int addr, Data* cont) {
    Node *root = s_engine->Foundingroot;   
    if(s_engine->count == 5){
        //heapify

        //s_engine->Deletenode(root, a[])

    } 
    if(s_engine->count == 0){
        root->pro = new Elem(addr, cont, 1);
        s_engine->a[s_engine->count] = root->pro;
        //heapify
    }
    else{
        Node *newnode = new Node;
        newnode->pro = new Elem(addr, cont, 1);
        root = s_engine->AddNode(addr, root, newnode);
        s_engine->a[s_engine->count] = newnode->pro;
        //heapify
    }
    s_engine->count++;
    
        

    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    Node *root = s_engine->Foundingroot; 
    if(s_engine->count == 5){
            //heapify

        //s_engine->Deletenode(root, a[])
        }
    if(s_engine->count == 0){
        root->pro = new Elem(addr, cont, 0);
        s_engine->a[s_engine->count] = root->pro;
        s_engine->count++;
    }
    else{
        Node *found = s_engine->SearchNode(addr, root);
        if(found){
            found->pro->data = cont;
            found->pro->sync = 0;
            for(int i = 0; i < 5; i++){
                if(s_engine->a[i]->addr == found->pro->addr){
                    rp->ch[i] += 1;     
                }
            }   
        }
            //heapify       
        else{
            Node *newnode = new Node;
            newnode->pro = new Elem(addr, cont, 0);
            root = s_engine->AddNode(addr, root, newnode);
            s_engine->a[s_engine->count] = root->pro;
            s_engine->count++;
            //heapify
        }

    }

    return NULL;
}
void Cache::printRP() {
    cout <<"Print replacement/n";

}
void Cache::printSE() {
}
void Cache::printLP() {
}
