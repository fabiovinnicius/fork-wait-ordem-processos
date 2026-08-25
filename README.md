# Ordem de Criação vs. Ordem de Término de Processos Filhos

Trabalho 1 da disciplina de Sistemas Operacionais — investigação experimental
sobre se a ordem em que processos filhos são criados com `fork()` determina a
ordem em que eles terminam e são coletados pelo processo pai via `wait()`.

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

## Disciplina

Sistemas Operacionais — Trabalho 1: Chamadas de Sistema e Processos.
