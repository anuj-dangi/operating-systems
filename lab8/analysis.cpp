#include <iostream>
#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

typedef struct Frame
{
    int page_no;
    bool valid = false;
} F;

typedef struct Page
{
    int frame_no;
    bool valid = false;
} P;

vector<vector<int>> reference_string;

void workingSet(int t)
{
    vector<unordered_set<int>> working_set;
    int dt = 5;

    cout << "-----Working Set t=" << t << "-----\n";
    for(int i=0;i<reference_string.size();i++)
    {
        cout << "Process "<< i << " : ";
        unordered_set<int> temp;
        for(int j=t-dt+1;j<reference_string[i].size() && j<=t;j++)
        {
            temp.emplace(reference_string[i][j]);
        }

        working_set.push_back(temp);
        for(int ele: working_set[i])
        {
            cout << ele << " ";
        }
        cout << endl;
    }

}

void fifo(vector<int> page_no, vector<F> frames, vector<P> page_table);

void analysis(int size)
{
    vector<unordered_set<int>> working_set;
    int dt = 20;

    cout << "-----Working Set t=" << 20 << "-----\n";
    for(int i=0;i<reference_string.size();i++)
    {
        cout << "Process "<< i << " : ";
        unordered_set<int> temp;
        for(int j=0;j<reference_string[i].size() && j<=20;j++)
        {
            temp.emplace(reference_string[i][j]);
        }

        working_set.push_back(temp);
        for(int ele: working_set[i])
        {
            cout << ele << " ";
        }
        cout << endl;
    }

    int d = 0;
    for(int i=0;i<3;i++)
    {
        d += working_set[i].size();
    }

    if(d > size)
    {
        cout << "D : " << d << " and M : " << size;
        cout << "\n---Thrashing Occurred---\n";
    }

    for(int i=0;i<3;i++)
    {
        vector<F> frames(size);
        vector<P> page_table(reference_string[i].size());
        cout << "\n-----Process " << i << " Page replacement-----\n";
        fifo(reference_string[i], frames, page_table);
    }
}

void fifo(vector<int> page_no, vector<F> frames, vector<P> page_table)
{
    cout << "-----FIRST IN FIRST OUT-----\n\n";
    queue<int> q;

    int total_pagefault = 0;

    for (int i = 0; i < page_no.size(); i++)
    {
        if (page_table[page_no[i]].valid)
        {
            cout << "Page found in Frame\t";
            cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
        }
        else
        {
            bool found = false;
            for (int j = 0; j < 4; j++)
            {
                if (!frames[j].valid)
                {
                    frames[j].page_no = page_no[i];
                    frames[j].valid = true;

                    page_table[page_no[i]].frame_no = j;
                    page_table[page_no[i]].valid = true;
                    cout << "Page inserted in Frame\tPage no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
                    found = true;
                    q.push(j);
                    break;
                }
            }

            if (!found)
            {
                cout << "Page fault\t";
                total_pagefault++;

                int frame_no = q.front();
                q.pop();

                page_table[frames[frame_no].page_no].valid = false;
                page_table[page_no[i]].frame_no = frame_no;
                page_table[page_no[i]].valid = true;

                frames[frame_no].page_no = page_no[i];

                q.push(frame_no);

                cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
            }
        }
    }

    cout << "\nTotal Page fault : " << total_pagefault << endl;
}

int main()
{
    srand(time(0));

    cout << "-----Reference Strings-----" << endl;
    for(int i=0;i<3;i++)
    {
        cout << "Process " << i << " : ";
        vector<int> temp;
        for(int j=0;j<20;j++)
        {
            temp.push_back(rand()%10);
            cout << temp[j] << " ";
        }
        cout << endl;
        reference_string.push_back(temp);
    }

    workingSet(4);
    workingSet(6);
    workingSet(11);
    workingSet(18);

    analysis(4);
}