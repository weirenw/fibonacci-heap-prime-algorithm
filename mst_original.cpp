#include<iostream> 
#include<fstream> 
#include<vector> 
#include<set> 
#include<stdlib.h> 
#include "fibonacci.hpp"
#include<queue>
#include<time.h> 
#include<cstdlib> 
using namespace std; 

#define INF 0x7fffffff; 
clock_t Start,Time; 
typedef struct Node{ 
    int info; 
    int weight; 
    Node *next; 
    bool operator <(const Node& x) const { 
        return info<x.info; 
    } 
}; 

typedef struct HeadNode{ 
    int info; 
    Node *link; 
    bool operator <(const HeadNode& x) const { 
        return info<x.info; 
    }
}; 
/*
 * In the below, the program overload operator <. 
 * The operator < is for the set<Edge> class and
 * fibonacci heap. For the fibonacci heap, 
 * When the weight of two edges is not equal, we
 * pick the weight has lower one. For the Set<Edge>
 * when the two edges has different begin and end,
 * but same weight, it is different edge, the program 
 * return true. 
 * */ 
typedef struct Edge{ 
    int begin; 
    int end; 
    int weight; 
    bool operator <(const Edge& x) const {
        if(weight==x.weight){ 
            if(begin==x.begin&&end==x.end) return false;
            else return true; 
        } 
        return (weight<x.weight); 
    }
}; 

/* 
 * This is to print an edge information. 
 * It's Used to print results and debuging. 
 * */
void printedge(Edge e){ 
    cout<<"begin:"<<e.begin<<" end:"<<e.end<<" e.weight:"<<e.weight<<endl; 
}

/*
 * This is to print each edge in a edge set.
 * It's used to print results and debuging.
 * */ 
void printt(set<Edge> &t){
    cout<<"print t"<<endl;
    cout<<"t.size:"<<t.size()<<endl; 
    for(set<Edge>::iterator itr=t.begin();itr!=t.end();itr++){ 
        printedge(*itr); 
    } 
    cout<<"print t end"<<endl; 
} 

/* 
 * This is to print each node in a node set.
 * It's used to print results and debuging.
 * */ 
void printtv(set<HeadNode> &tv){
    cout<<"print tv"<<endl;
    cout<<"tv.size:"<<tv.size()<<endl; 
    for(set<HeadNode>::iterator itr=tv.begin();itr!=tv.end();itr++){
        cout<<(*itr).info<<endl;
    } 
    cout<<"print tv end"<<endl; 
} 


/* 
 * The function is to compute the new edges which need to be added to the Fibnonacci heap. 
 * The program get each edge of addnode(begin),and judge the whether the end of edge belong 
 * to tv. tv is the node set that already joined the spanining tree. If the end node of edge
 * has already in tv, get the next edge. Otherwise, insert the edge into fibonacci heap. 
 * */
void addnewedges(HeadNode hnode[], HeadNode addnode, Fibonacci<Edge> &h, set<HeadNode> &tv){ 
    Node* n=addnode.link;
    int tvsize=tv.size(); 
    while(n!=NULL){
/* 
 * judge whether end node is in tv set, if it in the tv set,
 * go to next edge. 
 * */
        if(tv.find(hnode[n->info])!=tv.end()){ 
            bool tmp=tv.find(hnode[n->info])!=tv.end();
            n=n->next; 
            continue; 
        } 
/* 
 * The node is not in tv set, insert the edge(begin: addnode, end: n node, weight: weight)
 * into the fibonacci heap. Then insert the node into tv set. Then compute next node. 
 * */
        else{ 
            Edge e; 
            e.begin=addnode.info; 
            e.end=n->info; 
            e.weight=n->weight;
            h.insert(e);
/* 
 * printing part of computing result for debuging. 
 * */
/*
            cout<<"the heap edge is:"<<endl; 
            printedge(h.getheap()->value); 
            cout<<"the heap child edge is:"<<endl;
            if(h.getheap()->child!=NULL)
            printedge(h.getheap()->child->value);
            else 
                cout<<"the heap child is NULL, there is no child edge"<<endl;
            cout<<"Current Min edge"<<endl; 
            printedge(h.getmin());
*/
            n=n->next; 
        } 
    } 
} 


/* 
 * This function is to get the min edge from the fibonacci heap. Then the function judge whether this
 * edge connects two nodes already in a tv set. If one of them is node in the tv set. Then this edge is
 * part of MST. The function insert the edge into set<Edge> t. Then return the new node, which will join the 
 * tv set later. Otherwise, we simply ignore this edge and get another edge, untill the edge's one node is not 
 * in the tv set. 
 * */
