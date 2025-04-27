#define SIZE 100
int count = 0;
int arr[SIZE];
int i, j;

int delete(int arr[], int x)
{
  // 0. 예외적인 경우
  // 1. 삭제할 원소 (x)를 배열 (arr)에서 찾음
  for (i = 0; i < count; i++)
    if (arr[i] == x)
      break;
  if (i == count)
    return arr;
  // 2. 삭제할 원소 뒤에 있는 원소들을 앞으로 이동 (ß)
  for (j = i; j < count - 1; j++)
    arr[j] = arr[j + 1];
  // 3. 배열의 크기 (count)를 감소
  count--;
  return arr;
}