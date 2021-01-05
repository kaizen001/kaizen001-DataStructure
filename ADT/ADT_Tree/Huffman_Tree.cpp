using namespace std;

/* Huffman树的结点定义 */

template<class ElemType>
struct Huffman_TreeNode{
    Huffman_TreeNode *LChild, *RChild;  //左、右孩子指针
    ElemType data;   //结点值
    int weight;      //结点的权值
};

template<class ElemType>
bool visit(Huffman_TreeNode<ElemType> * root){
     
    if(root==nullptr) return false;
    else{
       if(root->LChild==nullptr && root->RChild==nullptr)
           cout<<root->data<<"("<<root->weight<<") ";
       else
           cout<<"("<<root->weight<<") ";
    }
    return true;
     
}

const int MAX_INT = 32767;

//Huffman树
template<class ElemType>
class Huffman_Tree{
private:
    Huffman_TreeNode<ElemType> *root;
    //销毁树（递归准备，private）T为根结点,销毁后保留根结点T，其左右孩子为空
    void BinaryTreeDestroy_Cursive(Huffman_TreeNode<ElemType> *T );
    //销毁树
    void BinaryTreeDestroy();
    void Location_Cursive( Huffman_TreeNode<ElemType> * root, const ElemType &x, Huffman_TreeNode<ElemType> * &location );//指针location为查找结果查找值为x的结点的位置（递归）
    void GetParent_Cursive(Huffman_TreeNode<ElemType> * parent, Huffman_TreeNode<ElemType> * x, Huffman_TreeNode<ElemType> * &result) const;//获取父结点（递归）
    
public:
    //带参数的构造函数
    Huffman_Tree(vector<ElemType> &data, vector<int> &w);
    //析构函数
    ~Huffman_Tree(){BinaryTreeDestroy();;}
    //获取根结点
    Huffman_TreeNode<ElemType> * GetRoot() const{ return root;}
    //前序遍历
    bool PreOrderTraverse() const{return PreOrderTraverse(root,visit);}  //前序遍历（递归）
    bool PreOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const;  //前序遍历（递归）
    //中序遍历
    bool InOrderTraverse() const{return InOrderTraverse(root,visit);}  //中序遍历（递归）
    bool InOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const;
    //后序遍历
    bool PostOrderTraverse() const{return PostOrderTraverse(root,visit);}  //后序遍历（递归）
    bool PostOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const;
    //层次遍历
    bool LayerOrderTraverse() const{return LayerOrderTraverse(visit);};
    bool LayerOrderTraverse(bool (*visit)(Huffman_TreeNode<ElemType> *T)) const;
    //删除huffman树
    void clear(Huffman_TreeNode<ElemType> *t);
    //查找从根结点到元素值为x的结点的路径，路径经过的结点指针存放在顺序队列中（用于获取编码）
    void FindPath( ElemType & x, stack<Huffman_TreeNode<ElemType> *> &Q );
    //查找结点的位置（外壳）
    Huffman_TreeNode<ElemType> * Location(ElemType &x);
    //获取父结点
    Huffman_TreeNode<ElemType> * GetParent(Huffman_TreeNode<ElemType> * x);
    bool Print_HuffmanTree();
    void Print_HuffmanTree( Huffman_TreeNode<ElemType> *root, int i );
};
template<class ElemType>
void Huffman_Tree<ElemType>::Print_HuffmanTree( Huffman_TreeNode<ElemType> *root, int i ){
     if(root==nullptr) return;
     
     if(root->RChild!=nullptr) Print_HuffmanTree(root->RChild, i + 1);
     for(int j = 1; j <= i; j++) cout<<"   ";
     if(!root->LChild && !root->RChild){
        cout<<root->weight<<"  "<<endl;
        for(int j = 1; j <= i; j++) cout<<"   ";
        cout<<"("<<root->data<<")"<<"  "<<endl;
     }
     else cout<<root->weight<<"  "<<endl;
     if(root->LChild!=nullptr) Print_HuffmanTree(root->LChild, i + 1);
          
}
//打印Huffman树
template<class ElemType>
bool Huffman_Tree<ElemType>::Print_HuffmanTree(){
    
    int layer = 0;

    if(root == NULL)  return false;
    Print_HuffmanTree(root, layer);
    return true;
}

