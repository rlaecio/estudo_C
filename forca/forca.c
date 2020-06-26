#include <stdio.h>
#include <string.h>
#include "forca.h"

// global variables
char palavrasecreta[20];
char chutes[26];
int chutesDados = 0;

// functions declarations
void abertura()
{
    printf("**************************************\n");
    printf("*       J O G O  D E  F O R C A      *\n");
    printf("**************************************\n\n");
}

void chuta()
{
    char chute;
    scanf(" %c", &chute);
    chutes[chutesDados] = chute;
    chutesDados++;
}

void desenhaforca()
{
    // imprime a palavra secreta
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        int achou = jachutou(palavrasecreta[i]);
        if (achou)
        {
            printf("%c ", palavrasecreta[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra()
{
    FILE* f;
    f = fopen("palavras.txt", "r");




    fclose(f);
}

int acertou()
{
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {
            return 0;
        }  
    }
    return 1;
}

int enforcou()
{
    int erros = 0;
    for (int i = 0; i < chutesDados; i++)
    {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++)
        {
            if (chutes[i] == palavrasecreta[j])
            {
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }
    return erros >= 5;
}

int jachutou(char letra)
{
    int achou = 0;
    for (int j = 0; j < chutesDados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }
    return achou;
}


// --
int main()
{   
    escolhepalavra();
    abertura();

    do
    {
        desenhaforca();
        chuta();
    } while (!acertou() && !enforcou());
}
