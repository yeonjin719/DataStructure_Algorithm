// prim_cxx11.cpp
// C++11 호환: input.txt의 여러 그래프에 대해 Prim MST 계산

#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility> // pair
#include <vector>

using namespace std;

struct Edge {
  int to, w;
};
struct Picked {
  int u, v, w;
}; // MST에 채택된 간선 (u-v, 가중치 w)

struct HeapItem {
  int w, u, v; // (가중치, from, to)
};
struct Cmp {
  bool operator()(const HeapItem &a, const HeapItem &b) const {
    return a.w > b.w; // min-heap
  }
};

pair<long long, vector<Picked>> prim_mst(int n, const vector<vector<Edge>> &g,
                                         int start) {
  vector<char> used(n + 1, 0);
  priority_queue<HeapItem, vector<HeapItem>, Cmp> pq;
  vector<Picked> mst;
  mst.reserve(n ? n - 1 : 0);
  long long total = 0;

  // start에서 나가는 간선 push
  used[start] = 1;
  for (size_t i = 0; i < g[start].size(); ++i) {
    const Edge &e = g[start][i];
    if (!used[e.to]) {
      HeapItem hi;
      hi.w = e.w;
      hi.u = start;
      hi.v = e.to;
      pq.push(hi);
    }
  }

  while (!pq.empty() && (int)mst.size() < n - 1) {
    HeapItem top = pq.top();
    pq.pop();
    if (used[top.v])
      continue;

    used[top.v] = 1;
    total += top.w;
    Picked p;
    p.u = top.u;
    p.v = top.v;
    p.w = top.w;
    mst.push_back(p);

    // 새로 편입된 정점에서 나가는 간선들 push
    int u = top.v;
    for (size_t i = 0; i < g[u].size(); ++i) {
      const Edge &e = g[u][i];
      if (!used[e.to]) {
        HeapItem hi;
        hi.w = e.w;
        hi.u = u;
        hi.v = e.to;
        pq.push(hi);
      }
    }
  }

  if ((int)mst.size() != n - 1) {
    return make_pair(-1LL, vector<Picked>()); // 비연결
  }
  return make_pair(total, mst);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ifstream fin("input.txt");
  if (!fin.is_open()) {
    cerr << "⚠️ input.txt 파일을 찾을 수 없습니다.\n";
    return 1;
  }

  int T; // 그래프 개수
  if (!(fin >> T))
    return 0;

  for (int t = 1; t <= T; ++t) {
    int n, m; // 정점 수, 간선 수
    fin >> n >> m;
    vector<vector<Edge>> g(n + 1);

    for (int i = 0; i < m; ++i) {
      int u, v, w;
      fin >> u >> v >> w;
      Edge e1;
      e1.to = v;
      e1.w = w;
      g[u].push_back(e1);
      Edge e2;
      e2.to = u;
      e2.w = w;
      g[v].push_back(e2); // 무방향
    }

    pair<long long, vector<Picked>> res = prim_mst(n, g, 1);

    cout << "=== Graph #" << t << " ===\n";
    if (res.first < 0) {
      cout << "Graph is not connected\n\n";
    } else {
      cout << "MST weight = " << res.first << "\n";
      cout << "Edges (u v w):\n";
      for (size_t i = 0; i < res.second.size(); ++i) {
        cout << res.second[i].u << ' ' << res.second[i].v << ' '
             << res.second[i].w << '\n';
      }
      cout << '\n';
    }
  }
  fin.close();
  return 0;
}