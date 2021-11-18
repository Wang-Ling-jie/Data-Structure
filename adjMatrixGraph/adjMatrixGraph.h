#ifndef adjMatrixGraph_h
#define adjMatrixGraph_h

template <class TypeOfVer,class TypeOfEdge>
class adjMatrixGraph{
    public:
        adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
        void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
        void remove(TypeOfVer x,TypeOfVer y);
        bool exist(TypeOfVer x,TypeOfVer y)const;
        ~adjMatrixGraph();
    private:
        TypeOfVer*ver;          //存放邻接矩阵
        TypeOfEdge**edge;       //存放结点值
        TypeOfEdge noEdge;      //邻接矩阵中无穷大的表示值
        int find(TypeOfVer v)const{
            for(int i=0;i<Vers;++i) if(ver[i]==v) return i;
        }
        int Vers,Edges;
        void floyd()const;
};

template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag){
    Vers=vSize;
    Edges=0;
    noEdge=noEdgeFlag;

    //存放结点都数组的初始化
    ver=new TypeOfVer[vSize];
    for(int i=0;i<vSize;++i){
        ver[i]=d[i];
    }

    //邻接矩阵的初始化
    edge=new TypeOfEdge*[vSize];
    for(int i=0;i<vSize;++i){
        edge[i]=new TypeOfEdge[vSize];
        for(int j=0;j<vSize;++j) edge[i][j]=noEdge;
        edge[i][i]=0;
    }
}

template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::~adjMatrixGraph(){
    for(int i=0;i<Vers;++i)  delete []edge[i];
    delete []ver;
    delete []edge;
}

template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
    ++Edges;
    int u=find(x),v=find(y);
    edge[u][v]=w;
}

template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y){
    --Edges;
    int u=find(x),v=find(y);
    edge[u][v]=noEdge;
}

template <class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x,TypeOfVer y)const{
    int u=find(x),v=find(y);
    if(edge[u][v]==noEdge) return false;
    return true;
}

template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::floyd()const{
    TypeOfEdge**d=new TypeOfEdge*[Vers];
    int **prev=new int*[Vers];
    int i,j,k;

    //初始化
    for(int i=0;i<Vers;++i){
        d[i]=new TypeOfEdge[Vers];
        prev[i]=new int [Vers];
        for(int j=0;j<Vers;++j){
            d[i][j]=edge[i][j];
            prev[i][j]=(edge[i][j]!=noEdge)?i:-1;
        }
    }

    //迭代过程
    for(k=0;k<Vers;++k){
        for(i=0;i<Vers;++i){
            for(j=0;j<Vers;++j){
                if(d[i][k]+d[k][j]<d[i][j]){
                    d[i][j]=d[i][k]+d[k][j];
                    prev[i][j]=prev[k][j];
                }
            }
        }
    }

    //输出过程
    cout<<"最短路径长度："<<endl;
    for(i=0;i<Vers;++i){
        cout<<endl;
        for(j=0;j<Vers;++j)  cout<<d[i][j]<<'\t';
    }

    cout<<"最短路径："<<endl;
    for(i=0;i<Vers;++i){
        cout<<endl;
        for(j=0;j<Vers;++j) cout<<prev[i][j]<<'\t';
    }
}

#endif