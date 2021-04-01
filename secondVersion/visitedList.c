#include "header.h"

vList_ptr makeVisitedList()
{
	vList_ptr head;

	head = (vList_ptr)malloc(sizeof(struct visitedList));

	if (head == NULL)
	{
		printf("Memory for visited list not allocated.\n");
		return NULL;
	}
	else
	{
		head->next = NULL;
		return head;
	}
}
int addToVL(vList_ptr head, char* key)
{
	vList_ptr newElement;

	newElement = (vList_ptr)malloc(sizeof(struct visitedList));
	strcpy(newElement->name, key);
	newElement->next = NULL;

	if (head->next == NULL)
	{
		head->next = newElement;
	}
	else
	{
		vList_ptr temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newElement;
		newElement->next = NULL;
	}

	return  0;
}

bool existsInVL(vList_ptr head, char* key)
{
	vList_ptr temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->name, key) == 0)
		{
			return true;
		}
		else
		{
			temp = temp->next;
		}
	}

	if (temp == NULL)
	{
		return false;
	}
}