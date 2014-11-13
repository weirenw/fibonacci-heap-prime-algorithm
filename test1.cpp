#include <stdio.h>
#include "fibonacci.hpp"



class DotFibonacciHeap : public Fibonacci<int> {
    public:
        void dump() {
            printf("digraph G {\n");
            if(heap==NULL) {
                printf("empty;\n}\n");
                return;
            }
            printf("minimum -> \"%p\" [constraint=false];\n",heap);
            Node<int>* c=heap;
            do {
                _dumpChildren(c);
                c=c->next;
            } while(c!=heap);
            printf("}\n");
        }

    private:

        void _dumpChildren(Node<int>* n) {
            printf("\"%p\" -> \"%p\" [constraint=false,arrowhead=lnormal];\n",n,n->next);
            printf("\"%p\" -> \"%p\" [constraint=false,arrowhead=ornormal];\n",n,n->prev);
            if(n->childcut)printf("\"%p\" [style=filled,fillcolor=grey];\n",n);
            if(n->parent!=NULL) {
                printf("\"%p\" -> \"%p\" [constraint=false,arrowhead=onormal];\n",n,n->getParent());
            }
            printf("\"%p\" [label=%d];\n",n,n->getValue());
            if(n->hasChildren()) {
                Node<int>* c=n->getChild();
                do {
                    printf("\"%p\" -> \"%p\";\n",n,c);
                    _dumpChildren(c);
                    c=c->getNext();
                } while(c!=n->getChild());
            }
        }
};


void test() {
    DotFibonacciHeap h;
    h.insert(2);
    h.insert(3);
    h.insert(1);
    h.insert(4);
    h.removemin();
    h.removemin();
    h.insert(5);
    h.insert(7);
    h.removemin();
    h.insert(2);
    node<int>* nine=h.insert(90);
    h.removemin();
    h.removemin();
    h.removemin();
    for(int i=0;i<20;i+=2)h.insert(30-i);
    for(int i=0;i<4;i++)h.removemin();
    for(int i=0;i<20;i+=2)h.insert(30-i);
    h.insert(23);
    for(int i=0;i<7;i++)h.removemin();
    h.decreaseKey(nine,1);

    h.dump();
}

int main() {
    test();
}
