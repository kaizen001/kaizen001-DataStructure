#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/* 边表的结点定义 */
template<class TypeOfEdge>
struct edgeNode{
    int data;
    TypeOfEdge weight;
    edgeNode<TypeOfEdge> *next;
    edgeNode(const int &d, edgeNode<TypeOfEdge> *ptr = nullptr) {//构造函数，用于构造其他结点（无权图）
        next = ptr;
        data = d;
    }
    edgeNode(const int &d, const TypeOfEdge &w, edgeNode<TypeOfEdge> *ptr = nullptr) {//构造函数，用于构造其他结点（带权图
        next = ptr;
        data = d;
        weight = w;
    }
};

//图的邻接表类
template<class TypeOfVer, class TypeOfEdge>
struct verNode{
    TypeOfVer ver;
    edgeNode<TypeOfEdge> *next;
    verNode(edgeNode<TypeOfEdge> *h = nullptr){next = h;}
};

template <class TypeOfVer, class TypeOfEdge>
class adjlist_graph{
private:
    int Vers;           //顶点数
    int Edges;          //边数
    vector<verNode<TypeOfVer,TypeOfEdge>> verList;

    string GraphKind;     //图的种类标志

    bool Delete_Edge( int u, int v );
    bool DFS(int u, int &num, int visited[]); //DFS遍历（递归部分）

public:
    adjlist_graph(const string &kd,const vector<TypeOfVer> v); //构造函数构造一个只有结点没有边的图。
    adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e); ////构造函数构造一个无权图。5个参数的含义：图的类型、结点数、边数、结点集和边集
    adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e, const vector<TypeOfEdge> &w); //构造函数构造一个有权图。
    bool GraphisEmpty() { return Vers == 0; }  //判断图空否
    string GetGraphKind(){ return GraphKind; }
    bool GetVer(int u, TypeOfVer &data); //取得G中指定顶点的值
    int GetFirstAdjVex(int u); //返回G中指定顶点u的第一个邻接顶点的位序（顶点集）。若顶点在G中没有邻接顶点，则返回-1
    int GetNextAdjVex(int u, int v); //返回G中指定顶点u的下一个邻接顶点（相对于v）的位序（顶点集）。若顶点在G中没有邻接顶点，则返回false
    bool PutVer(int u, TypeOfVer data); //对G中指定顶点赋值
    bool InsertVer(const TypeOfVer &data); //往G中添加一个顶点
    int LocateVer(TypeOfVer data); //返回G中指定顶点的位置
    bool ExistEdge(int u, int v);
    bool PrintVer();  //输出顶点集
    void PrintKind();
    bool PrintAdjList();  //输出邻接矩阵
    int GetVerNum(){ return Vers;}    //取得当前顶点数
    int GetEdgeNum(){ return Edges;}  //取得当前边数
    bool Insert_Edge(int u, int v); //无权图插入一条边
    bool Insert_Edge(int u, int v, TypeOfEdge w); //有权图插入一条边
    bool DeleteVer(int data); //往G中删除一个顶点
    bool DeleteEdge( int u, int v ); //删除边 (外壳：有向（删除1条边）， 无向（删除2条边））
    void DFS_Traverse(int u); //DFS遍历（外壳部分）
    void BFS_Traverse(int u); //BFS遍历
    ~adjlist_graph(); //析构函数
};
template <class TypeOfVer, class TypeOfEdge>
int adjlist_graph<TypeOfVer,TypeOfEdge>::GetNextAdjVex(int u, int v){
    if (verList[u].next == nullptr) return -1;
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while (p!=nullptr) {
        if (p->data == v) {
            if(p->next == nullptr)return -1;
            else return p->next->data;
        }
        p = p->next;
    }
    return -1;
}
template <class TypeOfVer, class TypeOfEdge>
int adjlist_graph<TypeOfVer,TypeOfEdge>::GetFirstAdjVex(int u){
    if (verList[u].next == nullptr) return -1;
    return verList[u].next->data;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::DeleteVer(int data){
    int num = data;
    if (num == -1) return false;
    edgeNode<TypeOfEdge> *p = verList[num].next;
    while (p!=nullptr) {
        edgeNode<TypeOfEdge> *pdel = p;
        p = p->next;
        delete pdel;
        Edges--;
    }
    verList.erase(verList.begin()+num);
    Vers--;
    for(auto &elm:verList){
        edgeNode<TypeOfEdge> *p = elm.next;
        if (p!=nullptr) {
            if(p->data == num){
                elm.next = p->next;
                delete p;
                if (GraphKind[0]!='U') Edges--;
            }
            else{
                while (p->next!=nullptr) {
                    if (p->next->data == num) {
                        edgeNode<TypeOfEdge> *pdel = p->next;
                        p->next = p->next->next;
                        delete pdel;
                        if (GraphKind[0]!='U') Edges--;
                        break;
                    }
                    p = p->next;
                }
            }
        }
    }
    for (int i = 0; i<Vers; i++) {
        edgeNode<TypeOfEdge> *p = verList[i].next;
        while(p!=nullptr){
            if (p->data>=data) {
                p->data--;
            }
            p = p->next;
        }
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::DeleteEdge( int u, int v){
    Edges--;
    if (GraphKind[0] == 'U') {
        if(Delete_Edge(u, v))return Delete_Edge(v, u);
        Edges++;
        return false;
    }
    bool flag = Delete_Edge(u, v);
    if (flag) {
        return true;
    }
    else {
        Edges++;
        return false;
    }
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::Delete_Edge( int u, int v ){
    edgeNode<TypeOfEdge> *p = verList[u].next;
    if (p==nullptr)return false;
    if (p->data == v) {
        verList[u].next = p->next;
        delete p;
        return true;
    }
    while(p->next!=nullptr){
        if (p->next->data == v) {
            edgeNode<TypeOfEdge> *pdel = p->next;
            p->next = p->next->next;
            delete pdel;
            return true;
        }
        p = p->next;
    }
    return false;
}
template <class TypeOfVer, class TypeOfEdge>
int adjlist_graph<TypeOfVer,TypeOfEdge>::LocateVer(TypeOfVer data){
    int i = 0;
    for (i = 0; i<Vers; i++) {
        if (verList[i].ver == data) {
            return i;
        }
    }
    return -1;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::InsertVer(const TypeOfVer &data){
    Vers++;
    verNode<TypeOfVer,TypeOfEdge> n;
    n.ver = data;
    verList.push_back(n);
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
adjlist_graph<TypeOfVer,TypeOfEdge>::adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e, const vector<TypeOfEdge> &w){
    GraphKind = kd;
    Vers = (int)v.size();
    Edges = (int)e.size();
    verList.resize(Vers);
    for (int i = 0; i<Vers; i++) verList[i].ver = v[i];
    for(int i = 0;i<Edges;i++){
        if (GraphKind[0] == 'U') {
            edgeNode<TypeOfEdge> *p = new edgeNode<TypeOfEdge>(e[i][1]);
            p->next = verList[e[i][0]].next;
            p->weight = w[i];
            verList[e[i][0]].next = p;
            
            p =  new edgeNode<TypeOfEdge>(e[i][1]);
            p->data = e[i][0];
            p->weight = w[i];
            p->next = verList[e[i][1]].next;
            verList[e[i][1]].next = p;
        }
        else{
            edgeNode<TypeOfEdge> *p = new edgeNode<TypeOfEdge>(e[i][1]);
            p->data = e[i][1];
            p->weight = w[i];
            p->next = verList[e[i][0]].next;
            verList[e[i][0]].next = p;
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjlist_graph<TypeOfVer,TypeOfEdge>::~adjlist_graph(){
    for(auto &elm : verList){
        edgeNode<TypeOfEdge> *p = elm.next;
        while(p!=nullptr){
            edgeNode<TypeOfEdge> *pdel = p;
            p = p->next;
            delete pdel;
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjlist_graph<TypeOfVer,TypeOfEdge>::adjlist_graph(const string &kd,const vector<TypeOfVer> v){
    GraphKind = kd;
    Vers = (int)v.size();
    Edges =
    verList.resize(Vers);
    for (int i = 0; i<Vers; i++) {
        verList[i].ver = v[i];
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjlist_graph<TypeOfVer,TypeOfEdge>::adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e){
    GraphKind = kd;
    Vers = (int)v.size();
    Edges = (int)e.size();
    verList.resize(Vers);
    for (int i = 0; i<Vers; i++) verList[i].ver = v[i];
    for(auto el2d:e){
        if (GraphKind[0] == 'U') {
            edgeNode<TypeOfEdge> *p = new edgeNode<TypeOfEdge>(el2d[1]);
            p->next = verList[el2d[0]].next;
            verList[el2d[0]].next = p;
            
            p =  new edgeNode<TypeOfEdge>(el2d[1]);
            p->data = el2d[0];
            p->next = verList[el2d[1]].next;
            verList[el2d[1]].next = p;
        }
        else{
            edgeNode<TypeOfEdge> *p = new edgeNode<TypeOfEdge>(el2d[1]);
            p->data = el2d[1];
            p->next = verList[el2d[0]].next;
            verList[el2d[0]].next = p;
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
void adjlist_graph<TypeOfVer,TypeOfEdge>::PrintKind(){
    cout<<GraphKind;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::PrintVer(){
    if (Vers == 0) return false;
    cout<<verList[0].ver;
    for (int i = 1; i<Vers; i++) {
        cout<<' '<<verList[i].ver;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::PrintAdjList(){
    if (Vers == 0) return false;
    for (int i = 0; i<Vers; i++) {
        if (i==0) cout<<verList[i].ver;
        else cout<<endl<<verList[i].ver;
        edgeNode<TypeOfEdge> *p = verList[i].next;
        while(p!=nullptr) {
            cout<<"->"<<p->data;
            if (*(GraphKind.end()-1)=='N') {
                cout<<'('<<p->weight<<')';
            }
            p = p->next;
        }
    }
    return true;
}

int main()
{
    //类型
    string kind;
    cin>>kind;
    
    //顶点数及定点
    int v;
    cin>>v;
    vector<string> vers(v);
    for (auto &elm:vers) cin>>elm;

    //边数及边集
    int e;
    cin>>e;
    vector<vector<int>> edges(e);
    for (auto &elm:edges) {
        vector<int> buff(2);
        cin>>buff[0]>>buff[1];
        elm = buff;
    }

//    //权值
//    vector<int> w(e);
//    for (auto &elm:w){
//        cin>>elm;
//    }
    
    adjlist_graph<string, int> agraph(kind,vers,edges);
    
//    agraph.PrintKind();
//    cout<<endl;
    agraph.PrintVer();
    cout<<endl;
//    cout<<agraph.GetVerNum();
//    cout<<endl;
//    cout<<agraph.GetEdgeNum();
//    cout<<endl;
    agraph.PrintAdjList();
    cout<<endl<<endl;
    
    int uu,vv;
    cin>>uu>>vv;
    cout<<agraph.GetNextAdjVex(uu, vv);
//    agraph.PrintVer();
//    cout<<endl;
//    cout<<agraph.GetVerNum();
//    cout<<endl;
//    cout<<agraph.GetEdgeNum();
//    cout<<endl;
//    agraph.PrintAdjList();
    
    

    return 0;
}

