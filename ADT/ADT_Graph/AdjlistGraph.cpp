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
    bool DFS(int u, int visited[]); //DFS遍历（递归部分）
    bool CheckRoute(int u,int v,int visited[]); //检查两个结点之间是否有路径存在（递归部分，私有成员函数）

public:
    adjlist_graph(const string &kd,const vector<TypeOfVer> v); //构造函数构造一个只有结点没有边的图。
    adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e); ////构造函数构造一个无权图。5个参数的含义：图的类型、结点数、边数、结点集和边集
    adjlist_graph(const string &kd,const vector<TypeOfVer> &v,const vector<vector<int>> &e, const vector<TypeOfEdge> &w); //构造函数构造一个有权图。
    bool GraphisEmpty() { return Vers == 0; }  //判断图空否
    string GetGraphKind(){ return GraphKind; }
    bool GetVer(int u, TypeOfVer &data); //取得G中指定顶点的值
    TypeOfVer GetVer(int u){return verList[u].ver;}; //取得G中指定顶点的值
    int GetFirstAdjVex(int u); //返回G中指定顶点u的第一个邻接顶点的位序（顶点集）。若顶点在G中没有邻接顶点，则返回-1
    int GetNextAdjVex(int u, int v); //返回G中指定顶点u的下一个邻接顶点（相对于v）的位序（顶点集）。若顶点在G中没有邻接顶点，则返回false
    int Get_Degree(int u);//求指定顶点的（出）度（无向图/网：度； 有向图/网：出度 ）
    int Get_InDegree(int u);//求有向图指定顶点的入度
    bool GetWeight(int u, int v, TypeOfEdge &w);//对于有权图，取两端点为v1和v2的边上的权值。获取成功，返回true；否则，返回false
    bool PutVer(int u, TypeOfVer data); //对G中指定顶点赋值
    bool InsertVer(const TypeOfVer &data); //往G中添加一个顶点
    int LocateVer(TypeOfVer data); //返回G中指定顶点的位置
    bool ExistEdge(int u, int v);
    bool PrintVer();  //输出顶点集
    void PrintKind();
    bool PrintAdjList();  //输出邻接矩阵
    int GetVerNum(){ return Vers;}    //取得当前顶点数
    int GetEdgeNum(){ return Edges;}  //取得当前边数
    bool CheckRoute(int u, int v);//检查两个结点之间是否有路径存在（外壳部分，公有成员函数）
    bool Insert_Edge(int u, int v); //无权图插入一条边
    bool Insert_Edge(int u, int v, TypeOfEdge w); //有权图插入一条边
    bool DeleteVer(int data); //往G中删除一个顶点
    bool DeleteEdge( int u, int v ); //删除边 (外壳：有向（删除1条边）， 无向（删除2条边））
    void DFS_Traverse(int u); //DFS遍历（外壳部分）
    void BFS_Traverse(int u); //BFS遍历
    bool isDAG();//有向无环图（DAG）的判断
    bool TopSort(vector<int> &topsort); //topsort：拓扑排序序列的序号信息
    ~adjlist_graph(); //析构函数
};
template<class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::isDAG(){
    vector<int> tops;
    return TopSort(tops);
}
template<class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::TopSort(vector<int> &topsort){
    vector<int> inDegree(Vers);
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    queue<int> que;
    for (int i = 0; i<Vers; i++) {
        inDegree[i] = Get_InDegree(i);
        if (inDegree[i] == 0) que.push(i);
    }
    topsort.clear();
    
    while(!que.empty()){
        topsort.push_back(que.front());
        int buff = que.front();
        que.pop();
        visited[buff] = 1;
        
        edgeNode<TypeOfEdge> *p = verList[buff].next;
        while(p!=nullptr){
            if (!visited[p->data]) {
                inDegree[p->data]--;
                if (inDegree[p->data] == 0) {
                    que.push(p->data);
                }
            }
            p = p->next;
        }
        
    }
    for (int i = 0; i<Vers; i++)
        if (!visited[i]) {
            return false;
        }
    delete[] visited;
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::CheckRoute(int u ,int v){
    if (u == v) return true;
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    
    visited[u] = 1;
    bool flag = false;
    flag = CheckRoute(u,v, visited);
    
    delete[] visited;
    return flag;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::CheckRoute(int u,int v,int visited[]){
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while (p!=nullptr) {
        if(p->data == v)return true;
        if (visited[p->data]==0) {
            visited[p->data] = 1;
            if(CheckRoute(p->data,v, visited))return true;
        }
        
    }
    return false;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::ExistEdge(int u, int v){
    if (u>=Vers||v>=Vers) return false;
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while(p != nullptr){
        if(p->data == v) return true;
        p = p->next;
    }
    return false;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::GetWeight(int u, int v, TypeOfEdge &w){
    if (u>=Vers||v>=Vers) {
        return false;
    }
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while(p != nullptr){
        if(p->data == v){
            w = p->weight;
            return true;
        }
        p = p->next;
    }
    return false;
}
template <class TypeOfVer, class TypeOfEdge>
void adjlist_graph<TypeOfVer, TypeOfEdge>::BFS_Traverse(int u){
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    
    cout<<verList[u].ver;
    visited[u] = 1;
    queue<int> q;
    q.push(u);
    
    while(!q.empty()){
        int pos=q.front();
        q.pop();
        edgeNode<TypeOfEdge> *p = verList[pos].next;
        while (p!=nullptr) {
            if (visited[p->data]!=1) {
                q.push(p->data);
                cout<<"->"<<verList[p->data].ver;
                visited[p->data] = 1;
            }
            p = p->next;
        }
    }
    delete[] visited;
}
template <class TypeOfVer, class TypeOfEdge>
void adjlist_graph<TypeOfVer, TypeOfEdge>::DFS_Traverse(int u){
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    
    cout<<verList[u].ver;
    visited[u] = 1;
    DFS(u, visited);
    
    delete[] visited;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer, TypeOfEdge>::DFS(int u,int visited[]){
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while(p!=nullptr) {
        if (visited[p->data]==0) {
            cout<<"->"<<verList[p->data].ver;
            visited[p->data] = 1;
            DFS(p->data, visited);
        }
        p = p->next;
        
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::Insert_Edge(int u,int v,TypeOfEdge w){
    if (u>=Vers||v>=Vers) return false;
    edgeNode<TypeOfEdge> *e = verList[u].next;
    while(e!=nullptr){
        if (e->data == v) {
            return false;
        }
        e = e->next;
    }
    
    e = new edgeNode<TypeOfEdge>(v,w,verList[u].next);
    verList[u].next = e;
    Edges++;
    if (GraphKind[0] == 'U') {
        e = new edgeNode<TypeOfEdge>(u,w,verList[v].next);
        verList[v].next = e;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjlist_graph<TypeOfVer,TypeOfEdge>::Insert_Edge(int u,int v){
    if (u>=Vers||v>=Vers) return false;
    edgeNode<TypeOfEdge> *e = verList[u].next;
    while(e!=nullptr){
        if (e->data == v) {
            return false;
        }
        e = e->next;
    }
    
    e = new edgeNode<TypeOfEdge>(v,verList[u].next);
    verList[u].next = e;
    Edges++;
    if (GraphKind[0] == 'U') {
        e = new edgeNode<TypeOfEdge>(u,verList[v].next);
        verList[v].next = e;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
int adjlist_graph<TypeOfVer,TypeOfEdge>::Get_InDegree(int u){
    if (u>=Vers||GraphKind[0] == 'U') return -1;
    int i = 0;
    edgeNode<TypeOfEdge> *p = nullptr;
    for(int j = 0;j<Vers;j++){
        p = verList[j].next;
        while (p!=nullptr) {
            if(j!=u){
                if (p->data == u) {
                    i++;
                    break;
                }
                p = p->next;
            }
            else{
                break;
            }
        }
    }
    return i;
}
template <class TypeOfVer, class TypeOfEdge>
int adjlist_graph<TypeOfVer,TypeOfEdge>::Get_Degree(int u){
    if (u>=Vers) return -1;
    int i = 0;
    edgeNode<TypeOfEdge> *p = verList[u].next;
    while(p!=nullptr){
        p = p->next;
        i++;
    }
    return i;
}
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