HeadNode selectminedgenode(HeadNode hnode[], Fibonacci<Edge> &h, set<HeadNode> &tv, set<Edge> &t, set<Edge> &rmedge){ 
    Edge e=h.getmin();
/* 
 * if the edge node is in the tv set, then we continue get min edge from fibonacci heap, untill the edge node is
 * not in the tv set. set<Edge> rmedge is a set to store the edge that the program ignored. 
 * */
    while(tv.find(hnode[e.end])!=tv.end()){
        rmedge.insert(e); 
        h.removemin();
        if(&e==NULL){ 
            cout<<"h.getmin return a null"<<endl; 
        }
        e=h.getmin();
    }
    rmedge.insert(e); 
    h.removemin();
/* 
 * insert the edge into set<Edge> t. t is used for storing mst edges.
 * cout is to print current status
 * */ 
/*
 * cout<<"select edge and remove====================="<<endl;
 * printedge(e);
**/
    t.insert(e); 
    return hnode[e.end]; 
} 

/* 
 * This function is the mst generating function, fibonacci heap version. 
 * The funtion return the weight of the mst. The function call addnewedges
 * and selectminedgenode untill the set<Edge> t has generated the mst. 
 * */ 
int primf(HeadNode hnode[], int Gnumm){ 
    set<HeadNode> tv; 
    set<Edge> t;
    Edge e;
    HeadNode addnode;
/* 
 * set the first addnode as the node who has adjacent node.
 * the program need to do this because that it is possible that a node is
 * isolated. In this case, there  will be no spanning tree
 * */ 
    for(int i=0;i<Gnumm+1;i++){ 
       if(hnode[i].link!=NULL){
         addnode=hnode[i]; 
         break; 
       } 
    }
/* 
 * initial Fibonacci heap, insert a edge has INF weight
 * The edge will never be selected if program goes well.
 * */
    e.begin=Gnumm+1; e.end=Gnumm+1; e.weight=INF;
    Fibonacci<Edge> h(e);
    set<Edge> rmedge;
/* when t.size equal to Gnumm, then the mst has been generated.
 * Otherwise, continue call addnewedges and selectminedgenode
 * */
    Start=clock(); 
    while(t.size()<Gnumm){  
        tv.insert(addnode);
         addnewedges(hnode,addnode,h,tv); 
         addnode=selectminedgenode(hnode,h,tv,t,rmedge);
/* 
 * print information of current state.
 *         cout<<"addnode:"<<addnode.info<<"===================="<<endl;
 *         cout<<"current tvnodes are:"<<endl; 
 *         printtv(tv);
 *         cout<<"current tedges are:"<<endl; 
 *         printt(t);
 *         cout<<"remove edges are:"<<endl; 
 *         printt(rmedge);
 *         cout<<endl<<endl<<endl; 
 * */          
    }
    Time=clock()-Start; 
/*
 * print set<Edge> t, the mst and computing the total weight.
 * */ 
    if(t.size()<Gnumm){ 
//        cout<<"no spanning tree"<<endl; 
    } 
    else{
        int weight=0; 
        for(set<Edge>::iterator itr=t.begin();itr!=t.end();itr++){
            weight=weight+(*itr).weight; 
        } 
        cout<<weight<<endl; 
        for(set<Edge>::iterator itr=t.begin();itr!=t.end();itr++){
            cout<<(*itr).begin<<" "<<(*itr).end<<endl;
            weight=weight+(*itr).weight; 
        } 
        return weight; 
    } 
} 

        


/* 
 * This function is the prim algorithm for the basic scheme.The function return the total 
 * weight of mst. we first insert a start node into the set<HeadNode> tv. Then get a minmum edge,
 * whose two end nodes, one is in tv set, the other is not. When the set<Edge> t size is equal to 
 * Gnumm, which is size of mst. The algorithm stop. 
 * */
