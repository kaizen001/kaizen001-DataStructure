using namespace std;
//希尔排序（一趟）
template<class ElemType>
void ShellInsert( vector<ElemType> &A, int dk ){
    for (int j = 0; j<dk; j++) {
        int begin_p = j;
        for (int i = begin_p+dk; i<A.size(); i+=dk) {
            int p = i;
            for(int k = (i-dk);k>=0&&A[k]>A[p];k-=dk){
                ElemType buff = A[p];
                A[p] = A[k];
                A[k] = buff;
                p = k;
            }
        }
    }
    
}
//希尔排序（主函数）
template<class ElemType>
void ShellSort( vector<ElemType> &A, int dlta[], int t ){  //t为希尔排序的趟数
    for (int i = 0; i<t; i++) {
        ShellInsert(A, dlta[i]);
        cout<<dlta[i]<<endl;
        for(auto elm:A){
            cout<<elm<<' ';
        }
        cout<<endl;
    }
}
