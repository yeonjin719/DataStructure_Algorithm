void SLL_InsertBefore(Node** Head, Node* Current, Node* NewHead)
{
	if (*Head == Current)
	{
		NewHead->NextNode = (*Head);
		*Head = NewHead;
	}
	else
	{
		NewHead->NextNode = Current;
		Node* Target = *Head;
		while (Target != NULL && Target->NextNode != Current)
		{
			Target = Target->NextNode;
		}
		if (Target != NULL)
		{
			Target->NextNode = NewHead;
	}
}
