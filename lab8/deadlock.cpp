#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int dfsrec(vector<int> &reach, vector<vector<int>> graph, int i)
{
    if(i == 0 && reach.size() != 0)
    {
        reach.push_back(i);
        cout << "Deadlock detected! Cycle: ";
        return 1;
    }

    reach.push_back(i);

    for(int j=0;j<4;j++)
    {
        if(graph[i][j] == 1)
        {
            if(dfsrec(reach, graph, j))
                return 1;
        }
    }

    return 0;
}

void dfs(vector<vector<int>> graph)
{
    vector<pair<int, int>> allo;
    vector<pair<int, int>> requ;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(graph[i][j] == 1)
            {
                if(i > 1)
                {
                    allo.push_back({i, j});
                }
                else
                {
                    requ.push_back({i, j});
                }
            }
        }
    }

    vector<string> node = {"p1", "p2", "r1", "r2"};

    cout << "Allocate edges : ";
    for(int i=0;i<allo.size();i++)
    {
        cout << "(" << node[allo[i].first] << ", " << node[allo[i].second] << ") ";
    }
    cout << endl;

    cout << "Request edges : ";
    for(int i=0;i<requ.size();i++)
    {
        cout << "(" << node[requ[i].first] << ", " << node[requ[i].second] << ") ";
    }
    cout << endl;

    vector<int> reach;

    if(dfsrec(reach, graph, 0))
    {
        for(int i=0;i<reach.size()-1;i++)
        {
            cout << node[reach[i]] << "->";
        }
        cout << node[reach[reach.size()-1]] << endl << endl;

    }
    else
    {
        cout << "No Deadlock Detected" << endl;
    }

}

int main()
{
    //p1, p2, r1 ,r2
    vector<vector<int>> graph1 = {
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 1, 0, 0},
        {1, 0, 0, 0}
    };

    vector<vector<int>> graph2 = {
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };

    dfs(graph1);
    dfs(graph2);
}