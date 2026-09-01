# Ordem de Criação vs. Ordem de Término de Processos Filhos

Trabalho 1 da disciplina de Sistemas Operacionais — investigação experimental
sobre se a ordem em que processos filhos são criados com `fork()` determina a
ordem em que eles terminam e são coletados pelo processo pai via `wait()`.

## Equipe

- Fábio Vinnicius Silva Sousa
- Jonatas Andrade do Nascimento

Curso de Ciência da Computação — Instituto Federal Campus Maracanaú

## Sobre o projeto

**Problema:** a ordem de criação dos processos filhos garante a ordem em que
eles serão executados e terminados?

**Hipótese:** a ordem em que os processos filhos são criados influencia a
ordem em que eles serão executados e terminados; consequentemente, ao
utilizar `wait()`, o processo pai tenderá a receber os filhos na mesma ordem
em que foram criados.

O experimento cria N processos filhos em sequência, cada um executando uma
carga de trabalho de duração aleatória e independente, e compara a ordem de
criação com a ordem real de término observada pelo pai. Os resultados foram
comparados ao modelo teórico de uma permutação aleatória (probabilidade
1/N! de coincidência exata por acaso).

## Estrutura do repositório

```
.
├── README.md
├── src/
│   ├── experiment.c
│   └── run_experiments.sh
└── artigo/
    ├── artigo.tex
    └── artigo.pdf
```

## Como compilar e executar

Requer um compilador C (gcc) em um ambiente Linux/Unix (WSL, Replit Shell,
etc.) — o código usa chamadas POSIX (`fork()`, `wait()`) que não existem no
Windows nativo.

```bash
cd src
gcc -Wall -o experiment experiment.c

# executa uma vez com N filhos (padrão: 5)
./experiment 5

# roda em lote e calcula a % de vezes em que a ordem foi preservada
# uso: ./run_experiments.sh <numero_de_filhos> <numero_de_rodadas>
chmod +x run_experiments.sh
./run_experiments.sh 5 200
```

## Referências

- A. Silberschatz, P. B. Galvin, and G. Gagne, *Operating System Concepts*, 10th ed. Wiley, 2018.
- W. R. Stevens and S. A. Rago, *Advanced Programming in the UNIX Environment*, 3rd ed. Addison-Wesley, 2013.
- Linux manual pages: [`fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html), [`wait(2)`](https://man7.org/linux/man-pages/man2/wait.2.html)
