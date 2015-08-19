#include "node_config.h"
#include "haversin.h"
#include <string.h>

int main ( int arcv, char ** argc ){

	FILE * first_occurency, * taxi_data, * out_file;
	char out_name[200];


	char line[200];
	int map[400], h, aux, n, ctime = 0, select, i, j, day=1;
	int qtd[MAX + 1], ex_min[MAX + 1];
	double time[MAX + 1], temp;
	
	if(!(first_occurency = malloc(sizeof(FILE))))exit(1);
	if(!(first_occurency = fopen(argc[1], "r")))exit(1);
	if(!(taxi_data = malloc(sizeof(FILE)))) exit(1);
	if(!(taxi_data = fopen(argc[2], "r"))) exit(1);

	printf("0 - Analise da rede como um todo\n1 - Analise da rede com táxis com maior range(alfa)\n2 - Analise diaria da rede\n\n");
	scanf("%d", &select);
	printf("Digite o nome do arquivo de saída(max 200 carac.\n");
	scanf(" %s", out_name);
	strcat(out_name, ".txt");
	
	if(!(out_file = malloc(sizeof(FILE))))exit(1);
	if(!(out_file = fopen(out_name, "w+")))exit(1);

	memset(qtd, 0, (MAX + 1)*sizeof(int));
	memset(time, 0, (MAX + 1)*sizeof(double));
	memset(ex_min, 0, (MAX + 1)*sizeof(int));
		
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

	//depois de montar, é necessário contabilizar o tamanho dos componentes criados
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

		//Conforme as alterações nas arestas, é feita a reorganização dos componentes
		change(map[n]);
		
		for ( h = 0; h < MAX; h++ ){
			if(new[h] && ch[h]==h){
				qtd[sz[h]]++;
				time[sz[h]]+=difference(BIRTH[h], NOW);
				BIRTH[h] = NOW;   
			}
		}

		if(select == 2){
			if (NOW.dd != day){
				fprintf(out_file, "%d/%d/%d\n", NOW.yy, NOW.mm, day);
				day = NOW.dd;
				for ( h = 0; h < MAX; h++ )
					if(ch[h] == h){
						time[sz[h]]+=difference(BIRTH[h], NOW);
						if(!qtd[sz[h]]) qtd[sz[h]]++;			//caso o componente não tenha se modificado de um dia para outro. É importante deixar claro que ele existe para contabilizar o tempo.
					}
																
				for( h = 0; h < MAX; h++)
					BIRTH[h] = NOW;
			
				for ( h = 0; h <= MAX; h++ )
					if(qtd[h]) fprintf(out_file, "%d -> %d | media : %lf\n", h, qtd[h], time[h]/qtd[h]);
				memset(qtd, 0, (MAX + 1)*sizeof(int));
				memset(time, 0, (MAX + 1)*sizeof(double));
			}
		}

	
		if(select == 1){
			if(ctime++ == 0){
				floyd_warshall();
				temp = raio();
				for( i = 0; i < MAX; i++)
					for ( j = 0; j < MAX; j++)
						if(dist[i][j] == temp){
							ex_min[i]++;
							ex_min[j]++;
						}
			}else if( ctime == 1000 )
					ctime = 0;
				
		}
	}
	switch(select){
		case 0:
				for ( h = 0; h < MAX; h++ )
					if(ch[h] == h)
						time[sz[h]]+=difference(BIRTH[h], NOW);
	
				for ( h = 0; h <= MAX; h++ )
					if(qtd[h]) fprintf(out_file, "%d -> %d | media : %lf\n", h, qtd[h], time[h]/qtd[h]);

				break;
								
		case 1: 
				for ( i = 0; i < MAX; i++ )
					fprintf(out_file, "%d -> %d\n", i, ex_min[i]);
				
				break;

		default: exit(1);
	}
	return 0;
}
