#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> selection(vector<int> carrival)
{
	vector<int> index;

	for(int i=0;i<carrival.size();i++)
	{
		int min = carrival[i];
		int ind = i;
		for(int j=i+1;j<carrival.size();j++)
		{
			if(carrival[j] < min)
			{
				min = carrival[j];
				ind = j;
			}
		}
		int temp = carrival[i];
		carrival[i] = min;
		carrival[ind] = temp;
		index.push_back(ind);
	}

	return index;
}

void fcfs(vector<int> arrival, vector<int> cpuCycle)
{
	vector<int> index = selection(arrival);

	vector<int> tat(arrival.size());

	int ta = 0;

	for(int i=0;i<index.size();i++)
	{
		tat.push_back(ta+cpuCycle[index[i]]-arrival[index[i]]);
		ta = tat[(i==0) ? 0 : i-1];
	}

	for(int i=0;i<tat.size();i++)
	{
		cout << "Process " << (index[i]+1) << " -> ";
		cout << "Arrival Time :" <<  arrival[index[i]] << ", ";
		cout << "Next cpu time :" << cpuCycle[index[i]] << ", ";
		cout << "tat :" << tat[i] << endl;
	}
}

int main()
{
	vector<int> arrival;
	vector<int> cpuCycle;

	srand(time(0));

	int processes = rand()%10;
	
	for(int i=0;i<processes;i++)
	{
		arrival.push_back(rand()%11);
		cpuCycle.push_back(rand()%101);
	}

	for(int i=0;i<processes;i++)
	{
		cout << "Process " << (i+1) << " -> ";
		cout << "Arrival Time :" <<  arrival[i] << ", ";
		cout << "Next cpu time :" << cpuCycle[i] << endl;
	}

	fcfs(arrival, cpuCycle);
	
	return 0;
}


