#include "header.h"

int makeAdjacencyList(graph_ptr* adj_list, int numberOfVer)
{
	for (int i = 0; i < numberOfVer; i++)
	{
		adj_list[i] = (graph_ptr)malloc(sizeof(struct graphNode));

		if (adj_list[i] == NULL)
		{
			printf("Problem with memory allocation.\n");
			return -1;
		}

		adj_list[i]->edge = 0;
		adj_list[i]->next = NULL;
	}

	return 0;
}

int readGraph(graph_ptr* adj_list, int numberOfVer, dList_ptr head, path_ptr* paths)
{
	char vertexName[MAX];
	int numberOfNeighbours;
	char neighbourName[MAX];
	int neighbourEdge;

	for (int i = 0; i < numberOfVer; i++)
	{
		printf("\n");

		fflush(stdin);
		printf("Enter the name of the %d. vertex: ", i + 1);
		scanf(" %[^\n]s", vertexName);

		while (existsInTheAdjList(adj_list, vertexName, numberOfVer))
		{
			printf("\nSomething went wrong...\n");
			printf("Vertex with than name already exists in the adjacency list.\n");
			printf("Please be careful and try again.\n\n");

			printf("Enter the name of the %d. vertex: ", i + 1);
			scanf(" %[^\n]s", vertexName);
		}
		
		strcpy(adj_list[i]->name, vertexName);
		strcpy(paths[i]->name, vertexName);
		addToDL(head, vertexName);

		printf("Enter number of neighbours for the vertex named %s: ", adj_list[i]->name);
		scanf(" %d", &numberOfNeighbours);

		for (int j = 0; j < numberOfNeighbours; j++)
		{
			printf("Enter %d. neighbour: ", j + 1);
			scanf(" %[^\n]s", neighbourName);

			printf("Enter a non-negative edge weight of %d. neighbour: ", j + 1);
			scanf(" %d", &neighbourEdge);

			graph_ptr new;
			new = (graph_ptr)malloc(sizeof(struct graphNode));

			if (new == NULL)
			{
				printf("Memory not allocated for current neighbour.\n");
			}
			else
			{
				if (neighbourEdge < 0)
				{
					printf("\nYou were told not to enter negative edge weigth\n");
					printf("Because of this, distance from the %s to %s will be put at infinity.\n\n", adj_list[i]->name, neighbourName);
					new->edge = INFINITY;
				}
				else
				{
					new->edge = neighbourEdge;
				}

				strcpy(new->name,neighbourName);

				new->next = NULL;

				if (adj_list[i]->next == NULL)
				{
					adj_list[i]->next = new;
				}
				else
				{
					graph_ptr temp = adj_list[i]->next;

					while (temp->next != NULL)
					{
						temp = temp->next;
					}

					new->next = temp->next;
					temp->next = new;
				}
			}
		}

		printf("\n\n");
	}

	return 0;
}

int printGraph(graph_ptr* adj_list, int numberofvertices)
{
	system("cls");
	printf("Graph looks like this: \n\n");
	printf("First number represents name of the vertex and the second one represents edge weight.\n\n");

	for (int i = 0; i < numberofvertices; i++)
	{
		graph_ptr temp = adj_list[i]->next;

		printf("%s ---> ", adj_list[i]->name);

		if (temp == NULL)
		{
			printf("There aren't any neighbours.");
		}
		else
		{
			while (temp != NULL)
			{
				printf("(%s, %d) ", temp->name, temp->edge);
				temp = temp->next;
			}
		}

		printf("\n");
	}

	return 0;
}

