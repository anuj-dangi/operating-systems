#include <iostream>
#include <vector>
using namespace std;

int n = 4;
int m = 3;

bool deadlock_detection(vector<int> available, vector<vector<int>> max, vector<vector<int>> allocated, vector<vector<int>> need, vector<vector<int>> request)
{
    vector<int> work = available;

    vector<bool> finish(4);

    bool is_request;
    for(int i=0;i<n;i++)
    {
        is_request = false;
        for(int j=0;j<m;j++)
        {
            if(request[i][j] > 0)
            {
                is_request = true;
                break;
            }
        }
        finish[i] = !is_request;
    }

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
                    if(request[i][j] > work[j])
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
                    cout << "Work vector after simulation: ";
                    for (int w : work) cout << w << " ";
                    cout << endl;

                    finish[i] = true;

                    loop = true;
                }

            }
        }
    }

    bool deadlock = false;
    for (int i = 0; i < n; i++) 
    {
        if (!finish[i]) 
        {
            cout << "Process P" << i << " is in deadlock." << endl;
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "No Deadlock detected." << endl;

    return !deadlock;
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

    vector<vector<int>> request = {{1, 0, 1}, {2, 0, 3}, {0, 0, 0}, {0, 0, 1}};
    deadlock_detection(available, max, allocated, need, request);

    return 0;
}