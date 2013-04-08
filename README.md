trabalhocg
==========

Rubik Cube OpenGL

Trabalho da disciplina de Computacao Grafica. 
O Trabalho consiste em implementar um Cubo Rubik, juntamente com suas operações, utilizando a linguagem C juntamente com a API OpenGL.

DONE:

-Criar em memória as estruturas de dados para renderizar o cubo.
-Renderizar o Cubo, utilizando OpenGL+GLUT.

TO DO:
-Estudar funcoes de comandos via mouse.
-Implementar as operações que podem ser aplicadas ao Cubo.


URL's uteis:

http://paulbourke.net/dataformats/ply/     explica o formato .ply
http://w3.impa.br/~diego/software/rply/	   exemplo de um codigo em C que le e grava arquivos .ply
http://openglsamples.sourceforge.net/      varios exemplos de codigo OpenGL, incluindo um que renderiza um arquivo .ply



TO REMEMBER:

- Cada cubo deve armazenar suas informacoes de transformacao: rotacao e translacao.
- Ao clicar com o mouse segurando Ctrl, o programa deve traçar uma reta com base em (x,y) clicado e verificar qual cubo colide com ela, utilizando os dados armazenados das transformacoes para saber onde o cubo esta sendo desenhado. A cada transformacao, os dados devem ser atualizados (multiplicar matrizes) para sempre manter a posicao atual do cubo.
  O algoritmo escolhe o cubo com maior Z. 
- Escrever na tela qual cubo foi selecionado. Rodar a face com base nos comandos A,W,D.