#include<iostream>
#include <vector>

using namespace std;

class Segmentation
{
public:
    vector<pair<int, int>> segment;   //Base, limit

    Segmentation(int n)
    {
        for(int i=0;i<n;i++)
        {
            segment.push_back({-1, -1});
        }
    }
    
    void printSegmentTable()
    {
        cout << "Segment#\t" << "Base Address\t" << "Limit" << endl;

        for(int i=0;i<segment.size();i++)
        {
            if(segment[i].first != -1)
                cout << i << "\t\t" << segment[i].first << "\t\t" << segment[i].second << endl;
        }
    }

    int logicalToPhysical(int segmentNo, int limit)
    {
        if(segmentNo >= segment.size() || segmentNo < 0)
        {
            cout << "Error Segment number out of Bound!\n";
            return -1;
        }

        if(limit > segment[segmentNo].second)
        {
            cout << "Error Segmentation fault!\n";
            return -1;
        }

        int physical = segment[segmentNo].first + limit;

        return physical;
    }
};

int main()
{
    int n;

    cout << "Enter Segments numbers to insert: ";
    cin >> n;

    Segmentation p(n);

    int k;
    for(int i=0;i<n;i++)
    {
        cout << "Segment " << i << " base address followed by limit: ";
        cin >> p.segment[i].first >> p.segment[i].second;
    }
    p.printSegmentTable();

    int logical, segmentNo = 0;
    while(segmentNo != -1)
    {
        cout << "\nEnter Segment No(-1 for exit) followed by logical address: ";
        cin >> segmentNo;
        if(segmentNo == -1)
            return 0;
        cin >> logical;

        int physical = p.logicalToPhysical(segmentNo, logical);
        if(segmentNo != -1)
        {
            cout << "Phyical address: " << physical << endl;
        }
    }

    return 0;
}