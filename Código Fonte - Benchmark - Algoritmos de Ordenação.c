/*
    Universidade Estadual Paulista "Júlio de Mesquita Filho"
    Campus de São José do Rio Preto - IBILCE

    DCCE :: Departamento de Ciências de Computação e Estatística
    Docente: Geraldo Francisco Donegá Zafalon
    Discente: Victor Hugo Bernardes de Souza
    R.A.: 09107-3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 150000

int* gPiorCaso();   //Gera vetor para Pior caso = vetor não ordenado
int* gMedioCaso();  //Gera vetor para Medio caso = vetor semi-ordenado
int* gMelhorCaso(); //Gera vetor para Melhor caso = Vetor ordenado

double tempo();

void bolha(int *v,int n);
void selecao(int *v, int n);
void insercao(int *v, int n);
void quicksort(int *v, int inicio, int fim);
long heapsort(int *v, int N);
void shellsort(int *v, int n);

void piorcaso(); //Executa os 6 metodos de ordenacao usando um vetor desordenado
void mediocaso(); //Executa os 6 metodos de ordenacao usando um vetor semi-ordenado
void melhorcaso(); //Executa os 6 metodos de ordenacao usando um vetor ordenado
void resultados(); //recebe o caso testado e as suas respectivas informações para a exibicao dos resultados

int main()
{
    piorcaso();
    mediocaso();
    melhorcaso();
    return 0;
}


int* gPiorCaso()  //Gera vetor para Pior caso = vetor não ordenado
{
    int i, *vetor;
    vetor = (int*) malloc(sizeof(int) * TAMANHO);

    for(i=TAMANHO; i>0; i--)
        vetor[TAMANHO-i] = i;

    return vetor;
}

int* gMedioCaso() //Gera vetor para Medio caso = vetor semi-ordenado
{
    /*
    *   Preenche o vetor de maneira ordenada até a metade
    *   e de maneira desordenada da metade do vetor até o final.
    */

    int i, j, meioTamanho=TAMANHO/2, *vetor;
    vetor = (int*) malloc(sizeof(int) * TAMANHO);

    for(i=0; i<meioTamanho; i++) //Preenche ordenado até a metade
        vetor[i] = i;

    for(i=TAMANHO-1,j=meioTamanho; i>=meioTamanho; i--,j++) //Preenche desordenado da metade até o fim
    {
        vetor[i] = j;
    }
    return vetor;
}

int* gMelhorCaso() //Gera vetor para Melhor caso = Vetor ordenado
{
    int i, *vetor;
    vetor = (int*) malloc(sizeof(int) * TAMANHO);

    for(i=0; i<TAMANHO; i++)
        vetor[i] = i;

    return vetor;
}


double tempo()
{
    struct timeval instante;

    gettimeofday(&instante, NULL);
    return instante.tv_sec+(instante.tv_usec/1000000.0);
}


void bolha(int *v,int n)
{
    int i,j,aux;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(v[i] > v[j])
            {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}

void selecao(int *v, int n)
{
    int i,j,menor,aux;
    for(i=0; i<n-1; i++)
    {
        menor=i;
        for(j=i+1; j<n; j++)
            if(v[j]<v[menor])
                menor=j;
        aux=v[i];
        v[i]=v[menor];
        v[menor]=aux;
    }
}

void insercao(int *v, int n)
{
    int i,j,aux;


    for(j=1; j<n; j++)
    {
        aux=v[j];
        for(i=j-1; i>=0 && v[i]>aux; i--)
            v[i+1]=v[i];
        v[i+1]=aux;
    }

}

void quicksort(int *v, int inicio, int fim)
{

    int i, j, x, aux;
    x = v[(inicio+fim)/2];
    i=inicio;
    j=fim;

    while (i<=j)
    {
        while ( v[i] < x && i < fim ) i++;
        while ( v[j] > x && j > inicio) j--;

        if ( i <= j )
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }

    }

    if ( j > inicio )
        quicksort(v, inicio, j);
    if ( i < fim )
        quicksort(v, i, fim);
}

long heapsort(int *v, int n)
{
    long trocas =0;
    int meioTamanho = n/2, parent, child, t;

    for (;;)
    {
        if (meioTamanho > 0)
        {
            meioTamanho--;
            t = v[meioTamanho];
        }
        else
        {
            n--;
            if (n == 0) return trocas;
            t = v[n];
            v[n] = v[0];
        }

        parent = meioTamanho;
        child = meioTamanho*2 + 1;

        while (child < n)
        {
            if (child + 1 < n  &&  v[child + 1] > v[child])
            {
                child++;
            }
            if (v[child] > t)
            {
                v[parent] = v[child];
                parent = child;
                child = parent*2 + 1;
                trocas = trocas +1;
            }
            else
            {
                break;
            }
        }
        v[parent] = t;
    }

}

void shellsort(int *v, int n)
{
    int x, i, j, k, passo[5], inc;
    passo[0] = 9;
    passo[1] = 7;
    passo[2] = 5;
    passo[3] = 3;
    passo[4] = 1;

    for (k=0; k<5; k++)
    {
        inc = passo[k];
        for (i=inc; i<n; i++)
        {
            x = v[i];
            for (j=i-inc; j>=0 && v[j]>x; j=j-inc)
                v[j+inc] = v[j];
            v[j+inc] = x;
        }
    }
}


