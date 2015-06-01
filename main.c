#include "node_config.h"
#include "haversin.h"

int main ( int arcv, char ** argc ){

	FILE * first_occurency, * taxi_data;
	char line[200];
	int map[400], h, aux, n;
	int qtd[MAX];
	double time[MAX];
	
	date NOW;


	if(!(first_occurency = malloc(sizeof(FILE))))exit(1);
	if(!(first_occurency = fopen(argc[1], "r")))exit(1);
	if(!(taxi_data = malloc(sizeof(FILE)))) exit(1);
	if(!(taxi_data = fopen(argc[2], "r"))) exit(1);

	memset(qtd, 0, MAX*sizeof(int));
	memset(time, 0, MAX*sizeof(double));


	for ( n = 0; n < MAX; n++ ){
		fscanf( first_occurency, " %[^\n]", line );
		sscanf( line, "%d", &h );
		map[h] = n;

		for ( aux = 0; line[aux]!= '('; aux++ );
		sscanf( &line[++aux], "%lf %lf", &grid[n].x, &grid[n].y);
	}

	for( h = 0; h < MAX; h++ ){
		BIRTH[h].yy = 2014;
		BIRTH[h].mm = 02;
		BIRTH[h].dd = 01;
		BIRTH[h].hr = BIRTH[h].min = BIRTH[h].sec = 0;
	}
	
	mount();
	
	for( h = 0; h < MAX; h++ )
		if(ch[h] == h)
			qtd[sz[h]]++;

	while( fscanf( taxi_data, " %d;", &n) != EOF ){
		memset(new, 0, MAX*sizeof(int));
		
		//leitura
		fscanf(taxi_data, "%d-%d-%d %d:%d:%lf", &NOW.yy, &NOW.mm, &NOW.dd, &NOW.hr, &NOW.min, &NOW.sec);
		fscanf(taxi_data, " %[^\n]", line);
		for ( aux = 0; line[aux]!= '('; aux++ );
		sscanf( &line[++aux], "%lf %lf", &grid[map[n]].x, &grid[map[n]].y);

		change(map[n]);
/*
		for ( h = 0; h < MAX; h++ )
			if(new[h]){
				printf("Aumenta\n");
				exit(1);
			}

*/
		for ( h = 0; h < MAX; h++ )
			if(new[h] && ch[h]==h){
				qtd[sz[h]]++;
				time[sz[h]]+=difference(BIRTH[sz[h]], NOW);
				BIRTH[sz[h]] = NOW;
			}
	}

	for ( h = 0; h < MAX; h++ )
		if(qtd[h]) printf("%d -> %d | media : %lf\n", h, qtd[h], time[h]/qtd[h]);



	return 0;
}
