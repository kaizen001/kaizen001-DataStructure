using namespace std;

/* 二叉表的结点定义 */
template<class ElemType>
struct BinaryTreeNode
{
       ElemType data;
       BinaryTreeNode<ElemType> *LChild, *RChild;
       BinaryTreeNode() : LChild(nullptr), RChild(nullptr){} //构造函数1，用于构造根结点
       BinaryTreeNode(const ElemType &item, BinaryTreeNode<ElemType> *Lptr = nullptr, BinaryTreeNode<ElemType> *Rptr = nullptr) //构造函数2，用于构造其他结点
       //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
       {
           LChild = Lptr;
           RChild = Rptr;
           data = item;
       }
       
       ElemType getData(){ return data;}  //取得结点中的数据
       void SetLChild( BinaryTreeNode<ElemType> *link ){ LChild = link; }  //修改结点的左孩子域
       void SetRChild( BinaryTreeNode<ElemType> *link ){ RChild = link; }  //修改结点的右孩子域
       void SetData( ElemType value ){ data = value; }   //修改结点的data域
       BinaryTreeNode<ElemType> * GetLChild() const{ return LChild;} //获取左孩子结点
       BinaryTreeNode<ElemType> * GetRChild() const{ return RChild;} //获取左孩子结点
};
template<class ElemType>
bool visit(BinaryTreeNode<ElemType> * root){
     
    if(!root) return false;
    else{
        cout<<root->data<<" ";
        return true;
    }
}
//作为队列中的元素类型
template<class ElemType>
struct elem{
    BinaryTreeNode<ElemType> *node;
    int num;
};

const int MAXLISTSIZE = 100;
template<class ElemType>
class SqQueue{
private:
    ElemType *elem;   // 存储空间基址
    int front;   // 队头指针
    int rear;   // 队尾指针
    int maxSize;        // 允许的最大存储容量(以sizeof(ElemType)为单位
public:
    //初始化顺序队列
    SqQueue(int ms = 20);
    //删除顺序队列
    ~SqQueue(){QueueDestroy();}
    //将顺序队列置为空
    bool QueueClear();
    //设置顺序栈的长度
    //bool SetListLength(int len);
    //判断顺序队列是否为空
    bool QueueisEmpty() const{ return front == rear; }
    //判断顺序队列是否为满
    bool QueueFull() const{return (rear+1)%maxSize==front?true:false;};
    //用e返回队头元素
    bool GetFront(ElemType &e){e = elem[front];return 1;};
    ElemType GetFront(){return elem[front];};
    //入队
    bool enQueue(ElemType e);
    //出队
    bool deQueue(ElemType &e);
    ElemType deQueue();
    //销毁顺序队列
    bool QueueDestroy();
    //顺序队列最大存储空间加倍
    bool DoubleSpace();
    
    void Trav();
    };

template<class ElemType>
SqQueue<ElemType>::SqQueue(int ms){
    if (ms>MAXLISTSIZE+1) {
        cout<<"ms too large";
        return;
    }
    elem = new ElemType[ms];
    maxSize = ms+1;
    front = 0;
    rear = front;
}

template<class ElemType>
bool SqQueue<ElemType>::QueueDestroy(){
    delete[] elem;
    front = rear = 0;
    elem = nullptr;
    maxSize = 0;
    return 1;
}

template<class ElemType>
bool SqQueue<ElemType>::QueueClear(){
    front = 0;
    rear = front;
    return 1;
}

template<class ElemType>
bool SqQueue<ElemType>::enQueue(ElemType e){
    if (QueueFull()&&(!DoubleSpace())) return false;
    elem[rear] = e;
    rear = (rear+1)%maxSize;
    
    return true;
}

template<class ElemType>
bool SqQueue<ElemType>::deQueue(ElemType &e){
    if (QueueisEmpty()) {
        cout<<"Queue is EMPTY can not de";
        return false;
    }
    e = elem[front];
    front = (front+1)%maxSize;
    return true;
}
template<class ElemType>
ElemType SqQueue<ElemType>::deQueue(){
    if (QueueisEmpty()) {
        cout<<"Queue is EMPTY can not de";
        return NULL;
    }
    int ff = front;
    front = (front+1)%maxSize;
    return elem[ff];
}

