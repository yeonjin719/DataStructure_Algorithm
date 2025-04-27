#define SIZE 100
int count = 0;
int arr[SIZE];

int binary_search(int s, int e, int key)
{
  if (s == e)
    return (arr[s] == key) ? s : -1;
  int mid = (s + e) / 2;
  if (key == arr[mid])
    return mid;
  else if (arr[mid] > key)
    return binary_search(s, mid - 1, key);
  else
    return binary_search(mid + 1, e, key);
}