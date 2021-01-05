using namespace std;

template<class ElemType>
void BubbleSort( vector<ElemType> &A ){
    bool flag = true;
    for (int i = 0; i<A.size()&&flag; i++) {
        flag = false;
        for (int j = 0; j<A.size()-i-1; j++) {
            if(A[j]>A[j+1]){
                ElemType buff = A[j];
                A[j] = A[j+1];
                A[j+1] = buff;
                flag = true;
            }
        }
        if (flag) {
            for(auto elm:A){
                cout<<elm<<' ';
            }
            cout<<endl;
        }
    }
}