template<class ElemType>
bool SqQueue<ElemType>::DoubleSpace(){
    if ((maxSize-1)*2+1>MAXLISTSIZE+1) {
        cout<<"size will BIGGER than MAXLIMIT,DoubleSpace failed";
        return 0;
    }
    maxSize = (maxSize-1) * 2+1;
    ElemType *newBuff = new ElemType[maxSize];
    if (rear<front) {
        for (int i = 0; i<rear; i++) newBuff[i] = elem[i];
        for (int i = front; i<maxSize/2+1; i++)
            newBuff[(maxSize-1)/2+i] = elem[i];
        front = front+(maxSize-1)/2;
    }
    else{
        for (int i = front; i<rear; i++) newBuff[i] = elem[i];
    }
    elem = newBuff;
    return 1;
}

template<class ElemType>
void SqQueue<ElemType>::Trav(){
    int i;
    for (i = rear-1;; i--) {
        i = i%maxSize;
        if (i == front)break;
        cout<<elem[i]->data<<' ';
    }
    cout<<elem[front]->data;
}


//二叉树
template<class ElemType>
class BinaryTree{
private:
    BinaryTreeNode<ElemType> *root;   // 头指针
    //销毁树（递归准备，private）T为根结点,销毁后保留根结点T，其左右孩子为空
    void BinaryTreeDestroy_Cursive( BinaryTreeNode<ElemType> *T );
    //建立二叉树的存储结构
    BinaryTreeNode<ElemType>* CreateBinaryTree(ElemType x[], const ElemType &empty, int &n);
    //拷贝建立二叉树的存储结构
    BinaryTreeNode<ElemType>* CreateBinaryTree(BinaryTreeNode<ElemType> *po);
    void GetParent_Cursive(BinaryTreeNode<ElemType> * parent, ElemType &x, BinaryTreeNode<ElemType> * &result) const;//获取父结点（递归）
    void Location_Cursive( BinaryTreeNode<ElemType> * root, const ElemType &x, BinaryTreeNode<ElemType> * &location );//指针location为查找结果查找值为x的结点的位置（递归）
    //返回以元素值x为根结点的（子）二叉树的高度（递归）
    int GetBinaryTreeHeight_Cursive( BinaryTreeNode<ElemType> *root) const;
    //在以元素值x为根结点的位置插入子树
    bool Insert_ChildTree( BinaryTreeNode<ElemType> * parent, BinaryTreeNode<ElemType> * child);
    //运算符==重载函数
    bool checkEqual(const BinaryTreeNode<ElemType> *root1, const BinaryTreeNode<ElemType> *root2);
    //统计结点个数
    int BinaryTreeSize( BinaryTreeNode<ElemType> *T) const;
    //统计度为2的结点个数
    int CountDegreeTwo( BinaryTreeNode<ElemType> *T ) const;
    //获取二叉树的层数（成员函数，递归部分）
    int GetTreeLayers( BinaryTreeNode<ElemType> *root );
    //按树状打印出二叉树的形状（递归）
    void Print_BinaryTree( BinaryTreeNode<ElemType> *root, int i );
    //统计二叉树叶子的数目 （递归函数）
    void LeafCount_Cursive( BinaryTreeNode<ElemType> *root, int &sum);   //采用先序遍历的递归算法
    //交换二叉树中所有结点的左右子树 （递归）
    void Revolute_Cursive( BinaryTreeNode<ElemType> *root);
public:
    //无参数的构造函数
    BinaryTree():root(nullptr){}
    //带参数的构造函数
    BinaryTree(const ElemType &item){root = new BinaryTreeNode<ElemType>(item);}
    
