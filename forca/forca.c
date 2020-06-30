#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "forca.h"

// global variables
char palavrasecreta[TAMANHO_PALAVRA];
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
    // desenha a forca
    int erros = chuteserrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

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

void adicionapalavra()
{
    char quer;
    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if (quer == 'S')
    {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE *f;

        f = fopen("palavras.txt", "r+");
        if (f == 0)
        {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}

void escolhepalavra()
{
    FILE *f;
    f = fopen("palavras.txt", "r");
    if (f == 0)
    {
        printf("Desculpe, Banco de Dados não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavrasecreta);
    }
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

int chuteserrados()
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
        if (!existe)
        {
            erros++;
        }
    }
    return erros;
}

int enforcou()
{
    return chuteserrados() >= 5;
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

    if (acertou())
    {
        printf("\nParabéns, você ganhou!\n\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n");
    }
    else
    {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era ** %s **\n", palavrasecreta);
        printf("      _______________        \n");
        printf("     /               \\      \n");
        printf("    /                 \\      \n");
        printf("   /                  \\/\\   \n");
        printf("  \\|   XXXX     XXXX   | /   \n");
        printf("   |   XXXX     XXXX   |/    \n");
        printf("   |   XXX       XXX   |     \n");
        printf("   |                   |     \n");
        printf("   \\__      XXX      __/     \n");
        printf("     |\\     XXX     /|       \n");
        printf("     | |           | |       \n");
        printf("     | I I I I I I I |       \n");
        printf("     |  I I I I I I  |       \n");
        printf("     \\_             _/       \n");
        printf("       \\_         _/         \n");
        printf("         \\_______/           \n");
    }
}
