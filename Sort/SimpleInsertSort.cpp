using namespace std;

template<class ElemType>
void SimpleInsertSort( vector<ElemType> &A ){
    for (int i = 1; i<A.size(); i++) {
        if (A[i]<A[i-1]) {
            //find position
            int h = i-1;
            int l = 0;
            int min = (h+l)/2;
            while(h>=l){
                if (A[min]>=A[i]) {
                    h = min-1;
                }else{
                    l = min+1;
                }
                min = (h+l)/2;
            }
            //insert
            for (int j = i; j>l; j--) {
                ElemType buff = A[j];
                A[j] = A[j-1];
                A[j-1] = buff;
            }
        }
        for(auto elm:A){
            cout<<elm<<' ';
        }
        cout<<endl;
    }
}
