#include <iostream> 
#include"fibonacci.hpp"
using namespace std; 
int main(){ 
    
    Fibonacci<int> h(4);
    h.insert(5);
    h.insert(6); 
    h.insert(2);
    h.insert(1);
    h.insert(0);
    FNode<int>*nine=h.insert(3);
    cout<<h.getmin()<<endl;
    cout<<endl<<endl;
    cout<<endl<<endl;
    h.removemin(); 
    cout<<endl<<endl<<endl<<endl; 
    cout<<h.getmin()<<endl; 


    if(h.getheap()->child->next!=NULL)
    cout<<"heap.child next:"<<h.getheap()->child->next->value<<endl;
    else
        cout<<"heap.child next is null"<<endl; 
    
    
    if(h.getheap()->child!=NULL)
    cout<<"heap.child:"<<h.getheap()->child->value<<endl;
    else
        cout<<"heap.child is null"<<endl;


    cout<<endl<<endl<<endl<<endl; 
    h.removemin(); 
    cout<<endl<<endl<<endl<<endl; 

    cout<<h.getmin()<<endl;
    h.removemin(); 
    return 0; 
} 

