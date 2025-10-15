#include<iostream>
#include<vector>
using namespace std;

#define MAX_FRAME 3

typedef struct Frame
{
    int page_no;
    bool valid = false;
}F;

typedef struct Page
{
    int frame_no;
    bool valid = false;
}P;

vector<F> frames(MAX_FRAME);
vector<P> page_table(6);

void simulation(vector<int> page_no)
{
    int total_pagefault = 0;

    for(int i=0;i<page_no.size();i++)   
    {
        if(page_table[page_no[i]].valid)
        {
            cout << "Page found in Frame\t";
            cout << "Page no: " << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
        }
        else
        {
            bool found=false;
            for(int j=0;j<MAX_FRAME;j++)
            {
                if(!frames[j].valid)
                {
                    frames[j].page_no = page_no[i];
                    frames[j].valid = true;

                    page_table[page_no[i]].frame_no = j;
                    page_table[page_no[i]].valid = true;
                    cout << "Page inserted in Frame\tPage no: " << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                cout << "Page fault\t";
                total_pagefault++;

                int victim_index = i;
                int frame_no = 0;
                //using optimal policie
                for(int j=0;j<MAX_FRAME;j++)
                {
                    for(int k=i+1;k<page_no.size();k++)
                    {
                        if(frames[j].page_no == page_no[k] && victim_index < k)
                        {
                            victim_index = k;
                            frame_no = j;
                        }
                    }
                }

                page_table[page_no[victim_index]].valid = false;
                page_table[page_no[i]].frame_no = frame_no;
                page_table[page_no[i]].valid = true;

                frames[frame_no].page_no = page_no[i];

                cout << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
            }
        }
    }

    cout << "\nTotal Page fault : " << total_pagefault << endl;
}

int main()
{
    vector<int> reference_string = {0, 1, 2, 0, 3, 4, 1, 0, 3, 2, 4, 5, 1, 2, 3};

    simulation(reference_string);
}