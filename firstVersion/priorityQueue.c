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

int addToPQ(pq_ptr head, int index, int value)
{
	// provjeravanje situacije ako u pq-u vec postoji element s tim indeksom, onda cemo samo azurirat trenutni value u priority queue-u

	if (checkPQ(head, index))
	{
		pq_ptr temp = head->next;

		while (temp->name != index)
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
		pq_ptr new;
		new = (pq_ptr)malloc(sizeof(struct pqNode));
		new->name = index;
		new->value = value;

		// dodaj na pocetak ako je prazno

		if (head->next == NULL)
		{
			new->next = head->next;
			head->next = new;
		}
		else
		{
			// nadi gdje ces dodati i ubaci

			pq_ptr temp = head;

			while (temp->next != NULL)
			{
				if (temp->next->value >= new->value)
				{
					new->next = temp->next;
					temp->next = new;

					break;
				}
				else
				{
					temp = temp->next;
				}
			}

			if (temp->next == NULL)
			{
				new->next = temp->next;
				temp->next = new;
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

int removeFromPQ(pq_ptr head)
{
	pq_ptr temp;
	int toBeReturned;

	temp = head->next;
	head->next = temp->next;
	toBeReturned = temp->name;
	free(temp);

	return toBeReturned;
}

bool checkPQ(pq_ptr head, int key)
{
	pq_ptr temp = head->next;

	while (temp != NULL)
	{
		if (temp->name == key)
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