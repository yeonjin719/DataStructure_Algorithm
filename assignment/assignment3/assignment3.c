#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
  char name[20];
  struct Node *parent;
  struct Node *first_child;
  struct Node *next_sibling;
} Node;

Node *create_node(const char *name)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  strcpy(new_node->name, name);
  new_node->parent = NULL;
  new_node->first_child = NULL;
  new_node->next_sibling = NULL;
  return new_node;
}

Node *find_node(Node *root, const char *name)
{
  if (root == NULL)
    return NULL;
  if (strcmp(root->name, name) == 0)
    return root;

  Node *found = find_node(root->first_child, name);
  if (found != NULL)
    return found;

  return find_node(root->next_sibling, name);
}

void add_child(Node *parent, Node *child)
{
  child->parent = parent;
  if (parent->first_child == NULL)
  {
    parent->first_child = child;
  }
  else
  {
    Node *sibling = parent->first_child;
    while (sibling->next_sibling != NULL)
    {
      sibling = sibling->next_sibling;
    }
    sibling->next_sibling = child;
  }
}

void print_descendants(Node *node)
{
  if (node == NULL)
    return;

  Node *child = node->first_child;
  while (child != NULL)
  {
    printf("%s ", child->name); // 자식 이름 출력
    print_descendants(child);   // 자식의 자식들도 재귀적으로 출력
    child = child->next_sibling;
  }
}

void answer1(Node *nodes[], int count)
{
  printf("[01] 조선의 왕을 순서대로 출력하시오: \n");
  for (int i = 0; i < count; i++)
  {
    Node *cur = nodes[i];
    printf("%s ", cur->name);
    Node *child = cur->first_child;
  }
  printf("\n\n");
}

void answer2(Node *nodes[], int count)
{
  printf("[02] 조선의 왕을 역순으로 출력하시오: \n");
  for (int i = count - 1; i >= 0; i--)
  {
    printf("%s ", nodes[i]->name);
  }
  printf("\n\n");
}

void answer3(int num)
{
  printf("[03] 조선의 왕은 모두 몇 명인가? \n");
  printf("%d명", num);
  printf("\n\n");
}

void answer4(Node *nodes[], int count)
{
  printf("[04] 조선의 왕 중에서 인조의 후손은 누구누구인가?\n");

  for (int i = 0; i < count; i++)
  {
    Node *cur = nodes[i];
    if (strcmp(cur->name, "인조") == 0)
    {
      print_descendants(cur);
      printf("\n\n");
      return;
    }
  }
}

void answer5(Node *nodes[], int count)
{
  printf("[05] 직계 후손이 왕이 되지 못한 왕은 누구누구인가?\n");

  for (int i = 0; i < count; i++)
  {
    Node *cur = nodes[i];
    Node *child = cur->first_child;
    int has_king_child = 0;

    while (child != NULL)
    {
      for (int j = 0; j < count; j++)
      {
        if (nodes[j] == child)
        {
          has_king_child = 1; // 왕이 된 자식 발견
          break;
        }
      }
      if (has_king_child)
        break;
      child = child->next_sibling;
    }

    if (!has_king_child)
    {
      printf("%s ", cur->name);
    }
  }
  printf("\n\n");
}

void answer6(Node *nodes[], int count)
{
  printf("[06] 직계 후손이 왕이 된 수가 가장 많은 왕은 누구인가?\n");

  int max_count = -1;
  char king_with_max_children[20] = "";

  for (int i = 0; i < count; i++)
  {
    Node *cur = nodes[i];
    Node *child = cur->first_child;
    int king_children = 0;

    while (child != NULL)
    {
      for (int j = 0; j < count; j++)
      {
        if (nodes[j] == child)
        {
          king_children++;
          break;
        }
      }
      child = child->next_sibling;
    }

    if (king_children > max_count)
    {
      max_count = king_children;
      strcpy(king_with_max_children, cur->name);
    }
  }

  printf("%s (%d명)\n\n", king_with_max_children, max_count);
}

