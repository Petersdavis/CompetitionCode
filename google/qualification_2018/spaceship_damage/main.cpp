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

        int D;
        string P;
        int solution;

        Test(int dmg, string code){

            D = dmg;
            P=code;
            solution = 0;
        }

        int calculateDamage(){
           char tmp [P.length()+1];
           strcpy (tmp, P.c_str());
           int dmg_total = 0;
           int dmg_level = 1;

           for(int i=0; i<P.length();++i){
               if(tmp[i]=='S'){
                 dmg_total += dmg_level;
               }else{
                 dmg_level *= 2;
               }
           }
           return dmg_total;
        }

        string reduceDamage(){
            char tmp [P.length()+1];
            strcpy (tmp, P.c_str());

            for(int i=P.length()-1; i>0; --i){
                if(tmp[i] == 'S' && tmp[i-1]== 'C') {
                    tmp[i]='C';
                    tmp[i-1]='S';
                    return string(tmp);
                }
            }
            cout << "SHOULD NEVER GET HERE"<< endl;
            exit(1);

        }

        void solveIt(){

            size_t n = std::count (P.begin(), P.end(), 'S');

            if(n > D){
                cout<< "IMPOSSIBLE" << endl;
            } else {
                int steps = 0;

                while(calculateDamage()>D){
                    P=reduceDamage();
                    steps++;
                }
                cout << steps <<endl;
            }
        }

};


int main(){
    ifstream inFile;
    inFile.open("./tests");

    if(!inFile){
        cerr<<"could not open file";
        exit(1);
    }

    //Get Test Cases:
    int T;
    inFile>>T;


    vector<Test> TestCases;
    int i;

    for(i=0; i<T;++i){
        int dmg;
        string code;
        inFile>>dmg>>code;
        TestCases.push_back(Test(dmg, code));
    }


    for(i=0; i<T;++i){
        TestCases[i].solveIt();
    }
    return 0;
}