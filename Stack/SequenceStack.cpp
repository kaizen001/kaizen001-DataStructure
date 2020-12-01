using namespace std;

const int MAXLISTSIZE = 100;
template<class ElemType>
class SqStack{
   private:
      ElemType *base;   // 栈底指针
      ElemType *top;   // 栈顶指针
      int maxSize;        // 允许的最大存储容量(以sizeof(ElemType)为单位
   public:
      SqStack(int ms = 20);//初始化顺序栈
      ~SqStack(){StackDestroy();}//删除顺序栈
      bool StackClear( ){top = base;};//将顺序栈置为空表
      int StackLength() const {return top - base;}//返回顺序栈的长度
      //bool SetListLength(int len);//设置顺序栈的长度
      bool StackisEmpty() const{ return top == base; }//判断顺序栈是否为空栈
    bool StackFull() const{return top==base+maxSize?1:0;};//判断顺序栈是否为满栈
    bool GetTop(ElemType &e) const{return &top;};//用e返回栈顶元素
    bool push(ElemType &e);//入栈
    bool push(ElemType e);//入栈
      bool pop(ElemType &e);//出栈
    ElemType pop();//出栈
      bool StackDestroy();//销毁顺序栈
      void StackTraverse() const;//遍历顺序栈
      bool DoubleSpace();//栈空间加倍
};

template<class ElemType>
SqStack<ElemType>::SqStack(int ms){
    maxSize = ms;
    base = new ElemType[maxSize];
    top = base;
}

template<class ElemType>
bool SqStack<ElemType>::StackDestroy(){
    maxSize = 0;
    delete[] base;
    return 1;
}

template<class ElemType>
bool SqStack<ElemType>::push(ElemType &e){
    *top = e;
    top++;
    if (StackFull()) return DoubleSpace();
    return true;
}

template<class ElemType>
bool SqStack<ElemType>::push(ElemType e){
    *top = e;
    top++;
    if (StackFull()) return DoubleSpace();
    return true;
}

template<class ElemType>
bool SqStack<ElemType>::pop(ElemType &e){
    if (StackisEmpty()) {
        cout<<"已经为空栈禁止弹出";
        return 0;
    }
    top--;
    e = *top;
    return true;
}

template<class ElemType>
ElemType SqStack<ElemType>::pop(){
    if (StackisEmpty()) {
        cout<<"已经为空栈禁止弹出";
        return 0;
    }
    top--;
    
    return *top;
}

template<class ElemType>
void SqStack<ElemType>::StackTraverse() const {
    ElemType *p = top-1;
    while (p!=base-1) {
        cout<<*p<<' ';
        p--;
    }
}

template<class ElemType>
bool SqStack<ElemType>::DoubleSpace(){
    maxSize*=2;
    if (maxSize>MAXLISTSIZE) {
        cout<<"栈大于预设的阈值，空间加倍失败";
        return 0;
    }
    ElemType *oldTop = top;
    ElemType *oldBase = base;
    
    base = new ElemType[maxSize];
    top = base+(oldTop - oldBase);
    while (oldTop!=oldBase-1) {
        base[oldTop - oldBase] = *oldTop;
        oldTop--;
    }
    delete[] oldBase;
    return 1;
}
