#ifndef adjListGraph_h
#define adjListGraph_h

#include <iostream>
#include "priorityQueue.h"
#include "DisjointSet.h"
#include "linkQueue.h"
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void dfs()const;
    void bfs()const;
    void EulerCircuit(TypeOfVer start);     //欧拉回路，无向图
    void topSort()const;                    //拓扑排序，有向无环图
    void criticalPath()const;               //寻找关键路径以及各结点的时间
    void kruskal()const;                    //Kruskal算法求最小生成树
    void prim(TypeOfEdge noEdge)const;      //prim算法求最小生成树
    void unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const;//求非加权图的单源最短路径
    void dijkstra(TypeOfVer start,TypeOfEdge noEdge)const;//求单源加权图的最短路径

private:
    struct edgeNode
    {
        int end;           //终点编号
        TypeOfEdge weight; //边的权值
        edgeNode *next;

        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
    };

    struct verNode
    {
        TypeOfVer ver;  //顶点值
        edgeNode *head; //对应单链表的头指针

        verNode(edgeNode *h = NULL) { head = h; }
    };

    verNode *verList;
    int find(TypeOfVer v) const
    {
        for (int i = 0; i < Vers; ++i)
            if (verList[i].ver == v)
                return i;
    }
    int Vers, Edges;

    struct EulerNode{
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver){NodeNum = ver;next = NULL;}
    };

    struct edge{
        int beg,end;
        TypeOfEdge w;
        bool operator<(const edge&rp) {return w<rp.w;}
    };

    void dfs(int start,bool visited[])const;
    verNode *clone()const;
    void EulerCircuit(int start,EulerNode*&beg,EulerNode*&end);
    void printPath(int start,int end,int prev[])const;
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize;
    Edges = 0;
    verList = new verNode[Vers];
    for (int i = 0; i < Vers; ++i)
        verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *p;
    for (int i = 0; i < Vers; ++i)
    {
        while ((p = verList[i].head) != NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete []verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u = find(x);
    int v = find(y);
    if (u != Vers && v !=  Vers)
    {
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u = find(x), v = find(y);
    edgeNode *p = verList[u].head;

    if (p == NULL)
        return;
    if (p->end == v)
    {
        verList[u].head = p->next;
        delete p;
        --Edges;
        return;
    }

    while (p->next != NULL && p->next->end != v)
        p = p->next;
    if (p->next != NULL)
    {
        --Edges;
        edgeNode *q = p->next;
        p->next = p->next->next;
        delete q;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
    int u = find(x);
    int v = find(y);
    edgeNode *p = verList[u].head;
    while (p && p->end != v)
        p = p->next;
    if (p == NULL)
        return false;
    else
        return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs()const{
    bool *visited=new bool [Vers];      //记录每个结点是否已被访问
    for(int i = 0; i < Vers; ++i) visited[i]=false;

    cout<<"深度优先遍历： "<<endl;

    for(int i = 0; i < Vers; ++i){
        if(visited[i]==true) continue;
        dfs(i,visited);
        cout<<endl;                     //一个顶点已经完全遍历
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start,bool visited[])const{
    edgeNode *p=verList[start].head;
    cout<<verList[start].ver<<'\t';                         //访问start结点

    visited[start]=true;
    while(p!=NULL){
        if(visited[p->end]==false) dfs(p->end,visited);     //对start的后继节点执行dfs
        p=p->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs()const{
    bool *visited=new bool[Vers];
    int currentNode;
    linkQueue<int> q;
    edgeNode *p;

    for(int i=0;i<Vers;++i) visited[i]=false;       //初始化所有元素为未访问

    cout<<"广度优先遍历："<<endl;

    for(int i = 0; i < Vers; ++i){                  
        if(visited[i]==true) continue;
        q.enQueue(i);
        while(!q.isEmpty()){
            currentNode=q.deQueue();                //当前结点出队访问
            if(visited[currentNode]==true) continue;
            cout<<verList[currentNode].ver<<'\t';
            visited[currentNode]=true;
            p=verList[currentNode].head;
            while(p!=NULL){                         //将刚刚访问过的结点的所有未访问过的后继节点进队
                if(visited[p->end]==false) q.enQueue(p->end);
                p=p->next;
            }
        }
        cout<<endl;                                 //一个顶点已经完全遍历
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start){
    EulerNode *beg,*end,*p,*q,*tb,*te;        //beg,end为欧拉回路的起点和终点
    int numOfDegree,i;
    edgeNode *r;
    verNode *tmp;

    //检查是否存在欧拉回路
    if(Edges==0){
        cout<<"不存在欧拉回路"<<endl;
        return;
    }
    for(i=0;i<Vers;++i){
        numOfDegree=0;
        r=verList[i].head;
        while(r!=NULL){
            ++numOfDegree;
            r=r->next;
        }
        if(numOfDegree%2==1){
            cout<<"不存在欧拉回路"<<endl;
            return;
        }
    }

    //寻找起始节点的编号
    i=find(start);
    //创建一份邻接表的副本
    tmp=clone();

    //寻找从i出发的路径，路径的起点和终点地址分别是beg和end
    EulerCircuit(i,beg,end);
    while(true){
        p=beg;
        while(p->next != NULL){         //检查p的后继节点是否有边尚未访问
            if(verList[p->next->NodeNum].head!=NULL) break; //p的后继节点有边尚未访问
            else p=p->next;
        }
            if(p->next==NULL) break;    //所有的边都已被访问
            q=p->next;                  //尚有未被访问边的结点
            EulerCircuit(q->NodeNum,tb,te);//从此结点开始找一段回路
            te->next=q->next;
            p->next=tb;
            delete q;
    }

    //恢复原图
    delete []verList;
    verList=tmp;

    //显示得到的欧拉回路
    cout<<"欧拉回路为："<<endl;
    while(beg!=NULL){
        cout<<verList[beg->NodeNum].ver<<'\t';
        p=beg;
        beg=beg->next;
        delete p;
    }
    cout<<endl;
}

template <class TypeOfVer,class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode* adjListGraph<TypeOfVer, TypeOfEdge>::clone()const{
    verNode*tmp=new verNode[Vers];
    edgeNode*p;
    for(int i=0;i<Vers;++i){
        tmp[i].ver=verList[i].ver;
        p=verList[i].head;
        while(p!=NULL){
            tmp[i].head=new edgeNode(p->end,p->weight,tmp[i].head);
            p=p->next;
        }
    }
    return tmp;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start,EulerNode*&beg,EulerNode*&end){
    int nextNode;
    beg=end=new EulerNode(start);   //将起始结点放入欧拉回路
    while(verList[start].head!=NULL){//起始结点尚有边未被访问
        nextNode=verList[start].head->end; 
        remove(start,nextNode);
        remove(nextNode,start);
        end->next=new EulerNode(nextNode);
        start=nextNode; 
        end=end->next;
    }
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::topSort()const{
    linkQueue<int>que;
    edgeNode *p;
    int current;
    int *inDegree=new int [Vers];

    for(int i=0;i<Vers;++i) inDegree[i]=0;
    for(int i=0;i<Vers;++i){
        for(p=verList[i].head;p!=NULL;p=p->next)
            ++inDegree[p->end];
    }
    for(int i=0;i<Vers;++i)  que.enQueue(i);
    cout<<"拓扑序列为："<<endl;
    while(!que.isEmpty()){
        current=que.deQueue();
        cout<<verList[current].ver<<'\t';
        for(p=verList[current].head;p!=NULL;p=p->next){
            if(--inDegree[p->end]==0)
                que.enQueue(p->end);
        }
    }
    cout<<endl;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::criticalPath()const{
    TypeOfEdge *le=new TypeOfEdge[Vers],*ee=new TypeOfEdge[Edges];//ee保存每个结点的最早发生时间，le保存最迟发生时间
    int *top=new int[Vers],*inDegree=new int [Vers];  //top数组用于保存拓扑序列，inDegree存放每个结点的入度
    linkQueue<int> q;
    int i;
    edgeNode *p;
    
    //找出拓扑序列，放入数组top
    for(int i=0;i<Vers;++i) inDegree[i]=0;
    for(int i=0;i<Vers;++i){        //计算每个结点的入度
        for(p=verList[i].head;p!=NULL;p=p->next)  ++inDegree[p->end];
    }

    for(i=0;i<Vers;++i){            //将入度为零的结点入队
        if(inDegree[i]==0) q.enQueue(i);
    }
    i=0;
    while(!q.isEmpty()){
        top[i]=q.deQueue();
        for(p=verList[top[i]].head;p!=NULL;p=p->next){
            if(--inDegree[p->end]==0) q.enQueue(p->end);
        }
        ++i;
    }
    
    //找最早发生时间
    for(i=0;i<Vers;++i) ee[i]=0;
    for(i=0;i<Vers;++i){
        for(p=verList[top[i]].head;p!=NULL;p=p->next){
            if(ee[p->end]<ee[top[i]]+p->weight) ee[p->end]=ee[top[i]]+p->weight;
        }
    }

    //找最晚发生时间
    for(i=0;i<Vers;++i) le[i]=ee[top[Vers-1]];
    for(i=Vers-1;i>=0;--i){
        for(p=verList[top[i]].head;p!=NULL;p=p->next){
            if(le[p->end]-p->weight<le[top[i]]) le[top[i]]=le[p->end]-p->weight;
        }
    }
    for(int i=0;i<Vers;++i)
        if(le[top[i]]==ee[top[i]]) cout<<"("<<verList[top[i]].ver<<", "<<ee[top[i]]<<")";
}


template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::kruskal()const{
    int edgesAccepted=0,u,v;
    edgeNode*p;
    edge e;
    DisjointSet ds(Vers);
    priorityQueue <edge>pq;
    
    //生成优先级队列
    for(int i=0;i<Vers;++i){
        for(p=verList[i].head;p!=NULL;p=p->next){
            if(i<p->end){
                e.beg=i;
                e.end=p->end;
                e.w=p->weight;
                pq.enQueue(e);
            }
        }
    }

    //开始归并
    while(edgesAccepted<Vers-1){
        e=pq.deQueue();
        u=ds.Find(e.beg);
        v=ds.Find(e.end);
        if(u!=v){       //加入(u,v)后不会形成回路
            edgesAccepted++;
            ds.Union(u,v);
            cout<<'('<<verList[e.beg].ver<<','<<verList[e.end].ver<<')\t';
        }
    }
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::prim(TypeOfEdge noEdge)const{
    bool *flag=new bool [Vers];
    TypeOfEdge *lowCost=new TypeOfEdge [Vers];
    int *startNode=new int [Vers];

    edgeNode *p;
    TypeOfEdge min; //min为到达所有V-U中的结点的距离的最小值
    int start,i,j;

    for(i=1;i<Vers;++i){        //初始化，所有节点都不在生成树中
        flag[i]=false;
        lowCost[i]=noEdge;
    }

    start=0;                    //将0作为第一个加入生成树的结点

    for(i=1;i<Vers;++i){
        flag[start]=true;//将start标记为已在u中
        min=noEdge;

        for(p=verList[start].head;p!=NULL;p=p->next){//检查start的边
            if(!flag[p->end]&&lowCost[p->end]>p->weight){//更新距离信息
                lowCost[p->end]=p->weight;
                startNode[p->end]=start;
            }
        }
        
        for(j=0;j<Vers;++j)//寻找U到V-U的权值最小的边并更新start
            if(lowCost[j]<min) {min=lowCost[j];start=j;}
        cout<<'('<<verList[startNode[start]].ver<<','<<verList[start].ver<<'\t';
        lowCost[start]=noEdge;     //将到达新的start的边的权值设置为无穷大，表示寻找边时不再考虑该结点
    }

    delete []flag;
    delete []startNode;
    delete []lowCost;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::unweightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const{
    linkQueue<int>q;
    TypeOfEdge *distance=new TypeOfEdge[Vers];
    int *prev=new int [Vers];
    int u,sNo;
    edgeNode *p;

    for(int i=0;i<Vers;++i)  distance[i]=noEdge;//初始化

    //寻找起始结点的编号
    sNo=find(start);

    //寻找最短路径
    distance[sNo]=0;
    prev[sNo]=sNo;
    q.enQueue(sNo);

    while(!q.isEmpty()){
        u=q.deQueue();
        for(p=verList[u].head;p!=NULL;p=p->next){
            if(distance[p->end]==noEdge){
                distance[p->end]=distance[u]+1;
                prev[p->end]=u;
                q.enQueue(p->end);
            }
        }
    }
    //输出最短路径
    for(int i=0;i<Vers;++i){
        cout<<"从"<<start<<"到"<<verList[i].ver<<"的路径为"<<endl;
        printPath(sNo,i,prev);
        cout<<endl;
    }
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::printPath(int start,int end,int prev[])const{
    if(start==end){
        cout<<verList[start].ver;
        return;
    }
    printPath(start,prev[end],prev);
    cout<<"-"<<verList[end].ver;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::dijkstra(TypeOfVer start,TypeOfEdge noEdge)const{
    TypeOfEdge *distance=new TypeOfEdge[Vers];
    int *prev=new int [Vers];
    bool *known=new bool [Vers];

    int u,sNo,i,j;
    edgeNode*p;
    TypeOfEdge min;

    for(i=0;i<Vers;++i){
        known[i]=false;
        distance[i]=noEdge;
    }

    sNo=find(start);
    distance[sNo]=0;
    prev[sNo]=sNo;
    for(i=1;i<Vers;++i){
        min=noEdge;
        for(j=0;j<Vers;++j){    //寻找不在S中的具有最短距离的结点
            if(!known[j]&&distance[j]<min){
                min=distance[j];
                u=j;
            }
        }
        known[u]=true;          //将u放入S
        for(p=verList[u].head;p!=NULL;p=p->next){   //更新u的邻接点距离
            if(!known[p->end]&&distance[p->end]>min+p->weight){
                distance[p->end]=min+p->weight;
                prev[p->end]=u;
            }
        }
    }
    for(i=0;i<Vers;++i){
        cout<<"从"<<start<<"到"<<verList[i].ver<<"的路径为："<<endl;
        printPath(sNo,i,prev);
        cout<<'\t长度为：'<<distance[i]<<endl;
    }
}

#endif