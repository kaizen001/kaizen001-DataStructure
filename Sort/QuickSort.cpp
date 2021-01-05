using namespace std;
//划分函数（快速排序）
template<class ElemType>
int divide( vector<ElemType> &A, int low, int high ){
    ElemType pivotElm = A[low];
    while (low<high) {
        while (low<high&&A[high]>=pivotElm) high--;
        A[low] = A[high];
        while (low<high&&A[low]<=pivotElm) low++;
        A[high] = A[low];
    }
    A[low] = pivotElm;
    return low;
}
//快速排序的实现（递归）
template<class ElemType>
void QuickSort( vector<ElemType> &A, int low, int high){
    if (low<high) {
        int pivot = divide(A, low, high);
        cout<<pivot<<' '<<A[pivot]<<endl;
        for(auto elm:A){
            cout<<elm<<' ';
        }
        cout<<endl;
        QuickSort(A, low, pivot-1);
        QuickSort(A, pivot+1, high);
        
    }
}
//快速排序的实现（外壳）
template<class ElemType>
void QuickSort( vector<ElemType> &A ){
    QuickSort(A, 0,A.size()-1);
}
