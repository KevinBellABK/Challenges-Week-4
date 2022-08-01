// Chap 1 - AStar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    char name = ' ';
    int hvalue = 0;
    node* parent = nullptr;
    bool beenChecked = false;
    vector<node*> neighbors;
    vector<int> cost;
};

int findBestRoute(node* start, node* end)
{
    int cost = 0;
    queue<node*> check;
    check.push(start);
    while (!check.empty())
    {
        node* currNode = check.front();
        int size = currNode->neighbors.size(), currCost = INT_MAX, childIdx = -1;
        for (int i = 0; i < size; i++)
        {
            if (currNode->neighbors[i]->beenChecked)
                continue;
            int childCost = currNode->neighbors[i]->hvalue + currNode->cost[i];
            if (childCost < currCost)
            {
                childIdx = i;
                currCost = childCost;
            }
        }
        if (childIdx != -1)
        {
            cost += currCost;
            currNode->beenChecked = true;
            currNode->neighbors[childIdx]->parent = currNode;
            check.push(currNode->neighbors[childIdx]);
        }
        check.pop();
    }
    return cost;
}

int main()
{
    node A;
    node B;
    node C;
    node D;
    vector<node*> allNodes = { &A, &B, &C, &D };

    A.neighbors = { &B, &D };
    A.cost = { 5, 7 };

    B.neighbors = { &A, &C };
    B.cost = { 5, 1 };

    C.neighbors = { &B, &D };
    C.cost = { 1, 1 };

    D.neighbors = { &A, &C };
    D.cost = { 7, 1 };

    cout << "Cost of best route: " << findBestRoute(& A, & D) << endl;
}