    BinaryTree(BinaryTree<ElemType> &T);
    //生成树
    void makeBinaryTree( const ElemType &item, BinaryTree &left, BinaryTree &right);
    //析构函数
    ~BinaryTree(){BinaryTreeDestroy();}
    //重载函数:赋值
    //LinkList<ElemType>& operator=(LinkList<ElemType> &List);
    //运算符==重载函数
    bool operator ==(const BinaryTree<ElemType> &T);
    //销毁树
    void BinaryTreeDestroy();
    //销毁子树
    bool ChildTreeDestroy(ElemType &x,bool isRight);
    //清空链表
    //bool LinkQueueClear();
    //计算以元素值x为根结点的（子）二叉树的高度（外壳）
    int GetBinaryTreeHeight(ElemType &x);
    int GetBinaryTreeHeight(){return GetBinaryTreeHeight(root->data);};
    //统计结点个数
    int BinaryTreeSize() const;
    //判断是否是完全二叉树
    bool isCompleteTree() const;
    //统计度为2的结点个数
    int CountDegreeTwo() const;
    //统计二叉树叶子的数目
    int LeafCount();
    //判断二叉树是否为空
    bool BinaryTreeisEmpty() const{return root == nullptr;}
    //获取根结点元素值
    ElemType GetRootData() const{ return root->data;}
    //给元素值为x的结点重新赋值
    bool AssignNodeData(ElemType &x, ElemType &value);
    //返回以元素值x为父结点的孩子结点的指针（外壳，isRight=0，左孩子；isRight=1，右孩子）
    BinaryTreeNode<ElemType> * LocationChild(ElemType &x, bool isRight);
    //查找结点的位置（外壳）
    BinaryTreeNode<ElemType> * Location(ElemType &x);
    //返回指向值为x的结点的兄弟结点的指针（isRight=0，左兄弟；isRight=1，右兄弟）
    BinaryTreeNode<ElemType> * GetSibling(ElemType &x, bool isRight);
    //交换二叉树中所有结点的左右子树 （外壳）
    void Revolute();
    //在以元素值为x的结点的位置插入子树（isRight=0，左孩子；isRight=1，右孩子）
    bool InsertChildTree(BinaryTree<ElemType> &R, ElemType &x, bool isRight);
    //设置根结点
    void SetRoot(BinaryTreeNode<ElemType> * p){ root = p;}
    //获取根结点
    BinaryTreeNode<ElemType> * GetRoot() const{ return root;}
    //获取父结点
    BinaryTreeNode<ElemType> * GetParent(ElemType &x);
    //查找从根结点到元素值为x的结点的路径
    void FindPath( ElemType &x, SqQueue<BinaryTreeNode<ElemType> *> &Q );
    //前序遍历
    bool PreOrderTraverse() const{return PreOrderTraverse(root,visit);}  //前序遍历（递归）
    bool PreOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const;  //前序遍历（递归）
    //中序遍历
    bool InOrderTraverse() const{return InOrderTraverse(root,visit);}  //中序遍历（递归）
    bool InOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const;
    //后序遍历
    bool PostOrderTraverse() const{return PostOrderTraverse(root,visit);}  //后序遍历（递归）
    bool PostOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const;
    //建立二叉树的存储结构 （外壳部分，用户函数）
    //str格式：A B # C D # # E # # F # G # H # #(先序遍历)
    void CreateBinaryTree(ElemType &str,ElemType &empty);
    //打印二叉树
    bool Print_BinaryTree();
    //层次遍历，成员函数
    bool LayerOrderTraverse(bool (*visit)(BinaryTreeNode<ElemType> *T)) const;
    bool LayerOrderTraverse() const{return LayerOrderTraverse(visit);};
};
template<class ElemType>
void BinaryTree<ElemType>::Revolute(){
    Revolute_Cursive(root);
}
template<class ElemType>
void BinaryTree<ElemType>::Revolute_Cursive( BinaryTreeNode<ElemType> *root){
    if(root->LChild==nullptr&&root->RChild==nullptr)return;
    else{
        if(root->LChild!=nullptr)Revolute_Cursive(root->LChild);
        if(root->RChild!=nullptr)Revolute_Cursive(root->RChild);
        BinaryTreeNode<ElemType> *RCO = root->RChild;
        root->RChild = root->LChild;
        root->LChild = RCO;
    }
}
template<class ElemType>
int BinaryTree<ElemType>::LeafCount(){
    int sum = 0;
    LeafCount_Cursive(root, sum);
    return sum;
}
//统计二叉树叶子的数目 （递归函数）
template<class ElemType>
void BinaryTree<ElemType>::LeafCount_Cursive( BinaryTreeNode<ElemType> *root, int &sum){
    if (root->RChild==nullptr&&root->LChild==nullptr) sum++;
    else{
        if (root->LChild!=nullptr)LeafCount_Cursive(root->LChild, sum);
        if (root->RChild!=nullptr)LeafCount_Cursive(root->RChild, sum);
    }
}
template<class ElemType>
bool BinaryTree<ElemType>::Print_BinaryTree(){
    BinaryTreeNode<ElemType> *root;
    int layer = 0;
    root = GetRoot();
    if(root == nullptr)  return false;
    Print_BinaryTree(root, layer);
    return true;
}
template<class ElemType>
void BinaryTree<ElemType>::Print_BinaryTree( BinaryTreeNode<ElemType> *root, int i ){
     if(!root) return;
     
     if(root->RChild!=nullptr) Print_BinaryTree(root->RChild, i + 1);
     for(int j = 0; j < i; j++) cout<<"  ";
     cout<<root->data<<" "<<endl;
     if(root->LChild!=nullptr) Print_BinaryTree(root->LChild, i + 1);
}

