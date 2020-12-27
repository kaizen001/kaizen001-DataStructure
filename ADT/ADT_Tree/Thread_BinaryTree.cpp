/* 线索二叉树的结点定义 */
enum Tags{Link, Thread};//孩子，线索

template<class ElemType>
struct Thread_BinaryTreeNode
{
       Thread_BinaryTreeNode<ElemType> *LChild, *RChild;
       ElemType data;
       Tags lTag = Thread, rTag = Thread;

};
template<class ElemType>
bool visit(Thread_BinaryTreeNode<ElemType> * root){
     
    if(!root) return false;
    else{
        cout<<root->data<<" ";
        return true;
    }
}
//中序线索二叉树
template<class ElemType>
class Thread_BinaryTree{
private:
    Thread_BinaryTreeNode<ElemType> *root;   // 根结点指针
    void Thread_BinaryTreeDestroy_Cursive( Thread_BinaryTreeNode<ElemType> *T ); //销毁树（递归部分，private）
    void InThreading( Thread_BinaryTreeNode<ElemType> *root, Thread_BinaryTreeNode<ElemType> * &pre ); //中序线索化二叉树（递归, private）
    //建立二叉树的存储结构 (递归）
    Thread_BinaryTreeNode<ElemType>* CreateThreadBinaryTree(ElemType x[], ElemType &empty, int &n);
    void Location_Cursive( Thread_BinaryTreeNode<ElemType> * root, const ElemType &x, Thread_BinaryTreeNode<ElemType> * &location );
public:
    //无参数的构造函数
    Thread_BinaryTree():root(NULL){}
    //带参数的构造函数
    Thread_BinaryTree(const ElemType &item){root = new Thread_BinaryTreeNode<ElemType>(item);}
    //生成树
    //void makeBinaryTree( const ElemType &item, BinaryTree &left, BinaryTree &right);
    //析构函数
    ~Thread_BinaryTree(){Thread_BinaryTreeDestroy();}
    //重载函数:赋值
    //LinkList<ElemType>& operator=(LinkList<ElemType> &List);
    //销毁线索二叉树
    void Thread_BinaryTreeDestroy();
    //判断线索二叉树是否为空
    bool Thread_BinaryTreeisEmpty() const{return root == NULL;}
    //获取根结点元素值
    ElemType GetRootData() const{ return root->data;}
    //设置根结点
    void SetRoot(Thread_BinaryTreeNode<ElemType> * p){ root = p;}
    //返回指向根结点的指针
    Thread_BinaryTreeNode<ElemType> * GetRoot() const{ return root;}
    //查找值为x的结点的位置 （递归）
    Thread_BinaryTreeNode<ElemType> * Location(ElemType &x);
    //在中序线索二叉树上查找值为x的结点的中序前驱结点
    Thread_BinaryTreeNode<ElemType> * FindPrior_InorderTree( Thread_BinaryTreeNode<ElemType> * pointer );
    //在中序线索二叉树上查找值为x的结点的中序后继结点
    Thread_BinaryTreeNode<ElemType> * FindNext_InorderTree( Thread_BinaryTreeNode<ElemType> * pointer );
    //二叉树的中序线索化
    Thread_BinaryTreeNode<ElemType>* InOrderThreading(Thread_BinaryTreeNode<ElemType> *root);
    //中序线索二叉树的遍历
    bool InOrderTraverse() const{return InThreading_Traverse(root,visit);}  //中序遍历（递归）
    bool InThreading_Traverse(Thread_BinaryTreeNode<ElemType> *root, bool (*visit)(Thread_BinaryTreeNode<ElemType> *root)) const;
    //建立二叉树的存储结构 (递归）
    void CreateThreadBinaryTree(ElemType &str, ElemType &empty);
};

