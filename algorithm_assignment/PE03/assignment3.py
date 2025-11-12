# 6 11
# 1 2 50
# 1 3 45
# 1 4 10
# 2 3 10
# 2 4 15
# 3 5 30
# 4 1 20
# 4 5 15
# 5 2 20
# 5 3 15
# 5 6 3

import math
from heapq import heappop, heappush
from pathlib import Path
from typing import Iterable, List, Optional, Tuple


def read_graph(path: str) -> Tuple[int, List[List[Tuple[int, int]]]]:
    with open(path, "r", encoding="utf-8") as f:
        V, E = map(int, f.readline().split())
        adj = [[] for _ in range(V + 1)]  # 1-based indexing
        for _ in range(E):
            u, v, w = map(int, f.readline().split())
            adj[u].append((v, w))

    return V, adj


def dijkstra(
    V: int, adj: List[List[Tuple[int, int]]], start: int
) -> Tuple[List[float], List[int]]:
    """Compute shortest distances and predecessors from start."""

    dist = [math.inf] * (V + 1)
    parent = [-1] * (V + 1)
    dist[start] = 0

    pq: List[Tuple[float, int]] = [(0, start)]
    while pq:
        d, u = heappop(pq)
        if d > dist[u]:
            continue
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                parent[v] = u
                heappush(pq, (nd, v))

    return dist, parent


def rebuild_path(parent: List[int], start: int, end: int) -> List[int]:
    if start == end:
        return [start]

    path = [end]
    cur = end
    while cur != start and cur != -1:
        cur = parent[cur]
        if cur == -1:
            return []
        path.append(cur)

    path.reverse()
    return path


def main(starts: Optional[Iterable[int]] = None) -> None:
    graph_path = Path(__file__).with_name("assignment3.txt")
    V, adj = read_graph(str(graph_path))

    if starts is None:
        starts = range(1, V + 1)

    for start in starts:
        if not 1 <= start <= V:
            print(f"start {start}: invalid (valid range 1..{V})")
            continue

        dist, parent = dijkstra(V, adj, start)
        print(f"=== start {start} ===")
        for v in range(1, V + 1):
            if math.isinf(dist[v]):
                print(f"{start} -> {v}: unreachable")
                continue

            path = rebuild_path(parent, start, v)
            path_repr = " -> ".join(map(str, path)) if path else "(path unavailable)"
            print(f"{start} -> {v}: cost {dist[v]}, path {path_repr}")

        print()


if __name__ == "__main__":
    main()
