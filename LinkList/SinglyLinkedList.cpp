using namespace std;


/* 单链表的结点定义 */
template<class ElemType>
struct LinkNode
{
    ElemType data;
    LinkNode<ElemType> *next;
    
    LinkNode(LinkNode<ElemType> *ptr = nullptr){next = ptr;} //构造函数1，用于构造头结点
    LinkNode(const ElemType &item, LinkNode<ElemType> *ptr = nullptr) //构造函数2，用于构造其他结点
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        next = ptr;
        data = item;
    }
    ElemType getData(){ return data;}  //取得结点中的数据
    void SetLink( LinkNode<ElemType> *link ){ next = link; }  //修改结点的next域
    void SetLink( ElemType value ){ data = value; }   //修改结点的next域
};

//带头结点的单链表
template<class ElemType>
class LinkList
{
   private:
    LinkNode<ElemType> *head;   // 头结点
    LinkNode<ElemType> *tail;   // 尾结点
    int length;
    bool isPosInside(int pos);//判断链表是否有pos位置，pos从零开始，避免不让用length
   public:
    
    LinkList();//无参数的构造函数.
    LinkList(const ElemType &item);//带参数的构造函数.
    LinkList(LinkList<ElemType> &List);//拷贝构造函数
    ~LinkList();//析构函数.
    //重载函数:赋值
    //LinkList<ElemType>& operator=(LinkList<ElemType> &List);
    void ListDestroy();                             //销毁链表.
    void ListClear();                               //清空链表.
    int ListLength() const;                         //返回链表的长度.
    bool ListEmpty() const;                         //判断链表是否为空表.
    bool InsFirst( ElemType e );                    //在首节点之前插入一个结点.
    bool InsBack(ElemType e);                       //在尾节点之前插入一个结点.
    LinkNode<ElemType>* GetHead() {return head;}    //获取链表头结点.
    void SetHead(LinkNode<ElemType> *p){ head = p;} //设置链表头结点.
    LinkNode<ElemType>* GetTail() { return tail;}   //获取链表尾结点.
    ElemType GetElem(int pos);                      //用e返回链表的第i个元素,从零开始.
    bool ListInsert_prior(int pos,ElemType e);      //在链表的第pos个位置之前插入e元素.
    bool ListInsert_next(int pos,ElemType e);       //在链表的第pos个位置之后插入e元素.
    //删除链表的首结点
    //bool DelFirst( ElemType &e);
    void CreateList_Head(int n, ElemType *A);//表头插入法动态生成链表（A为数组）.
    void CreateList_Tail(int n, ElemType *A);//表尾插入法动态生成链表（A为数组）.
    void CreateList_Tail(int n, vector<ElemType> A);
    ElemType ListDelete(int pos);//删除链表的第pos个位置的元素.
    //compare函数，用来判断a和b是否相等
    //bool compare(ElemType a, ElemType *b);
    //按序号查找，从链表的第一个结点开始，判断当前结点是否是第i个，
    //若是，则返回该结点的数据域的值；否则继续后一个，直至表结束。没有第i个结点时返回空。
    bool FindElem( int k, ElemType &e);
    //bool compare(ElemType a, ElemType *b);
    //按值查找，即定位。从链表的第一个结点开始，判断当前结点值是否等于e。
    //若是，则返回该结点的序号；否则继续后一个，直至表结束。找不到时返回0。
    int SearchElem( const ElemType &e) const;
    //返回链表给定数据元素的前驱数据元素的值
    //bool PriorElem(ElemType cur_e, ElemType &pri_e);
    
    bool NextElem(LinkNode<ElemType> *p, ElemType &e);//返回链表给定数据元素的后继数据元素的值.
    //遍历链表
    bool ListTraverse() const;//遍历输出.
};

template<class ElemType>
LinkList<ElemType>::LinkList(){
    this->SetHead(new LinkNode<ElemType>);
    tail = head;
    length = 1;
}

template<class ElemType>
LinkList<ElemType>::LinkList(const ElemType &item){
    this->SetHead(new LinkNode<ElemType>);
    tail = head;
    length = 1;
}

template<class ElemType>
LinkList<ElemType>::~LinkList(){
    ListDestroy();
}

template<class ElemType>
void LinkList<ElemType>::ListDestroy(){
    while(head != nullptr){
        LinkNode<ElemType> * p = head;
        head = head->next;
        delete p;
    }
    head = nullptr;
    tail = head;
    length = 0;
}

template<class ElemType>
bool LinkList<ElemType>::isPosInside(int pos){
    if (pos>=length||pos<0) return false;
    else return true;
    
    /*
    LinkNode<ElemType> *p = head;
    int n = 0;
    while(p->next!=nullptr){
        if (n==pos) {
            return true;
        }
        n++;
        p = p->next;
    }
    return false;
     */
}

template<class ElemType>
void LinkList<ElemType>::ListClear(){
    this->ListDestroy();
    this->SetHead(new LinkNode<ElemType>);
    tail = head;
    length = 1;
}

template<class ElemType>
ElemType LinkList<ElemType>::GetElem(int pos){
    LinkNode<ElemType> *p = head;
    if (!isPosInside(pos)) {
        std::cout<<"错误：此链表中没有这么多元素";
        return head->getData();
    }
    for (int i = 0; i<pos; i++) p = p->next;
    return p->data;
}

