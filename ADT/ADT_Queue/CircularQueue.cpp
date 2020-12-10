using namespace std;

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
    front = (front+1)%maxSize;
    return elem[front];
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
    for (int i = front;; i++) {
        i = i%maxSize;
        if (i == rear)break;
        cout<<elem[i]<<' ';
    }
}