void piorcaso()
{
    int *vetor;
    double processo,inicial,info[6]; //Bolha, Seleção, Inserção, Quick, Heap, Shell
    char caso[10] = {"PIOR CASO"};

    processo = tempo();

    vetor = gPiorCaso();

    inicial = tempo();
    bolha(vetor,TAMANHO);
    info[0]=tempo()-inicial;
    free(vetor);

    vetor = gPiorCaso();

    inicial = tempo();
    selecao(vetor,TAMANHO);
    info[1]=tempo()-inicial;
    free(vetor);

    vetor = gPiorCaso();

    inicial = tempo();
    insercao(vetor,TAMANHO);
    info[2]=tempo()-inicial;
    free(vetor);

    vetor = gPiorCaso();

    inicial = tempo();
    quicksort(vetor,0,TAMANHO-1);
    info[3]=tempo()-inicial;
    free(vetor);

    vetor = gPiorCaso();

    inicial = tempo();
    heapsort(vetor,TAMANHO);
    info[4]=tempo()-inicial;
    free(vetor);

    vetor = gPiorCaso();

    inicial = tempo();
    shellsort(vetor,TAMANHO);
    info[5]=tempo()-inicial;
    free(vetor);

    resultados(caso,info);
    printf("\nO processo de teste para o vetor desordenado(%s) demorou: %fs\n\n",caso,tempo()-processo);
}

void mediocaso()
{
    int *vetor;
    double processo,inicial,info[6]; //Bolha, Seleção, Inserção, Quick, Heap, Shell
    char caso[10] = {"CASO MEDIO"};

    processo = tempo();

    vetor = gMedioCaso();

    inicial = tempo();
    bolha(vetor,TAMANHO);
    info[0]=tempo()-inicial;
    free(vetor);

    vetor = gMedioCaso();

    inicial = tempo();
    selecao(vetor,TAMANHO);
    info[1]=tempo()-inicial;
    free(vetor);

    vetor = gMedioCaso();

    inicial = tempo();
    insercao(vetor,TAMANHO);
    info[2]=tempo()-inicial;
    free(vetor);

    vetor = gMedioCaso();

    inicial = tempo();
    quicksort(vetor,0,TAMANHO-1);
    info[3]=tempo()-inicial;
    free(vetor);

    vetor = gMedioCaso();

    inicial = tempo();
    heapsort(vetor,TAMANHO);
    info[4]=tempo()-inicial;
    free(vetor);

    vetor = gMedioCaso();

    inicial = tempo();
    shellsort(vetor,TAMANHO);
    info[5]=tempo()-inicial;
    free(vetor);

    resultados(caso,info);
    printf("\nO processo de teste para o vetor desordenado(%s) demorou: %fs\n\n",caso,tempo()-processo);
}

void melhorcaso()
{
    int *vetor;
    double processo,inicial,info[6]; //Bolha, Seleção, Inserção, Quick, Heap, Shell
    char caso[11] = {"MELHOR CASO"};

    processo = tempo();

    vetor = gMelhorCaso();

    inicial = tempo();
    bolha(vetor,TAMANHO);
    info[0]=tempo()-inicial;
    free(vetor);

    vetor = gMelhorCaso();

    inicial = tempo();
    selecao(vetor,TAMANHO);
    info[1]=tempo()-inicial;
    free(vetor);

    vetor = gMelhorCaso();

    inicial = tempo();
    insercao(vetor,TAMANHO);
    info[2]=tempo()-inicial;
    free(vetor);

    vetor = gMelhorCaso();

    inicial = tempo();
    quicksort(vetor,0,TAMANHO-1);
    info[3]=tempo()-inicial;
    free(vetor);

    vetor = gMelhorCaso();

    inicial = tempo();
    heapsort(vetor,TAMANHO);
    info[4]=tempo()-inicial;
    free(vetor);

    vetor = gMelhorCaso();

    inicial = tempo();
    shellsort(vetor,TAMANHO);
    info[5]=tempo()-inicial;
    free(vetor);

    resultados(caso,info);
    printf("\nO processo de teste para o vetor desordenado(%s) demorou: %fs\n\n",caso,tempo()-processo);
}

void resultados(char *str,double *info)
{
    int i,maior,menor;
    char metodos[6][20] = {"Bubblesort", "Selection Sort", "Insertion Sort", "Quicksort", "Heapsort", "Shellsort"};

    puts("+----------------------------------------------------------------------------+");
    printf("\tResultados do (%s) com vetor de %d posicoes:\n",str,TAMANHO);
    for (i=0; i<6; i++)
        printf("\t%s \t--> %fs\n",metodos[i],info[i]);

    maior = 0; //maior tempo = pior metodo
    menor = 0; //menor tempo = melhor metodo
    for (i=0; i<6; i++)
    {
        if (info[maior] < info[i])
            maior = i;
        if (info[menor] > info[i])
            menor = i;
    }
    printf("\nMelhor metodo:\n\t%s \t-> %fs\n",metodos[menor],info[menor]);
    printf("\nPior metodo:\n\t%s \t-> %fs\n",metodos[maior],info[maior]);
}