template<class ElemType>
Huffman_TreeNode<ElemType> * Huffman_Tree<ElemType>::Location(ElemType &x){
    Huffman_TreeNode<ElemType> * location = nullptr;
    Location_Cursive(root, x,location);
    return location;
}
template<class ElemType>  //指针location为查找结果
void Huffman_Tree<ElemType>::Location_Cursive( Huffman_TreeNode<ElemType> * root, const ElemType &x, Huffman_TreeNode<ElemType> * &location ){
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
Huffman_TreeNode<ElemType> * Huffman_Tree<ElemType>::GetParent(Huffman_TreeNode<ElemType> * x){
    if (root == x||root == nullptr) return nullptr;
    Huffman_TreeNode<ElemType> * result = nullptr;
    GetParent_Cursive(root, x, result);
    return result;
}

template<class ElemType>
void Huffman_Tree<ElemType>::GetParent_Cursive(Huffman_TreeNode<ElemType> * parent, Huffman_TreeNode<ElemType> * x, Huffman_TreeNode<ElemType> * &result) const{
    if (parent->LChild != nullptr&&result==nullptr) {
        if (parent->LChild == x) result = parent;
        else GetParent_Cursive(parent->LChild, x, result);
    }
    if (parent->RChild != nullptr&&result==nullptr) {
        if (parent->RChild == x) result = parent;
        else GetParent_Cursive(parent->RChild, x, result);
    }
}
template<class ElemType>
void Huffman_Tree<ElemType>::FindPath( ElemType &x, stack<Huffman_TreeNode<ElemType> *> &Q ){
    Huffman_TreeNode<ElemType> *p = Location(x);
    if (p == nullptr) return;
    while(p!=root){
        Q.push(p);
        p = GetParent(p);
    }
    Q.push(root);
}
template<class ElemType>
bool Huffman_Tree<ElemType>::LayerOrderTraverse(bool (*visit)(Huffman_TreeNode<ElemType> *T)) const{
    vector<vector<Huffman_TreeNode<ElemType>*>> Layer;
    if (root == nullptr) return false;
    while(1){
        if (Layer.size() == 0) {
            vector<Huffman_TreeNode<ElemType>*> buff;
            buff.push_back(root);
            Layer.push_back(buff);
        }
        else{
            vector<Huffman_TreeNode<ElemType>*> last_layer(Layer[Layer.size()-1]);
            vector<Huffman_TreeNode<ElemType>*> buff;
            for (auto elm:last_layer) {
                if (elm!=nullptr&&elm->LChild!=nullptr) buff.push_back(elm->LChild);
                if (elm!=nullptr&&elm->RChild!=nullptr) buff.push_back(elm->RChild);
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
bool Huffman_Tree<ElemType>::PreOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const{
    bool out;
    if(!visit(T))return false;
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
bool Huffman_Tree<ElemType>::InOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const{
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
bool Huffman_Tree<ElemType>::PostOrderTraverse( Huffman_TreeNode<ElemType> *T, bool (*visit)(Huffman_TreeNode<ElemType> *T) ) const{
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
void Huffman_Tree<ElemType>::BinaryTreeDestroy(){
    BinaryTreeDestroy_Cursive(root);
    delete root;
    root = nullptr;
}
template<class ElemType>
void Huffman_Tree<ElemType>::BinaryTreeDestroy_Cursive( Huffman_TreeNode<ElemType> *T ){
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
Huffman_Tree<ElemType>::Huffman_Tree(vector<ElemType> &data, vector<int> &w){
    if (data.size()!=w.size()) {
        cout<<"数据数不等于权重数";
        return;
    }
    vector<Huffman_TreeNode<ElemType> *> pNode(data.size());
    for (int i = 0; i<data.size(); i++) {
        pNode[i] = new Huffman_TreeNode<ElemType>;
        pNode[i]->data = data[i];
        pNode[i]->weight = w[i];
    }
    sort(pNode.begin(), pNode.end(),[](Huffman_TreeNode<ElemType> *a,Huffman_TreeNode<ElemType> *b){ if(a==nullptr)return false;if(b==nullptr)return true;return a->weight<b->weight;});
    while (pNode.size()>=2&&pNode[1]!=nullptr) {
        Huffman_TreeNode<ElemType> *pl = new Huffman_TreeNode<ElemType>;
        pl->LChild = pNode[0];
        pl->RChild = pNode[1];
        pl->weight=pl->RChild->weight+pl->LChild->weight;
        pNode[0] = pl;
        pNode[1] = nullptr;
        
        sort(pNode.begin(), pNode.end(),[](Huffman_TreeNode<ElemType> *a,Huffman_TreeNode<ElemType> *b){ if(a==nullptr)return false;if(b==nullptr)return true;return a->weight<b->weight;});
    }
    root = pNode[0];
}
