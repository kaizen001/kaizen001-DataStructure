using namespace std;


/* 单链表的结点定义 */
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

//带头结点的单链表
template<class ElemType>
class LinkedListQueue
{
private:
    LinkNode<ElemType> *head;   // 头结点
    LinkNode<ElemType> *tail;   // 尾结点
    int lenght = 0;
public:
    LinkedListQueue(){head = nullptr;tail = head;}//无参数的构造函数
    LinkedListQueue(const ElemType &item){
        head = new LinkNode<ElemType>(item);
        lenght++;
        tail = head;} //带参数的构造函数
    LinkedListQueue(LinkedListQueue<ElemType> &List);//拷贝构造函数
    ~LinkedListQueue(){QueueDestroy();}//析构函数
    //LinkList<ElemType>& operator=(LinkList<ElemType> &List);//重载函数:赋值
    void QueueDestroy();//销毁链表
    void QueueClear();//清空链表
    int QueueLength() const;//返回链表的长度
    bool QueueEmpty() const;//判断链表是否为空表
    bool GetFront(ElemType &e){
        if(QueueEmpty()){
            cout<<"空队列无首元素";
            return 0;
        }
        e = *head;
        return 1;
    };
    bool enQueue(ElemType e);//入队
    LinkNode<ElemType>* GetHead() { return head;}//获取链表头结点
    LinkNode<ElemType>* GetTail() { return tail;}//获取链表尾结点
    ElemType GetElem(int pos);
    int SearchElem( const ElemType &e) const;
    bool deQueue(ElemType &e);//删除队列的首结点
    ElemType deQueue();
    bool QueueTraverse() const;//遍历链表
};

template<class ElemType>
LinkedListQueue<ElemType>::LinkedListQueue(LinkedListQueue<ElemType> &List){
    LinkNode<ElemType> *p = List.head;
    QueueClear();
    LinkNode<ElemType> *pthis = head;
    
    while(p!=nullptr){
        LinkNode<ElemType> *node = new LinkedListQueue<ElemType>(p->getData());
        lenght++;
        p = p->next;
        pthis->next = node;
    }
}

template<class ElemType>
void LinkedListQueue<ElemType>::QueueDestroy(){
    while(head!=nullptr){
        LinkNode<ElemType> *p = head;
        head = head->next;
        delete p;
    }
    head = nullptr;
    tail = nullptr;
    lenght=0;
}

template<class ElemType>
void LinkedListQueue<ElemType>::QueueClear(){
    this->ListDestroy();
}

template<class ElemType>
int LinkedListQueue<ElemType>::QueueLength() const{
    return lenght;
}

template<class ElemType>
bool LinkedListQueue<ElemType>::QueueEmpty() const{
    if (head == nullptr) return true;
    return false;
}

template<class ElemType>//TODO做pos的越界保护
ElemType LinkedListQueue<ElemType>::GetElem(int pos){
    if (QueueEmpty()) {
        cout<<"为空队列，无法查找";
        return NULL;
    }
    if (pos == 0) return head->getData();
    LinkNode<ElemType> *p = head;
    for (int i = 0; i<pos; i++) {
        p = p->next;
        if (p==nullptr) {
            cout<<"输入长度大于队列长度，获取失败";
            return NULL;
        }
    }
    return p->getData();
}

template<class ElemType>
bool LinkedListQueue<ElemType>::deQueue(ElemType &e){
    if (head == nullptr){
        cout<<"空队列禁止弹出";
        return false;
    }
    LinkNode<ElemType> *p = head;
    head = head->next;
    e = p->getData();
    delete p;
    lenght--;
    if (head == nullptr) tail = head;
    return true;
}

template<class ElemType>
ElemType LinkedListQueue<ElemType>::deQueue(){
    if (head == nullptr){
        cout<<"空队列禁止弹出";
        return NULL;
    }
    LinkNode<ElemType> *p = head;
    head = head->next;
    ElemType e = p->getData();
    delete p;
    lenght--;
    if (head == nullptr) tail = head;
    return e;
}

template<class ElemType>
bool LinkedListQueue<ElemType>::enQueue(ElemType e){
    if (QueueEmpty()) {
        head = new LinkNode<ElemType>(e);
        lenght++;
        tail = head;
        return 1;
    }
    tail->next = new LinkNode<ElemType>(e);
    lenght++;
    tail = tail->next;
    return 1;
}

template<class ElemType>
int LinkedListQueue<ElemType>::SearchElem( const ElemType &e) const{
    LinkNode<ElemType> *p = head;
    int counter = 0;
    while(p!=nullptr&&p->getData()!=e){
        p = p->next;
        counter++;
    }
    if (p==nullptr) return -1;
    return counter;
}

template<class ElemType>
bool LinkedListQueue<ElemType>::QueueTraverse() const{
    LinkNode<ElemType> *p = head;
    while (p!=nullptr) {
        cout<<p->getData()<<' ';
        p = p->next;
    }
    return 1;
}
