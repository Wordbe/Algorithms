### DFS (깊이 우선 탐색)

그래프의 모든 정점을 발견하는 가장 단순하고 고전적인 방법.

* 현재 정점과 인접한 간선들을 하나씩 검사가하다가, 아직 방문하지 않은 정점으로 향하는 간선이 있으면 그 간선을 따라간다. dfs(edge)
* 막힌 정점에 도달하면 포기하고, 마지막에 따라왔던 간선을 따라 뒤로 돌아간다. dfs 종료



```c++
#include <vector>
using namespace std;

// adjacent list
vector<vector<int> > adj;
vector<bool> visited;

/*
    Depth First Search
    node u --> v
*/
void dfs(int u){
    visited[u] = true;
    // 모든 인접 정점을 순회하면서
    for (int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        // 방문한 적 없으면 방문한다.
        if (!visited[v])
            dfs(v);
    }
    // 더 이상 방문할 정점이 없으므로, 재귀 호출 종료하고 이전 정점으로 돌아간다.
}

void dfsAll(){
    visited = vector<bool>(adj.size(), false);
    for (int i=0; i<adj.size(); ++i){
        if (!vistied[i])
            dfs(i);
    }
}
```



#### DFS 시간복잡도

**인접리스트**의 경우

​	dfs() 한 정점마다 한 번씩 호출 되므로 dfs()는 |V|번 호출 된다.

​	dfs() 안의 for문은 모든 인접 간선을 검사하는 데 쓰이므로,

​	모든 간선을 정확히 한 번(방향 그래프, directed graph) 혹은 두 번(무향 그래프, indirected graph) 확인한다. 

​	따라서 O(|V| + |E|) 이다.

**인접행렬**의 경우

​	dfs() 호출 횟수는 |V|번이다.

​	하지만, dfs() 안에서 다른 모든 정점을 순회하며 간선이 있는가를 확인해야 하기 때문에 |V|번 확인한다. 

​	따라서 O(|V|<sup>2</sup>)이다.



### 응용

1) 두 정점이 서로 연결되어 있는지 확인

* visited 확인하면 된다.

2) 연결된 부분집합의 개수 세기

* 그래프가 쪼개어져 있는 경우 각 부분그래프를 컴포넌트(component) 혹은 요소라 한다.
* dfs로 주어진 그래프가 몇 개의 컴포넌트로 구성되어 있는지 확인 가능하다.

3) 위상 정렬(Topological sort)

* 의존성 그래프(dependency graph), 즉 DAG(directed acyclic graph)의 정점을 배열하는 문제

* dfsALL()을 수행하며, dfs()가 종료될 때마다 현재 정점을 기록하고, 기록순서를 뒤집으면 위상정렬 중 하나가 나온다.

>  이는 귀류법으로 증명이 가능하다. 
>
>  왼쪽에서 오른쪽으로 위상 정렬 해놓았을 때,
>
>  "오른쪽에서 왼쪽으로 가는 간선(u, v)이 있다고 가정하자."  (v <------- u)
>
>  == "dfs(u) 종료 후 dfs(v)가 종료되었다고 가정하자."
>
> 그런데 dfs(u)는 종료 전 모든 인접 간선을 보기 때문에, (u, v)또한 검사했을 것이다. 이 때 visted[v]는 참이었을까?
>
> 1) visited[v]가 거짓이었다면, dfs(u)는 dfs(v)를 재귀호출 했을 것이다. dfs(v)가 종료한 후에 dfs(u)가 종료되었을 것이고, 따라서 u가 v 왼쪽에 있어야 한다. 가정에 모순입니다.
>
> 2) visited[v]가 참이었다면, dfs(v)가 이미 한번 호출되었어야 한다. 그런데도 dfs(v)가 dfs(u)보다 늦게 끝났다는 것은 dfs(v)에서 재귀 호출을 거쳐 dfs(u)가 호출되어야 하는데, 이를 위해 간선(v, u)가 존재 했어야 합니다. 하지만 여기에 (u, v)가 있다면 사이클이 생기므로 DAG라는 가정에 모순이 됩니다.
>
>  두 경우 가정에 모순이 되므로 간선(u, v)는 존재할 수 없고, 항상 적절한 위상 정렬이 된다.



<참고: 알고리즘 문제해결 전략 2권>