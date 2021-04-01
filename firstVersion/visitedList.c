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

int addToVL(vList_ptr head, int key)
{
	vList_ptr new;

	new = (vList_ptr)malloc(sizeof(struct visitedList));
	new->index = key;
	new->next = NULL;

	if (head->next == NULL)
	{
		head->next = new;
	}
	else
	{
		vList_ptr temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = new;
		new->next = NULL;
	}

	return  0;
}

bool existsInVL(vList_ptr head, int key)
{
	vList_ptr temp = head->next;

	while (temp != NULL)
	{
		if (temp->index == key)
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