template<class ElemType> //Q为存放路径的顺序队列
void BinaryTree<ElemType>::FindPath( ElemType &x, SqQueue<BinaryTreeNode<ElemType> *> &Q ){
    BinaryTreeNode<ElemType> *p = Location(x);
    if (p == nullptr) return;
    while(p!=root){
        Q.enQueue(p);
        p = GetParent(p->data);
    }
    Q.enQueue(root);
}
/*template<class ElemType>
int BinaryTree<ElemType>::GetBinaryTreeHeight(ElemType &x){
    BinaryTreeNode<ElemType> p = Location(x);
    if(p==nullptr)return 0;
    return GetTreeLayers(p);
}
template<class ElemType>
int BinaryTree<ElemType>::GetTreeLayers( BinaryTreeNode<ElemType> *root ){
    if (root->LChild==nullptr&&root->RChild==nullptr) return 1;
    int lh = GetTreeLayers(root->LChild);
    int rh = GetTreeLayers(root->RChild);
    return lh>rh?lh+1:rh+1;
}*/
template<class ElemType>
int BinaryTree<ElemType>::CountDegreeTwo() const{
    return CountDegreeTwo(root);
}
template<class ElemType>
int BinaryTree<ElemType>::CountDegreeTwo( BinaryTreeNode<ElemType> *T ) const{
    if (T->LChild==nullptr&&T->RChild==nullptr) return 0;
    if (T->LChild!=nullptr&&T->RChild!=nullptr){
        int ln = CountDegreeTwo(T->LChild);
        int rn = CountDegreeTwo(T->RChild);
        return ln+rn+1;
    }
    if (T->LChild!=nullptr)return CountDegreeTwo(T->LChild);
    if (T->RChild!=nullptr)return CountDegreeTwo(T->RChild);
    return 0;
}
template<class ElemType>
int BinaryTree<ElemType>::BinaryTreeSize() const{
    if (root == nullptr) return 0;
    return BinaryTreeSize(root);
}
template<class ElemType>
int BinaryTree<ElemType>::BinaryTreeSize(BinaryTreeNode<ElemType> *T) const{
    int ln = 0,rn = 0;
    if (T == nullptr) return 0;
    ln = BinaryTreeSize(T->LChild);
    rn = BinaryTreeSize(T->RChild);
    return ln+rn+1;
}
template<class ElemType>  ////判断是否是完全二叉树
bool BinaryTree<ElemType>::isCompleteTree() const{
    vector<vector<elem<ElemType>>> Layer;
    if (root == nullptr) return false;
    int number = 1;
    while(1){
        if (Layer.size() == 0) {
            vector<elem<ElemType>> Lbuff;
            elem<ElemType> e;
            e.node = root;
            e.num = number;
            number++;
            Lbuff.push_back(e);
            Layer.push_back(Lbuff);
        }
        else{
            vector<elem<ElemType>> last_layer(Layer[Layer.size()-1]);
            vector<elem<ElemType>> Lbuff;
            for (auto elm:last_layer) {
                if ((elm.node)->LChild!=nullptr) {
                    elem<ElemType> e;
                    e.node = (elm.node)->LChild;
                    e.num = number;
                    number++;
                    Lbuff.push_back(e);
                }
                if ((elm.node)->RChild!=nullptr) {
                    elem<ElemType> e;
                    e.node = (elm.node)->RChild;
                    e.num = number;
                    number++;
                    Lbuff.push_back(e);
                }
            }
            if (Lbuff.empty()) break;
            Layer.push_back(Lbuff);
        }
    }
    if (Layer.size() == 1) return true;
    for (auto el2d = Layer.begin(); el2d<Layer.end()-1; el2d++) {
        vector<elem<ElemType>> pareLar(*el2d);
        vector<elem<ElemType>> chilLar(*(el2d+1));
        for(auto pareElm = pareLar.begin();pareElm<pareLar.end();pareElm++){
            if ((*pareElm).node->RChild != nullptr) {
                for(auto chilElm = chilLar.begin();chilElm<chilLar.end();chilElm++){
                    if((*chilElm).node == (*pareElm).node->LChild) {
                        if((*chilElm).num!=((*pareElm).num*2))return false;
                    }
                    if((*chilElm).node == (*pareElm).node->RChild) {
                        if((*chilElm).num!=(((*pareElm).num*2)+1))return false;
                        break;
                    }
                }
            }
            else if((*pareElm).node->LChild != nullptr){
                for(auto chilElm = chilLar.begin();chilElm<chilLar.end();chilElm++){
                    if((*chilElm).node == (*pareElm).node->LChild) {
                        if((*chilElm).num!=((*pareElm).num*2))return false;
                        if ((*chilElm).num!=number-1) return false;
                        return true;
                    }
                }
            }
        }
    }
    
    return 1;
}
template<class ElemType>
bool BinaryTree<ElemType>::operator ==(const BinaryTree<ElemType> &T){
    return checkEqual(root, T.root);
}
template<class ElemType>
bool BinaryTree<ElemType>::checkEqual(const BinaryTreeNode<ElemType> *root1, const BinaryTreeNode<ElemType> *root2){
    if (root1 == nullptr&&root2 == nullptr) return true;
    if (root1 == nullptr&&root2 != nullptr) return false;
    if (root2 == nullptr&&root1 != nullptr) return false;
    if (root1->data!=root2->data) return false;
    bool check_l = checkEqual(root1->LChild, root2->LChild);
    if (check_l == false) return false;
    bool check_r = checkEqual(root1->RChild, root2->RChild);
    if (check_r == false) return false;
    return true;
}
template<class ElemType>
BinaryTreeNode<ElemType> * BinaryTree<ElemType>::GetSibling(ElemType &x, bool isRight){
    BinaryTreeNode<ElemType> *p = GetParent(x);
    if (p==nullptr)return nullptr;
    if (isRight) {
        if(p->RChild->data == x)return nullptr;
        return p->RChild;
    }
    else{
        if(p->LChild->data == x)return nullptr;
        return p->LChild;
    }
}
template<class ElemType>
bool BinaryTree<ElemType>::AssignNodeData(ElemType &x, ElemType &value){
    BinaryTreeNode<ElemType> *p = Location(x);
    if (p==nullptr)return false;
    p->data = value;
    return true;
}
template<class ElemType>
BinaryTree<ElemType>::BinaryTree(BinaryTree<ElemType> &T){
    if(root!= nullptr)BinaryTreeDestroy();
    root = CreateBinaryTree(T.root);
}
template<class ElemType>
BinaryTreeNode<ElemType>* BinaryTree<ElemType>::CreateBinaryTree(BinaryTreeNode<ElemType> *po){
    if (po == nullptr) return nullptr;
    BinaryTreeNode<ElemType> *pl = CreateBinaryTree(po->LChild);
    BinaryTreeNode<ElemType> *pr = CreateBinaryTree(po->RChild);
    BinaryTreeNode<ElemType> *pn = new BinaryTreeNode<ElemType>;
    pn->RChild = pr;
    pn->LChild = pl;
    pn->data = po ->data;
    return pn;;
}
template<class ElemType>
bool BinaryTree<ElemType>::InsertChildTree(BinaryTree<ElemType> &R, ElemType &x, bool isRight){
    BinaryTreeNode<ElemType> *p = nullptr;
    p = Location(x);
    if (p==nullptr)return false;
    if (isRight) {
        BinaryTreeDestroy_Cursive(p->RChild);
        if(p->RChild!=nullptr)delete p->RChild;
        p->RChild = nullptr;
        BinaryTree<ElemType> *buff = new BinaryTree<ElemType>(R);
        p->RChild = buff->root;
        buff->root = nullptr;
        delete buff;
    }
    else{
        BinaryTreeDestroy_Cursive(p->LChild);
        if(p->LChild!=nullptr)delete p->LChild;
        p->LChild = nullptr;
        BinaryTree<ElemType> *buff = new BinaryTree<ElemType>(R);
        p->LChild = buff->root;
        buff->root = nullptr;
        delete buff;
    }
    return true;
}
template<class ElemType>
bool BinaryTree<ElemType>::Insert_ChildTree( BinaryTreeNode<ElemType> * parent, BinaryTreeNode<ElemType> * child){
    
}
template<class ElemType>
bool BinaryTree<ElemType>::ChildTreeDestroy(ElemType &x, bool isRight){
    BinaryTreeNode<ElemType> *p = nullptr;
    p = Location(x);
    if (p==nullptr)return false;
    if (isRight) {
        if (p->RChild == nullptr) return false;
        BinaryTreeDestroy_Cursive(p->RChild);
        delete p->RChild;
        p->RChild = nullptr;
    }
    else {
        if (p->LChild == nullptr) return false;
        BinaryTreeDestroy_Cursive(p->LChild);
        delete p->LChild;
        p->LChild = nullptr;
    }
    return true;
}
template<class ElemType>
BinaryTreeNode<ElemType> * BinaryTree<ElemType>::LocationChild(ElemType &x, bool isRight){
    BinaryTreeNode<ElemType> *p = nullptr;
    p = Location(x);
    if (p==nullptr)return p;
    if (isRight) return p->RChild;
    else return p->LChild;
}

