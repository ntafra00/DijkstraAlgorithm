#include "header.h"

pq_ptr makePQ()
{
	pq_ptr head;

	head = (pq_ptr)malloc(sizeof(struct pqNode));

	if (head == NULL)
	{
		printf("Memory for priority queue not allocated!\n");
		return NULL;
	}
	else
	{
		head->next = NULL;
		return head;
	}
}

int addToPQ(pq_ptr head, char* name, int value)
{
	// provjeravanje situacije ako u pq-u vec postoji element s tim indeksom, onda cemo samo azurirat trenutni value u priority queue-u

	if (checkPQ(head, name))
	{
		pq_ptr temp = head->next;

		while (strcmp(temp->name, name) != 0)
		{
			temp = temp->next;
		}

		if (temp->value > value)
		{
			temp->value = value;
		}
	}
	else
	{
		pq_ptr newElement;
		newElement = (pq_ptr)malloc(sizeof(struct pqNode));
		strcpy(newElement->name, name);
		newElement->value = value;

		if (head->next == NULL)
		{
			newElement->next = head->next;
			head->next = newElement;
		}
		else
		{
			pq_ptr temp = head;

			while (temp->next != NULL)
			{
				if (temp->next->value >= newElement->value)
				{
					newElement->next = temp->next;
					temp->next = newElement;

					break;
				}
				else
				{
					temp = temp->next;
				}
			}

			if (temp->next == NULL)
			{
				newElement->next = temp->next;
				temp->next = newElement;
			}
		}
	}

	return 0;
}

bool isEmpty(pq_ptr head)
{
	if (head->next == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char* removeFromPQ(pq_ptr head)
{
	pq_ptr temp;
	char toBeReturned[MAX];

	temp = head->next;
	head->next = temp->next;
	strcpy(toBeReturned, temp->name);
	free(temp);

	return toBeReturned;
}

bool checkPQ(pq_ptr head, char* key)
{
	pq_ptr temp = head->next;

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