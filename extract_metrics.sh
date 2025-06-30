#!/bin/bash
PROGRAM="./bubble_sort_exec"
OUTPUT_FILE="results.txt"
if [ ! -f "$PROGRAM" ]; then
    echo "Erro: Executável $PROGRAM não encontrado!"
    echo "Compile o programa com: gcc -fopenmp bubblesort.c -o bubble_sort_exec"
    exit 1
fi
echo "==== MÉTRICAS BUBBLE SORT ODD-EVEN TRANSPOSITION ====" > $OUTPUT_FILE
echo "" >> $OUTPUT_FILE
extract_metrics() {
    local n=$1
    local output="$2"
    echo "==== N = $n ====" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
    local time_1=$(echo "$output" | grep -A3 "1 THREAD:" | grep "Tempo de execução:" | awk '{print $4}')
    local time_2=$(echo "$output" | grep -A3 "2 THREADS:" | grep "Tempo de execução:" | awk '{print $4}')
    local time_4=$(echo "$output" | grep -A3 "4 THREADS:" | grep "Tempo de execução:" | awk '{print $4}')
    local speedup_2=$(echo "$output" | grep -A3 "2 THREADS:" | grep "Speedup:" | awk '{print $2}')
    local speedup_4=$(echo "$output" | grep -A3 "4 THREADS:" | grep "Speedup:" | awk '{print $2}')
    local efficiency_2=$(echo "$output" | grep -A3 "2 THREADS:" | grep "Eficiência:" | awk '{print $2}')
    local efficiency_4=$(echo "$output" | grep -A3 "4 THREADS:" | grep "Eficiência:" | awk '{print $2}')
    echo "1 thread: $time_1 s" >> $OUTPUT_FILE
    echo "2 threads: $time_2 s (Speedup: $speedup_2, Eficiência: $efficiency_2)" >> $OUTPUT_FILE
    echo "4 threads: $time_4 s (Speedup: $speedup_4, Eficiência: $efficiency_4)" >> $OUTPUT_FILE
    echo "----------------------------------------" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
}
sizes=(50000 100000 500000)
for n in "${sizes[@]}"; do
    echo "Executando teste com N = $n..."
    output=$($PROGRAM $n 2>&1)
    if [ $? -eq 0 ]; then
        echo "Teste N=$n concluído com sucesso!"
        extract_metrics $n "$output"
    else
        echo "Erro na execução com N=$n" >> $OUTPUT_FILE
        echo "Saída de erro: $output" >> $OUTPUT_FILE
        echo "" >> $OUTPUT_FILE
    fi
done
echo "====  FIM DA CAPTAÇÃO DAS MÉTRICAS ====" >> $OUTPUT_FILE