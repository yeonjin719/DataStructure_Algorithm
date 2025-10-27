#include <iostream>

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void print(const int A[], int size)
{
	for (int i = 0; i < size; ++i) {
		std::cout << A[i] << ' ';
	}
	std::cout << '\n';
}

int partition(int A[], int s, int e)
{
	int pivot, left, right;
  left = s+1;
  right = e;
  pivot = A[s];
  while (left <= right) {
    while ((A[right]>= pivot) && (left <= right)) {
      right--;
    }
    while ((A[left] <= pivot) && (left <= right)) {
      left++;
    }
    if (left <= right) {
      swap(A[left], A[right]);
    }
  }
  swap(A[s], A[right]);
  return right;
}

void quick_sort(int A[], int s, int e, int size, int cnt)
{
	if (s >= e)
		return;
  printf("Step %d: \n", cnt++);
	int mid = partition(A, s, e);
	quick_sort(A, s, mid - 1, size, cnt);
	print(A, size);
	quick_sort(A, mid + 1, e, size, cnt);
}

int main()
{
	int arr[] = {40, 30, 20, 80, 50, 10, 70, 60};
	const int size = sizeof(arr) / sizeof(arr[0]);
  int cnt = 1;
	quick_sort(arr, 0, size - 1, size, cnt);

	return 0;
}
