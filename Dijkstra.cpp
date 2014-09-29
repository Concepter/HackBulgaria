#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>
#define MAXNODES 10001
#define INF 1000000001
 
using namespace std;
 
struct Edge
{
        int to, weight;
        Edge (int _to = 0,int _weight = 0)
        {
                to = _to;
                weight = _weight;
        }
};
 
struct State
{
        int prev, node;
        long long weight;
        State (int _prev = 0, int _node = 0, long long _weight = 0)
        {
                prev = _prev;
                node = _node;
                weight = _weight;
        }
 
        bool operator < (const State& r) const
        {
                return (weight != r.weight) ? (weight > r.weight) : (node < r.node);
        }
};

void ResetParameters(int nodesNumber)
{
        for(int node=0; node<nodesNumber; node++)
        {
                graph[node].resize(0);
                visited[node] = false;
                parent[node] = -1;
                dist[node] = INF;
        }
}
 
long long Dijkstra(int startNode, int endNode)
{
        State nextNode, curNode;
		// cur - current
        priority_queue<State> q;
 
        dist[startNode] = 0;
       
        q.push(State(startNode, 0, 0));
 
        while(!q.empty())
        {
                curNode = q.top();
                q.pop();
 
                if(visited[curNode.node]) continue;
 
                visited[curNode.node] = true;
 
                for(int edge = 0; edge<(int)graph[curNode.node].size(); edge++)
                {
                        nextNode.node = graph[curNode.node][edge].to;
                        nextNode.prev = curNode.node;
                        nextNode.weight = curNode.weight + graph[curNode.node][edge].weight;
 
                        if(nextNode.weight < dist[nextNode.node])
                        {
                                parent[nextNode.node] = curNode.node;
                                dist[nextNode.node] = nextNode.weight;
                                q.push(nextNode);
                        }
                }
 
        }
 
        if(dist[endNode] >= INF)
                return -1;
        else
                return dist[endNode];
}
 
bool visited[MAXNODES] = {false};
long long dist[MAXNODES] = {INF};
int parent[MAXNODES] = {-1};
vector <Edge> graph[MAXNODES];
 
void ResetParameters(int nodesNumber);
long long Dijkstra(int startNode, int endNode);
 
int main()
{
        int T = 0, N = 0, M = 0;
        int N1, N2, C;
        long long result = -1;
        stack<int> path;
 
        scanf_s("%d", &T);
 
       
        for(int test = 0; test < T; test++)
        {
                scanf_s("%d %d", &N, &M);
 
                /* resetting distances between parent and "son" */
                ResetParameters(N);
 
                /* initialization */
                for(int vertex=0; vertex<M; vertex++)
                {
                        scanf_s("%d %d %d", &N1, &N2, &C);
                        graph[N1-1].push_back(Edge(N2-1, C));
                        graph[N2-1].push_back(Edge(N1-1, C));
                }
 
                result = Dijkstra(0, N-1);
                printf("%lld\n", result);
                if(result != -1)
                {
                        int node = N - 1;
                        int nodesCount = 0;
                        while(node != -1)
                        {
                                path.push(node);
                                node = parent[node];
                                nodesCount++;
                        }
 
                        printf("%d\n", nodesCount);
                        for(int curNode = 0; curNode<nodesCount-1; curNode++)
                        {
                                printf("%d ", path.top() + 1);
                                path.pop();
                        }
                        printf("%d\n", path.top() + 1);
                        path.pop();
                }
        }
 
        return 0;
}
 
