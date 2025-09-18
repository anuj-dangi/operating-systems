#include<iostream>
#include <vector>
#include <ctime>
#include <time.h>
using namespace std;

class PageTable
{
public:
    int pt[120];

    PageTable()
    {
        for(int i=0;i<120;i++)
        {
            pt[i] = -1;
        }
    }

    int frameNo(int pageNo)
    {
        if(pageNo >= 120 || pageNo < 0)
        {
            cout << "Error Page No. Out of Bound!\n";
            return -2;
        }

        return pt[pageNo];
    }
    
    void printPageTable()
    {
        cout << "Page#\t" << "Fram#" << endl;

        for(int i=0;i<120;i++)
        {
            if(pt[i] != -1)
                cout << i << "\t" << pt[i] << endl;
        }
    }

    int logicalToPhysical(int logical)
    {
        int pageNo = logical/1024;
        cout << "Page no: " << pageNo << endl;
        int offset = logical%1024;
        cout << "offset: " << offset << endl;
        int frame;

        if( (frame = frameNo(pageNo)) )
        {
            if(frame == -1)
            {
                cout << "Page Fault!\n";
                return -1;
            }
            else if(frame == -2)
            {
                return -1;
            }
        }

        cout << "Frame No: " << frame << endl;

        int physical = (frame*1024) + offset;

        return physical;
    }
};

int main()
{
    PageTable p;
    srand(time(NULL));
    int n;

    cout << "Enter page no to insert: ";
    cin >> n;

    int k;
    for(int i=0;i<n;i++)
    {
        cout << "Page No followed by Frame no: ";
        cin >> k;
        cin >> p.pt[k];
    }
    p.printPageTable();

    int logical = 0;
    while(logical != -1)
    {
        cout << "\nEnter logical address(-1 for exit): ";
        
        cin >> logical;

        int physical = p.logicalToPhysical(logical);
        if(physical != -1)
        {
            cout << "Phyical address: " << physical << endl;
        }
    }

    return 0;
}