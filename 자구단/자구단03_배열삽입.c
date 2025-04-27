#define SIZE 100
int count = 0;
int arr[SIZE];

int insert_by_value(int arr[], int x)
{
  // 0. 예외 처리
  // 1. x를 삽입할 위치를 결정
  int i, j;
  for (i = 0; i < count; i++)
  {
    if (arr[i] > x)
      break;
  }
  // 2. 삽입할 위치의 원소를 옮겨서 공간을 확보(->)
  for (j = count - 1; j >= i; j--)
    arr[j + 1] = arr[j];
  // 3. 원소를 삽입
  arr[i] = x;
  // 4. 배열의 크기 (count)를 증가
  count++;
  return arr;
}