void AS_Push(ArrayStack* Stack, ElementType Data)
{
  if (Stack -> Top == Stack->Capacity-1)
  {
    int NewCapacity = Stack->Capacity+(Stack->Capacity*30)/100;
    Stack->Nodes = (Node*)realloc(Stack->Nodes, sizeof(Node)*NewCapacity);
    Stack->Capacity = NewCapacity;
  }
  Stack->Top++;
  Stack->Nodes[Stack->Top].Data = Data;
}
