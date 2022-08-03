// Chap 1 - AStar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
/*
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

void printRoute(node* end)
{
    node* currNode = end;
    while (currNode->parent != nullptr)
    {
        cout << currNode->name << "<-";
        currNode = currNode->parent;
    }
    cout << currNode->name << endl;
}

int main()
{
    node A;
    A.name = 'A';
    node B;
    B.name = 'B';
    node C;
    C.name = 'C';
    node D;
    D.name = 'D';
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
    printRoute(&D);
}
*/

struct Node;

struct Edge {
    int m_cost = 0;
    Node* m_node = nullptr;

    Edge(int cost, Node* node)
        : m_cost(cost)
        , m_node(node)
    {

    }
};

struct Node {
    char m_name = ' ';
    int m_hValue = 0;
    vector<Edge*> neighbors;

    Node(char name, int hValue)
        : m_name(name)
        , m_hValue(hValue)
    {

    }

    Node(char name)
        : m_name(name)
        , m_hValue(0)
    {

    }

    int getCost(Node* node)
    {
        for (Edge* n : neighbors)
            if (n->m_node == node)
                return n->m_cost;
        return -1;
    }
};

struct VisitedNode {
    Node* m_node = nullptr;
    int m_currCost = 0;

    VisitedNode() = default;
    VisitedNode(Node* node, int currCost)
        : m_node(node)
        , m_currCost(currCost)
    {

    }

    friend bool operator < (VisitedNode const& n1, VisitedNode const& n2)
    {
        return n1.m_currCost > n2.m_currCost;
    }
};

void DijkstraAlgo(Node* start, Node* goal)
{
    priority_queue<VisitedNode> openList;
    openList.push({ start, 0 });
    unordered_map<Node*, VisitedNode> cameFrom;
    cameFrom[start] = { nullptr, 0 };

    while (!openList.empty())
    {
        Node* curr = openList.top().m_node;
        openList.pop();

        if (curr == goal)
            break;

        for (Edge* n : curr->neighbors)
        {
            Node* neigh = n->m_node;
            int newCost = cameFrom[curr].m_currCost + n->m_cost;
            if (cameFrom.find(neigh) == cameFrom.end() || newCost < cameFrom[neigh].m_currCost)
            {
                openList.push({ neigh, newCost });
                cameFrom[neigh] = {curr, newCost};
            }
        }
    }

    cout << cameFrom[goal].m_currCost << endl;

    Node* curr = goal;
    vector<Node*> path;
    while (curr != start)
    {
        path.push_back(curr);
        curr = cameFrom[curr].m_node;
    }
    path.push_back(start);
    for (int i = path.size() - 1; i > -1; i--)
    {
        if (i == path.size() - 1)
            cout << path[i]->m_name;
        else
            cout << "->" << path[i]->m_name;
    }
}

void addNeigh(Node* n, Node* con, int cost)
{
    n->neighbors.push_back(new Edge(cost, con));
}

int main()
{
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');
    Node* G = new Node('G');

    /*
    addNeigh(A, B, 2); addNeigh(A, E, 1); addNeigh(A, F, 3);
    addNeigh(B, A, 2); addNeigh(B, C, 1);
    addNeigh(C, B, 1); addNeigh(C, E, 1); addNeigh(C, D, 2);
    addNeigh(D, C, 2); addNeigh(D, E, 5); addNeigh(D, F, 1);
    addNeigh(E, A, 1); addNeigh(E, C, 1); addNeigh(E, D, 5); addNeigh(E, F, 1);
    */
    
    A->neighbors.push_back(new Edge(5, B)); A->neighbors.push_back(new Edge(10, D));
    B->neighbors.push_back(new Edge(5, A)); B->neighbors.push_back(new Edge(1, C));
    C->neighbors.push_back(new Edge(1, B)); C->neighbors.push_back(new Edge(1, D));
    D->neighbors.push_back(new Edge(1, C)); D->neighbors.push_back(new Edge(10, A));
    
/*
    addNeigh(A, B, 2); addNeigh(A, C, 6);
    addNeigh(B, A, 2); addNeigh(B, D, 5);
    addNeigh(C, A, 6); addNeigh(C, D, 8);
    addNeigh(D, B, 5); addNeigh(D, C, 8); addNeigh(D, E, 15); addNeigh(D, F, 10);
    addNeigh(E, D, 15); addNeigh(E, F, 6); addNeigh(E, G, 6);
    addNeigh(F, D, 10); addNeigh(F, E, 6); addNeigh(F, G, 2);
    addNeigh(G, E, 6); addNeigh(G, F, 2);
*/
    DijkstraAlgo(A, D);
}
