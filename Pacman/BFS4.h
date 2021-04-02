#include <queue>
#include <utility>
#include <map>
using namespace std;
int bfsv4(int arr[37][33], int gx, int gy, int pcx, int pcy)
{
    queue<pair<int, int> >q;

    int x[] = { 1,-1,0,0 };
    int y[] = { 0,0,1,-1 };

    pair<int, int> currentNode, neighborNode;

    pair<int, int> pacmanPosition = make_pair(pcx, pcy);
    pair<int, int> ghostPosition = make_pair(gx, gy);

    q.push(ghostPosition);

    map< pair<int, int>, pair<int, int> >parent;

    bool vis[37][33];

    for (int i = 0; i < 37; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            vis[i][j] = false;
        }
    }
    vis[gx][gy] = true;
    int sz, level = 0;
    parent[ghostPosition] = make_pair(-1, -1);
    bool isitinside = false;
    while (!q.empty())
    {
        sz = q.size();
        level++;
        while (sz--)
        {
            currentNode = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                if (
                    currentNode.first + x[i] < 36 && currentNode.first + x[i] > 0 &&
                    currentNode.second + y[i] < 32 && currentNode.second + y[i] > 0 &&
                    !vis[currentNode.first + x[i]][currentNode.second + y[i]] &&
                    (arr[currentNode.first + x[i]][currentNode.second + y[i]] == 9 || arr[currentNode.first + x[i]][currentNode.second + y[i]] == 0 || arr[currentNode.first + x[i]][currentNode.second + y[i]] == 99 || arr[currentNode.first + x[i]][currentNode.second + y[i]] == 98)
                    )
                {
                    neighborNode = make_pair(currentNode.first + x[i], currentNode.second + y[i]);
                    vis[neighborNode.first][neighborNode.second] = true;
                    q.push(neighborNode);
                    parent[neighborNode] = currentNode;
                    if (neighborNode.first == pcx && neighborNode.second == pcy)
                    {
                        if (level <= 10)
                        {
                            isitinside = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    if (isitinside)
    {
        return bfs(arr, gx, gy, 35, 1);
    }
    currentNode = pacmanPosition;

    while (parent[parent[currentNode]].first != -1 && parent[parent[currentNode]].second != -1)
    {
        currentNode = parent[currentNode];
    }

    if (currentNode.first == ghostPosition.first + 1)
        return 1;
    if (currentNode.first == ghostPosition.first - 1)
        return 0;
    if (currentNode.second == ghostPosition.second + 1)
        return 2;
    if (currentNode.second == ghostPosition.second - 1)
        return 3;
}
