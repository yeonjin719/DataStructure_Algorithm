from collections import defaultdict
from typing import Dict, List, Hashable, Iterable, Set

Graph = Dict[Hashable, Iterable[Hashable]]

def load_edge_list(path: str, directed: bool = False) -> Graph:
    g: Graph = defaultdict(list)
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            u_str, v_str = line.split()
            u, v = int(u_str), int(v_str)
            g[u].append(v)
            if not directed:
                g[v].append(u)

    # 이웃 정렬(선택): 탐색 순서를 일정하게 유지하고 싶을 때 유용
    for k in g:
        g[k] = sorted(set(g[k]))
    return dict(g)

# 1) 재귀 DFS (슬라이드 왼쪽)
def dfs_recursive(graph: Graph, u) -> List:
    visited: Set = set()
    order: List = []

    def rec(x):
        visited.add(x)
        order.append(x)
        for w in graph.get(x, []):
            if w not in visited:
                rec(w)

    rec(u)
    return order


# 2) 백트래킹형 반복 DFS (슬라이드 가운데)
#  - "갈 수 있으면 현재 정점을 push하고 다음 정점으로 이동,
#    갈 수 없으면 pop해서 되돌아감" 의 흐름을 그대로 살림.
def dfs_iter_backtrack(graph, start):
    visited = set()
    order = []
    stack = []

    u = start
    while True:
        if u not in visited:        # 도착 시점에서 방문 처리
            visited.add(u)
            order.append(u)

        # u의 방문하지 않은 이웃 찾기
        nxt = next((v for v in graph.get(u, []) if v not in visited), None)

        if nxt is not None:
            stack.append(u)         # 현재 정점 기억
            u = nxt                 # 다음 정점으로 이동
        else:
            if not stack:           # 더 이상 되돌아갈 곳 없으면 종료
                break
            u = stack.pop()         # 되돌아가기
    return order


# 3) 전형적인 스택 기반 DFS (슬라이드 오른쪽)
#  - 스택에서 pop → 이미 방문이면 continue
#  - 아니면 방문 처리 후, 이웃을 push
def dfs_iter_stack(graph, s):
    visited = set()
    order = []
    stack = [s]

    while stack:
        u = stack.pop()
        if u in visited:
            continue
        
        visited.add(u)
        order.append(u)
        for v in sorted(graph.get(u, []), reverse=True):
            if v not in visited:
                stack.append(v)
    return order
# 사용 예시
if __name__ == "__main__":
    graph = load_edge_list("searchgraph.txt", directed=False)
    print(f"노드 수: {len(graph)}")
    # 실제 전체 노드 수는 고립 노드가 없다는 가정 하에 len(graph)와 동일
    # 몇 개 이웃만 확인
    sample_keys = list(graph.keys())[:5]
    for k in sample_keys:
        print(k, "->", graph[k])

# 예: 시작 정점을 48로
print('\n\n')
print('재귀 dfs: \n',dfs_recursive(graph, 1))
print('\n')
print('백트래킹형 반복 dfs: \n',dfs_iter_backtrack(graph, 1))
print('\n')
print('스택 기반 dfs: \n',dfs_iter_stack(graph, 1))

