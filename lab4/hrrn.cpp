#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void hrrn(vector<pair<int, pair<int, int>>> processes)
{
    int currTime = 0;

    while (!processes.empty())
    {
        int n = processes.size();
        vector<double> response(n, -1); 

        for (int i = 0; i < n; i++)
        {
            if (processes[i].first <= currTime)
            {
                int waitingTime = currTime - processes[i].first;
                int burstTime = processes[i].second.first;
                response[i] = 1.0 + ((double)waitingTime / burstTime);
            }
        }

        int index = -1;
        double maxResponse = -1;

        for (int i = 0; i < n; i++)
        {
            if (response[i] > maxResponse)
            {
                maxResponse = response[i];
                index = i;
            }
        }

        if (index == -1)
        {
            currTime = processes[0].first;
            continue;
        }

        int arrival = processes[index].first;
        int burst = processes[index].second.first;

        int startTime = max(currTime, arrival);
        int completionTime = startTime + burst;

        cout << "Process " << processes[index].second.second
             << ", Process with Arrival: " << arrival
             << ", Burst: " << burst << endl;

        currTime = completionTime;

        processes.erase(processes.begin() + index); 
    }
}


int main()
{
	vector<pair<int, pair<int, int>>> processes; // first = arrival, second = burst

	srand(time(0));
	int processNo = (rand() % 10) + 1;

	for (int i = 0; i < processNo; i++)
	{
		processes.push_back({rand() % 10, {(rand() % 100) + 1, i+1}});
	}

	//sort on basis of first->arrival
	sort(processes.begin(), processes.end());

	cout << "-----Processes-----" << endl;
	for (int i = 0; i < processNo; i++)
	{
        processes[i].second.first = i+1;
		cout << "Process " << (i + 1) << " -> ";
		cout << "Arrival Time :" << processes[i].first << ", ";
		cout << "Next cpu time :" << processes[i].second.first << endl;
	}	

    hrrn(processes);

	return 0;
}