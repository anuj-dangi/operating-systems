#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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

bool deadlock_detection(vector<int> available, vector<vector<int>> max, vector<vector<int>> allocated, vector<vector<int>> need, vector<vector<int>> request)
{
    vector<int> work = available;

    vector<bool> finish(n);

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
    srand(time(0));
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

    vector<vector<int>> request(4, vector<int> (3));
    // bankers(available, max, allocated, need, request, 1);

    int choice = 1;
    while(choice != 3)
    {
        cout << "Enter 1 for Deadlock Avoidance algo(bankers)\n";
        cout << "Enter 2 for Deadlock Detection and Recovery\n";
        cout << "Enter 3 to exit\n";
        cin >> choice;

        for(int i=0;i<n;i++)
        {
            cout << "requst for process " << i << " resources: ";
            for(int j=0;j<m;j++)
            {
                request[i][j] = rand()%3;
                cout << request[i][j] << " ";
            }
            cout << "\n";
        }

        switch(choice)
        {
            case 1: for(int i=0;i<n;i++)
                    {
                        cout << "bankers for process" << i << " request\n";
                        bankers(available, max, allocated, need, request[i], i);
                    }
                    break;
            case 2: for(int i=0;i<n;i++)
                    {
                        for(int j=0;j<m;j++)
                        {
                            if(request[i][j] <= available[j])
                            {
                                
                            }
                        }
                    }
            deadlock_detection(available, max, allocated, need, request);
                    break;
            default: break;
        }
    }

    return 0;
}