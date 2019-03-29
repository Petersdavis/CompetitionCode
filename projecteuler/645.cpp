
/*
On planet J, a year lasts for D days. Holidays are defined by the two following rules.

At the beginning of the reign of the current Emperor, his birthday is declared a holiday from that year onwards.
If both the day before and after a day d are holidays, then d also becomes a holiday.
Initially there are no holidays. Let E(D) be the expected number of Emperors to reign before all the days of the year are holidays, assuming that their birthdays are independent and uniformly distributed throughout the D days of the year.

You are given E(2)=1, E(5)=31/6, E(365)≈1174.3501.

Find E(10000). Give your answer rounded to 4 digits after the decimal point.

Recursive strategy :  N days in the year.

Let n be the number of days in a subsection of the year.
birthday on a given day probability is 1/N;

if n = 1  ==>  P(n) = 1 < == it is holiday by definition/1
if n = 2  ==>  P(n) = 2/N
if n = 3  ==>  P(n=>2) = 2/N  P(n) => 1/N
if n > 4  ==>  Split group into a + b = n-1 even probability


Expected time to hit a day is infinite sum i*p(1-p)^(i-1) == 1/p

Therefore
E(1) => 0
E(2) => N/2
E(3) =>  Best case is  1/N ==> Done  2/N => E(2) => N/2+1 else no progress



*/





int main(){
	cout <<"STARTING TO EXECUTE PROGRAM"<<endl;
	Problem3 *p3 = new Problem645;
	cin.ignore();
	exit(0);
};