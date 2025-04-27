#define SIZE 100
int count = 0;
int arr[SIZE];
int linear_search(int x)
{
  for (int i = 0; i < count; i++)
    if (arr[i] == x)
      return i;
  return -1;
}
