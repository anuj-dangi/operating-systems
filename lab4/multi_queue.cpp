#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef struct Process
{
	int pid;
	int arrival;
	int burst;
	int priority;
}P;

void multiQueue(vector<P> processes)
{
    //let no of queues to be 3;
    queue<P> q1, q2, q3;

	int currTime = 0;
    while(!processes.empty() || !q1.empty() || !q2.empty() || !q3.empty())
	{
		for(auto it = processes.begin(); it != processes.end(); )
		{
			if(currTime >= it->arrival)
			{
				switch(it->priority)
				{
					case 3: q1.push(*it);
							break;
					case 2: q2.push(*it);
							break;
					default: q3.push(*it);
							break;
				}

				it = processes.erase(it);
			}
			else
			{
				++it;
			}
		}

		P process;
		bool found = true;

		if(!q1.empty())
		{
			process = q1.front();
			q1.pop();
		}
		else if(!q2.empty())
		{
			process = q2.front();
			q2.pop();
		}
		else if(!q3.empty())
		{
			process = q3.front();
			q3.pop();
		}
		else
		{
			if(!processes.empty())
				currTime += processes[0].arrival;
			found = false;
		}

		if(found)
		{
			currTime += process.burst;

			cout << "Process " << process.pid
				<< ", Process with Arrival: " << process.arrival
				<< ", Burst: " << process.burst
				<< ", Priority : " << process.priority << endl;

		}
	}
}

int main()
{
	vector<P> processes; // first -> first = arrival, second = burst
    //second -> first = priority, second = index;

	srand(time(0));
	int processNo = (rand() % 10) + 1;

	//priority level -3, 2, 1(high -> low)
	for (int i = 0; i < processNo; i++)
	{
		P p;
		p.arrival = rand() % 10;
		p.burst = (rand() % 100) + 1;
		p.priority = rand()%3+1;
		p.pid = i+1;
		processes.push_back(p);
	}

	//sort on basis of first->arrival
	sort(processes.begin(), processes.end(), [](const P &a, const P &b){
        return a.arrival < b.arrival;
    });

	cout << "-----Processes-----" << endl;
	for (int i = 0; i < processNo; i++)
	{
        processes[i].pid = i+1;
		cout << "Process " << (i + 1) << " -> ";
		cout << "Arrival Time :" << processes[i].arrival << ", ";
		cout << "Next cpu time :" << processes[i].burst
			<< ", Priority : " << processes[i].priority << endl;
	}	

    multiQueue(processes);

	return 0;
}