template<class ElemType>
int BinaryTree<ElemType>::GetBinaryTreeHeight(ElemType &x){
    int out = 0;
    BinaryTreeNode<ElemType> * p = Location(x);
    if (p == nullptr) return out;//查找失败
    out = GetBinaryTreeHeight_Cursive(p);
    out++;
    return out;
}
template<class ElemType>
int BinaryTree<ElemType>::GetBinaryTreeHeight_Cursive(BinaryTreeNode<ElemType> *root) const{
    int lH = 0,rH = 0;
    if (root->LChild!=nullptr){
        lH = GetBinaryTreeHeight_Cursive(root->LChild);
        lH++;
    }
    if (root->RChild!=nullptr){
        rH = GetBinaryTreeHeight_Cursive(root->RChild);
        rH++;
    }
    return lH>rH?lH:rH;
}
template<class ElemType>
BinaryTreeNode<ElemType> * BinaryTree<ElemType>::Location(ElemType &x){
    BinaryTreeNode<ElemType> * location = nullptr;
    Location_Cursive(root, x,location);
    return location;
}
template<class ElemType>  //指针location为查找结果
void BinaryTree<ElemType>::Location_Cursive( BinaryTreeNode<ElemType> * root, const ElemType &x, BinaryTreeNode<ElemType> * &location ){
    if (root->data == x&&location==nullptr) {
        location = root;
    }
    else{
        if (root->LChild != nullptr&&location==nullptr) {
            Location_Cursive(root->LChild, x, location);
        }
        if (root->RChild != nullptr&&location==nullptr) {
            Location_Cursive(root->RChild, x, location);
        }
    }
}


