#include <queue>
#include <utility>
#include <map>

using namespace std;

int bfsv2(int arr[37][33], int gx, int gy, int pcx, int pcy, char c) //(Board.txt 2D array, ghost x position, ghost y position, pacman x position, pacman y position ) 
{

    queue<pair<int, int> >q;

    int x[] = { 1,-1,0,0 };
    int y[] = { 0,0,1,-1 };

    pair<int, int> currentNode, neighborNode;
    int positionsAway = 4;

    pair<int, int> pacmanPosition;
    switch (c)
    {
    case('U'):
    {
        while (positionsAway >= 0)
        {
            if (pcx - positionsAway < 36 && pcx - positionsAway > 0 && (arr[pcx - positionsAway][pcy] == 9 || arr[pcx - positionsAway][pcy] == 0 || arr[pcx - positionsAway][pcy] == 99 || arr[pcx - positionsAway][pcy] == 98))
            {
                pacmanPosition = make_pair(pcx - positionsAway, pcy);
                break;
            }
            positionsAway--;
        }
        break;
    }
    case('D'):
    {
        while (positionsAway >= 0)
        {
            if (pcx + positionsAway < 36 && pcx + positionsAway > 0 && (arr[pcx + positionsAway][pcy] == 9 || arr[pcx + positionsAway][pcy] == 0 || arr[pcx + positionsAway][pcy] == 99 || arr[pcx + positionsAway][pcy] == 98))
            {
                pacmanPosition = make_pair(pcx + positionsAway, pcy);
                break;
            }
            positionsAway--;
        }
        break;
    }
    case('R'):
    {
        while (positionsAway >= 0)
        {
            if (pcy + positionsAway < 32 && pcy + positionsAway > 0 && (arr[pcx][pcy + positionsAway] == 9 || arr[pcx][pcy + positionsAway] == 0 || arr[pcx][pcy + positionsAway] == 99 || arr[pcx][pcy + positionsAway] == 98))
            {
                pacmanPosition = make_pair(pcx, pcy + positionsAway);
                break;
            }
            positionsAway--;
        }
        break;
    }
    case('L'):
    {
        while (positionsAway >= 0)
        {
            if (pcy - positionsAway < 32 && pcy - positionsAway > 0 && (arr[pcx][pcy - positionsAway] == 9 || arr[pcx][pcy - positionsAway] == 0 || arr[pcx][pcy - positionsAway] == 99 || arr[pcx][pcy - positionsAway] == 98))
            {
                pacmanPosition = make_pair(pcx, pcy - positionsAway);
                break;
            }
            positionsAway--;
        }
        break;
    }
    }
    if (pacmanPosition.first == gx && pacmanPosition.second == gy)
    {
        return 1;
    }
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

    parent[ghostPosition] = make_pair(-1, -1);
    while (!q.empty())
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
                    break;
            }
        }
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