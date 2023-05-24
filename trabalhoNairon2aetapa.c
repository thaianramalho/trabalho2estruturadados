#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(long int arr[], long int n, long int *comparacoes, long int *trocas)
{
    long int i, j, indiceMinimo, temp;
    for (i = 0; i < n - 1; i++)
    {
        indiceMinimo = i;
        for (j = i + 1; j < n; j++)
        {
            (*comparacoes)++;
            if (arr[j] < arr[indiceMinimo])
                indiceMinimo = j;
        }
        if (indiceMinimo != i)
        {
            (*trocas)++;
            temp = arr[i];
            arr[i] = arr[indiceMinimo];
            arr[indiceMinimo] = temp;
        }
    }
}

void insertionSort(long int arr[], long int n, long int *comparacoes, long int *trocas)
{
    long int i, chave, j;
    for (i = 1; i < n; i++)
    {
        chave = arr[i];
        j = i - 1;
        (*comparacoes)++;
        while (j >= 0 && arr[j] > chave)
        {
            (*comparacoes)++;
            (*trocas)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void bubbleSort(long int arr[], long int n, long int *comparacoes, long int *trocas)
{
    long int i, j, temp;
    long int trocou;
    for (i = 0; i < n - 1; i++)
    {
        trocou = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            (*comparacoes)++;
            if (arr[j] > arr[j + 1])
            {
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

void shellSort(long int arr[], long int n, long int *comparacoes, long int *trocas)
{
    long int i, j, temp, intervalo;
    for (intervalo = n / 2; intervalo > 0; intervalo /= 2)
    {
        for (i = intervalo; i < n; i++)
        {
            temp = arr[i];
            j = i;
            (*comparacoes)++;
            while (j >= intervalo && arr[j - intervalo] > temp)
            {
                (*comparacoes)++;
                (*trocas)++;
                arr[j] = arr[j - intervalo];
                j = j - intervalo;
            }
            arr[j] = temp;
        }
    }
}

long int particao(long int arr[], long int baixo, long int alto, long int *comparacoes, long int *trocas)
{
    long int pivo = arr[alto];
    long int i = (baixo - 1);
    long int j, temp;
    for (j = baixo; j <= alto - 1; j++)
    {
        (*comparacoes)++;
        if (arr[j] < pivo)
        {
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

void quickSort(long int arr[], long int baixo, long int alto, long int *comparacoes, long int *trocas)
{
    if (baixo < alto)
    {
        long int pi = particao(arr, baixo, alto, comparacoes, trocas);
        quickSort(arr, baixo, pi - 1, comparacoes, trocas);
        quickSort(arr, pi + 1, alto, comparacoes, trocas);
    }
}

void heapify(long int arr[], long int n, long int i, long int *comparacoes, long int *trocas)
{
    long int maior = i;
    long int esquerda = 2 * i + 1;
    long int direita = 2 * i + 2;
    long int temp;
    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;
    if (direita < n && arr[direita] > arr[maior])
        maior = direita;
    (*comparacoes)++;
    if (maior != i)
    {
        (*trocas)++;
        temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        heapify(arr, n, maior, comparacoes, trocas);
    }
}

void heapSort(long int arr[], long int n, long int *comparacoes, long int *trocas)
{
    long int i, temp;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparacoes, trocas);
    for (i = n - 1; i >= 0; i--)
    {
        (*trocas)++;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, comparacoes, trocas);
    }
}

void merge(long int arr[], long int esquerda, long int meio, long int direita, long int *comparacoes, long int *trocas)
{
    long int i, j, k;
    long int n1 = meio - esquerda + 1;
    long int n2 = direita - meio;
    long int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2)
    {
        (*comparacoes)++;
        if (L[i] <= R[j])
        {
            (*trocas)++;
            arr[k] = L[i];
            i++;
        }
        else
        {
            (*trocas)++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        (*trocas)++;
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        (*trocas)++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long int arr[], long int esquerda, long int direita, long int *comparacoes, long int *trocas)
{
    if (esquerda < direita)
    {
        long int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(arr, esquerda, meio, comparacoes, trocas);
        mergeSort(arr, meio + 1, direita, comparacoes, trocas);
        merge(arr, esquerda, meio, direita, comparacoes, trocas);
    }
}

void imprimirArray(long int arr[], long int n)
{
    long int i;
    for (i = 0; i < n; i++)
        printf("%ld ", arr[i]);
    printf("\n");
}

void gerarArrayAleatorio(long int arr[], long int n)
{
    long int i;
    for (i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

long int main()
{
    srand(time(0));

    long int tamanhos[] = {1000, 10000, 100000, 200000};
    long int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    long int i, j;
    for (i = 0; i < numTamanhos; i++)
    {
        long int tamanho = tamanhos[i];
        long int *vetorOriginal = (long int *)malloc(tamanho * sizeof(long int));
        long int *copiaVetor = (long int *)malloc(tamanho * sizeof(long int));

        gerarArrayAleatorio(vetorOriginal, tamanho);

        printf("# # # # # Tamanho do vetor: %ld # # # # #\n", tamanho);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        long int comparacoes = 0;
        long int trocas = 0;
        selectionSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("SelectionSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        insertionSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("InsertionSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        bubbleSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("BubbleSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        shellSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("ShellSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        quickSort(copiaVetor, 0, tamanho - 1, &comparacoes, &trocas);
        printf("QuickSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        heapSort(copiaVetor, tamanho, &comparacoes, &trocas);
        printf("HeapSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        for (j = 0; j < tamanho; j++)
            copiaVetor[j] = vetorOriginal[j];

        comparacoes = 0;
        trocas = 0;
        mergeSort(copiaVetor, 0, tamanho - 1, &comparacoes, &trocas);
        printf("MergeSort:\n");
        printf("Comparacoes: %ld\n", comparacoes);
        printf("Trocas: %ld\n\n", trocas);

        free(vetorOriginal);
        free(copiaVetor);
    }

    return 0;
}
