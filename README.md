# Projeto Multithread

Projeto 1 da matéria MC504 ministrada pela Profa. Islene Calciolari Garcia.

## Integrante
- Gabriel Henrique Antunes Martins - 216260


## Pré Requisitos

- GCC (MingGW) instalado no sistema operacional

## Como rodar

- $ gcc bathroom.c -lpthread -o bathroom
- ./bathroomarg1 arg2
- No repositório também há versões já compiladas "bathroom" ou "bathroom.exe", caso queira pular a primeira parte.

## Argumentos

- arg1 se refere a quantos espaços terão no banheiro
- arg2 se refere a quantas pessoas irão utilizar
- Exemplo: "./main 3 10" -> banheiro com 3 sanitários e 10 pessoas irão entrar na fila para usar

## Motivação

O projeto visa treinar os conceitos de programação concorrente aprendidos na matéria MC504 - Sistemas Operacionais, fazendo uso de semáforos, mutex lock e variáveis de condição.

## O problema

O "Problema do Banheiro Unissex" está presente no livro The Little Book of Semaphores (Allen B. Downey) e é formulado da seguinte forma: Um banheiro unissex de uma empresa com duas filas precisa ser controlado por semáforos seguindo as regras:

- Não pode ter homem e mulher no banheiro ao mesmo tempo
- Nunca deve haver mais de três* funcionários esbanjando tempo no banheiro.

Para resolvê-lo, foram usadas as bibliotecas pthread e semaphore na linguagem C, e o código está no arquivo bathroom.c.
*no caso desta implementação, temos a opção de aumentar o número de vagas no banheiro através dos argumentos.

## Estado global
Toda vez que um homem ou mulher entram no banheiro, é printado no console o estado global da aplicação, como no exemplo:

X X X
F X X
F F X
F X X
X X X
M X X
X X X