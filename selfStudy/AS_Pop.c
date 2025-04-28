ElementType AS_Pop(ArrayStack* Stack)
{
  int Position = --(Stack->Top);
  if (Stack->Top < (Stack->Capacity*70)/100)
  {
    int NewCapacity= Stack->Capacity-(Stack->Capacity*20)/100;
    if (NewCapacity < 1)
    {
      NewCapacity = 1;
    }
    Stack->Nodes = (Node*)realloc(Stack->Nodes, sizeof(Node)*NewCapacity);
    Stack->Capacity = NewCapacity;
  }
  return Stack->Nodes[Position].Data;
}
