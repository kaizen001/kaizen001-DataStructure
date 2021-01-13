using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjmatrix_graph{
private:
    int Vers;        //顶点数
    int Edges;       //边数
    vector<vector<TypeOfEdge>> edge;  //存放邻接矩阵（TypeOfEdge表示顶点关系类型。对于无权图，用1或0，表示相邻否；对于带权图，则为权值类型）
    vector<TypeOfVer> ver;    //存放结点值
    TypeOfEdge noEdge;  //邻接矩阵中的∞的表示值
    string GraphKind;   //图的种类标志 DG（有向图）, DN（有向网）, UDG（无向图）, UDN（无向网）网有权 图无权

    bool DFS(int u,int visited[]); //DFS遍历（递归部分）
    bool CheckRoute(int u,int v ,int visited[]);//检查两个结点之间是否有路径存在（递归部分，私有成员函数）

public:
    adjmatrix_graph( const string &kd, const vector<TypeOfVer> d, const TypeOfEdge noEdgeFlag=0); //构造函数构造一个只有结点没有边的图。4个参数的含义：图的类型、结点数、结点值和邻接矩阵中表示结点间没有边的标记（无权图：0，有权图：输入参数定）
    adjmatrix_graph(const string &kd,const vector<TypeOfVer> d, const vector<vector<TypeOfEdge>> e); //构造函数构造一个无权图。5个参数的含义：图的类型、结点数、边数、结点集和边集
    adjmatrix_graph(const string &kd, const TypeOfEdge noEdgeFlag,const vector<TypeOfVer> d, const vector<vector<TypeOfEdge>> e,const vector<TypeOfEdge> w); //构造函数构造一个有权图。7个参数的含义：图的类型、结点数、边数、无边标记、结点集、边集、权集
    bool GraphisEmpty() { return Vers == 0; }  //判断图空否
    string GetGraphKind(){ return GraphKind; }
    bool GetVer(int u, TypeOfVer &data); //取得G中指定顶点的值
    int GetFirstAdjVex(int u, TypeOfVer &v); //返回G中指定顶点u的第一个邻接顶点的位序（顶点集）。若顶点在G中没有邻接顶点，则返回-1
    int GetNextAdjVex(int u, int v, TypeOfVer &w); //返回G中指定顶点u的下一个邻接顶点（相对于v）的位序（顶点集）。若顶点在G中没有邻接顶点，则返回-1
    int Get_InDegree(int u);//求指定顶点的入度
    int Get_Degree(int u);//求有向图指定顶点的出度
    bool PutVer(int u, TypeOfVer data); //对G中指定顶点赋值
    bool InsertVer(const TypeOfVer &data); //往G中添加一个顶点
    int LocateVer(TypeOfVer data); //返回G中指定顶点的位置
    bool ExistEdge(int u, int v);//检查指定2个顶点是否是邻接顶点
    bool PrintMatrix();  //输出邻接矩阵
    bool PrintAll();
    bool PrintVers();
    bool PrintKind();
    int GetVerNum(){ return Vers;}    //取得当前顶点数
    int GetEdgeNum(){ return Edges;}  //取得当前边数
    bool Insert_Edge(int u, int v); //无权图插入一条边
    bool Insert_Edge(int u, int v, TypeOfEdge w); //有权图插入一条边
    bool DeleteVer(const TypeOfVer &data); //往G中删除一个顶点
    bool Delete_Edge(int u, int v); //无权图删除一条边
    void DFS_Traverse(int u); //DFS遍历（外壳部分）
    void BFS_Traverse(int u); //BFS遍历
    bool CheckRoute(int u, int v);//检查两个结点之间是否有路径存在（外壳部分，公有成员函数）
    ~adjmatrix_graph(){}; //析构函数
};
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::Insert_Edge(int u, int v, TypeOfEdge w){
    if (edge[u][v]!=noEdge) return false;
    if (*(GraphKind.end()-1)=='G') return false;
    Edges++;
    if (GraphKind[0] == 'U') {
        edge[u][v]=w;
        edge[v][u]=w;
    }else{
        edge[u][v]=w;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::Insert_Edge(int u, int v){
    if (edge[u][v]!=noEdge) return false;
    if (*(GraphKind.end()-1)=='N') return false;
    Edges++;
    if (GraphKind[0] == 'U') {
        edge[u][v]=1;
        edge[v][u]=1;
    }else{
        edge[u][v]=1;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::ExistEdge(int u, int v){
    if (u>=Vers||v>=Vers) return false;
    return edge[u][v]!=noEdge/*&&edge[v][u]!=noEdge*/;
}
template <class TypeOfVer, class TypeOfEdge>
int adjmatrix_graph<TypeOfVer, TypeOfEdge>::Get_Degree(int u){
    if (u>=Vers) {
        return -1;
    }
    int n = 0;
    for(auto elm : edge[u]){
        if (elm != noEdge) n++;
    }
    n = n==0?-1:n;
    return n;
}
template <class TypeOfVer, class TypeOfEdge>
int adjmatrix_graph<TypeOfVer, TypeOfEdge>::Get_InDegree(int u){
    if (u>=Vers) {
        return -1;
    }
    int n = 0;
    for(auto el2d : edge){
        if (el2d[u] != noEdge) n++;
    }
    n = n==0?-1:n;
    return n;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::CheckRoute(int u ,int v){
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
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::CheckRoute(int u,int v,int visited[]){
    for (int i = 0; i<Vers; i++) {
        if(edge[u][i]!=noEdge&&i == v)return true;
        if (visited[i]==0&&edge[u][i]!=noEdge) {
            visited[i] = 1;
            if(CheckRoute(i,v, visited))return true;
        }
        
    }
    return false;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::Delete_Edge(int u, int v){
    if (edge[u][v] == noEdge) {
        return false;
    }
    Edges--;
    if (GraphKind[0] == 'U') {
        edge[u][v] = noEdge;
        edge[v][u] = noEdge;
    }
    else{
        edge[u][v] = noEdge;
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
void adjmatrix_graph<TypeOfVer, TypeOfEdge>::BFS_Traverse(int u){
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    
    cout<<ver[u];
    visited[u] = 1;
    queue<int> q;
    q.push(u);
    
    while(!q.empty()){
        int pos=q.front();
        q.pop();
        
        for (int i = 0; i<Vers; i++) {
            if (edge[pos][i] != noEdge&&visited[i]!=1) {
                q.push(i);
                cout<<"->"<<ver[i];
                visited[i] = 1;
            }
        }
    }
    
    delete[] visited;
}
template <class TypeOfVer, class TypeOfEdge>
void adjmatrix_graph<TypeOfVer, TypeOfEdge>::DFS_Traverse(int u){
    int *visited  = new int [Vers];
    for (int i = 0; i<Vers; i++) visited[i] = 0;
    
    cout<<ver[u];
    visited[u] = 1;
    DFS(u, visited);
    
    delete[] visited;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::DFS(int u,int visited[]){
    for (int i = 0; i<Vers; i++) {
        if (visited[i]==0&&edge[u][i]!=noEdge) {
            cout<<"->"<<ver[i];
            visited[i] = 1;
            DFS(i, visited);
        }
        
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
int adjmatrix_graph<TypeOfVer, TypeOfEdge>::GetNextAdjVex(int u, int v, TypeOfVer &w){
    int i = 0;
    if (u==Vers) {
        return -1;
    }
    int flag = 0;
    for(const auto &elm:edge[u]){
        i++;
        if (elm!=noEdge) {
            flag++;
            if (flag == v+1) {
                break;
            }
        }
    }
    if (i==Vers||flag!=v+1) {
        return -1;
    }
    else return i-1;
}
template <class TypeOfVer, class TypeOfEdge>
int adjmatrix_graph<TypeOfVer, TypeOfEdge>::GetFirstAdjVex(int u, TypeOfVer &v){
    int i = 0;
    if (u==Vers) {
        return -1;
    }
    for(const auto &elm:edge[u]){
        i++;
        if (elm!=noEdge) break;
    }
    if (i==Vers) {
        return -1;
    }
    else return i-1;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::DeleteVer(const TypeOfVer &data){
    int p = LocateVer(data);
    if (p==-1) {
        return false;
    }
    Vers--;
    ver.erase(ver.begin()+p);
    edge.erase(edge.begin()+p);
    for (auto &el2d:edge) {
        if (el2d[p] != noEdge) {
            if (GraphKind[0] == 'U') {
                Edges-=2;
            }
            else Edges--;
        }
        el2d.erase(el2d.begin()+p);
    }
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
int adjmatrix_graph<TypeOfVer, TypeOfEdge>::LocateVer(const TypeOfVer data){
    for (int i = 0; i<Vers; i++) {
        if (data == ver[i]) {
            return i;
        }
    }
    return -1;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::InsertVer(const TypeOfVer &data){
    for(auto &el2d:edge){
        el2d.push_back(noEdge);
    }
    Vers++;
    ver.push_back(data);
    
    edge.push_back(vector<TypeOfEdge>(Vers,noEdge));
    return 1;
}
template <class TypeOfVer, class TypeOfEdge>
adjmatrix_graph<TypeOfVer, TypeOfEdge>::adjmatrix_graph( const string &kd,const vector<TypeOfVer> d, const TypeOfEdge noEdgeFlag){
    GraphKind = kd;
    Vers = d.size();
    ver = d;
    Edges = 0;
    noEdge = noEdgeFlag;
    for (int i = 0; i<Vers; i++) {
        vector<TypeOfEdge> buff(Vers,noEdge);
        edge.push_back(buff);
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjmatrix_graph<TypeOfVer, TypeOfEdge>::adjmatrix_graph(const string &kd,const vector<TypeOfVer> d, const vector<vector<TypeOfEdge>> e){
    GraphKind = kd;
    ver = d;
    Vers = (int)d.size();
    Edges = (int)e.size();
    noEdge = 0;
    for (int i = 0; i<Vers; i++) {
        vector<TypeOfEdge> buff(Vers,noEdge);
        edge.push_back(buff);
    }
    if (GraphKind[0] == 'U') {
        for(auto &elm:e){
            edge[elm[0]][elm[1]] = 1;
            edge[elm[1]][elm[0]] = 1;
        }
    }
    else{
        for(auto &elm:e){
            edge[elm[0]][elm[1]] = 1;
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjmatrix_graph<TypeOfVer, TypeOfEdge>::adjmatrix_graph(const string &kd, const TypeOfEdge noEdgeFlag,const vector<TypeOfVer> d, const vector<vector<TypeOfEdge>> e,const vector<TypeOfEdge> w){
    GraphKind = kd;
    ver = d;
    Vers = d.size();
    Edges = e.size();
    noEdge = noEdgeFlag;
    for (int i = 0; i<Vers; i++) {
        vector<TypeOfEdge> buff(Vers,noEdge);
        edge.push_back(buff);
    }
    if (GraphKind[0] == 'U') {
        for(int i = 0;i<e.size();i++){
            edge[e[i][0]][e[i][1]] = w[i];
            edge[e[i][1]][e[i][0]] = w[i];
        }
    }
    else{
        for(int i = 0;i<e.size();i++){
            edge[e[i][0]][e[i][1]] = w[i];
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::PrintAll(){
    cout<<GraphKind<<endl;
    if (ver.empty()) return 0;
    cout<<ver[0];
    for(int i = 1;i<ver.size();i++)cout<<' '<<ver[i];
    cout<<endl<<endl;
    for(auto &el2d:edge){
        for(auto &elm:el2d)cout<<elm<<' ';
        cout<<endl;
    }
    return 1;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::PrintMatrix(){
    if (ver.empty()) return 0;
    for(int i = 0;i<Vers;i++)cout<<edge[0][i]<<' ';
    for(int i = 1;i<Vers;i++){
        cout<<endl;
        for(auto &elm:edge[i])cout<<elm<<' ';
    }
    return 1;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::PrintVers(){
    if (ver.empty()) return 0;
    cout<<ver[0];
    for(int i = 1;i<ver.size();i++)cout<<' '<<ver[i];
    return 1;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjmatrix_graph<TypeOfVer, TypeOfEdge>::PrintKind(){
    cout<<GraphKind<<endl;
    return 1;
}
