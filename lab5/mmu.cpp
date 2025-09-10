#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int frameNo;

typedef struct PageTableEntry
{
    int frameNumber = -1;
    bool bit = false;;
}PTE;

typedef struct Frame
{
    bool free = true;
    int processNo = -1;
    int pageNumber = -1;
}F;

vector<F> FrameTable(100);

typedef struct Process
{
	int pid;
    int pages;
    vector<PTE> PageTable;
}P;

bool allocateFrames(P &process)
{
    for(int i=0;i<frameNo;i++)
    {
        if(FrameTable[i].free)
        {
            FrameTable[i].free = false;
            FrameTable[i].processNo = process.pid;
            FrameTable[i].pageNumber = process.PageTable.size();

            PTE f;
            f.frameNumber = i;
            f.bit = true;
            process.PageTable.push_back(f);
            return true;;
        }
    }

    return false;
}

void allocateResources(int sharedLibrary, vector<P> &processes)
{
    //shared first
    for(int i=0;i<processes.size();i++)
    {
        for(int j=0;j<sharedLibrary;j++)
        {
            FrameTable[j].free = false;
            FrameTable[j].processNo = -1;
            FrameTable[j].pageNumber = processes[i].PageTable.size();

            PTE f;
            f.frameNumber = j;
            f.bit = true;
            processes[i].PageTable.push_back(f);
        }
    }

    for(int i=0;i<processes.size();i++)
    {
        for(int j=0;j<processes[i].pages-sharedLibrary;j++)
        {
            if(!allocateFrames(processes[i]))
            {
                cout << "Error: memory full!";
                exit(1);
            }
        }
    }
}

void printout(vector<P> processes, int sharedLibrary)
{
    for(int i=0;i<processes.size();i++)
    {
        cout << "Page Table for Process "<< i << endl << endl;
        
        for (int j=0;j<processes[i].PageTable.size();j++)
        {
            if(j<sharedLibrary)
                cout << "Page " << j << " (Lib) -> " << "Frame " << processes[i].PageTable[j].frameNumber << endl;
            else
                cout << "Page " << j << " (Data) -> " << "Frame " << processes[i].PageTable[j].frameNumber << endl;
        }
        cout << endl;
    }
}

int addressTranslation(vector<P> processes)
{
    int pid, logicalAddress;
    cout << "Enter Process ID and Logical Address(1001 -> for 1 page and 1 offset) to be translated: ";
    cin >> pid >> logicalAddress;

    if(pid<1 || pid>processes.size())
    {
        cout << "Error: Invalid Process ID!" << endl;
        return -1;
    }

    P process = processes[pid-1];
    int pageNumber = logicalAddress / 1000;
    int offset = logicalAddress % 1000;     

    if(pageNumber<0 || pageNumber>=process.pages)
    {
        cout << "Error: Invalid Logical Address!" << endl;
        return -1;
    }   
    PTE pte = process.PageTable[pageNumber];
    if(!pte.bit)
    {
        cout << "Error: Page not present!" << endl;
        return -1;      
    }
    int physicalAddress = pte.frameNumber * 1000 + offset;
    return physicalAddress;
}   

int main()
{
    int processNo, sharedLibrary;
	cout << "Total number of physical memory frames: ";
    cin >> frameNo;
    cout << "Size of shared Library(in Pages): ";
    cin >> sharedLibrary;
    cout << "No of processes: ";
    cin >> processNo;

    vector<P> processes;

	for (int i = 0; i < processNo; i++)
	{
		P p;
		p.pid = i+1;
        int input;
        cout << "Size of private data segment in process " << p.pid << " (in Pages): ";
        cin >> input;
        p.pages = sharedLibrary+input;
		processes.push_back(p);
	}

	cout << "\n-----Processes-----" << endl;
	for (int i = 0; i < processNo; i++)
	{
		cout << "Process ID " << processes[i].pid << " -> ";
        cout << "Total Pages: " << processes[i].pages  << endl;
	}	

    allocateResources(sharedLibrary, processes);
    printout(processes, sharedLibrary);
    int physicalAddress = addressTranslation(processes);
    if(physicalAddress!=-1)
        cout << "Physical Address: " << physicalAddress << endl; 

	return 0;
}