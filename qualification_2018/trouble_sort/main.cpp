#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <limits.h>
#include <regex>



using namespace std;

class Test {

    public:
        vector<int> V;
        int N;
        int solution;
        int i;

        Test(vector<int> numbers, int count, int index){
            V = numbers;
            N = count;
            solution = 0;
            i=index+1;
        }

        void Print(vector<int> z){
            for(int i = 0; i<z.size();++i){
                cout << z[i] << " ";
            }
            cout <<endl;
        }

        vector<int> SortItProperly(){
            vector<int> tmp_vector (V.size());
            std::partial_sort_copy (V.begin(), V.end(), tmp_vector.begin(), tmp_vector.end());
            return tmp_vector;
        }

        vector<int> TroubleSort(){
            bool has_diffs = true;
            vector<int> tmp1, tmp2, final;

            //copy vector
            for (int i=0; i<V.size(); ++i && ++i)
                    tmp1.push_back(V[i]);

            for (int i=1; i<V.size(); ++i && ++i)
                    tmp2.push_back(V[i]);

            std::sort(tmp1.begin(), tmp1.end());
            std::sort(tmp2.begin(), tmp2.end());

            auto it = tmp1.begin();
            auto it2 = tmp2.begin();
            for ( ; it != tmp1.end(); ++it, ++it2) {
              // if the current index is needed:
               final.push_back(*it);
               if(it2 != tmp2.end()){
                    final.push_back(*it2);
               }
            }
            return final;
        }




        int FindFirstDiff(vector<int> a, vector<int> b){
            int i;

            for(i=0;i<a.size();++i){
                if(a[i]!=b[i]){
                    return i;
                }
            }
            return -1;
        }


        void solveIt(){
           vector<int> sorted, maybe_sorted;
           sorted = SortItProperly();
           maybe_sorted = TroubleSort();

           solution = FindFirstDiff(sorted, maybe_sorted);
           if(solution == -1){
                cout<<"Case #"<<i<<": OK"<<endl;
           }else{
                cout<<"Case #"<<i<<": "<<solution<<endl;
           }


           return;
        }

};


int main(){

    //Get Test Cases:
    int T;
    cin>>T;


    vector<Test> TestCases;
    int i, j;

    for(i=0; i<T;++i){
        int N;
        cin>>N;

        vector<int> V;

        for(j=0; j<N;++j){
            int x;
            cin>>x;
            V.push_back(x);
        }
        TestCases.push_back(Test(V, N, i));
    }


    for(i=0; i<T;++i){
        TestCases[i].solveIt();
    }
    return 0;
}