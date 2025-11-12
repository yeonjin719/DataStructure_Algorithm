int OPT_memoization_iterative(int n, int w[], int P[]) {
  int M[];
  M[0] = 0;
  for (i = 1; i <= n; i++)
    M[i] = max(w[i] + M[P[i]], M[i - 1]);
}