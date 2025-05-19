#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int prime(int szam)
{
    if (szam == 1 || szam <= 0)
    {
        return 0; // hamis
    }
    else
    {
        float hat = sqrt(szam);
        for (int j = 2; j <= hat; j++)
        {
            if (szam % j == 0)
            {
                return 0; // hamis
                break;
            }
        }
    }
    return 1; // igaz
}

int legnagyobbprim(int *szamok, int len)
{
    int max = *szamok;
    for (int i = 0; i < len; i++)
    {
        if (prime(szamok[i]) == 1 && max < szamok[i])
        {
            max = szamok[i];
        }
    }
    return max;
}

int primosszeg(int *szamok, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (prime(szamok[i]) == 1)
        {
            sum += szamok[i];
        }
    }

    return sum;
}

void rendezes(int *szamok, int len)
{
    for (int i = 1; i < len; i++)
    {
        if (szamok[i - 1] > szamok[i])
        {
            int temp = szamok[i];
            szamok[i] = szamok[i - 1];
            int j;
            for (j = i - 2; j > -1 && szamok[j] > temp; j--)
            {
                szamok[j + 1] = szamok[j];
            }
            szamok[j + 1] = temp;
        }
    }
}

void utolsoHarom(int *szamok, int len)
{
    
    rendezes(szamok, len);
    for (int i = len - 3; i < len - 1; i++)
    {
        printf(" %d", szamok[i]);
    }
    printf(" %d", szamok[len - 1]);
}

int paratlane(int szam)
{
    if (szam % 2 != 0)
    {
        return 1;
    }
    return 0;
}
void filebaIras(int *szamok, int len)
{
    FILE *fpo;
    fpo = fopen("output.txt", "w");
    int ind = 0;
    while ((paratlane(szamok[ind]) != 1) && (ind < len))
    {
        ind++;
    }
    fprintf(fpo, "%d", szamok[ind]);
    for (int i = ind + 1; i < len; i++)
    {
        if (paratlane(szamok[i]))
        {
            fprintf(fpo, " %d", szamok[i]);
        }
    }

    fclose(fpo);
}
int main()
{
    FILE *fpi;
    fpi = fopen("input.txt", "r");

    int len = 5;
    int *szamok = malloc(sizeof(int)*len);
    
    int db = 0;
    int szam;
    while (fscanf(fpi, "%d", &szam) == 1)
    {
        if (db < len)
        {
            szamok[db] = szam;
        }
        else
        {
            len +=10;
            int *tmp = realloc(szamok, len * sizeof(int));
            if(tmp != NULL)
            {
                szamok = tmp;
            }
            else 
            {
                printf("Nincs elég memoria");
            }
            szamok[db] = szam;
        }        
        db++;
    }
    int *tmp = realloc(szamok, db * sizeof(int));
    if(tmp != NULL)
    {
        szamok = tmp;
    }
    fclose(fpi);

    len = 5;
    int *nemPrimek = malloc(sizeof(int)*len);
    int nemPrimDB = 0;

    for(int i = nemPrimDB; i < db;i++)
    {
        if (prime(szamok[i])==0)
        {
            if (nemPrimDB < len)
            {
                nemPrimek[nemPrimDB] = szamok[i];
            }
            else
            {
                len +=5;
                int *tmp2 = realloc(nemPrimek, nemPrimDB * sizeof(int));
                if(tmp2 != NULL)
                {
                    nemPrimek = tmp2;
                }
                else 
                {
                    printf("Nincs elég memoria");
                }
                
                nemPrimek[nemPrimDB] = szamok[i];
            }        
            nemPrimDB++;
        }
        
        
        
    }
    int *tmp2 = realloc(nemPrimek, nemPrimDB * sizeof(int));
    if(tmp2 != NULL)
    {
        nemPrimek = tmp2;
    }

    
    printf("%d ", legnagyobbprim(szamok, db));
    printf("%d", primosszeg(szamok, db));
    utolsoHarom(nemPrimek, nemPrimDB);
    filebaIras(nemPrimek, nemPrimDB);

    free(szamok);
    free(nemPrimek);

    return 0;
}