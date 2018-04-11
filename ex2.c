/* ************************************************************************ *
 *    Simulador de Rede de Petri                                            *
 *                                                                          *
 *    Copyright (C) 2018 by Douglas Azevedo Pereira Dantas                  *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *    To contact the author, please write to:                               *
 *    Douglas Azevedo Pereira Dantas <douglasazevedo839@gmail.com>          *
 *    Webpage: https://github.com/DodoAz                                    *
 *    Phone: +55 (81) 99158-2473                                            *
 * ************************************************************************ *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define PMAX 10
#define ITERA 100

void disparar(int[MAX][MAX], int[MAX][MAX], int[MAX], int);
int habilitada(int[MAX][MAX], int[MAX], int, int);
void sortear(int, int[MAX]);

int main(void)
{
    int arcP[MAX][MAX] = {0}, arcC[MAX][MAX] = {0};
    int tokens[MAX];
    int aleatorio[MAX];
    int nl, nt, l, t, cons, prod;
    int i, j;

    srand(time(NULL));

    scanf("%d", &nl);
    printf("Numero de lugares: %d\n", nl);
    for(i = 0; i < nl; i++)
    {
        scanf("%d", &tokens[i]);
        printf("Tokens no lugar %d: %d\n", i, tokens[i]);
    }

    scanf("%d", &nt);
    printf("Numero de transicoes: %d\n", nt);

    scanf("%d", &cons);
    printf("Numero de arcos consumidores: %d\n", cons);
    for(i = 0; i < cons; i++)
    {
        scanf("%d %d ", &l, &t);
        scanf("%d",&arcC[l][t]);
        printf("Arco %d: %d %d %d\n", i, l, t, arcC[l][t]);
    }

    scanf("%d", &prod);
    printf("Numero de arcos produtores: %d\n", prod);
    for(i = 0; i < prod; i++)
    {    
        scanf("%d %d ", &t, &l);
        scanf("%d",&arcP[t][l]);
        printf("Arco %d: %d %d %d\n", i, t, l, arcP[t][l]);
    }

    for(i=0; i < ITERA; i++)
    { 
        sortear(nt, aleatorio);
        printf("\nVetor aleatorio: ");
        for(j=0; j < nt; j++)
            printf("%d ", aleatorio[j]);
        printf("\n");

        for(j = 0; j < nt; j++)
            if(habilitada(arcC, tokens, nl, aleatorio[j]))
            {   
                printf("---> A transicao %d foi disparada!\n", aleatorio[j]);
                break;
            }
            else
                printf("---> A transicao %d nao pode ser disparada!\n", aleatorio[j]);


        if(j == nt)
        {
            printf("---> Nenhuma transicao pode ser disparada.\n");
            break;
        }

        disparar(arcP, arcC, tokens,aleatorio[j]);

        printf("Tokens apos disparo: ");
        for(j = 0; j < nl; j++)
            printf("L%d(%d) ", j, tokens[j]);
        printf("\n");
    }

    if(i != ITERA)
        printf("\nNao eh possivel realizar mais disparos.\n Numero de iteracoes: %d\n", i);
    else
        printf("\nForam realizadas todas a %d iteracoes.\n", ITERA);

    return 0;
}

void sortear(int nt, int vetoral[MAX])
{
    int i, j, x, alert;

    for(i = 0; i < nt; i++)
    {
        do
        {
            alert = 0;

            x = rand() % nt;

            for(j = 0; j < i; j++)
                if(x == vetoral[j])
                    alert = 1;
        } while(alert);

        vetoral[i] = x;
    }

    return; 
} 

int habilitada(int arcC[MAX][MAX], int tokens[MAX], int nl, int t)
{
    int i;

    for(i = 0; i < nl; i++)
        if(arcC[i][t] > tokens[i])
            return 0; /* nao habilitado*/

    return 1;
}

void disparar(int arcP[MAX][MAX], int arcC[MAX][MAX], int tokens[MAX], int t)
{
    int i;

    for(i=0; i<MAX; i++)
        tokens[i]+= arcP[t][i];

    for(i=0; i<MAX; i++)    
        tokens[i]-= arcC[i][t];

    return;
}
