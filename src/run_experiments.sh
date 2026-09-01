#!/usr/bin/env bash

# Executa o binário `experiment` várias vezes e calcula em que fração das rodadas a ordem de término dos filhos bateu com a ordem em que foram criados.

# Uso: ./run_experiments.sh [numero_de_filhos] [numero_de_rodadas]

# Exemplo:./run_experiments.sh 5 200 

set -uo pipefail

BINARIO="./experiment"
FILHOS="${1:-5}"
RODADAS="${2:-1000}"

if [ ! -x "$BINARIO" ]; then
    echo "Erro: '$BINARIO' não encontrado ou não é executável." >&2
    echo "Compile primeiro com: gcc -Wall -o experiment experiment.c" >&2
    exit 1
fi

preservada=0

for ((r = 1; r <= RODADAS; r++)); do
    "$BINARIO" "$FILHOS" > /dev/null
    if [ $? -eq 0 ]; then
        preservada=$((preservada + 1))
    fi

    if (( r % 50 == 0 )); then
        echo "  ... $r/$RODADAS rodadas" >&2
    fi
done

echo "Filhos por rodada: $FILHOS"
echo "Rodadas:           $RODADAS"
echo "Ordem preservada:  $preservada / $RODADAS"
awk -v p="$preservada" -v r="$RODADAS" 'BEGIN { printf "Percentual:         %.2f%%\n", (100*p/r) }'