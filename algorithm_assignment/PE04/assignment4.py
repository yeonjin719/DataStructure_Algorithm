from __future__ import annotations
from dataclasses import dataclass
import heapq
import math
from typing import Dict, Optional, Tuple

@dataclass(order=True)
class Node:
    weight: float
    _seq: int                # 힙 타이브레이커(동일 가중치 대비)
    left: Optional['Node']=None
    right: Optional['Node']=None
    symbol: Optional[str]=None  # 리프일 때만 채움

def build_huffman(freq: Dict[str, float]) -> Dict[str, str]:
    """
    freq: 문자 -> 빈도(혹은 확률). 합이 1이 아니어도 됨(내부에서 정규화).
    return: 문자 -> 허프만 코드(문자열)
    """
    # 0이거나 음수 빈도 제거 + 정규화
    items = [(s, f) for s, f in freq.items() if f > 0]
    total = sum(f for _, f in items)
    if total == 0:
        raise ValueError("모든 빈도가 0입니다.")
    items = [(s, f / total) for s, f in items]

    # 단일 심볼 예외 처리
    if len(items) == 1:
        s, _ = items[0]
        return {s: "0"}   # 한 글자만 있으면 0 한 비트로 할당

    # 초기 힙 구성
    heap: list[Node] = []
    seq = 0
    for s, p in items:
        heap.append(Node(p, seq, None, None, s))
        seq += 1
    heapq.heapify(heap)

    # 허프만 트리 만들기
    while len(heap) > 1:
        a = heapq.heappop(heap)
        b = heapq.heappop(heap)
        merged = Node(a.weight + b.weight, seq, a, b, None)
        seq += 1
        heapq.heappush(heap, merged)

    root = heap[0]

    # 트리 순회하여 코드 생성
    codes: Dict[str, str] = {}
    def dfs(n: Node, path: str):
        if n.symbol is not None:
            codes[n.symbol] = path or "0"   # 안전장치
            return
        if n.left:  dfs(n.left,  path + "0")
        if n.right: dfs(n.right, path + "1")
    dfs(root, "")
    return codes

def encode(text: str, codes: Dict[str, str]) -> str:
    try:
        return "".join(codes[ch] for ch in text)
    except KeyError as e:
        raise KeyError(f"코드가 없는 문자 발견: {e.args[0]!r}")

def decode(bits: str, codes: Dict[str, str]) -> str:
    rev = {v: k for k, v in codes.items()}
    # 트라이 없이 선형 스캔(코드가 접두어-무충돌이므로 가능)
    out = []
    cur = ""
    for b in bits:
        cur += b
        if cur in rev:
            out.append(rev[cur])
            cur = ""
    if cur:
        raise ValueError("비트열이 잘린 것 같습니다(완전한 코드어로 끝나지 않음).")
    return "".join(out)

def avg_code_length(freq: Dict[str, float], codes: Dict[str, str]) -> float:
    total = sum(max(f, 0) for f in freq.values())
    if total == 0:
        return 0.0
    return sum((freq[s]/total) * len(codes[s]) for s in codes)

def entropy(freq: Dict[str, float]) -> float:
    total = sum(max(f, 0) for f in freq.values())
    if total == 0:
        return 0.0
    H = 0.0
    for f in freq.values():
        if f <= 0: 
            continue
        p = f / total
        H -= p * math.log2(p)
    return H

if __name__ == "__main__":
    freq = {
        'A': 0.08833, 'B': 0.01267, 'C': 0.02081, 'D': 0.04376, 'E': 0.14878,
        'F': 0.02455, 'G': 0.01521, 'H': 0.05831, 'I': 0.05644, 'J': 0.00080,
        'K': 0.00867, 'L': 0.04124, 'M': 0.02361,
        'N': 0.06498, 'O': 0.07245, 'P': 0.02575, 'Q': 0.00080, 'R': 0.06872,
        'S': 0.05537, 'T': 0.09351, 'U': 0.02762, 'V': 0.01160, 'W': 0.01868,
        'X': 0.00146, 'Y': 0.01521, 'Z': 0.00053,
    }
    codes = build_huffman(freq)
    print("Huffman codes (일부):", {k: codes[k] for k in sorted(codes)[:8]})
    print("평균 코드 길이:", round(avg_code_length(freq, codes), 4), "bits/symbol")
    print("엔트로피(하한):", round(entropy(freq), 4), "bits/symbol")

    msg = "HELLOWORLD"
    bits = encode(msg, codes)
    rec = decode(bits, codes)
    print("원문:", msg)
    print("인코딩:", bits)
    print("디코딩:", rec)