int prim(HeadNode hnode[],int Gnumm){//Gnumm=Gnum-1 
    set<HeadNode> tv;
    HeadNode addnode;
/* 
 * set the first addnode as the node who has adjacent node.
 * the program need to do this because that it is possible that a node is
 * isolated. In this case, there  will be no spanning tree
 * */ 
    for(int i=0;i<Gnumm+1;i++){ 
       if(hnode[i].link!=NULL){
         addnode=hnode[i]; 
         break; 
       } 
    } 
    tv.insert(addnode); 
    set<Edge> t;
/*
 * judge whether the set<Edge> t has achieved generating mst, if not, continue
 * */
    Start=clock(); 
    for(Edge edge;(t.size()<Gnumm)&&(tv.size()<Gnumm+1);t.insert(edge)){ //t.size()==Gnumm when loop break 
      edge.begin=-1; edge.end=-1; edge.weight=INF;
/* 
 * select the min edge, whose two end nodes, one is in tv set, the other is not
 * */
      for(std::set<HeadNode>::iterator itr=tv.begin();itr!=tv.end();++itr){ 
          for(Node* node=(*itr).link;node!=NULL;node=node->next){
              if(tv.find(hnode[node->info])!=tv.end()) continue; 
              if(node->weight<edge.weight){ 
                  edge.weight=node->weight; 
                  edge.begin=(*itr).info;
                  edge.end=node->info; 
              }  
          } 
      } 
    tv.insert(hnode[edge.end]); 
    }
    Time=clock()-Start; 
/* 
 * print and return result
 * */
    if(t.size()<Gnumm){ 
//        cout<<"no spanning tree"<<endl; 
    } 
    else{
        int weight=0; 
        for(set<Edge>::iterator itr=t.begin();itr!=t.end();itr++){
            weight=weight+(*itr).weight; 
        }
        cout<<weight<<endl; 
        for(set<Edge>::iterator itr=t.begin();itr!=t.end();itr++){
           cout<<(*itr).begin<<" "<<(*itr).end<<endl;
        }
//        cout<<"total prim time:"<<Time<<endl; 
        return weight; 
    } 
} 

/* 
 * This function is add a new node, whose info is end, value is weight,
 * to the HeadNode addnode. This function is used for building the adjacency list
 * */
void add(HeadNode &addnode,int end, int weight){ 
    Node *node=new Node; 
    node->info=end; 
    node->weight=weight; 
    node->next=addnode.link; 
    addnode.link=node; 
} 


/*
 * This function is to delete a node from a Headnode, the node info is end. 
 * This function is used fo building the adjacency list. 
 * */ 
void dlt(HeadNode &dltnode,int end){
    if(&dltnode==NULL||dltnode.link==NULL){ 
//        cout<<"dltnode is NULL"<<endl; 
    }

    Node *n=dltnode.link; 
    if(n!=NULL&&n->info==end){ 
        dltnode.link=n->next;
        return; 
    }
    while(n->next!=NULL&&n->next->info!=end){
        n=n->next; 
    }
    n->next=n->next->next;
} 


/* 
 * This function is to judge whether the HeadNode hnode[begin] 
 * has a adjacancy node end.
 * */
bool isexist(HeadNode hnode[],int begin,int end){ 
    Node *n=hnode[begin].link; 
    while(n!=NULL){ 
        if(n->info==end){ 
            return true; 
        } 
        n=n->next; 
    } 
    return false; 
} 

/* 
 * This function is to judge whether the nodes are all visited.
 * This function it used for bfs algorithm.
 **/
bool isconnect(bool isvisited[], int Gnum){ 
    for(int i=0;i<Gnum;i++){ 
        if(!isvisited[i]){ 
            return false; 
        } 
    } 
    return true; 
} 

/*
 * This function is a depth first search algorithm. The function is to judge whether the graph
 * is connected. If it is connected, return true. Otherwise, return false. 
 * */
bool bfs(HeadNode hnode[], bool isvisited[], int Gnum,set<Edge> &redundant,int startnum){ 
    for(int i=0;i<Gnum;i++){ 
        isvisited[i]=false; 
    } 
    queue<int> q; 
    q.push(startnum); 
    isvisited[startnum]=true; 
    while(!q.empty()){ 
        int x=q.front(); 
        q.pop();
        Node *n=hnode[x].link; 
        while(n!=NULL){ 
            if(!isvisited[n->info]){ 
                q.push(n->info);
                isvisited[n->info]=true;
            } 
            else{ 
                Edge e;
                e.begin=x;
                e.end=n->info;
                e.weight=n->weight; 
                redundant.insert(e); 
            } 
            n=n->next; 
        } 
    } 
    return isconnect(isvisited,Gnum); 
} 

/*
 * This function is to find a node that hasn't been visited, 
 * return the node's id.
 * */
int unconnectnode(bool isvisited[], int Gnum){ 
    for(int i=0;i<Gnum;i++){ 
        if(!isvisited[i]){ 
            return i; 
        } 
    }
} 


/*
 * This funciton is to find a node that has been visited.
 * return the node's id. 
 * */
int connectnode(bool isvisited[], int Gnum){ 
    for(int i=0;i<Gnum;i++){ 
        if(isvisited[i]){ 
            return i;
        } 
    } 
} 

/*
 * This function is to print out the adjacency list(graph) that the 
 * program generated.
 * */
void printgraph(HeadNode hnode[],int Gnum){ 
    Node *n;
    for(int i=0;i<Gnum;i++){ 
        if(hnode[i].link==NULL){ 
            continue; 
        } 
        n=hnode[i].link;
        cout<<"node:"<<i<<endl; 
        while(n!=NULL){ 
            cout<<n->info<<" "<<n->weight<<endl;
            n=n->next; 
        } 
    } 
} 

