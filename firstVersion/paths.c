#include "header.h"



int makePath(path_ptr* array, int sizeOfArray)
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		path_ptr beginning;

		beginning = (path_ptr)malloc(sizeof(struct pathNode));

		if (beginning == NULL)
		{
			printf("Memory for %d. element of array not allocated!\n");
			return -1;
		}
		else
		{
			beginning->next = NULL;
			array[i] = beginning;
		}
	}
	return 0;
}

int updatePath(path_ptr elementForUpdate, int value)
{
	path_ptr temp = elementForUpdate;
	path_ptr new;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	new = (path_ptr)malloc(sizeof(struct pathNode));

	if (new == NULL)
	{
		printf("Memory for new element of the path not allocated\n");
		return -1;
	}

	new->station = value;
	new->next = NULL;
	temp->next = new;

	return 0;
}

int reconstructPath(path_ptr givenElement, path_ptr elementForReconstruction)
{
	path_ptr temp = givenElement->next;

	if (elementForReconstruction->next != NULL)
	{
		freeMemoryOfThePath(elementForReconstruction);
	}

	while (temp != NULL)
	{
		updatePath(elementForReconstruction, temp->station);
		temp = temp->next;
	}

	return 0;
}

int changeOneWhereItAllBegins(path_ptr* paths, int numberOfVertices, int keyValue)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (paths[i]->name == keyValue)
		{
			path_ptr startPoint;
			startPoint = (path_ptr)malloc(sizeof(struct pathNode));

			if (startPoint == NULL)
			{
				printf("Memory not allocated for the first station of the path.\n");
				return -1;
			}

			startPoint->station = keyValue;
			startPoint->next = NULL;
			paths[i]->next = startPoint;
		}
	}

	return 0;
}

path_ptr returnPath(path_ptr * paths, int numberOfVertices, int keyValue)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (paths[i]->name == keyValue)
		{
			return paths[i];
		}
	}
}

int printParticularPath(path_ptr* paths, int numberOfVertices, int startPoint, int endPoint)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (paths[i]->name == endPoint)
		{

			if (paths[i]->next == NULL)
			{
				printf("\n\nPath from %d to %d is: ", startPoint, endPoint);
				printf("particular path doesn't exist\n");
			}
			else if (paths[i]->next->next == NULL)
			{
				printf("\n\nPath from %d to %d is: ", startPoint, endPoint);
				printf("Why do you even ask? You don't have to move at all!\n");
			}
			else
			{
				printf("\n\nPath from %d to %d is: ", startPoint, endPoint);

				path_ptr temp = paths[i]->next;

				while (temp->next != NULL)
				{
					printf("%d -> ", temp->station);
					temp = temp->next;
				}

				printf("%d\n", temp->station);
			}
		}
	}

	return 0;
}

int printAllPaths(path_ptr* paths, int numberOfVertices, int startPoint)
{
	printf("\nPaths: \n\n");

	for (int i = 0; i < numberOfVertices; i++)
	{
		if (paths[i]->next == NULL)
		{
			printf("Path from %d to %d is : ", startPoint, paths[i]->name);
			printf("Particular path doesn't exist.\n");


		}
		else if (paths[i]->next->next == NULL)
		{
			printf("Path from %d to %d is : ", startPoint, paths[i]->name);
			printf("Why do you even ask? You don't have to move at all!\n");
		}
		else
		{
			printf("Path from %d to %d is: ", startPoint, paths[i]->name);

			path_ptr temp = paths[i]->next;

			while (temp->next != NULL)
			{
				printf("%d -> ", temp->station);
				temp = temp->next;
			}

			printf("%d\n", temp->station);
		}
	}

	return 0;
}