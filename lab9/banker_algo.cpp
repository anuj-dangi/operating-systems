#include <iostream>
#include <vector>
using namespace std;

int n = 4;
int m = 3;

bool safety(vector<int> available, vector<vector<int>> max, vector<vector<int>> allocated, vector<vector<int>> need)
{
    vector<int> work = available;

    vector<bool> finish(4, false);
    cout << "Order of Process exectution: ";

    bool loop = true;
    while(loop)
    {
        loop = false;
        for(int i=0;i<n;i++)
        {
            if(!finish[i])
            {
                bool b = true;
                for(int j=0;j<m;j++)
                {
                    if(need[i][j] > work[j])
                    {
                        b = false;
                        break;
                    }
                }

                if(b)
                {
                    for(int j=0;j<m;j++)
                    {
                        work[j] += allocated[i][j];
                    }
                    finish[i] = true;

                    cout << "P" << i << " ";
                    loop = true;
                }

            }
        }
    }

    for(int j=0;j<n;j++)
    {
        if(!finish[j])
        {
            return false;
        }
    }
    cout << endl;

    return true;
}

int bankers(vector<int> &available, vector<vector<int>> &max, vector<vector<int>> &allocated, vector<vector<int>> &need, vector<int> &request, int pno)
{
    for(int j=0;j<m;j++)
    {
        if(request[j] > need[pno][j])
        {
            cout << "Error, Illegal Request!" << endl;
            return -1;
        }
    }

    for(int j=0;j<m;j++)
    {
        if(request[j] > available[j])
        {
            cout << "Wait" << endl;
            return -2;
        }
    }

    //simulation
    for(int j=0;j<m;j++)
    {
        allocated[pno][j] = allocated[pno][j] + request[j];
        need[pno][j] = need[pno][j] - request[j];
        available[j] = available[j] - request[j];
    }

    cout << "Requesting for resources for P" << pno << endl;
    for (int i=0;i<m;i++)
    {
        cout << request[i] << " ";
    }
    cout << endl;
    if(safety(available, max, allocated, need))
    {
        cout << "Commit allocation" << endl;
        return 1;
    }
    else
    {
        //roolback
        for(int j=0;j<m;j++)
        {
            allocated[pno][j] = allocated[pno][j] - request[j];
            need[pno][j] = need[pno][j] + request[j];
            available[j] = available[j] + request[j];
        }

        return 0;   
    }
    
}

int main()
{
    vector<int> available = {5, 5, 4};
    vector<vector<int>> max = {
        {4, 1, 3},
        {1, 0, 2},
        {0, 2, 3},
        {0, 0, 1}
    };
    vector<vector<int>> allocated = {
        {1, 1, 1},
        {0, 0, 1},
        {0, 1, 2},
        {0, 0, 0}
    };
    vector<vector<int>> need = {
        {3, 0, 2},
        {1, 0, 1},
        {0, 1, 1},
        {0, 0, 1}
    };

    vector<int> request = {1, 0, 0};
    bankers(available, max, allocated, need, request, 1);

    return 0;
}