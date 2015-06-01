#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define MAX 316       //Number of nodes
#define RANGE 18000

typedef struct node{
  double x, y;
}node ;

typedef struct date{
	int yy, mm, dd, hr, min;
	double sec;
} date;

//unionn/find  data structures
int ch[MAX], sz[MAX], new[MAX];

//dfs structures
int cor[MAX];

//adj matrix
char M[MAX][MAX];

//grid structures
node grid[MAX];

date BIRTH[MAX];  


//return the chef of v
int find ( int v );


//join two components of the graph
void unionn ( int v, int u );


//Component builder
void unionn_DFS( int v );

void change ( int v );


//initial graph
void mount();

double difference( date a, date p );








