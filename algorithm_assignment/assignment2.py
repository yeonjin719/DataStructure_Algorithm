# kosaraju_partition.py
import sys

def read_graph(path: str):
    with open(path, "r", encoding="utf-8") as f:
        V, E = map(int, f.readline().split())
        adj  = [[] for _ in range(V + 1)]   # 1-based
        radj = [[] for _ in range(V + 1)]
        for _ in range(E):
            u, v = map(int, f.readline().split())
            adj[u].append(v)
            radj[v].append(u)
    return V, adj, radj

def kosaraju(V, adj, radj):
    # 1) 역그래프에서 종료순서(order) 만들기
    visited = [False] * (V + 1)
    order = []
    for s in range(1, V + 1):
        if visited[s]: continue
        stack = [(s, 0, 0)]  # (u, i, stage) stage:0 진행, 1 post 기록
        visited[s] = True
        while stack:
            u, i, st = stack.pop()
            if st == 1:
                order.append(u)
                continue
            if i < len(radj[u]):
                stack.append((u, i+1, 0))
                w = radj[u][i]
                if not visited[w]:
                    visited[w] = True
                    stack.append((w, 0, 0))
            else:
                stack.append((u, 0, 1))

    # 2) 원그래프에서 order 역순으로 DFS → SCC 수집
    visited = [False] * (V + 1)
    sccs = []
    for s in reversed(order):
        if visited[s]: continue
        comp = []
        stack = [s]
        visited[s] = True
        while stack:
            u = stack.pop()
            comp.append(u)
            for w in adj[u]:
                if not visited[w]:
                    visited[w] = True
                    stack.append(w)
        comp.sort()
        sccs.append(comp)

    # 보기 좋은 정렬(선택): 크기 내림차순, 같으면 사전순
    sccs.sort(key=lambda c: (-len(c), c))
    return sccs

def format_partition(sccs):
    return ", ".join("{" + ", ".join(map(str, comp)) + "}" for comp in sccs)

def main():
    path = "searchgraph.txt"
    if len(sys.argv) > 1:
        path = sys.argv[1]

    V, adj, radj = read_graph(path)
    sccs = kosaraju(V, adj, radj)
    print(format_partition(sccs))

if __name__ == "__main__":
    sys.setrecursionlimit(1_000_000)
    main()