template<class ElemType>
BinaryTreeNode<ElemType> * BinaryTree<ElemType>::GetParent(ElemType &x){
    if (root->data == x||root == nullptr) return nullptr;
    BinaryTreeNode<ElemType> * result = nullptr;
    GetParent_Cursive(root, x, result);
    return result;
}

template<class ElemType>
void BinaryTree<ElemType>::GetParent_Cursive(BinaryTreeNode<ElemType> * parent, ElemType &x, BinaryTreeNode<ElemType> * &result) const{
    if (parent->LChild != nullptr&&result==nullptr) {
        if (parent->LChild->data == x) result = parent;
        else GetParent_Cursive(parent->LChild, x, result);
    }
    if (parent->RChild != nullptr&&result==nullptr) {
        if (parent->RChild->data == x) result = parent;
        else GetParent_Cursive(parent->RChild, x, result);
    }
}

template<class ElemType>
bool BinaryTree<ElemType>::LayerOrderTraverse(bool (*visit)(BinaryTreeNode<ElemType> *T)) const{
    vector<vector<BinaryTreeNode<ElemType>*>> Layer;
    if (root == nullptr) return false;
    while(1){
        if (Layer.size() == 0) {
            vector<BinaryTreeNode<ElemType>*> buff;
            buff.push_back(root);
            Layer.push_back(buff);
        }
        else{
            vector<BinaryTreeNode<ElemType>*> last_layer(Layer[Layer.size()-1]);
            vector<BinaryTreeNode<ElemType>*> buff;
            for (auto elm:last_layer) {
                if (elm->LChild!=nullptr) buff.push_back(elm->LChild);
                if (elm->RChild!=nullptr) buff.push_back(elm->RChild);
            }
            if (buff.empty()) break;
            Layer.push_back(buff);
        }
    }
    for(auto el2d:Layer){
        for (auto elm:el2d) {
            if(visit(elm)==0)return 0;
        }
    }
    return 1;
}
template<class ElemType>
bool BinaryTree<ElemType>::PreOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const{
    bool out;
    out = visit(T);
    if(out == 0)return false;
    if (T->LChild != nullptr){
        out = PreOrderTraverse(T->LChild,visit);
        if(out == 0)return false;
    }
    if (T->RChild != nullptr){
        out = PreOrderTraverse(T->RChild,visit);
        if(out == 0)return false;
    }
    return true;
}
template<class ElemType>
bool BinaryTree<ElemType>::InOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const{
    bool out;
    if (T->LChild != nullptr){
        out = InOrderTraverse(T->LChild,visit);
        if(out == 0)return false;
    }
    out = visit(T);
    if(out == 0)return false;
    if (T->RChild != nullptr){
        out = InOrderTraverse(T->RChild,visit);
        if(out == 0)return false;
    }
    return true;
    
}
template<class ElemType>
bool BinaryTree<ElemType>::PostOrderTraverse( BinaryTreeNode<ElemType> *T, bool (*visit)(BinaryTreeNode<ElemType> *T) ) const{
    bool out;
    if (T->LChild != nullptr){
        out = PostOrderTraverse(T->LChild,visit);
        if(out == 0)return false;
    }
    if (T->RChild != nullptr){
        out = PostOrderTraverse(T->RChild,visit);
        if(out == 0)return false;
    }
    out = visit(T);
    if(out == 0)return false;
    return true;
}