template<class ElemType>
bool Thread_BinaryTree<ElemType>::InThreading_Traverse( Thread_BinaryTreeNode<ElemType> *T, bool (*visit)(Thread_BinaryTreeNode<ElemType> *T) ) const{
    bool out;
    if (T->lTag != Thread){
        out = InThreading_Traverse(T->LChild,visit);
        if(out == 0)return false;
    }
    out = visit(T);
    if(out == 0)return false;
    if (T->rTag != Thread){
        out = InThreading_Traverse(T->RChild,visit);
        if(out == 0)return false;
    }
    return true;
    
}
template<class ElemType>
void Thread_BinaryTree<ElemType>::Thread_BinaryTreeDestroy(){
    Thread_BinaryTreeDestroy_Cursive(root);
    delete root;
    root = nullptr;
}
template<class ElemType>
void Thread_BinaryTree<ElemType>::Thread_BinaryTreeDestroy_Cursive( Thread_BinaryTreeNode<ElemType> *T ){
    if (T == nullptr) return;
    else{
        if (T->lTag != Thread) {
            Thread_BinaryTreeDestroy_Cursive(T->LChild);
            delete T->LChild;
            T->LChild = nullptr;
        }
        if (T->rTag != Thread) {
            Thread_BinaryTreeDestroy_Cursive(T->RChild);
            delete T->RChild;
            T->RChild = nullptr;
        }
    }
}
template<class ElemType>
void Thread_BinaryTree<ElemType>::CreateThreadBinaryTree(ElemType &str, ElemType &empty){
    ElemType tmp, t[100];
    int num = 0;
    stringstream input_T(str);
    while(input_T >> tmp){
         t[num] = tmp;
         num++;
    }
    num = 0;
    SetRoot(CreateThreadBinaryTree(t, empty, num));
    Thread_BinaryTreeNode<ElemType> *pre = new Thread_BinaryTreeNode<ElemType>(),*d;
    d = pre;
    InThreading(root, pre);
    pre->rTag = Thread;
    delete d;
}
//建立二叉树的存储结构 (递归部分，成员函数）
template<class ElemType>
Thread_BinaryTreeNode<ElemType>* Thread_BinaryTree<ElemType>::CreateThreadBinaryTree(ElemType x[], ElemType &empty, int &n){
    ElemType ch = x[n];
    n++;
    if (ch == empty)return nullptr;
    else{
        Thread_BinaryTreeNode<ElemType> *Node = new Thread_BinaryTreeNode<ElemType>;
        Node->data = ch;
        Node->lTag = Link;
        Node->LChild = CreateThreadBinaryTree(x, empty, n);
        Node->rTag = Link;
        Node->RChild = CreateThreadBinaryTree(x, empty, n);
        return Node;
    }
}
template<class ElemType>
void Thread_BinaryTree<ElemType>::InThreading( Thread_BinaryTreeNode<ElemType> *root, Thread_BinaryTreeNode<ElemType> * &pre ){
    if(root!=nullptr){
        InThreading(root->LChild, pre);
        if (root->LChild == nullptr) {
            root->LChild = pre;
            root->lTag = Thread;
        }
        if (pre->RChild == nullptr) {
            pre->RChild = root;
            pre->rTag = Thread;
        }
        pre = root;
        InThreading(root->RChild, pre);
    }
}
template<class ElemType>
Thread_BinaryTreeNode<ElemType> * Thread_BinaryTree<ElemType>::Location(ElemType &x){
    Thread_BinaryTreeNode<ElemType> * location = nullptr;
    Location_Cursive(root, x,location);
    return location;
}
template<class ElemType>  //指针location为查找结果
void Thread_BinaryTree<ElemType>::Location_Cursive( Thread_BinaryTreeNode<ElemType> * root, const ElemType &x, Thread_BinaryTreeNode<ElemType> * &location ){
    if (root->data == x&&location==nullptr) {
        location = root;
    }
    else{
        if (root->lTag != Thread&&location==nullptr) {
            Location_Cursive(root->LChild, x, location);
        }
        if (root->rTag != Thread&&location==nullptr) {
            Location_Cursive(root->RChild, x, location);
        }
    }
}
