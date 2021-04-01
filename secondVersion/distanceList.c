#include "header.h"

dList_ptr makeDistanceList()
{
	dList_ptr head = NULL;

	head = (dList_ptr)malloc(sizeof(struct distanceList));

	if (head == NULL)
	{
		printf("Memory for the head of the distance list not allocated.\n");
		return NULL;
	}

	head->next = NULL;

	return head;
}

int addToDL(dList_ptr headOfDL, char * elementName)
{
	dList_ptr newElement;
	newElement = (dList_ptr)malloc(sizeof(struct distanceList));

	if (newElement == NULL)
	{
		printf("Memory for element of the distance list not allocated.\n");
		return -1;
	}

	//ubacivanje u distance listu

	if (headOfDL->next == NULL)
	{
		newElement->next = headOfDL->next;
		strcpy(newElement->name, elementName);
		headOfDL->next = newElement;
	}
	else
	{
		dList_ptr temp = headOfDL->next;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		newElement->next = temp->next;
		strcpy(newElement->name, elementName);
		temp->next = newElement;
	}

	return 0;
}

int printDistances(dList_ptr temp, char* key)
{
	printf("Distances: \n\n");

	while (temp != NULL)
	{
		printf("Distance from %s to %s is: %d\n", key, temp->name, temp->distance);
		temp = temp->next;
	}

	return 0;
}

int putAtInfinityOrZero(dList_ptr temp, char* keyValue)
{
	while (temp != NULL)
	{
		if (strcmp(temp->name, keyValue) == 0)
		{
			temp->distance = 0;
		}
		else
		{
			temp->distance = INFINITY;
		}

		temp = temp->next;
	}

	return 0;
}

dList_ptr findAndReturn(dList_ptr temp, char* keyValue)
{
	while (temp != NULL)
	{
		if (strcmp(temp->name, keyValue) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}
}

int returnDistance(dList_ptr temp, char* key)
{
	while (temp != NULL)
	{
		if (strcmp(temp->name, key) == 0)
		{
			return temp->distance;
		}
		temp = temp->next;
	}
}