template<class ElemType>
void BinaryTree<ElemType>::BinaryTreeDestroy(){
    BinaryTreeDestroy_Cursive(root);
    delete root;
    root = nullptr;
}
template<class ElemType>
void BinaryTree<ElemType>::BinaryTreeDestroy_Cursive( BinaryTreeNode<ElemType> *T ){
    if (T == nullptr) return;
    else{
        if (T->LChild != nullptr) {
            BinaryTreeDestroy_Cursive(T->LChild);
            delete T->LChild;
            T->LChild = nullptr;
        }
        if (T->RChild != nullptr) {
            BinaryTreeDestroy_Cursive(T->RChild);
            delete T->RChild;
            T->RChild = nullptr;
        }
    }
}
template<class ElemType>
void BinaryTree<ElemType>::CreateBinaryTree(ElemType &str, ElemType &empty){
    ElemType tmp, t[100];
    int num = 0;
    stringstream input_T(str);
    while(input_T >> tmp){
         t[num] = tmp;
         num++;
    }
    num = 0;
    SetRoot(CreateBinaryTree(t, empty, num));
}

//建立二叉树的存储结构 (递归部分，成员函数）
template<class ElemType>
BinaryTreeNode<ElemType>* BinaryTree<ElemType>::CreateBinaryTree(ElemType x[], const ElemType &empty, int &n){
        ElemType ch = x[n];
        n++;
        if (ch == empty)return nullptr;
        else{
            BinaryTreeNode<ElemType> *Node = new BinaryTreeNode<ElemType>;
            Node->data = ch;
            Node->LChild = CreateBinaryTree(x, empty, n);
            Node->RChild = CreateBinaryTree(x, empty, n);
            return Node;
        }
}
