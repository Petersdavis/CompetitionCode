#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <limits.h>
#include <regex>
#include <array>



using namespace std;

struct Point {
    int x;
    int y;
};

class Test {

    public:

        int A;
        int width;
        int count;

        Test(int area){
            A = area;
            count = 0;
        }

        int decideWidth(){
           int w;
           w= (A/3)+1;
           return w;
        }

        Point getInput(){
            Point p;
            cin>>p.x>>p.y;
            //cerr << "GOPHER DUG: " << p.x << " "<<p.y << endl;
            ++count;
            return p;

        }

        inline bool allTrue( array<bool,3> arr){
            if(arr[0]==false||arr[1]==false||arr[2]==false){
                return false;
            }
            return true;
        }

        void sendGopher(int x, int y){
            cout << x << " "<< y<< endl;
            cout.flush();
        }

       void printLine(){
            array <bool,3> left ={false};
            array <bool,3> middle ={false};
            array <bool,3> right ={false};


            int x = 2;

            while( x < width - 1){
                while(allTrue(left)){
                    ++x;
                    left = middle;
                    middle = right;
                    right.fill(false);
                }
                
                sendGopher(x, 2);
                Point result = getInput();

                if(result.x == -1 && result.y == -1){
                    cerr<<"ERROR FAILED TEST"<<endl;
                    return;
                } else if(result.x==0 && result.y==0){
                    cerr<<"SUCCESS COMPLETED TEST in "<< count <<"Attempts" <<endl;
                    return;
                } else {
                    switch(result.x - x){
                        case -1:
                            left[result.y-1]= true;
                            break;
                        case 0:
                            middle[result.y-1]= true;
                            break;
                        case 1:
                            right[result.y-1]= true;
                            break;

                    }
                }
            }

            while(!allTrue(left) || !allTrue(middle) || !allTrue(right)){
                sendGopher(x, 2);
                Point result = getInput();

                if(result.x == -1 && result.y == -1){
                    cerr<<"ERROR FAILED TEST"<<endl;
                    return;
                } else if(result.x==0 && result.y==0){
                    cerr<<"SUCCESS COMPLETED TEST "<< count <<" Attempts" <<endl;
                    return;
                } else {
                    switch(result.x - x){
                        case -1:
                            left[result.y-1]= true;
                            break;
                        case 0:
                            middle[result.y-1]= true;
                            break;
                        case 1:
                            right[result.y-1]= true;
                            break;

                    }
                }
            }
        }

        void solveIt(){
            width = decideWidth();
            printLine();
        }

};


int main(){

    //Get Test Cases:
    int T;
    cin>>T;

    cerr <<T<<endl;


    int i;


    for(i=0; i<T;++i){
        int area;
        cin>>area;

        Test test_case = Test(area);
        test_case.solveIt();
    }

    return 0;

}