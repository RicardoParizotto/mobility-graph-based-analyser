UNIVERSIDADE FEDERAL DA FRONTEIRA SUL

Aluno: Ricardo Parizotto



A aplicação tem como objetivo analisar traços reais de mobilidade aplicando algumas métricas 
que podem ser relacionadas com teoria de grafos (e.g. Conectividade, diâmetro).

As seguintes funcionalidades já estão disponíveis:
	- Acompanhar a média de componentes criados conforme a rede se altera
	- Acompanhar, com logs diários, o comportamento da rede
	- Cálculo de distâncias entre os nodos da rede (raio, diâmetro)
	- Tempo de duração médio dos enlaces conforme o raio de alcance dos táxis



Para rodar a aplicação, é necessário de um arquivo com os logs dos táxis e outro com as posições 
iniciais do mesmo.

Ambos os arquivos contém entradas formatadas da seguinte maneira:

id_nodo; ano-mês-dia hora:minuto:segunto; POINT( latitude, longitude )