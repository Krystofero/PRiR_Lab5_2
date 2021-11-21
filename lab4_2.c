#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include "err.h"
#include <math.h>

double Leibniz(int n)
{
    int i;
    double wynik = 0;

    for(i = 1; i <= n; i++){
        wynik += (pow(-1, i - 1)/(2 * i - 1));
    }
    wynik *= 4;
    return wynik;
}

int main ()
{
 pid_t pid;
 int i, procesy, seed;
 time_t t;
 printf("Podaj ilosc procesow: ");
 scanf("%d", &procesy);

 for (i = 1; i <= procesy; i++){
    switch (pid = fork()) {
        case -1:
            perror("Error in fork\n");
        case 0:
		    seed = time(&t);
		    srand(seed + i);
		    n = (rand()%4901) + 100;
            printf("Jestem procesem potomnym. Moj PID = %d\n", getpid());
            printf("Rezultat to: %f\n", Leibniz(n));
            return 0;
        default:
        printf("Jestem procesem macierzystym. Moj PID = %d\n", getpid());
    } 
 }
 return 0;
}
