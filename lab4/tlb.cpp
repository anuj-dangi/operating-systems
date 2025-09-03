#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

void tlb(int n, vector<int> mem, double h, double T, double t)
{
	for(int i=0;i<n;i++)
	{
		int Mi = mem[i];

		
	}
}

int main()
{
	srand(time(0));	//time->ctime
	//srand->cstdlib

	int n;
	cout << "Enter no of processes: ";
	cin >> n;

	vector<int> mem(n);
	for(int i=0;i<n;i++)
	{
		mem[i] = (rand()%200)+100;
	}

	double h = 0.9;
	double T = 100;		//nanosecond
	double t = 1;

	tlb(n, mem, h, T, t);

	return 0;
}