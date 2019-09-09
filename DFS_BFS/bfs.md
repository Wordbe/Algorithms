## BFS (너비 우선 탐색)

> 시작점에서 가까운 정점부터 순서대로 방문하는 탐색 알고리즘



* 각 정점을 방문할 때마다 모든 인접 정점을 검사합니다.
* 처음 보는 정점을 발견하면 이 점을 방문 예정(discoverd)이라고 기록한 뒤, 별도의 위치(queue)에 저장합니다.
* 인접한 정점을 모두 검사하고 나면, 저장한 목록에서 다음 정점을 꺼내서 방문합니다.



BFS (너비 우선 탐색)에서 새 정점을 발견하는데 사용했던 간선을 모은 트리를 BFS Spanning Tree(너비 우선 탐색 신장 트리) 라고 부릅니다.



```c++
#include <vector>
#include <queue>
using namespace std;

// Adjacent List
vector<vector<int> > adj;
vector<int> order;

/*
    start 노드로부터 시작하여 너비 우선 탐색하여 각 정점을 방문한 순서를 order에 기록한다.
*/
void bfs(int start){
    vector<bool> discoverd(adj.size(), false);
    queue<int> q;

    discoverd[start] = true;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order.emplace_back(u);
        // u와 인접한 모든 노드 v에 대하여
        for (int i=0; i<adj[u].size(); ++i){
            int v = adj[u][i];
            // 발견되지 않았으면 발견되었다고 표시한 다음 큐에 넣는다.
            if (!discoverd[v]){
                discoverd[v] = true;
                q.push(v);
            }
        }
    }
}

```



### BFS 시간복잡도

모든 정점을 한 번씩 방문하며, 방문할 때마다 인접한 모든 간선을 검사하기 때문에 

인접 리스트에서는 O(|V| + |E|),

인접 행렬에서는 O(|V|<sup>2</sup>)가 걸립니다.



DFS에서는 다양한 문제를 푸는데 응용 되었지만 (두 정점의 연결 확인, 연결된 부분집합 개수 세기, 위상 정렬 등)

BFS에서는 단 하나의 용도로 사용되는데 그것이 바로 *최단 경로 문제*를 푸는 것입니다.

> BFS 과정에서 간선 (u, v)를 통해 정점 v를 처음 발견해 큐에 넣었다고 합시다.
>
> 이 때 시작점으로 부터 v까지 최단 거리를 distance[v]라 하면, distance[v] = distance[u] + 1 이 성립합니다.
>
> 즉, 시작점으로부터 다른 모든 정점까지의 최단 경로를 BFS spanning tree로 찾을 수 있다는 것입니다.



```C++
vector<int> distance;
vector<int> parent;

void bfs2(int start){
    distance = vector<int> (adj.size(), -1);
    parent = vector<int> (adj.size(), -1);
    // 방문할 정점 목록을 유지하는 큐
    queue<int> q;
    
    distance[start] = 0;
    parent[start] = start;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();

        for (int i=0; i<adj[u].size(); ++i){
            int v = adj[u][i];
            if (distance[v] == -1){
                distance[v] = distance[u] + 1;
                q.push(v);
                parent[v] = u;
            }
        }
    }
}

vector<int> shortestPath(int v){
    vector<int> path(1, v);
    while(parent[v] != v){
        v = parent[v];
        path.emplace_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
```





#### 모든 점 발견?

그래프 전체 구조에 관한 정보를 얻기 위해 사용되는 깊이 우선 탐색과 달리, 너비 우서 탐색은 대게 시작점으로부터 다른 정점들까지의 거리를 구하기 위해 사용됩니다. DFS처럼 모든 정점을 검사하면서 탐색을 수행하는 작업은 잘하지 않습니다.

​	

