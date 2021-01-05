using namespace std;

template<class ElemType>
void SimpleSelectSort( vector<ElemType> &A ){
    for (int i = 0; i<A.size()-1; i++) {
        int min_ptr = i;
        for (int j = i+1; j<A.size(); j++) {
            if(A[j]<A[min_ptr]){
                min_ptr = j;
            }
        }
        ElemType buff = A[i];
        A[i] = A[min_ptr];
        A[min_ptr] = buff;
        for(auto elm:A){
            cout<<elm<<' ';
        }
        cout<<endl;
    }
}
