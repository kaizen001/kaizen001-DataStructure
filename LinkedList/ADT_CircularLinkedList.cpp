using namespace std;


/* 结点定义 */
template<class ElemType>
struct LinkNode
{
    ElemType data;
    LinkNode<ElemType> *next;
    LinkNode(LinkNode<ElemType> *ptr = NULL){next = ptr;} //构造函数1，用于构造头结点
    LinkNode(const ElemType &item, LinkNode<ElemType> *ptr = NULL) //构造函数2，用于构造其他结点
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        next = ptr;
        data = item;
    }
    ElemType getData(){ return data;}  //取得结点中的数据
    void SetLink( LinkNode<ElemType> *link ){ next = link; }  //修改结点的next域
    void SetLink( ElemType value ){ data = value; }   //修改结点的next域
};

//循环链表
template<class ElemType>
class CirLinkList
{
   private:
      LinkNode<ElemType> *head;   // 头结点
      LinkNode<ElemType> *tail;   // 尾结点
   public:
    CirLinkList(){head = new LinkNode<ElemType>;tail = head;head->next = head;}//无参数的构造函数
    CirLinkList(const ElemType &item){head = new LinkNode<ElemType>(item);} //带参数的构造函数
    CirLinkList(CirLinkList<ElemType> &List);//拷贝构造函数
    ~CirLinkList(){ListDestroy();}//析构函数
    //LinkList<ElemType>& operator=(LinkList<ElemType> &List);//重载函数:赋值
    void ListDestroy();//销毁链表
    void ListClear();//清空链表
    int ListLength() const;//返回链表的长度
    bool ListEmpty() const;//判断链表是否为空表
    bool InsFirst( ElemType e );//在首节点之前插入一个结点
    LinkNode<ElemType>* GetHead() { return head;}//获取链表头结点
    void SetHead(LinkNode<ElemType> *p){ head = p;}//设置链表头结点
    LinkNode<ElemType>* GetTail() { return tail;}//获取链表尾结点
    ElemType GetElem(int pos);//用e返回链表的第i个元素
    bool ListInsert_prior(int pos,ElemType e); //在链表的第pos个位置之前插入e元素
    bool ListInsert_next(int pos,ElemType e);//在链表的第pos个位置之后插入e元素
    bool DelFirst(ElemType &e);//删除链表的首结点
    void CreateList_Head(int n, ElemType *A);//表头插入法动态生成链表,A为数组
    void CreateList_Tail(int n, ElemType *A);//表尾插入法动态生成链表,A为数组
    ElemType ListDelete(int pos);//删除链表的第pos个位置的元素
    //bool compare(ElemType a, ElemType *b);//compare函数，用来判断a和b是否相等
    //按序号查找，从链表的第一个结点开始，判断当前结点是否是第i个，
    //若是，则返回该结点的数据域的值；否则继续后一个，直至表结束。没有第i个结点时返回空。
    bool FindElem( int k, ElemType &e);
    //按值查找，即定位。从链表的第0个结点开始，判断当前结点值是否等于e。
    //若是，则返回该结点的序号；否则继续后一个，直至表结束。找不到时返回-1。
    int SearchElem( const ElemType &e) const;
    //bool PriorElem(ElemType cur_e, ElemType &pri_e);//返回链表给定数据元素的前驱数据元素的值
    bool NextElem(LinkNode<ElemType> *p, ElemType &e);//返回链表给定数据元素的后继数据元素的值
    bool ListTraverse() const;//遍历链表
};

template<class ElemType>
CirLinkList<ElemType>::CirLinkList(CirLinkList<ElemType> &List){
    LinkNode<ElemType> *p = List.head;
    while(p!=nullptr){
        LinkNode<ElemType> *node = new CirLinkList<ElemType>(p->getData());
        p = p->next;
        LinkNode<ElemType> *pthis = head;
        while(pthis->next!=nullptr)pthis = pthis->next;
        pthis->next = node;
    }
}

template<class ElemType>
void CirLinkList<ElemType>::ListDestroy(){
    tail->next = nullptr;
    while(head!=nullptr){
        LinkNode<ElemType> *p = head;
        head = head->next;
        delete p;
    }
    head = tail = nullptr;
}

