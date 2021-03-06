#ifndef DisjointSet_h
#define DisjointSet_h

class DisjointSet{
    private:
        int size;
        int *parent;
    
    public:
        DisjointSet(int s);
        ~DisjointSet(){delete []parent;}
        void Union(int root1,int root2);
        int Find(int x);
};

DisjointSet::DisjointSet(int n){
    size=n;
    parent=new int [size];
    for(int i=0;i<size;++i)  parent[i]=-1;
}

int DisjointSet::Find(int x){
    if(parent[x]<0) return x;
    else return parent[x]=Find(parent[x]);
}

void DisjointSet::Union(int root1,int root2){
    if(root1==root2) return;
    if(parent[root1]>parent[root2]){
        parent[root2]+=parent[root1];
        parent[root1]=root2;
    }
    else{
        parent[root1]+=parent[root2];
        parent[root2]=root1;
    }
}

#endif