template<class ElemType>
int LinkList<ElemType>::ListLength() const{
    return length;
}

template<class ElemType>
bool LinkList<ElemType>::ListEmpty() const{
    return length==1;
}

template<class ElemType>
bool LinkList<ElemType>::InsFirst( ElemType e ){
    LinkNode<ElemType> *p = new LinkNode<ElemType>(e,head);
    this->SetHead(p);
    length++;
    return true;
}
template<class ElemType>
bool LinkList<ElemType>::InsBack( ElemType e ){
    LinkNode<ElemType> *p = new LinkNode<ElemType>(e,head);
    tail->next = p;
    tail = p;
    length++;
    return true;
}

template<class ElemType>
bool LinkList<ElemType>::ListInsert_prior(int pos,ElemType e){
    LinkNode<ElemType> *p = head;
    if (!isPosInside(pos)) {
        std::cout<<"错误：此链表中没有这么多元素";
        return false;
    }
    for (int i = 0; i<pos-1; i++) p = p->next;
    if (pos == 0)this->InsFirst(e);
    else p->SetLink(new LinkNode<ElemType>(e,p->next));
    length++;
    return true;
}

template<class ElemType>
bool LinkList<ElemType>::ListInsert_next(int pos,ElemType e){
    if(isPosInside(pos)&&!isPosInside(pos+1)){
        tail->next = new LinkNode<ElemType>(e);
        tail = tail->next;
        length++;
        return true;
    }
    return this->ListInsert_prior(pos+1, e);
}

template<class ElemType>
bool LinkList<ElemType>::ListTraverse() const{
    LinkNode<ElemType> *p = head;
    for(int i = 0;i<length;i++){
        std::cout<<p->getData()<<' ';
        p = p->next;
    }
    return true;
}

//按序号查找，从链表的第一个结点开始，判断当前结点是否是第i个，
//若是，则返回该结点的数据域的值；否则继续后一个，直至表结束。没有第i个结点时返回空。
template<class ElemType>
bool LinkList<ElemType>::FindElem( int k, ElemType &e){
    if (k>length-1) return false;
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<k; i++) {
        p = p->next;
    }
    e = p->getData();
    return true;
}

//按值查找，即定位。从链表的第一个结点开始，判断当前结点值是否等于e。
//若是，则返回该结点的序号；否则继续后一个，直至表结束。找不到时返回0。
template<class ElemType>
int LinkList<ElemType>::SearchElem( const ElemType &e) const{
    LinkNode<ElemType> *p = head;
    int i = 0;
    while ((p!=nullptr)&&(p->getData()!=e)) {
        p = p->next;
        i++;
    }
    if (p==nullptr) return 0;
    return i;
}

template<class ElemType>
bool LinkList<ElemType>::NextElem(LinkNode<ElemType> *p, ElemType &e){
    if (p == nullptr) return false;
    if (p->next == nullptr) return false;
    e = p->next->gerData();
    return true;
}

template<class ElemType>
ElemType LinkList<ElemType>::ListDelete(int pos){//1.jpg
    if (!isPosInside(pos)) return GetElem(0);
    if (pos == 0) {
        LinkNode<ElemType> *p = head;
        head = head->next;
        ElemType e = p->getData();
        delete p;
        length--;
        return e;
    }
    
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<pos-1; i++) {
        p = p->next;
    }
    ElemType e = p->next->getData();
    LinkNode<ElemType> *deletePtr = p->next;
    p->next = p->next->next;
    delete deletePtr;
    length--;
    return e;
}


template<class ElemType>//表头插入法动态生成链表（A为数组）
void LinkList<ElemType>::CreateList_Head(int n, ElemType *A){
    if (n<0) std::cout<<"n必须大于等于0";
    else for (int i = n-1; i>=0; i--) this->InsFirst(A[i]);
}

template<class ElemType>//表尾插入法动态生成链表（A为数组）
void LinkList<ElemType>::CreateList_Tail(int n, ElemType *A){
    if (n<0) std::cout<<"n必须大于等于0";
    else {
        LinkNode<ElemType> *p = tail;
        for (int i = 0;i<n;i++){
            p->next = new LinkNode<ElemType>(A[i]);
            p = p->next;
        }
        tail = p;
        length+=n;
    }
}

template<class ElemType>//表尾插入法动态生成链表（A为数组）
void LinkList<ElemType>::CreateList_Tail(int n, vector<ElemType> A){
    if (n<0) std::cout<<"n必须大于等于0";
    else {
        LinkNode<ElemType> *p = tail;
        for (int i = 0;i<n;i++){
            p->next = new LinkNode<ElemType>(A[i]);
            p = p->next;
        }
        tail = p;
        length+=n;
    }
}

template<class ElemType>
int InPutLL( LinkList<ElemType> &L,int n){
    for (int i = 0; i<n; i++) {
        ElemType nodeData;
        cin>>nodeData;
        L.InsBack(nodeData);
    }
    L.ListDelete(0);
    
    int m;
    cin>>m;
    return m;
}
template<class ElemType>
void Exchange_L( LinkList<ElemType> &L, int m ){
    vector<ElemType> buff(m);
    for (int i = 0; i<m; i++) {
        buff[i] = L.ListDelete(0);
    }
    L.CreateList_Tail(m, buff);
}
