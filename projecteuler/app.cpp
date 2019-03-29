

/* Includes */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "sys/time.h"

/* NameSpace */
using namespace std;

class Problem{
	protected:
	long int start_time;
	long int end_time;
	std::vector<void (*)()> solutions;

	protected:
	Problem(){
	}

	void startTimer(){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		start_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}
	void stopTimer(){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		end_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}

};


class Problem4:public Problem{
	const string description = "Find the largest palindrome made from the product of two 3-digit numbers.";
	int solution;

	public:
		Problem4(){
			cout <<"STARTING TO EXECUTE PROGRAM 4:"<<endl;
			this->startTimer();
			this->solution1();
			this->stopTimer();
			cout << "SOLUTION1 IS: " << this->solution << endl;
			cout <<	"SOLUTION TOOK " << this->end_time - this->start_time << "ms" <<endl;
		}
		bool isPalindrome(int number){
		    int rev;
		    int x = number;
		    rev = 0;

		    while(x != 0){
		     digit = x % 10;
             rev = (rev * 10) + digit;
             x = x / 10;
		    }

		    return rev == number;
		}

		int test(int depth){
		    bool found_palindrome = false
		    int curr_palindrome = 0
		    int x, y;
		    int prod;
		    x=0;
		    y=depth;

		    while(x<=depth){
		        prod = (999-x)*(999-y);
		        if(isPalindrome(prod)){
		           curr_palindrome = std::max(curr_palindrome, prod);
		           found_palindrome = true;
		        }
		    ++x
		    --y
		    }


		    if(!found_palindrome){
		        depth ++;
		        test(depth);
		    }

		}

		void solution1(){
		    int solution;
		    int x, y;
		    x=999;
		    y=999;

		    if(isPalindrome (x*y) )





		    $this->solution = solution
			return
		}
};

class Problem3:public Problem{
	const string description = "What is the largest prime factor of the number 600851475143 ?";
	int solution;

	public:
		Problem3(){
			cout <<"STARTING TO EXECUTE PROGRAM 3:"<<endl;
			this->startTimer();
			this->solution1();
			this->stopTimer();
			cout << "SOLUTION1 IS: " << this->solution << endl;
			cout <<	"SOLUTION TOOK " << this->end_time - this->start_time << "ms" <<endl;		
		}
		void solution1(){
			vector<int> primes;
			int count, count2;
			primes.push_back(2);

			long long target = 600851475143;

			int a = 1;
			int b = 2;
			int c = 0;
			for(count=3; target!=1; count++){
				bool prime = true;
				for(count2=0;count2<primes.size()||primes[count2]*primes[count2]>count;++count2){
					if(count%primes[count2]== 0){
						prime=false;
						break;
					}
				}
				if(prime == true){
					primes.push_back(count);
					if(target%count == 0){
						target = target / count;
						break;
					}					
				}
			}

			this->solution = count;
			this->stopTimer();
			return;
		}
};	



class Problem2:public Problem{
	const string description = "By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.";
	int solution;

	public:
		Problem2(){
			cout <<"STARTING TO EXECUTE PROGRAM 2:"<<endl;
			this->startTimer();
			this->solution1();
			this->stopTimer();
			cout << "SOLUTION1 IS: " << this->solution << endl;
			cout <<	"SOLUTION TOOK " << this->end_time - this->start_time << "ms" <<endl;		
		}
		void solution1(){
			int a = 1;
			int b = 2;
			int c = 0;
			int total = 2;
			while(b<4000000){
				cout << b <<endl;
				c=b;
				b=a+b;
				a=c;
				if(b%2==0){
					total+= b;
				}
			}

			
			this->solution = total;
			this->stopTimer();
			return;
		}
};

class Problem1: public Problem{
	const string description = "Find the sum of all the multiples of 3 or 5 below 1000.";
	int solution;

	public:
		Problem1(){
			cout <<"STARTING TO EXECUTE PROGRAM 1:"<<endl;
			this->startTimer();
			this->solution1();
			this->stopTimer();
			cout << "SOLUTION1 IS: " << this->solution << endl;
			cout <<	"SOLUTION TOOK " << this->end_time - this->start_time << "ms" <<endl;		
		}

		void solution1(){
			int x = 0;
			int total = 0;

			while(x < 1000){
				if(x%3==0 ||x%5==0){
					total += x;
				}
				++x;
			}

			this->solution = total;
			this->stopTimer();
			return;
		}



};

class EuclidLibrary{
	std::vector <Problem> problems;
	string user_action;
	
	public : EuclidLibrary(){
	}
	
	public : void loadFile(){
		/*
		string filename;
		string tmp_name;
		string tmp_desc;
		ifstream inFile;
		
		
		cout << "Enter filename to read videos from: "<<endl;
		
		cin >> filename;
		inFile.open(filename);
		cin.ignore();	
		while(getline(inFile, tmp_name) && getline(inFile, tmp_desc)){
			
			//During Testing I found that getline was adding a carriage return but not a newline character.  
			//This was because I am working on a virtual unix shell using a text file created in Windows.
			//Line 172 is a hacky workarround to fix the line endings.
			tmp_name.erase( std::remove(tmp_name.begin(), tmp_name.end(), '\r'), tmp_name.end() );
		
			Video video(tmp_name, tmp_desc);
			videos.push_back(video);
			cout << "ADDED VIDEO :: " << tmp_name << endl;
			cout << "PRESS ANYKEY TO CONTINUE " << endl;
			cin.ignore();	
		}
		return;
		*/
	}
	
	public : void selectVideo(){
		/*
		cout << "Please select a video or action from the list: " <<endl;
		for (int i = 0; i < videos.size(); i++){
			cout << "[" << i << "] " << videos[i].name << endl;
        }
		
		cout << "[a] Import videos from text file. "<< endl;
		cout << "[q] Leave Application. " << endl;
		cin >> user_action;
		
		if(user_action == "a"){
			loadFile();
			return selectVideo();
		} else if(user_action == "q"){
			exit(0);
		} else {
			for (int i = 0; i < videos.size(); i++){
				if(to_string(i) == user_action){
					videos[i].selectAction();
					return selectVideo();
				}
			}
			
			cout << "WARNING :: INVALID INPUT! " <<endl;
			return selectVideo();
		}
	*/
	}
};



int main(){
	cout <<"STARTING TO EXECUTE PROGRAMS"<<endl;
	Problem3 *p3 = new Problem3;
	cin.ignore();
	exit(0);
};