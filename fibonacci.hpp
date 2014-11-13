#include<vector> 
#include<iostream> 
using namespace std; 
template <class V> class Fibonacci;
/* 
 * Define a FNode used in Fibonacci heap, 
 * each node has a V class value.
 * */
template <class V> struct FNode{
    public:
    friend class Fibonacci<V>; 
    int degree; 
    FNode<V>* parent; 
    FNode<V>* child; 
    FNode<V>* prev; 
    FNode<V> *next; 
    V value; 
    bool childcut;
}; 





/* 
 * Define the class Fibonacci
 * */ 
template <class V> class Fibonacci{ 
    protected: FNode<V> *heap;
    public:    
               FNode<V> *getheap(){ 
                   return heap; 
               } 
/* 
 * This is constructor of Fibonacci heap, 
 * the function generate a new FNode to store value
 * */ 
               Fibonacci(V value){
                   heap=new FNode<V>; 
                   heap->degree=0;
                   heap->value=value; 
                   heap->parent=NULL; 
                   heap->child=NULL; 
                   heap->prev=heap; heap->next=heap; 
                   heap->childcut=false; 
               }


/*
 * This is destructor of Fibonacci heap. 
 * */
               virtual ~Fibonacci(){ 
               }


/* 
 * This function is to merge two FNodes.
 * */
               FNode<V>* merge(FNode<V>* aheap, FNode<V>* bheap){ 
                   if(aheap==NULL) return bheap; 
                   else if(bheap==NULL) return aheap;
                   if(bheap->value<aheap->value){ 
                       FNode<V> *tmp=aheap->next; 
                       aheap=bheap; 
                       bheap=tmp; 
                   }
                   FNode<V> *an=aheap->next; 
                   FNode<V> *bp=bheap->prev;
                   aheap->next=bheap;
                   bheap->prev=aheap; 
                   an->prev=bp;
                   bp->next=an;
/*
                   aheap->prev->next=bheap; 
                   bheap->prev->next=aheap;
                   FNode<V>* tmp;  
                   tmp=bheap->prev; 
                   aheap->prev=tmp;
                   bheap->prev=aheap->prev; 
*/
                   return aheap;
               } 
               


/*
 * This Function is to generate a new node to store the value 
 * then return the node pointer.
 * */
              FNode<V>* initnode(V value){ 
                   FNode<V>* ret=new FNode<V>; 
                   ret->degree=0;
                   ret->value=value; 
                   ret->parent=NULL; 
                   ret->child=NULL; 
                   ret->prev=ret; ret->next=ret; 
                   ret->childcut=true; 
                   return ret; 
              } 


/* 
 * This function is to insert a new value into the Fibonacci heap
 * */
               FNode<V>* insert(V value){ 
                  FNode<V>* a=initnode(value); 
                  if(heap->value<a->value){ 
                  heap=merge(heap,a); 
                  } 
                  else{ 
                      heap=merge(a,heap); 
                  }
/*
                  FNode<V>* n=heap;
                  while(n->next!=heap){ 
                      cout<<"n->next value:"<<n->value<<endl; 
                      n=n->next; 
                  } 
                  heap->ismin=true;
*/
                  return heap; 
               } 



/* 
 * This function is to reture the minmimue V value in the fibonacci heap.
 * */
               V getmin(){
                   if(heap==NULL){ 
                       cout<<"Fibonacci heap is NULL"<<endl; 
                   } 
                   return heap->value; 
               } 


/* 
 * This function is to add a child to a parent node. 
 * Note: In this funtion, the parent->value is smaller than child->value
 * */
               FNode<V>* _addchild(FNode<V> *parent, FNode<V> *child){ 
                   if(parent->child==NULL){ 
                       parent->child=child;
                       child->parent=parent; 
                       child->next=child;
                       child->prev=child;
                       parent->degree=1; 
                   } 
                   child->prev=child->next=child; 
                   child->parent=parent; 
                   parent->degree++;
                   
                   if(parent->child->value<child->value){ 
                       merge(parent->child,child); 
                   } 
                   else{ 
                       merge(child,parent->child);
                   } 
                   return parent;   
/*                   if(parent->child==NULL){ 
                       parent->child=child;
                       child->parent=parent; 
                       child->next=child;
                       child->prev=child;
                       parent->degree=1; 
                   } 
                   else{ 
                       parent->child=merge(parent->child,child); 
                       parent->child->parent=parent; 
                       child->parent=parent;  
                       parent->degree++; 
                   } 
*/
               } 



/* 
 * This function is to set  a node list parent and childcut to NUll and False.
 * */
               void _unMarkAndParentAll(FNode<V> *n){ 
                   if(n==NULL) return; 
                   FNode<V> *c=n; 
                   do{ 
                       c->childcut=false; 
                       c->parent=NULL;
                       c=c->next; 
                   }while(c!=n); 
               } 


/* 
 * This function is to remove the min element in the fibonacci heap.
 * details are discussed in the function. 
 * */
               void removemin(){ 
                   _unMarkAndParentAll(heap->child);
/* 
 * if heap->next is heap,then we simply let heap=heap->child to delete 
 * the min element.
 * else, we delete heap, and merge heap->next node with heap->child node. 
 * */ 
                   if(heap->next==heap){
                       heap=heap->child; 
                   }
                   else{ 
                       heap->next->prev=heap->prev; 
                       heap->prev->next=heap->next; 
                       heap=merge(heap->next,heap->child); 
                   }
                   if(heap==NULL) return; 
/*                   if(heap->child==NULL){ 
                       if(heap->next==heap){ 
                           heap=NULL;
                           return; 
                       } 
                       else{
                       heap->prev->next=heap->next; 
                       heap->next->prev=heap->prev;
                       heap=heap->next;  
                       }                          
                   } 

                   else{ 
                       FNode<V>* child=heap->child; 
                       if(heap->next=heap){ 
                           heap=child;
                           heap->parent=NULL;  
                       } 
                       else{
                       heap->prev->next=heap->next; 
                       heap->next->prev=heap->prev; 
                       heap=merge(child,heap->next); 
                       } 
                   } 
*/                   
                   FNode<V>* tree[64]={NULL};
                   FNode<V> *n=heap;
/*                   do{ 
                       cout<<"nvalue:"<<n->value<<endl;
                       n=n->next; 
                   }while(n!=heap);
*/


/* 
 * This part is to pariwise merge the elements. 
 * */
                   while(true){
                      if(tree[n->degree]!=NULL){
                          FNode<V> *t=tree[n->degree];
                          if(t==n) break;
//                      cout<<"t->value===:"<<t->value<<endl;
//                      cout<<"n->value===:"<<n->value<<endl;
                          tree[n->degree]=NULL; 

                          if(n->value<t->value){ 
                                        t->prev->next=t->next;
                                        t->next->prev=t->prev;
                                        _addchild(n,t);
                                } else {
                                        t->prev->next=t->next;
                                        t->next->prev=t->prev;
                                        if(n->next==n) {
                                                t->next=t->prev=t;
                                                _addchild(t,n);
                                                n=t;
                                        } else {
                                                n->prev->next=t;
                                                n->next->prev=t;
                                                t->next=n->next;
                                                t->prev=n->prev;
                                                _addchild(t,n);
                                                n=t;
                                        }
                                }
                                continue;
                        } else {
//                                cout<<"put n in degree"<<n->value<<" "<<n->degree<<endl; 
                                tree[n->degree]=n;
                        }
                        n=n->next;
                }
 
/*                             
                             tree[treenode->degree]->prev->next=tree[treenode->degree]->next; 
                             tree[treenode->degree]->next->prev=tree[treenode->degree]->prev; 
                             if(treenode->next==treenode){ 
                                 tree[treenode->degree]->prev=tree[treenode->degree]->next=tree[treenode->degree]; 
                                 FNode<V> *parent=_addchild(tree[treenode->degree],treenode); 
                                 treenode=parent; 
                             } 
                             else{ 
                                 treenode->prev->next=tree[treenode->degree]; 
                                 treenode->next->prev=tree[treenode->degree]; 
                                 tree[treenode->degree]->next=treenode->next; 
                                 tree[treenode->degree]->prev=treenode->prev; 
                                 FNode<V> *parent=_addchild(tree[treenode->degree],treenode); 
                                 treenode=parent; 
//                             cout<<"tree[parent->degree]:"<<tree[parent->degree]->value<<endl; 
                             } 
                          } 

                          else{ 
                              tree[treenode->degree]->prev->next=tree[treenode->degree]->next; 
                              tree[treenode->degree]->next->prev=tree[treenode->degree]->prev;  
                              FNode<V>* parent=_addchild(treenode,tree[treenode->degree]); 
                              //no need to change parent next and prev, it is the same as treenode 
                              treenode=parent; 
//                              cout<<"tree[parent->degree]:"<<tree[parent->degree]->value<<endl; 
                          } 
                          tree[treenode->degree]=NULL; 
                          continue; 
                      } 

                      else{ 
                           tree[treenode->degree]=treenode; 
                           //since the later use of treenode->next. even we don't set treenode->next=treenode
                           //still work correct in the later code 
                           //FNode<V>* parent=_addchild(tree[treenode->degree],treenode); 
                      }
                      treenode=treenode->next; 
                   } 
*/
                   FNode<V>* min=n;
                   heap=n;
                   do{ 
//                       cout<<"n->value is:"<<n->value<<endl; 
                       if(n->value<min->value) min=n;
                       n=n->next; 
                   }while(n!=heap); 
                   heap=min;
               } 


/* 
 * This part is for the cut function in the Fibonacci heap
 * */ 

               FNode<V>* _cut(FNode<V> *n){ 
                   if(n->next==n){ 
                       n->parent->child=NULL; 
                   } 
                   else{ 
                       n->next->prev=n->prev; 
                       n->prev->next=n->next; 
                       n->parent->child=n->next; 
                   } 
                   n->next=n->prev=n; 
                   n->childcut=false; 
                   if(n->value<heap->value){ 
                       merge(n,heap); 
                   } 
                   else{ 
                       merge(heap,n); 
                   } 
                   return heap; 
               } 






/* 
 * This function is to decrease a node's value by value.
 * node-> value=node->value->value
 * */ 
               FNode<V>* decreasekey(FNode<V>* n, V value){ 
                   n->value=n->value-value; 
                   if(n->parent!=NULL&&n->value<n->parent->value){ 
                       heap=_cut(n); 
                       while(true){ 
                       FNode<V>* parent=n->parent; 
                       if(parent!=NULL&&parent->childcut==true){ 
                           heap=_cut(parent); 
                           n=parent; 
                       } 
                       else{ 
                           if(parent!=NULL&&parent->parent!=NULL){ 
                               parent->childcut=true; 
                           } 
                           break; 
                       } 
                       } 
                   } 
                   else if(n->parent==NULL&&n->value<heap->value){ 
                       heap=n; 
                   } 
               } 

                           
                           
}; 



                      

                          























