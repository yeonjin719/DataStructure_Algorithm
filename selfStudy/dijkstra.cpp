#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdio>
#include <limits>

using namespace std;

const int INF = 1000000;

int n;
vector<pair<int,int>> graph[100];
int dist[100];
int visit[100];

void dijkstra(int s) {
  for (int i = 1; i <= n; i++) {
    dist[i] = 1000000;
    visit[i] = 0;
  }
  dist[s] = 0;
  int v, w, lvw, d;
  priority_queue<pair<int, int>> pq;
  for (int i = 1; i <= n; i++)
    pq.push(make_pair(-dist[i], i));
    
  while (!pq.empty()) {
    v = pq.top().second;
    d = pq.top().first;
    pq.pop();
    printf("%d, %d\n", v, -d);
    if (visit[v] == 1)
      continue;
    visit[v] = 1;
    for (int j = 0; j < graph[v].size(); j++) {
      w = graph[v][j].first;
      lvw = graph[v][j].second;
      if (visit[w] == 1)
        continue;
      if (dist[w] > dist[v] + lvw) {
        dist[w] = dist[v] + lvw;
        pq.push(make_pair(-dist[w], w));
      }
    }
  }
}

int main() {
    n = 6;
    graph[1] = {{2,50},{3,45},{4,10}};
    graph[2] = {{3,10},{4,15}};
    graph[3] = {{5,30}};
    graph[4] = {{1,20}, {5,15}};
    graph[5] = {{2,20},{3,15}};
    graph[6] = {{5,3}};
    dijkstra(1);
}