#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>
#include <cctype>   
using namespace std;

int n, m;
vector<pair<int, pair<int,int>>> edges;

inline int toId(char ch){ return toupper((unsigned char)ch) - 'A' + 1; }
inline char toChar(int id){ return 'A' + id - 1; }

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n){
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x){
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y){
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
        return true;
    }
};

void kruskal(){
    vector<pair<int,int>> mcst;
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<pair<int, pair<int,int>>>
    > pq;

    UnionFind uf(n);
    for (int i = 0; i < m; i++) pq.push(edges[i]);

    while (!pq.empty() && (int)mcst.size() < n - 1){
        int w = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
				// union-find를 고려하여 사이클이 발생하지 않는 경우에만 간선을 선택
        if (uf.find(u) != uf.find(v)){
            mcst.push_back({u, v});
            uf.unite(u, v);
        }
    }

    if ((int)mcst.size() < n - 1){
        printf("No MCST\n");
        return;
    }
    for (int i = 0; i < (int)mcst.size(); i++){
        printf("<%c, %c>\n", toChar(mcst[i].first), toChar(mcst[i].second));
    }
}

int main(){
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL){ perror("파일을 열 수 없습니다"); return 1; }

    int tc; fscanf(fp, "%d", &tc);
    for (int t = 0; t < tc; t++){
        edges.clear();

        fscanf(fp, "%d %d", &n, &m);      
        for (int i = 0; i < m; i++){
            char cu, cv; int w;
            fscanf(fp, " %c %c %d", &cu, &cv, &w);
            int u = toId(cu), v = toId(cv);
            edges.push_back({w, {u, v}});
        }
        kruskal();
        if (t != tc - 1) puts("");
    }
    fclose(fp);
    return 0;
}