/*
 * This function is to make every edge be undirected.
 * The method is to find a (begin,end,weight) edge, insert
 * a (end,begin,weight) edge to adjacency list.
 * */
void undirectgraph(HeadNode hnode[],int Gnum){ 
    Node *n;
    for(int i=0;i<Gnum;i++){ 
        if(hnode[i].link==NULL){ 
            continue; 
        } 
        n=hnode[i].link;
        while(n!=NULL){ 
            if(!isexist(hnode,n->info,i)){ 
                add(hnode[n->info],i,n->weight);
            } 
            n=n->next; 
        } 
    } 
} 


/* 
 * This function is to generate a random connected graph. There are mainly two parts.
 * Part 1: 
 * The function firstly generated the required density edges. 
 * All edges should be efficient. That means every two nodes has only one edge. In this implementation,
 * there are three cases. 
 * Part 2: 
 * After we generated efficient edges, we use bfs function to judege whether the graph is connected. If it is 
 * connected,return; Otherwise, we have a set<Edge> redundant, which stores the redundant edge connected two visited 
 * nodes. In this case, we generate a new edge between unconnected node connected node, delete one edge from redundant set. 
 * */
void randominit(int Gnum,int density,HeadNode hnode[]){ 
    int Edgenum=Gnum*(Gnum-1)/2*density/100; 
//    cout<<"Edge num:"<<Edgenum<<endl; 
    for(int i=0;i<Edgenum;){
        Edge e; 
        e.begin=rand()%(Gnum);
        e.end=rand()%Gnum; 
        e.weight=rand()%(1000)+1;
/* 
 * there are three cases that the edge is inefficient 
 * case1: edge is a circle 
 * case2: the edge has been generated 
 * case3: the edge hasn't been generated, however, the 
 *        opposite direction edge has been generated
 * */
        if(e.begin==e.end||isexist(hnode,e.begin,e.end)||isexist(hnode,e.end,e.begin)){ //do i need to overload find?  
            continue; 
        } 
        else{ 
            add(hnode[e.begin],e.end,e.weight);  
            i++; 
        } 
    } 
/* 
 * next we are going to judge whether the graph is connected
 * if it is not connected, we add one edge(connect one point
 * isvisited,one point not visited), and delete a edge from 
 * redundant edge set and hnode list 
 * */
    set<Edge> redundant;
    bool isvisited[Gnum];
    int startnum=unconnectnode(isvisited,Gnum); 
    while(bfs(hnode,isvisited,Gnum,redundant,startnum)!=true){
        startnum=connectnode(isvisited,Gnum); 
        int end=unconnectnode(isvisited,Gnum); 
        int begin=connectnode(isvisited,Gnum);
        add(hnode[begin],end,rand()%(1000)+1); 
//        cout<<"redundant size:"<<redundant.size()<<endl; 
        if(redundant.size()==0){ 
//            cout<<"error:there isn't enough edges for graph"<<endl; 
        } 
        set<Edge>:: iterator itr=redundant.begin();
        dlt(hnode[(*itr).begin], (*itr).end); 
        redundant.clear(); 
    }
/* 
 * print graph, adjacency list
 * printgraph(hnode,Gnum);
 * */ 
/*
 * make the graph to be undirected
 * */
    undirectgraph(hnode,Gnum);  
/* 
 * print graph, adjacency list
 * printgraph(hnode,Gnum);
 * */ 
} 




int main(int argc, char* argv[]){
    int Gnum,Edgenum,Density; 
    std::string arg = argv[1]; 
    if(arg=="-r"){ 
        Gnum=atoi(argv[2]); 
        Density=atoi(argv[3]); 
    } 
    else if(arg=="-s"||arg=="-f"){ 
        ifstream fin(argv[2]);  
        fin>>Gnum>>Edgenum; 
    } 
    HeadNode *hnode=new HeadNode[Gnum];
    for(int i=0;i<Gnum;i++){ 
        hnode[i].info=i; 
    } 
    if(arg=="-r") randominit(Gnum,Density,hnode);
    else if(arg=="-s"||arg=="-f"){
        ifstream fin(argv[2]); 
        fin>>Gnum>>Edgenum; 
        for(int i=0;i<Edgenum;i++){ 
            int begin,end,cost; 
            fin>>begin>>end>>cost; 
            add(hnode[begin],end,cost); 
            add(hnode[end],begin,cost); 
        } 
    } 
            
     if(arg=="-r"||arg=="-f"){ 
         int weightf=primf(hnode,Gnum-1);
     } 
     if(arg=="-r"||arg=="-s"){ 
         int weight=prim(hnode,Gnum-1); 
     } 
} 




