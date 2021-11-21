# PRiR_Lab5_2
Projekt przedstawia zadanie 2 z Labolatorium 5 z Programowania Równoległego i Rozproszonego.
Program napisano w języku C. Program tworzy p procesów potomnych za pomocą fork()-a, Każdy z procesów 
niezależnie oblicza i wyświetla na ekranie przybliżenie liczby PI z wzoru Leibniz-a

Najpierw załączam do projektu odpowiednie biblioteki:

  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <unistd.h>
  #include <time.h>
  #include "err.h"
  #include <math.h>
  
Funckja Leibniz, która liczy na podstawie wzoru przybliżenie liczby PI:

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

W funkcji main najpierw deklaruję odpowiednie zmienne:

   pid_t pid;
   int i, procesy, seed;
   time_t t;
   
Następnie wczytuję porządaną liczbę procesów:

   printf("Podaj ilosc procesow: ");
   scanf("%d", &procesy);
   
W pętli for dla każdego procesu sprawdzamy czy fork() jest równe 0 - wtedy ustawiamy ziarno (losując n z przedziału <100,5000> )
Wypisujemy numery procesów potomnych. Następnie wywoływana jest funkcja licząca przybliżenie liczby pi, której wartość wypisujemy na ekran. W pętli istnieje również możliwość wyłapania błędu w fork'u.:
   
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
