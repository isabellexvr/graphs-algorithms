<h1>Algoritmos de Grafos</h1>

<img align="center" src="./d&g.png" /><br>

<h3>Dupla</h3>
<p>Isabelle Xavier e Marcos Melo</p>


<h3>Professor</h3>
<p>Rian Gabriel Pinheiro</p>

<h3>Disciplina</h3>
<p>Teoria dos Grafos</p>

<h3>Conceito</h3>
<p>Implementação de 5 algoritmos de grafos em C++.</p>

<h3>Algoritmos Implementados</h3>
<ul>
  <li><strong>Prim</strong>: Algoritmo para encontrar a Árvore Geradora Mínima de um grafo.</li>
  <li><strong>Kruskal</strong>: Algoritmo para encontrar a Árvore Geradora Mínima, utilizando a abordagem de união e busca.</li>
  <li><strong>Kosaraju</strong>: Algoritmo para encontrar Componentes Fortemente Conectadas em um grafo dirigido.</li>
  <li><strong>Dijkstra</strong>: Algoritmo para encontrar o caminho mais curto de um vértice a todos os outros em um grafo com pesos não negativos.</li>
  <li><strong>Tarjan</strong>: Algoritmo para encontrar Componentes Fortemente Conectadas, utilizando a busca em profundidade.</li>
</ul>

<h3>Estrutura do Repositório</h3>
<pre>
 .
   ├── prim             # Pasta da implementação do algoritmo de Prim
        ├── prim.cpp
        ├── prim.bin
        ├── makefile
   ├── kruskal          # Implementação do algoritmo de Kruskal
        ├── kruskal.cpp
        ├── kruskal.bin
        ├── makefile
   ├── kosaraju         # Implementação do algoritmo de Kosaraju
        ├── kosaraju.cpp
        ├── kosaraju.bin
        ├── makefile
   ├── dijkstra         # Implementação do algoritmo de Dijkstra
        ├── dijkstra.cpp
        ├── dijkstra.bin
        ├── makefile
   └── tarjan           # Implementação do algoritmo de Tarjan
        ├── tarjan.cpp
        ├── tarjan.bin
        ├── makefile
└── README.md           # Este arquivo
</pre>

<h3>Compilação</h3>
<p>Para compilar o código, utilize o makefile que fica dentro da pasta do algoritmo escolhido. Execute o seguinte comando no terminal:</p>
<pre><code>make</code></pre>

<h3>Execução</h3>
<p>Após a compilação, os arquivos executáveis gerados estarão na pasta <code>"nome_do_algoritmo"</code>. Para executar um dos algoritmos, utilize:</p>
<pre><code>./nome_do_algoritmo.bin</code></pre>