template<class ElemType>
void CirLinkList<ElemType>::ListClear(){
    this->ListDestroy();
    head = new LinkNode<ElemType>(head);
    tail = head;
}

template<class ElemType>
int CirLinkList<ElemType>::ListLength() const{
    int counter = 1;
    LinkNode<ElemType> *p = head;
    while (p!=tail) {
        counter++;
        p = p->next;
    }
    return counter;
}

template<class ElemType>
bool CirLinkList<ElemType>::ListEmpty() const{
    if (head == nullptr) return true;
    return false;
}

template<class ElemType>
bool CirLinkList<ElemType>::InsFirst( ElemType e ){
    LinkNode<ElemType> *p = new LinkNode<ElemType>(e,head);
    head = p;
    tail->next = head;
    return true;
}

template<class ElemType>//TODO做pos的越界保护
ElemType CirLinkList<ElemType>::GetElem(int pos){
    if (pos == 0) return head->getData();
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<pos; i++) {
        p = p->next;
    }
    return p->getData();
}

template<class ElemType>//TODO做pos的越界保护
bool CirLinkList<ElemType>::ListInsert_prior(int pos,ElemType e){
    if (pos == 0) {
        InsFirst(e);
        return true;
    }
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<pos-1; i++) {
        p = p->next;
    }
    p->next = new LinkNode<ElemType>(e,p->next);
    if (p->next->next == head) tail = p->next;
    return true;
}

template<class ElemType>//TODO做pos的越界保护
bool CirLinkList<ElemType>::ListInsert_next(int pos,ElemType e){
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<pos; i++) {
        p = p->next;
    }
    p->next = new LinkNode<ElemType>(e,p->next);
    if (p->next->next == head) tail = p->next;
    return true;
}

template<class ElemType>//TODO做pos的越界保护
bool CirLinkList<ElemType>::DelFirst(ElemType &e){
    if (head == nullptr) return false;
    LinkNode<ElemType> *p = head;
    head = head->next;
    e = p->getData();
    delete p;
    tail->next = head;
    return true;
}

template<class ElemType>
void CirLinkList<ElemType>::CreateList_Head(int n, ElemType *A){
    for(int i = 0;i<n;i++){
        InsFirst(A[n-1-i]);
    }
}

template<class ElemType>
void CirLinkList<ElemType>::CreateList_Tail(int n, ElemType *A){
    LinkNode<ElemType> *p = head;
    while(p->next!=head)p = p->next;
    for(int i = 0;i<n;i++){
        p->next = new LinkNode<ElemType>(A[i],head);
        tail = p->next;
        p = p->next;
    }
}

template<class ElemType>
ElemType CirLinkList<ElemType>::ListDelete(int pos){
    if (pos == 0) {
        ElemType e = head->getData();
        LinkNode<ElemType> *pdelet = head;
        head = head->next;
        delete pdelet;
        return e;
    }
    LinkNode<ElemType> *pdeletfront = head;
    for (int i = 0; i<pos-1; i++) {
        pdeletfront = pdeletfront->next;
    }
    ElemType e = pdeletfront->next->getData();
    LinkNode<ElemType> *pdelet = pdeletfront->next;
    pdeletfront->next = pdeletfront->next->next;
    delete pdelet;
    return e;
}

template<class ElemType>
bool CirLinkList<ElemType>::FindElem(int k, ElemType &e){
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<k; i++) {
        if(p == nullptr){
            e = NULL;
            return 0;
        }
        p = p->next;
    }
    return p->getData();
}

template<class ElemType>
int CirLinkList<ElemType>::SearchElem( const ElemType &e) const{
    LinkNode<ElemType> *p = head;
    int counter = 0;
    while(p->next!=head&&p->getData()!=e){
        p = p->next;
        counter++;
    }
    if (p->next==head&&p->getData()!=e) return -1;
    return counter;
}

template<class ElemType>
bool CirLinkList<ElemType>::NextElem(LinkNode<ElemType> *p, ElemType & e){
    e = p->next->getData();
    return true;
}

template<class ElemType>
bool CirLinkList<ElemType>::ListTraverse() const{
    CirLinkList<ElemType> *p = head;
    while (p->next!=head) {
        cout<<p->getData()<<' ';
        p = p->next;
    }
    cout<<tail->getData()<<' ';
    return 1;
}
