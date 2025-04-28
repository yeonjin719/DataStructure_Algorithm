void SLL_DestroyAllNodes(Node** List)
{
    Node *Current = *List;
    Node *Next = NULL;

    while (Current != NULL)
    {
        Next = Current->NextNode;  
        SLL_RemoveNode(List, Current);
        SLL_DestroyNode(Current);     
        Current = Next;             
    }
    *List = NULL;
}
