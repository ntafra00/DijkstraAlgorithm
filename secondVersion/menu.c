#include "header.h"

int displayMainMenu()
{
	char choice;

	printf("WELCOME !\n\n");
	printf("This program finds shortest path between two points using Dijkstra's algorithm.\n");
	printf("Algorihtm was conceived by Edgar Dijkstra in 1956.\n");
	printf("Enjoy using it!\n\n");

	printf("For the beginning of the program press letter s: ");
	scanf(" %c", &choice);

	while (choice != 's')
	{
		printf("\nYou pressed the wrong letter!\n");
		printf("Be careful and try again.\n\n");

		printf("For the beginning of the program press letter s: ");
		scanf(" %c", &choice);
	}

	printf("Well done!\n");
	printf("The program is about to start.\n");
	Sleep(1500);
	system("cls");

	int vertices;
	graph_ptr adj[MAX];
	dList_ptr headOfDL = makeDistanceList();
	path_ptr path[MAX]; // niz sa head elementima pojedinog patha 

	printf("Enter number of vertices(cities): ");
	scanf(" %d", &vertices);


	makeAdjacencyList(adj, vertices); 
	makePath(path, vertices);
	readGraph(adj, vertices, headOfDL, path); // SADA CU UZ SVE O GRAFU U FUNKCIJU POSLATI I DISTANCE LISTU

	printGraph(adj, vertices);


	dijkstra(adj, vertices, headOfDL, path); // glavna funkcija programa, ona u kojoj je realiziran Dijkstrin algoritam

	freeAdjList(adj, vertices);
	freeDL(headOfDL);
	freePath(path, vertices);

	return 0;
}
