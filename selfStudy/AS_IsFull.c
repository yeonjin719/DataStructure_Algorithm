int AS_IsFull(ArrayStack* Stack)
{
	return (Stack->Top == Stack->Capacity-1);
}
