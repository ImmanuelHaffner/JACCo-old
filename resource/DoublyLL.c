DoublyLL DoublyLL_New()
{
  DoublyLL list = malloc( sizeof( *list ) );
  list->next = list;
  list->prev = list;
  list->data = 0;

  return list;
}

bool DoublyLL_IsEmpty( DoublyLL list )
{
  // TODO implement
}

void DoublyLL_PushFirst( DoublyLL list, int data )
{
  // Allocate memory on the heap
  DoublyLL elem = malloc( sizeof( *elem ) );

  // Initialize data
  elem->data = data;

  // Insert new element at the beginning of the list
  elem->next = list->next;
  list->next = elem;
  elem->next->prev = elem;
  elem->prev = list;
}

void DoublyLL_PushLast( DoublyLL list, int data )
{
  // TODO implement
}

int DoublyLL_PopFirst( DoublyLL list )
{
  // Save reference to the element we want to delete
  DoublyLL elem = list->next;

  // Remove the element from the list
  elem->next->prev = list;
  list->next = elem->next;

  // Extract the data from the element
  int data = elem->data;

  // Free the element from the heap
  //
  // !IMPORTANT!
  // We MUST free the memory, else the memory cannot be used anymore until the
  // program is closed. This is called a MEMORY LEAK.
  free( elem );

  return data;
}

int DoublyLL_PopLast( DoublyLL list )
{
  // TODO implement
}
