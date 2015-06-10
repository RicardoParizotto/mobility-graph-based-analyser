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
  int i, k;
  
  //devo comparar inserçoes antes, para não quebrar componentes
	for( i = 0; i < MAX; i++ ){
		if(haversin(grid[v].x, grid[v].y, grid[i].x, grid[i].y) <= RANGE ){
			//caso a aresta ainda não exista
      			if(M[v][i] == 0){
				M[v][i] = M[i][v] = 1;
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
			if(M[v][i] == 1){
				memset(cor, 0, MAX*sizeof(int));
				M[i][v] = M[v][i] = 0; //é necessário excluir a aresta antes de fazer a busca                              
				ch[v] = v;
				sz[v] = 1;
				k = find(v);
				BIRTH[v] = BIRTH[k];
				//aresta vi é ponte?
				unionn_DFS( v );
				if(cor[i] == 0){
					BIRTH[i] = BIRTH[k];
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

	for( i = 0; i < MAX; i++ )
		for ( j = i; j < MAX; j++ )
			M[i][j] = M[j][i] = (haversin(grid[i].x, grid[i].y, grid[j].x, grid[j].y) <= RANGE )? 1: 0;

	memset(cor, 0, MAX*sizeof(int));
	
	for( i = 0; i < MAX; i++)
		if(!cor[i]){ //certificar-se que cor inicia com 0
        		ch[i] = i;
        		sz[i] = 1;
        		unionn_DFS( i );              
		}
}


