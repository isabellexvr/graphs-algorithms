<img align="right" width="100px" src="./logo-ic.png" />
<img align="right" width="100px" src="./logo-ufal.png" />

<h1>Algoritmos de Grafos</h1>

<h2>Dupla</h2>
<p>Isabelle Xavier e Marcos Melo</p>

<h2>Professor</h2>
<p>Rian Gabriel Pinheiro</p>

<h2>Disciplina</h2>
<p>Teoria dos Grafos</p>

<h2>Conceito</h2>
<p>Implementação de 5 algoritmos de grafos em C++.</p>

<h2>Algoritmos Implementados</h2>
<ul>
  <li><strong>Prim</strong>: Algoritmo para encontrar a Árvore Geradora Mínima de um grafo.</li>
  <li><strong>Kruskal</strong>: Algoritmo para encontrar a Árvore Geradora Mínima, utilizando a abordagem de união e busca.</li>
  <li><strong>Kosaraju</strong>: Algoritmo para encontrar Componentes Fortemente Conectadas em um grafo dirigido.</li>
  <li><strong>Dijkstra</strong>: Algoritmo para encontrar o caminho mais curto de um vértice a todos os outros em um grafo com pesos não negativos.</li>
  <li><strong>Tarjan</strong>: Algoritmo para encontrar Componentes Fortemente Conectadas, utilizando a busca em profundidade.</li>
</ul>

<h2>Estrutura do Repositório</h2>
<pre>
.
├── src                 # Código fonte em C++
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

<h2>Compilação</h2>
<p>Para compilar o código, utilize o Makefile incluído no repositório. Execute o seguinte comando no terminal:</p>
<p>Para compilar o código, utilize o makefile que fica dentro da pasta do algoritmo escolhido. Execute o seguinte comando no terminal:</p>
<pre><code>make</code></pre>

<h2>Execução</h2>
<p>Após a compilação, os arquivos executáveis gerados estarão na pasta <code>bin</code>. Para executar um dos algoritmos, utilize:</p>
<pre><code>./bin/nome_do_algoritmo</code></pre>
