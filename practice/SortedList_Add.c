#include <stdio.h>
#include <stdlib.h>

int n;
int *arr;
arr = {3, 5, 8, 9};
void add(int num)
{
  int pos = n;
  for (int i = n - 1; arr[i] > num; i--)
  {
    arr[i + 1] = arr[i];
    pos--;
  }
  arr[pos] = num;
  n++;
};

int main()
{
  add(4);
};