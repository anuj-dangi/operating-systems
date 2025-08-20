#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> order(vector<pair<int, int>> processes, int start, int end)
{
	vector<pair<int, int>> arr; // {burst, index}

	for (int i = start; i <= end; i++)
		arr.push_back({processes[i].second, i});

	sort(arr.begin(), arr.end());

	vector<int> index;
	for (auto &p : arr)
		index.push_back(p.second);

	return index;
}

void fcfs(vector<pair<int, int>> processes)
{
	int n = processes.size();
	vector<int> tat;

	int currTime = 0, completionTime, avg = 0;

	cout << "\n-----FCFS-----\n";
	for (int i = 0; i < n; i++)
	{
		int start = max(currTime, processes[i].first);

		completionTime = start + processes[i].second;

		tat.push_back(completionTime - processes[i].first);
		avg += tat[i];

		currTime = completionTime;

		cout << "Process " << (i + 1) << " -> ";
		cout << "Arrival Time :" << processes[i].first << ", ";
		cout << "Next cpu time :" << processes[i].second << ", ";
		cout << "TAT :" << tat[i] << ", ";
		cout << "Response time: " << start - processes[i].first << ", ";
		cout << "Waiting time: " << tat[i] - processes[i].second << endl;
	}
	cout << "Avg tat: " << avg / n << endl;
}

void sjf(vector<pair<int, int>> processes)
{
	int n = processes.size();
	vector<int> tat(n, 0), rt(n, 0), wt(n, 0);
	vector<bool> done(n, false);

	int currTime = 0, completed = 0, avg = 0;

	cout << "\n-----SJF-----\n";

	while (completed < n)
	{
		int idx = -1;
		int minBurst = INT32_MAX;

		for (int i = 0; i < n; i++)
		{
			if (!done[i] && processes[i].first <= currTime)
			{
				if (processes[i].second < minBurst)
				{
					minBurst = processes[i].second;
					idx = i;
				}
			}
		}

		if (idx == -1)
		{
			currTime++;
			continue;
		}

		int start = currTime;
		currTime += processes[idx].second;
		int completionTime = currTime;

		tat[idx] = completionTime - processes[idx].first;
		wt[idx] = tat[idx] - processes[idx].second;
		rt[idx] = start - processes[idx].first;

		avg += tat[idx];
		done[idx] = true;
		completed++;

		cout << "Process " << (idx + 1) << " -> ";
		cout << "Arrival Time :" << processes[idx].first << ", ";
		cout << "Next cpu time :" << processes[idx].second << ", ";
		cout << "TAT :" << tat[idx] << ", ";
		cout << "Response time: " << rt[idx] << ", ";
		cout << "Waiting time: " << wt[idx] << endl;
	}

	cout << "Avg tat: " << avg / n << endl;
}

void rr(vector<pair<int, int>> processes, int quantum)
{
	int n = processes.size();
	vector<int> bt(n), rt(n, -1), tat(n, 0), wt(n, 0), rem(n);

	for (int i = 0; i < n; i++)
		rem[i] = processes[i].second, bt[i] = processes[i].second;

	int currTime = 0, completed = 0;
	queue<int> q;
	int i = 0; 

	cout << "\n-----Round Robin (q=" << quantum << ")-----\n";

	
	currTime = processes[0].first;
	while (i < n && processes[i].first <= currTime)
		q.push(i++);

	while (completed < n)
	{
		if (q.empty())
		{
			
			currTime = processes[i].first;
			while (i < n && processes[i].first <= currTime)
				q.push(i++);
			continue;
		}

		int idx = q.front();
		q.pop();

		if (rt[idx] == -1)
			rt[idx] = currTime - processes[idx].first;

		int execTime = min(quantum, rem[idx]);
		rem[idx] -= execTime;
		currTime += execTime;

		while (i < n && processes[i].first <= currTime)
			q.push(i++);

		if (rem[idx] > 0)
		{
			q.push(idx); 
		}
		else
		{
			completed++;
			tat[idx] = currTime - processes[idx].first;
			wt[idx] = tat[idx] - bt[idx];

			cout << "Process " << (idx + 1) << " -> ";
			cout << "Arrival Time :" << processes[idx].first << ", ";
			cout << "Burst Time :" << bt[idx] << ", ";
			cout << "TAT :" << tat[idx] << ", ";
			cout << "Response time: " << rt[idx] << ", ";
			cout << "Waiting time: " << wt[idx] << endl;
		}
	}

	int totalTAT = 0;
	for (int j = 0; j < n; j++)
		totalTAT += tat[j];

	cout << "Avg TAT: " << (double)totalTAT / n << endl;
}

int main()
{
	vector<pair<int, int>> processes; // first = arrival, second = burst

	srand(time(0));
	int processNo = (rand() % 10) + 1;

	for (int i = 0; i < processNo; i++)
	{
		processes.push_back({rand() % 10, (rand() % 100) + 1});
	}

	sort(processes.begin(), processes.end());

	cout << "-----Processes-----" << endl;
	for (int i = 0; i < processNo; i++)
	{
		cout << "Process " << (i + 1) << " -> ";
		cout << "Arrival Time :" << processes[i].first << ", ";
		cout << "Next cpu time :" << processes[i].second << endl;
	}

	fcfs(processes);
	sjf(processes);

	for (int i = 1; i <= 5; i++)
	{
		rr(processes, i * 5);
	}

	return 0;
}
