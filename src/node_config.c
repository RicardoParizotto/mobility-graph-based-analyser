#include "node_config.h"
#include "haversin.h"


int month[] = {31, 28, 31, 30, 31, 30}; 

double difference( date a, date p ){	
	if( a.mm == p.mm ){
		if(a.dd == p.dd ){
			if(a.hr == p.hr)
				return p.min - a.min;  		
			else
				return (p.hr - a.hr - 1)*60 + p.min + (60 - a.min);
		}else
			return (p.dd - a.dd - 1)*24*60 + (24- a.hr - 1)*60 + (60 - a.min) + p.min + p.hr*60;
	}
	return (p.mm - a.mm - 1)*30*24*60 + (p.dd - 1)*24*60 + p.hr*60 + p.min + (month[a.mm] - a.dd)*24*60 + (24 - a.hr - 1)*60 + (60 - a.min);
}


int find ( int v ) {
	int x = v;
	while( ch[x] != x )
    	x = ch[x];
    return x;
}

void unionn ( int v, int u ){
	if( sz[v] > sz[u] ){
		ch[u] = v;
		sz[v] += sz[u];
	}else{
		ch[v] = u;
		sz[u] += sz[v];
	}
}

void unionn_DFS( int v ){
	int i;
	cor[v] = 1;
	for ( i = 0; i < MAX; i++ ){
		if( M[v][i] && !cor[i] && v!=i){
	    		ch[i] = i;
			sz[i] = 1;
			unionn(find(i), find(v));
			unionn_DFS( i );
		}
	}
}


void change ( int v ){
  int i;
  double dist;

  //devo comparar inserçoes antes, para não quebrar componentes
	for( i = 0; i < MAX; i++ ){
		dist = haversin(grid[v].x, grid[v].y, grid[i].x, grid[i].y);
		if(dist <= RANGE ){
			//caso a aresta ainda não exista
      		if(M[v][i] == 0){
				M[v][i] = M[i][v] = dist;
				//caso estiverem em componentes diferentes
				if(find(v) != find(i)){		   
	  				unionn( find(v), find(i) );
	  				new[find(v)]  = 1;
				}
      		}
		}
	}
  
	for ( i = 0; i < MAX; i++ ){
		if(haversin(grid[v].x, grid[v].y, grid[i].x, grid[i].y) > RANGE ){
			//neste caso a aresta ira ser deletada
			if(M[v][i] != 0){
				memset(cor, 0, MAX*sizeof(int));
				M[i][v] = M[v][i] = 0; //é necessário excluir a aresta antes de fazer a busca                              
				BIRTH[v] = BIRTH[find(v)];
				ch[v] = v;
				sz[v] = 1;
				//aresta vi é ponte?
				unionn_DFS( v );
				if(cor[i] == 0){
					BIRTH[i] = BIRTH[v];
					new[i] = new[v] = 1;
					ch[i] = i;
					sz[i] = 1;
					unionn_DFS( i );
				}     
			}                  
		}
	}       
}

void mount(){
	int i, j;
	double dist;

	for( i = 0; i < MAX; i++ )
		for ( j = i; j < MAX; j++ ){
			dist = (haversin(grid[i].x, grid[i].y, grid[j].x, grid[j].y)); 
			M[i][j] = M[j][i] = ((dist <= RANGE )? dist: 0);
		}

	memset(cor, 0, MAX*sizeof(int));
	
	for( i = 0; i < MAX; i++)
		if(!cor[i]){ //certificar-se que cor inicia com 0
        		ch[i] = i;
        		sz[i] = 1;
        		unionn_DFS( i );              
		}
}

void floyd_warshall(){
	int i, j, k;


	for ( i = 0; i < MAX; i++ )
		for(j = 0; j < MAX; j++ )
			dist[i][j] = M[i][j] == 0 ? INFINITO:M[i][j];

	for ( i = 0; i < MAX; i++ )
		for ( j = 0; j < MAX; j++ )
			for( k = 0; k < MAX; k++ )
				if(dist[k][j] > dist[k][i] + dist[j][i])
					dist[k][j] = dist[k][i] + dist[j][i];
}

double diam (){
	int i, j;
	double diam;
	
	for ( diam = i = 0; i < MAX; i++ )
		for ( j = 0; j < MAX; j++ )
			if ( dist[i][j] > diam && dist[i][j] != INFINITO )
				diam = dist[i][j];
				
	return diam;	
} 

double raio (){
	int i, j;
	double r = INFINITO, temp;
		
	for ( i = 0; i < MAX; i++ ){
		for ( j = temp = 0; j < MAX; j++)
			temp = (dist[i][j] > temp && dist[i][j] != INFINITO)? dist[i][j] : temp;
		r = (temp < r)? temp:r;
	}
	return r;
}



