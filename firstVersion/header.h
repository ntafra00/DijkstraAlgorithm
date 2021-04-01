#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define INFINITY 999

typedef struct graphNode* graph_ptr;
typedef struct distanceList * dList_ptr;
typedef struct pqNode* pq_ptr;
typedef struct visitedList* vList_ptr;
typedef struct pathNode* path_ptr;

struct pathNode {
	int station;
	int name;
	path_ptr next;
};

struct distanceList {
	int index;
	int distance;
	dList_ptr next;
};

struct graphNode {
	int name;
	int edge;
	graph_ptr next;
};

struct pqNode {
	int name;
	int value;
	pq_ptr next;
};

struct visitedList {
	int index;
	vList_ptr next;
};


//GRAPH FUNCTIONS
int readGraph(graph_ptr*, int, dList_ptr, path_ptr*); // funkcija koja ce ucitati graf
int printGraph(graph_ptr*, int); // funkcija koja ce ispisati graf
int makeAdjacencyList(graph_ptr*, int); // funkcija koja postavljava sve headove adjacency liste na NULL
int dijkstra(graph_ptr*, int, dList_ptr, path_ptr*); // funkcija koja pomocu dijkstrinog algoritma racuna najkraci put u grafu
graph_ptr findInTheAdjList(graph_ptr *, int, int); // funkcija koja pronalazi trazeni element u adjacency listi
bool existsInTheAdjList(graph_ptr*, int, int); // funkcija koja provjerava postoji li trazeni element adjacency listi

//DISTANCE LIST FUNCTIONS
dList_ptr makeDistanceList(); // funkcija koja ce napraviti distance listu
int addToDL(dList_ptr, int); // funkcija koja dodaje elemente u distance listu
int printDistances(dList_ptr, int); // funkcija koja ce mi isprintati distance liste, samo u preventivne svrhe
int putAtInfinityOrZero(dList_ptr, int); // funkcija koja ce distance od starting pointa postaviti na nulu, a ostale na INFINITY
dList_ptr findAndReturn(dList_ptr, int); // funkcija koja ce pronaci trazeni element u distance listi
int returnDistance(dList_ptr, int); // funkcija koja ce vratiti vrijednost distance

//FREE FUNCTIONS
int freeMemoryOfThePath(path_ptr); // funkcija koja oslobada memoriju kod rekonstrukcije patha
int freePQ(pq_ptr); // funkcija koja oslobada memoriju koristenu za priority queue
int freeVL(vList_ptr); // funkcija koja oslobada memoriju koristenu za visited listu
int freeDL(dList_ptr); // funkcija koja oslobada memoriju koristenu za distance listu
int freePath(path_ptr*, int); // funkcija koja oslobada memoriju koristenu za path
int freeAdjList(graph_ptr*, int); // funkcija koja oslobada memoriju koristenu za graf

//PRIORITY QUEUE FUNCTIONS
pq_ptr makePQ(); // funkcija koja ce napraviti priority queue
int addToPQ(pq_ptr, int, int); // funkcija koja dodaje u priority queue
int removeFromPQ(pq_ptr); // funkcija koja izbacuje element najveceg prioriteta s priority queue-a
bool isEmpty(pq_ptr); // funckija koja provjerava je li priority queue prazan
bool checkPQ(pq_ptr, int); // funkcija koja provjerava postoji li element u priority queue-u


//VISITED LIST FUNCTIONS
vList_ptr makeVisitedList(); // funkcija koja ce napraviti listu sa posjecenim elementima
int addToVL(vList_ptr, int); // funkcija koja dodaje element u visited list
bool existsInVL(vList_ptr, int); // funkcija koja provjerava postoji li element u visited listi

//PATH FUNCTIONS
int makePath(path_ptr*, int); // funkcija koja ce napraviti path u obliku vezane liste 
int changeOneWhereItAllBegins(path_ptr*, int, int); // funkcija koja ce azurirati starting node
int updatePath(path_ptr, int); // funkcija koja ce azurirati put do odredista
int reconstructPath(path_ptr, path_ptr); // funkcija koja ce dani put rekonstruirati zbog mogucnosti boljeg puta
path_ptr returnPath(path_ptr*, int, int); // funkcija koja pronalazi trazeni path unutar path liste
int printParticularPath(path_ptr*, int, int, int); // funkcija koja ispisuje trazeni path
int printAllPaths(path_ptr*, int, int); // funkcija koja ispisuje sve pathove

//MAIN MENU FUNCTION
int displayMainMenu();