#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <string.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define INFINITY 9999

typedef struct graphNode* graph_ptr;
typedef struct distanceList * dList_ptr;
typedef struct pqNode* pq_ptr;
typedef struct visitedList* vList_ptr;
typedef struct pathNode* path_ptr;

struct graphNode {
	char name[MAX];
	int edge;
	graph_ptr next;
};

struct visitedList {
	char name[MAX];
	vList_ptr next;
};

struct distanceList {
	char name[MAX];
	int distance;
	dList_ptr next;
};

struct pathNode {
	char station[MAX];
	char name[MAX];
	path_ptr next;
};

struct pqNode {
	char name[MAX];
	int value;
	pq_ptr next;
};

//MAIN MENU FUNCTION
int displayMainMenu(); // funkcija koja ce pokrenuti program i ispisati menu za korisnika

//GRAPH FUNCTIONS
int readGraph(graph_ptr*, int, dList_ptr, path_ptr*); // funkcija koja ce ucitati graf
int printGraph(graph_ptr*, int); // funkcija koja ce ispisati graf
int makeAdjacencyList(graph_ptr*, int); // funkcija koja postavljava sve headove adjacency liste na NULL
int dijkstra(graph_ptr*, int, dList_ptr, path_ptr*); // funkcija koja pomocu dijkstrinog algoritma racuna najkraci put u grafu
graph_ptr findInTheAdjList(graph_ptr *, char*, int); // funkcija koja pronalazi vertex unutar adjacency liste
bool existsInTheAdjList(graph_ptr *, char*, int); // funkcija koja ce provjeriti je li vertex danog imena vec postoji u adjacency listi

//DISTANCE LIST FUNCTIONS
dList_ptr makeDistanceList(); // funkcija koja ce napraviti distance listu
int addToDL(dList_ptr, char*); // funkcija koja dodaje elemente u distance listuž
int printDistances(dList_ptr, char*); // funkcija koja ce mi isprintati distance liste, samo u preventivne svrhe
int putAtInfinityOrZero(dList_ptr, char*);
dList_ptr findAndReturn(dList_ptr, char*); // funkcija koja ce pronaci trazeni element u distance listi
int returnDistance(dList_ptr, char*); // funkcija koja ce vratiti vrijednost distance

//FREE FUNCTIONS
int freeMemory(path_ptr); // funkcija koja oslobada memoriju kod rekonstrukcije patha
int freePQ(pq_ptr); // funkcija koja oslobada memoriju koristenu za priority queue
int freeVL(vList_ptr); // funkcija koja oslobada memoriju koristenu za visited listu
int freeDL(dList_ptr); // funkcija koja oslobada memoriju koristenu za distance listu
int freePath(path_ptr*, int); // funkcija koja oslobada memoriju koristenu za path
int freeAdjList(graph_ptr*, int); // funkcija koja oslobada memoriju koristenu za graf

//PRIORITY QUEUE FUNCTIONS
pq_ptr makePQ(); // funkcija koja ce napraviti priority queue
int addToPQ(pq_ptr, char*, int); // funkcija koja dodaje u priority queue
char* removeFromPQ(pq_ptr); // funkcija koja izbacuje element najveceg prioriteta s priority queue-a
bool isEmpty(pq_ptr); // funckija koja provjerava je li priority queue prazan
bool checkPQ(pq_ptr, char*); // funkcija koja provjerava postoji li element u priority queue-u


//VISITED LIST FUNCTIONS
vList_ptr makeVisitedList(); // funkcija koja ce napraviti listu sa posjecenim elementima
int addToVL(vList_ptr, char*); // funkcija koja dodaje element u visited list
bool existsInVL(vList_ptr, char*); // funkcija koja provjerava postoji li element u visited listi

//PATH FUNCTIONS
int makePath(path_ptr*, int); // funkcija koja ce napraviti path u obliku vezane liste 
int changeOneWhereItAllBegins(path_ptr*, int, char*); // funkcija koja ce azurirati starting node
int updatePath(path_ptr, char*); // funkcija koja ce azurirati put do odredista
int reconstructPath(path_ptr, path_ptr); // funkcija koja ce dani put rekonstruirati zbog mogucnosti boljeg puta
path_ptr returnPath(path_ptr*, int, char*); // funkcija koja vraca element iz path niza
int printParticularPath(path_ptr*, int, char*, char*); // funkcija koja ispisuje trazeni path
int printAllPaths(path_ptr*, int, char*); // funkcija koja ispisuje sve pathove u grafu