int dijkstra(graph_ptr* adj_list, int numberOfVertices, dList_ptr headOfDL, path_ptr* paths)
{
	char startPoint[20];
	pq_ptr headOfPQ; // head priority queue-a
	vList_ptr headOfVL; // head element visited liste

	printf("\nEnter the city from which you want to start your journey: ");
	scanf(" %[^\n]s", startPoint);

	while (!existsInTheAdjList(adj_list, startPoint, numberOfVertices))
	{
		printf("\nEntered name cannot be found in the adjacency list...\n");
		printf("Please be careful and try again.\n");

		printf("\nEnter the city from which you want to start your journey: ");
		scanf(" %[^\n]s", startPoint);
	}

	headOfPQ = makePQ(); // napravljen priority queue;
	headOfVL = makeVisitedList(); // napravljena lista sa posjecenim elementima
	changeOneWhereItAllBegins(paths, numberOfVertices, startPoint);

	putAtInfinityOrZero(headOfDL, startPoint);

	dList_ptr temp = findAndReturn(headOfDL->next, startPoint);

	addToPQ(headOfPQ, temp->name, temp->distance);

	// MAIN LOOP ALGORITMA
	// sve dok priority queue nije prazan, izbacit cu element sa vrha jer isti ima najveci prioritet
	// u mom slucaju to ce biti element sa najmanjom udaljenoscu od promatranog elementa
	// proc cemo kroz sve susjede promatranog elementa i ako se otvori prilika za promjenu dogodit ce se sljedece...
	// provjerit cemo je li se promatrani susjed vec nalazi u listi posjecenih elemenata
	//   a) ako se nalazi - prelazimo na iduceg susjeda i ponavljamo prethodni korak
	//	 b) ako se ne nalazi - pogledat cemo kolika je njegova trenutna udaljenost
	//		1) ako smo pronasli bolji put, promjenit cemo njegovu udaljenost u manju i dodati ga u pq
	//		2) ako nismo pronasli bolji put, istog cemo samo dodati u pq
	// nakon sta se sve obavi promatrani element cemo poslati u visited listu i time oznaciti da smo ga posjetili

	while (!isEmpty(headOfPQ))
	{
		char returnedFromPQ[MAX];
		strcpy(returnedFromPQ, removeFromPQ(headOfPQ));

		graph_ptr toGoThrough = findInTheAdjList(adj_list, returnedFromPQ, numberOfVertices);
		toGoThrough = toGoThrough->next;

		dList_ptr keyVertex = findAndReturn(headOfDL->next, returnedFromPQ);

		while (toGoThrough != NULL)
		{
			if (!existsInVL(headOfVL, toGoThrough->name))
			{

				dList_ptr neighbour = findAndReturn(headOfDL->next, toGoThrough->name);

				if (neighbour->distance > keyVertex->distance + toGoThrough->edge)
				{
					neighbour->distance = keyVertex->distance + toGoThrough->edge;
			
					addToPQ(headOfPQ, toGoThrough->name, toGoThrough->edge);

					path_ptr oneThatWillUpdate = returnPath(paths, numberOfVertices, returnedFromPQ);
					path_ptr oneThatWillBeUpdated = returnPath(paths, numberOfVertices, toGoThrough->name);

					reconstructPath(oneThatWillUpdate, oneThatWillBeUpdated);
					updatePath(oneThatWillBeUpdated, toGoThrough->name);

					
					toGoThrough = toGoThrough->next;
				}
				else
				{
					addToPQ(headOfPQ, toGoThrough->name, toGoThrough->edge);
					toGoThrough = toGoThrough->next;
				}
			}
			else
			{
				toGoThrough = toGoThrough->next;
			}

		}

		addToVL(headOfVL, returnedFromPQ);
	}

	printf("\n\n");

	char choice;

	printf("Do you want to print all distances or just distance to the particular city?\n\n");
	printf("Press p for particular or any other letter for all places: ");
	scanf(" %c", &choice);

	if (choice == 'p')
	{
		char endPoint[MAX];

		printf("\nAt which city you want to finish your journey: ");
		scanf(" %[^\n]s", endPoint);

		while (!existsInTheAdjList(adj_list, endPoint, numberOfVertices))
		{
			printf("\nEntered city cannot be found...\n");
			printf("Please be careful and try again.\n");

			printf("\nAt which city you want to finish your journey: ");
			scanf(" %[^\n]s", endPoint);
		}

		system("cls");

		printf("Minimal distance from %s to %s is: %d", startPoint, endPoint, returnDistance(headOfDL->next, endPoint));
		printParticularPath(paths, numberOfVertices, startPoint, endPoint);
	}
	else
	{
		system("cls");

		printDistances(headOfDL->next, startPoint);
		printAllPaths(paths, numberOfVertices, startPoint);
	}

	printf("\n\nThank you for using this algorithm.\n");
	printf("Have a nice day and feel free to come back!\n\n");

	freePQ(headOfPQ);
	freeVL(headOfVL);

	return 0;
}


graph_ptr findInTheAdjList(graph_ptr * adj_list, char* keyValue, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (strcmp(adj_list[i]->name, keyValue) == 0)
		{
			return adj_list[i];
		}
	}
}

bool existsInTheAdjList(graph_ptr* adj_list, char* key, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (strcmp(adj_list[i]->name, key) == 0)
		{
			return true;
		}
	}

	return false;
}



