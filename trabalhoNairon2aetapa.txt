#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n, int* comparacoes, int* trocas) {
    int i, j, indiceMinimo, temp;
    for (i = 0; i < n-1; i++) {
        indiceMinimo = i;
        for (j = i+1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j] < arr[indiceMinimo])
                indiceMinimo = j;
        }
        if (indiceMinimo != i) {
            (*trocas)++;
            temp = arr[i];
            arr[i] = arr[indiceMinimo];
            arr[indiceMinimo] = temp;
        }
    }
}

void insertionSort(int arr[], int n, int* comparacoes, int* trocas) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;
        (*comparacoes)++;
        while (j >= 0 && arr[j] > chave) {
            (*comparacoes)++;
            (*trocas)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void bubbleSort(int arr[], int n, int* comparacoes, int* trocas) {
    int i, j, temp;
    int trocou;
    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (arr[j] > arr[j + 1]) {
                (*trocas)++;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0)
            break;
    }
}

void shellSort(int arr[], int n, int* comparacoes, int* trocas) {
    int i, j, temp, intervalo;
    for (intervalo = n/2; intervalo > 0; intervalo /= 2) {
        for (i = intervalo; i < n; i++) {
            temp = arr[i];
            j = i;
            (*comparacoes)++;
            while (j >= intervalo && arr[j - intervalo] > temp) {
                (*comparacoes)++;
                (*trocas)++;
                arr[j] = arr[j - intervalo];
                j = j - intervalo;
            }
            arr[j] = temp;
        }
    }
}

int particao(int arr[], int baixo, int alto, int* comparacoes, int* trocas) {
    int pivo = arr[alto];
    int i = (baixo - 1);
    int j, temp;
    for (j = baixo; j <= alto - 1; j++) {
        (*comparacoes)++;
        if (arr[j] < pivo) {
            i++;
            (*trocas)++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    (*trocas)++;
    temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    return (i + 1);
}

void quickSort(int arr[], int baixo, int alto, int* comparacoes, int* trocas) {
    if (baixo < alto) {
        int pi = particao(arr, baixo, alto, comparacoes, trocas);
        quickSort(arr, baixo, pi - 1, comparacoes, trocas);
        quickSort(arr, pi + 1, alto, comparacoes, trocas);
    }
}

void heapify(int arr[], int n, int i, int* comparacoes, int* trocas) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    int temp;
    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;
    if (direita < n && arr[direita] > arr[maior])
        maior = direita;
    (*comparacoes)++;
    if (maior != i) {
        (*trocas)++;
        temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        heapify(arr, n, maior, comparacoes, trocas);
    }
}

void heapSort(int arr[], int n, int* comparacoes, int* trocas) {
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparacoes, trocas);
    for (i = n - 1; i >= 0; i--) {
        (*trocas)++;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, comparacoes, trocas);
    }
}

void merge(int arr[], int esquerda, int meio, int direita, int* comparacoes, int* trocas) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            (*trocas)++;
            arr[k] = L[i];
            i++;
        } else {
            (*trocas)++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        (*trocas)++;
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        (*trocas)++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int esquerda, int direita, int* comparacoes, int* trocas) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(arr, esquerda, meio, comparacoes, trocas);
        mergeSort(arr, meio + 1, direita, comparacoes, trocas);
        merge(arr, esquerda, meio, direita, comparacoes, trocas);
    }
}

void imprimirArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void gerarArrayAleatorio(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

int main() {
    srand(time(0));

    int tamanhos[] = {1000, 10000, 100000, 200000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    int i, j;
    for (i = 0; i < numTamanhos; i++) {
        int tamanho = tamanhos[i];
        int* vetorOriginal = (int*)malloc(tamanho * sizeof(int));
        int* copiaVetor = (int*)malloc(tamanho * sizeof(int));

        gerarArrayAleatorio(vetorOriginal, tamanho);

        printf("Tamanho do vetor: %d\n", tamanho);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        int comparacoes = 0;
        int trocas = 0;
        selectionSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("SelectionSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        insertionSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("InsertionSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        bubbleSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("BubbleSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        shellSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("ShellSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        quickSort(copiaVetor, 0, tamanho - 1, &comparacoes, &trocas);
        printf("QuickSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        heapSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("HeapSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        mergeSort(copiaVetor, 0, tamanho - 1, &comparacoes, &trocas);
        printf("MergeSort:\n");
        printf("Comparacoes: %d\n", comparacoes);
        printf("Trocas: %d\n\n", trocas);

        free(vetorOriginal);
        free(copiaVetor);
    }

    return 0;
}