void answer7(Node *nodes[], int count)
{
  printf("[07] 정종의 형제로 조선의 왕이 된 사람은 누구인가?\n");

  Node *jeongjong = NULL;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(nodes[i]->name, "정종") == 0)
    {
      jeongjong = nodes[i];
      break;
    }
  }

  if (jeongjong == NULL || jeongjong->parent == NULL)
  {
    printf("정종이나 그의 부모를 찾을 수 없습니다.\n");
    return;
  }

  Node *sibling = jeongjong->parent->first_child;
  while (sibling != NULL)
  {
    if (sibling != jeongjong)
    { // 본인 제외
      for (int i = 0; i < count; i++)
      {
        if (nodes[i] == sibling)
        {
          printf("%s ", sibling->name);
          break;
        }
      }
    }
    sibling = sibling->next_sibling;
  }
  printf("\n\n");
}

void answer8(Node *nodes[], int count)
{
  printf("[08] 순종의 직계 선조를 모두 출력하시오:\n");

  Node *sunjong = NULL;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(nodes[i]->name, "순종") == 0)
    {
      sunjong = nodes[i];
      break;
    }
  }

  if (sunjong == NULL)
  {
    printf("순종을 찾을 수 없습니다.\n");
    return;
  }

  Node *cur = sunjong->parent;
  while (cur != NULL)
  {
    printf("%s ", cur->name);
    cur = cur->parent;
  }
  printf("\n\n");
}

void answer9(Node *nodes[], int count)
{
  printf("[09] 직계 후손이 2명 이상 왕이 된 왕은 몇 명인가?\n");

  int total = 0;

  for (int i = 0; i < count; i++)
  {
    Node *cur = nodes[i];
    Node *child = cur->first_child;
    int king_children = 0;

    while (child != NULL)
    {
      for (int j = 0; j < count; j++)
      {
        if (nodes[j] == child)
        {
          king_children++;
          break;
        }
      }
      child = child->next_sibling;
    }

    if (king_children >= 2)
    {
      total++;
    }
  }

  printf("%d명", total);
  printf("\n\n");
}

int find_generation(Node *ancestor, Node *descendant, int generation)
{
  if (ancestor == NULL)
    return -1;

  Node *child = ancestor->first_child;
  while (child != NULL)
  {
    if (child == descendant)
      return generation + 1;
    int result = find_generation(child, descendant, generation + 1);
    if (result != -1)
      return result;
    child = child->next_sibling;
  }
  return -1;
}

void answer10(Node *nodes[], int count)
{
  printf("[10] 예종은 태종의 몇 대 후손인가?:\n");

  Node *taejong = NULL;
  Node *yejong = NULL;

  for (int i = 0; i < count; i++)
  {
    if (strcmp(nodes[i]->name, "태종") == 0)
    {
      taejong = nodes[i];
    }
    if (strcmp(nodes[i]->name, "예종") == 0)
    {
      yejong = nodes[i];
    }
  }

  if (taejong == NULL || yejong == NULL)
  {
    printf("태종 또는 예종을 찾을 수 없습니다.\n");
    return;
  }

  int generation = find_generation(taejong, yejong, 0);
  printf("%d대 후손입니다.", generation);
  printf("\n\n");
}

int main()
{
  FILE *file = fopen("조선왕조.txt", "r");
  if (file == NULL)
  {
    printf("파일을 열 수 없습니다.\n");
    return 1;
  }

  char buffer1[20], buffer2[20];
  Node *root = NULL;
  Node *node_list[100]; // 등장 순서대로 저장할 배열
  int node_count = 0;

  // 첫 줄: 루트 노드
  if (fscanf(file, "%s", buffer1) == 1)
  {
    root = create_node(buffer1);
    node_list[node_count++] = root; // 첫 번째에 저장
  }
  else
  {
    printf("파일이 비어있거나 오류가 있습니다.\n");
    fclose(file);
    return 1;
  }

  // 이후 줄: 아들-아버지 관계
  while (fscanf(file, "%s %s", buffer1, buffer2) == 2)
  {
    Node *father = find_node(root, buffer2);
    if (father == NULL)
    {
      printf("부모 %s를 찾을 수 없습니다.\n", buffer2);
      continue;
    }
    Node *son = create_node(buffer1);
    add_child(father, son);

    node_list[node_count++] = son;
  }

  fclose(file);
  printf("== 질문에 대한 답변 ==\n\n");

  answer1(node_list, node_count);
  answer2(node_list, node_count);
  answer3(node_count);
  answer4(node_list, node_count);
  answer5(node_list, node_count);
  answer6(node_list, node_count);
  answer7(node_list, node_count);
  answer8(node_list, node_count);
  answer9(node_list, node_count);
  answer10(node_list, node_count);
  return 0;
}
