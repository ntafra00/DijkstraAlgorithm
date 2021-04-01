#include "header.h"

int freeMemoryOfThePath(path_ptr givenElement)
{
	path_ptr current = givenElement->next;
	path_ptr temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}

	givenElement->next = NULL;

	return 0;
}

int freePQ(pq_ptr head)
{
	free(head);

	return 0;
}

int freeVL(vList_ptr head)
{
	vList_ptr temp = head;

	while (temp != NULL)
	{
		head = temp;
		temp = temp->next;
		free(head);
	}

	return 0;
}

int freeDL(dList_ptr head)
{
	dList_ptr temp = head;

	while (temp != NULL)
	{
		head = temp;
		temp = temp->next;
		free(head);
	}

	return 0;
}

int freePath(path_ptr* paths, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		path_ptr temp = paths[i];

		while (temp != NULL)
		{
			paths[i] = temp;
			temp = temp->next;
			free(paths[i]);
		}
	}

	return 0;
}

int freeAdjList(graph_ptr* adjList, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		graph_ptr temp = adjList[i];

		while (temp != NULL)
		{
			adjList[i] = temp;
			temp = temp->next;
			free(adjList[i]);
		}
	}

	return 0;
}