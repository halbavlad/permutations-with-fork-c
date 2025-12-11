#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 100
int fd[2], n, solutie[MAX]; // fd pentru pipe, fd[0] - read, fd[1] - write
int valid(int k)
{
    for (int i = 0; i < k; i++)
        if (solutie[i] == solutie[k])
            return 0;
    return 1;
}
void afisare()
{
    write(fd[1], solutie,
          n * sizeof(int)); // trimite solutia prin pipe la parinte
                            // daca am pune printf aici, am avea probleme de sincronizare intre procese
}
void back(int k)
{
    if (k == n)
    {
        afisare();
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        solutie[k] = i;
        if (valid(k))
        {
            int pid=fork();
            if(pid==0){ //proces copil
                back(k + 1);
                exit(0); //iesim din procesul copil dupa ce a terminat backtracking-ul
                //nu putem da return deoarce copilul ar continua in main si ar executa codul
            } 
        }
    }
}

int main() { 
    pipe(fd); // creez pipe-ul
    printf("n =");
    scanf("%d", &n);
    back(0); //pornim backtracking-ul
    //parinte : 
    close(fd[1]); //inchidem capatul de scriere in parinte
    // functia read va bloca executia pana cand exista date de citit in pipe
    // de aia inchidem capatul de scriere in parinte
    int rezultat[MAX]; //in acest vector scriem permutarea
    while(read(fd[0],rezultat,n*sizeof(int))>0){ //read returneaza >0 daca e buna citirea 0 EOF si -1 eroare
        //read se uita la capatul de citire al pipe-ului fd[0]
        //read citeste din pipe in rezultat, bit cu bit, pana citeste n*sizeof(int) octeti,
        //adica o permutare completa
        //afisam permutarea citita
        for(int i=0;i<n;i++){
            printf("%d ",rezultat[i]);
        }
        printf("\n");
}
return 0;
}