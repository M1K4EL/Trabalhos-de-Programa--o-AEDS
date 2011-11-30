/*
Academicos: Mikael Patrick e Mariane Luyara
Descrição: Jogo Numeros da Sorte
Data de Desenvolvimento: 20/11/11
*/

//--BIBLIOTECAS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//-- CONSTANTES
#define TRUE  1
#define FALSE 0
#define MAX 10

//-------------------------- ESTRUTURAS EM GERAL - INICIO -----------------------------------------------------------------------------

//Estrutura Player (Jogador)
typedef struct{
    char nome[60];
    int score;
}Player;

//Lista Duplamente Encadeada Estruturas
typedef struct celula *Apontador;

typedef struct celula{
    Player item;
    Apontador prox, ant;
}Celula;

typedef struct{
    Apontador primeiro, ultimo;
}TipoLista;

//Arvore SBB Estrutura
typedef enum {
  Vertical, Horizontal
} Inclinacao;

typedef struct no* ApontadorNo;

typedef struct no {
  Player Reg;
  ApontadorNo Esq, Dir;
  Inclinacao BitE, BitD;
} No;

//---------------------------------- ESTRUTURAS EM GERAL - FIM ---------------------------------------------------------------------------


//--------------------------------- PROTOTIPOS DE FUNÇÕES - INICIO -----------------------------------------------------------------------

//Quick Sort Prototipos 
void Ordena(int esq, int dir, TipoLista *Lista);
void Particao(int esq, int dir, int *i, int *j, TipoLista *Lista);
void QuickSortLista( TipoLista *Lista, int tamanho);

//Tabela Hash Prototipos
void PesquisaHash(TipoLista *Hash, Player *x);
int CalculoPosicao(int x);
void PesquisaHashNome(TipoLista *Hash, Player *x);
int CalculoPosicaoNome(Player x);
void DesalocaHash (TipoLista *Hash);

//Arvore SBB Prototipos
void EE(ApontadorNo *Ap);
void ED(ApontadorNo *Ap);
void DD(ApontadorNo *Ap);
void DE(ApontadorNo *Ap);
void DesalocaArvore (ApontadorNo *Arvore);
void Inicializa(ApontadorNo *Arvore);
void EsqCurto(ApontadorNo *Ap, short *Fim);
void DirCurto(ApontadorNo *Ap, short *Fim);
void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim);

//Arvore SBB Prototipos Pesquisa por Nome do Player
void IInsere(Player x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void Insere(Player x, ApontadorNo *Ap);
void Retira(Player x, ApontadorNo *Ap);
void IRetira(Player x, ApontadorNo *Ap, short *Fim);
void Pesquisa(Player *x, ApontadorNo *p, int *achou);
void Testa1(ApontadorNo p, int nivel, int *NivelFolhas, short *PrimeiraFolha);
void Testa2(ApontadorNo p, int *NivelFolhas, short *PrimeiraFolha);
void Testa(ApontadorNo Arvore);
void Em_Ordem(ApontadorNo No);
void Pre_Ordem(ApontadorNo No);
void Pos_Ordem(ApontadorNo No);

//Arvore SBB Prototipos Pesquisa por Score
void IInsere_nome(Player x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void Insere_nome(Player x, ApontadorNo *Ap);
void IRetira_nome(Player x, ApontadorNo *Ap, short *Fim);
void Retira_nome(Player x, ApontadorNo *Ap);
void Pesquisa_nome(Player *x, ApontadorNo *p, int *achou);
void Testa1_nome(ApontadorNo p, int nivel, int *NivelFolhas, short *PrimeiraFolha);
void Testa2_nome(ApontadorNo p, int *NivelFolhas, short *PrimeiraFolha);
void Testa_nome(ApontadorNo Arvore);
void Em_Ordem_nome(ApontadorNo No);
void Pre_Ordem_nome(ApontadorNo No);
void Pos_Ordem_nome(ApontadorNo No);

//Lista Duaplemten Encadeada Prototipos
void IniciarLista (TipoLista *Lista);
int ListaVazia (TipoLista Lista);
void InserirCelula (TipoLista *Lista ,Player X);
void RetirarCelula (TipoLista *Lista, Player *X);
void ImprimeLista (TipoLista Lista);

//Quick Sort Duplamente Encadeada Prototipos
int ContarCelulas(TipoLista Lista);
void Ordena(int esq, int dir, TipoLista *Lista);
void Particao(int esq, int dir, int *i, int *j, TipoLista *Lista);
void QuickSort(TipoLista *Lista, int tamanho);

//Gravar em Arquivo Prototipo
void GravarArquivoLista(Player x);

//Diversas
void Logo();

//----------------------------- FUNÇÃO PRINCIPAL - INICIO -------------------------------------------------------------------------------

int main ()
{

    system("title Jogo Numeros da Sorte - Mikael e Mariane");
    system("color F0");

//---- GERANDO DIFERENTES SEMENTES PARA O RAND
    srand (time(NULL));

//---- VARIAVEIS COMUNS
    int pontucao, nivel, jogada, ops, posicao=0, ach =0, esc =0;

//--- VARIAVEIS CONTADORES
    int i, j, stop = 0, menu, pass, celulas = 0;

//-- VARIAVEIS PARA ARQUIVO
    FILE *score, *lista;
    char string_tmp[100], caractere[10];

//-- VARIAVEIS PARA LISTA
    Player Jogador, Player1, Play;
    TipoLista Numeros, Jogo;
    Apontador Aux;

//-- VARIAVEIS ARVORE SBB e HASH
    ApontadorNo Score_Arvore;
    ApontadorNo Nome_Arvore;
    TipoLista Score_Hash[MAX];
    TipoLista Nome_Hash[MAX];
    int pos;

//-- INICIALIZANDO LISTA DUPLAMENTE, ARVORE SBB E A TABELA HASH
     for(i=0; i<MAX; i++)
     { //TABELA HASH
        IniciarLista(&Score_Hash[i]);
        IniciarLista(&Nome_Hash[i]);
     }

    IniciarLista(&Numeros);
    IniciarLista(&Jogo);
    Inicializa(&Score_Arvore);
    Inicializa(&Nome_Arvore);
    
    Aux = Numeros.primeiro->prox;
      
//-- MENU PRINCIPAL

    Logo();
    system ("cls");

    do
    {
        for (i = 0; i< 80; i++) printf ("%c", 205);
        printf ("\t\t\t               Jogo Numeros da Sorte     \n");
        for (i = 0; i< 80; i++) printf ("%c", 205);

        printf ("\n\n(1)  Play\n\n", 228);
        printf ("(2)  Rank\n\n");
        printf ("(3)  Help\n\n");
        printf ("(4)  Developers\n\n");
        printf ("(5)  Exit\n\n");

        for (i = 0; i< 80; i++) printf ("%c", 205);

        printf ("\n\nDigite a Op%c%co do Menu que deseja acessar: ",135, 198);
        scanf ("%d", &menu);

        switch (menu)
        {
            case 1:
                    system ("cls"); //--Seleção Do Nivel
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Escolha Um Nivel de Dificuldade     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\n\n(1) Noob Master - Gerados 10 Numeros de 1 a 2\n");
                    printf ("\n(2) Very Easy - Gerados 10 Numeros de 1 a 5\n");
                    printf ("\n(3) Easy - Gerados 10 Numeros de 1 a 10\n");
                    printf ("\n(4) Normal - Gerados 10 Numeros de 1 a 50\n");
                    printf ("\n(5) Hard - Gerados 10 Numeros de 1 a 100\n");
                    printf ("\n(6) Very Hard - Gerados 10 Numeros de 1 a 300\n");
                    printf ("\n(7) Extreme - Gerados 10 Numeros de 1 a 600\n");
                    printf ("\n(8) Asian - Gerados 10 Numeros de 1 a 10.000\n\n");
                    
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    
                    printf ("\n\nDigite o numero do Nivel: ");
                    scanf ("%d", &nivel);
                    
                    ///////////////////////////////////////////////////////////////////////NIVEL NOOB MASTER
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 1)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 3;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 2: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 47; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Noob Master Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 47; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 1;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 40; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 40; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////NIVEL VERY EASY
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 2)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 6;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 5: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                   
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 45; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Very Easy Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 45; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 2;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////EASY
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 3)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 11;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 10: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                    
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 40; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Easy Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 40; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 3;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////NORMAL
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 4)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 51;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 50: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                    
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 42; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Normal Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 42; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 4;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////HARD
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 5)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 101;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 100: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                   
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 40; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Hard Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 40; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 5;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////VERY HARD
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 6)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 301;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 300: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                    
                        while (i < 10)
                        {
                    
                             if (jogada != Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 45; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Very Hard Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 45; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 6;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////EXTREME
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 7)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 601;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 600: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 43; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Extreme Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 43; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 7;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    
                    ////////////////////////////////////////////////////////////////////////////ASIAN
                    IniciarLista(&Numeros);
                    i = 0;
                    if (nivel == 8)
                    {
                         while (i < 10) //Loop que preenche com numeros aletarios a lista duplamente encadeada
                         {
                             Jogador.score = rand () % 10001;
                             InserirCelula (&Numeros, Jogador);
                             i++;
                         }
                         
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t          Jogo Numero da Sorte     \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);  
                    
                    printf ("\n\nEntre com seu Nome: ");
                    fflush(stdin);
                    gets(Player1.nome);
                    
                    printf ("\nEntre com um Numero de 1 a 10.000: ");
                    scanf  ("%d", &jogada);
                    
                    celulas = ContarCelulas(Numeros);
                    QuickSort(&Numeros, celulas);
                    
                    Aux = Numeros.primeiro;
                    
                    i = 0; //Zerando variavel para o proximo Loop
                    pass = 0;
                    
                        while (i < 10)
                        {
                    
                             if (jogada == Aux -> item.score)
                             {
                                  printf ("\n%c", 201);
                                  for (i = 0;i < 41; i++) printf ("%c", 205);
                                  printf ("%c\n%cNumero Encontrado! Nivel: Asian Completo!%c\n%c", 187,186,186, 200);
                                  for (i = 0;i < 41; i++) printf ("%c", 205);
                                  printf ("%c\n\n", 188);
                                  Player1.score = 8;
                                  pass = 1;      
                                  break;      
                             }
                             
                             Aux = Aux -> prox;
                             i++;
                       }
                      
                       if (pass != 1) 
                       {
                                printf ("\n%c", 201);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n%cNumero Nao Encontrado! Voce e Ruin Em !%c\n%c", 187, 186, 186, 200);
                                for (i = 0;i < 39; i++) printf ("%c", 205);
                                printf ("%c\n\n", 188); 
                       }
                       
                       if (pass == 1) 
                       {
                            InserirCelula (&Jogo, Player1);
                            Insere(Player1, &Score_Arvore);
                            Insere_nome(Player1, &Nome_Arvore);

                            posicao = CalculoPosicao(Player1.score);
                            InserirCelula(&Score_Hash[posicao], Player1);
                            posicao=0;

                            posicao = CalculoPosicaoNome(Player1);
                            InserirCelula(&Nome_Hash[posicao], Player1);
                            posicao=0;
                            
                            GravarArquivoLista(Player1);
                       }
                       printf ("\n\nPressione Qualquer Tecla Para Voltar ao Menu Inicial!");
                       getch();
                       system ("cls");
                       stop = 1;     
                    }
                    stop = 1;
                    system ("cls");
                    break;

            case 2:
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t                     Rank                  \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    
                    printf ("\nPesquisar Por Nome:\n\n(1) Arvore SBB\n\n(2) Hash\n");
                    printf ("\n\nPesquisar Por Score:\n\n(3) Avore SBB\n\n(4) Hash\n");
                    printf ("\n\n(5) Imprimir Rank Geral\n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\n\nDigite o Numero da Opcao: ");
                    scanf ("%d",&ops);
                    
                    //--PESQUISA POR NOME PELA SBB
                    if (ops == 1)
                    {
                            printf("\n\nDigite o nome que deseja encontrar no Rank: "); 
                            fflush(stdin);
                            gets(Play.nome);
                            fflush(stdin);
                    
                            Pesquisa_nome(&Play, &Nome_Arvore, &ach);
                       
                            if (ach == 1)
                            {
                                     printf("\n\nDeseja remove-lo?\n(1) Sim\n(2) Nao\n\nOpcao: ");
                                     scanf("%d", &esc); 
                                     fflush(stdin);
            
                                     if(esc == 1 && ach == 1)
                                     {
                                            Retira_nome(Play, &Nome_Arvore);
                                            RetirarCelula (&Jogo, &Play);
                                            Retira(Play, &Score_Arvore);
                                     }
                            }
                    }
                    
                    //--- PESQUISA POR NOME HASH
                    
                    else if (ops == 2)
                    {
                        printf("\n\nDigite o nome que deseja encontrar no Rank: ");
                        fflush(stdin);
                        gets(Player1.nome);
                        fflush(stdin);

                        posicao=CalculoPosicaoNome(Player1);
                        PesquisaHashNome(&Nome_Hash[posicao], &Player1);
                        posicao=0;        
                    }
                    
                    //--- PESQUISA POR SCORE SBB
                    
                    else if (ops == 3)
                    {
                         printf("\n\n\nDigite o Score (1 a 8) Que Deseja Encontrar No Rank: ");
                         scanf("%d", &Play.score); 
                         fflush(stdin);
                         Pesquisa(&Play, &Score_Arvore, &ach);
                         
                         if(ach==1)
                         {
                                     printf("\n\nDeseja remove-lo?\n(1) Sim\n(2) Nao\n\nOpcao: ");
                                     scanf("%d", &esc); 
                                     fflush(stdin);

                                   if(ach == 1 && esc == 1)
                                   {
                                            Retira_nome(Play, &Nome_Arvore);
                                            RetirarCelula (&Jogo, &Play);
                                            Retira(Play, &Score_Arvore);
                                   }
                          }
                      }
                      else if (ops == 4) //
                      {
                           printf("\n\n\nDigite o Score (1 a 8) Que Deseja Encontrar No Rank: ");
                           fflush(stdin);
                           scanf ("%d", &Player1.score);
                           fflush(stdin);

                           posicao=CalculoPosicao(Player1.score);
                           PesquisaHash(&Score_Hash[posicao], &Player1);
                           posicao=0;
                      }
                      else if (ops == 5) //Apenas Imprime o Rank
                      {
                           system ("cls");
                           for (i = 0; i< 80; i++) printf ("%c", 205);
                           printf ("\t\t\t                     Rank Geral                  \n");
                           for (i = 0; i< 80; i++) printf ("%c", 205);
                           printf ("\n\n");
                           
                            if(TesteListaVazia(Jogo) != 1)
                            {
                                celulas = ContarCelulas(Jogo);
                                QuickSort(&Jogo, celulas); 
                            }
                            
                            ImprimeLista (Jogo);
                      }
                    
                    getch();
                    system ("cls");
                    stop = 1;
                    break;

            case 3:
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t                     Ajuda               \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\nComo Jogar:\n\nPara jogar basta apenas jogar um numero que voce pensa que estara entre os numeros gerados aleatoriamente");
                    stop = 1;
                    getch();
                    system ("cls");
                    break;

           case 4:
                    system ("cls");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    printf ("\t\t\t                     Developers               \n");
                    for (i = 0; i< 80; i++) printf ("%c", 205);
                    
                    printf ("\n\n\n\t\t\tMikael Patrick Santos de Melo\n\n\t\t\tMariane Luyara Campos Magalhaes");
                    
                    stop = 1;
                    getch();
                    system ("cls");
                    break;
           case 5:
                    system ("cls");
                    stop = 2;
                    break;

            default:
                    system("cls");
                    printf ("\n\n\n\n\n\n\n\n\n\n\n\t\t\t%c", 201);
                    for (j = 0;j < 25; j++) printf ("%c", 205);
                    printf ("%c\n\t\t\t%cERRO: Menu Vai De 1 a 4 !%c\n\t\t\t%c", 187, 186, 186, 200);
                    for (j = 0;j < 25; j++) printf ("%c", 205);
                    printf ("%c\n\n\n\n\n\n\n\n\n\n\n", 188);
                    sleep(1000);
                    system ("cls");
                    stop = 1;
                    break;
        }

        getchar();

    }while (stop == 1);
    return 0;
}

//--- FUNÇÕES DA LISTA
void IniciarLista(TipoLista *Lista){
    Lista -> primeiro = (Apontador)malloc(sizeof(Celula));
    Lista -> primeiro -> prox = NULL;
    Lista -> primeiro -> ant = NULL;
    Lista -> ultimo = Lista -> primeiro;
}

int TesteListaVazia(TipoLista Lista){
    return(Lista.primeiro == Lista.ultimo);
}

void InserirCelula(TipoLista *Lista ,Player X){
    Apontador aux;

    aux = Lista -> ultimo;
    Lista -> ultimo -> prox = (Apontador)malloc(sizeof(Celula));
    Lista -> ultimo = Lista -> ultimo-> prox;
    Lista -> ultimo -> ant = aux;
    Lista -> ultimo ->item = X;
    Lista -> ultimo -> prox = NULL;
}

void RetirarCelula(TipoLista *Lista, Player *X){
    Apontador aux, aux2; 

    if(TesteListaVazia(*Lista) == 1){
        system("color F0");
        printf("\n\n Erro: Rank Vazio!\n\n");
        return;
    }

    aux = Lista -> primeiro -> prox;

    if(aux -> prox == NULL ){
        *X = aux -> item;
        Lista -> ultimo = Lista -> primeiro;
        free(aux);
        return;
    }

    aux2 = aux -> prox;
    *X = aux -> item;
    Lista -> primeiro -> prox = aux -> prox;
    aux2 -> ant = aux -> ant;
    free(aux);
}

void ImprimeLista (TipoLista Lista){
    Apontador aux;
    int i;

    if(TesteListaVazia(Lista) == 1){
        system("color F0");
        printf("\n\nErro: Rank Vazio!\n\n");
        return;
    }

    aux = Lista.primeiro -> prox;

    while (aux != NULL){
        printf("\nNome: %s\nScore: %d\n", aux->item.nome, aux->item.score);
        for (i = 0; i< 80; i++) printf ("%c", 205);
        aux = aux-> prox;
    }

}


//--- QUICKSORT FUNÇÕES
int ContarCelulas (TipoLista Lista){
    int i=0;
    Apontador aux;
    aux= Lista.primeiro->prox;
    while( aux!=NULL ){
        i++;
        aux=aux->prox;
   }
   return(i);
}

void QuickSort(TipoLista *Lista, int tamanho){
    Ordena(1, tamanho, Lista);
}

void Ordena(int esq, int dir, TipoLista *Lista){
    int i, j;

    Particao(esq, dir, &i, &j, Lista);

    if( esq<j){
        Ordena(esq, j, Lista);
    }
    if(i<dir){
        Ordena(i, dir, Lista);
    }
}


void Particao(int esq, int dir, int *i, int *j, TipoLista *Lista){

    int val1, val2;
    Apontador aux, aux2, aux_pivo;
    int pivo, prim,ulti, piv;
    Player tmp;

    *i=esq;
    *j=dir;

    aux=Lista->primeiro->prox;
    aux2= Lista->primeiro->prox;

    prim=1;
    while(prim != (*i)){
            aux=aux->prox;
            prim++;
    }

    ulti=1;
    while(ulti!=(*j)){
            aux2=aux2->prox;
            ulti++;
    }

    pivo = ( *i +*j )/2;

    piv=*i;
    aux_pivo = aux;
    while((piv!=pivo)){
            aux_pivo = aux_pivo ->prox;
            piv++;
        }

    pivo=aux_pivo->item.score;

    do{

        while(pivo < aux->item.score){
            (*i)++;
            aux=aux->prox;
        }

        while(pivo > aux2->item.score){
            (*j)--;
            aux2= aux2->ant;
        }
        if( (*i)<=(*j)){
            tmp = aux->item;
            aux->item = aux2->item;
            aux2->item = tmp;

            (*i)++;
            aux=aux->prox;

            (*j)--;
            aux2= aux2->ant;
        }

    }while((*i)<=(*j));

}

//--- ARVORE SBB FUNÇÕES
void DesalocaArvore(ApontadorNo *No){
    if((*No) == NULL){
       return;
    }
    DesalocaArvore(&((*No)->Esq));
    DesalocaArvore(&((*No)->Dir));
    free(*No);
    return;
}

void EE(ApontadorNo *Ap) {
  ApontadorNo Ap1;

  Ap1 = (*Ap)->Esq;
  (*Ap)->Esq = Ap1->Dir;
  Ap1->Dir = *Ap;
  Ap1->BitE = Vertical;
  (*Ap)->BitE = Vertical;
  *Ap = Ap1;
}

void ED(ApontadorNo *Ap) {
  ApontadorNo Ap1, Ap2;

  Ap1 = (*Ap)->Esq;
  Ap2 = Ap1->Dir;
  Ap1->BitD = Vertical;
  (*Ap)->BitE = Vertical;
  Ap1->Dir = Ap2->Esq;
  Ap2->Esq = Ap1;
  (*Ap)->Esq = Ap2->Dir;
  Ap2->Dir = *Ap;
  *Ap = Ap2;
}

void DD(ApontadorNo *Ap) {
  ApontadorNo Ap1;

  Ap1 = (*Ap)->Dir;
  (*Ap)->Dir = Ap1->Esq;
  Ap1->Esq = *Ap;
  Ap1->BitD = Vertical;
  (*Ap)->BitD = Vertical;
  *Ap = Ap1;
}

void DE(ApontadorNo *Ap) {
  ApontadorNo Ap1, Ap2;

  Ap1 = (*Ap)->Dir;
  Ap2 = Ap1->Esq;
  Ap1->BitE = Vertical;
  (*Ap)->BitD = Vertical;
  Ap1->Esq = Ap2->Dir;
  Ap2->Dir = Ap1;
  (*Ap)->Dir = Ap2->Esq;
  Ap2->Esq = *Ap;
  *Ap = Ap2;
}

void Inicializa(ApontadorNo *Arvore) {
  *Arvore = NULL;
}

void EsqCurto(ApontadorNo *Ap, short *Fim) {
  ApontadorNo Ap1;
  if ((*Ap)->BitE == Horizontal) {
	(*Ap)->BitE = Vertical;
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->BitD == Horizontal) {
	Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Esq = *Ap;
    *Ap = Ap1;
    if ((*Ap)->Esq->Dir->BitE == Horizontal) {
    	DE(&(*Ap)->Esq);
    	(*Ap)->BitE = Horizontal;
	}
    else
      if ((*Ap)->Esq->Dir->BitD == Horizontal) {
      	DD(&(*Ap)->Esq);
      	(*Ap)->BitE = Horizontal;
	  }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitD = Horizontal;
  if ((*Ap)->Dir->BitE == Horizontal) {
	DE(Ap);
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
	DD(Ap);
	*Fim = TRUE;
  }
}

void DirCurto(ApontadorNo *Ap, short *Fim) {
  ApontadorNo Ap1;
  if ((*Ap)->BitD == Horizontal) {
	(*Ap)->BitD = Vertical;
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->BitE == Horizontal) {
  	Ap1 = (*Ap)->Esq;
  	(*Ap)->Esq = Ap1->Dir;
  	Ap1->Dir = *Ap;
  	*Ap = Ap1;
    if ((*Ap)->Dir->Esq->BitD == Horizontal) {
		ED(&(*Ap)->Dir);
		(*Ap)->BitD = Horizontal;
	}
    else
      if ((*Ap)->Dir->Esq->BitE == Horizontal) {
		EE(&(*Ap)->Dir);
		(*Ap)->BitD = Horizontal;
	  }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitE = Horizontal;
  if ((*Ap)->Esq->BitD == Horizontal) {
  	ED(Ap);
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Esq->BitE == Horizontal) {
  	EE(Ap);
  	*Fim = TRUE;
  }
}

void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim) {
  if ((*r)->Dir != NULL) {
  	Antecessor(q, &(*r)->Dir, Fim);
    if (!*Fim)
		DirCurto(r, Fim);
    return;
  }
  q->Reg = (*r)->Reg;
  q = *r;
  *r = (*r)->Esq;
  free(q);
  if (*r != NULL)
    *Fim = TRUE;
}

//-- ARVORE SBB PESQUISA POR SCORE
void IRetira(Player x, ApontadorNo *Ap, short *Fim) {
  No *Aux;
  if (*Ap == NULL) {
    system("color F0");
	printf("\n\n\t Numero de Score Invalido ou Inexistente. \n");
	*Fim = TRUE;
	return;
	}
  if (x.score < (*Ap)->Reg.score) {
  	IRetira(x, &(*Ap)->Esq, Fim);
    if (!*Fim)
		EsqCurto(Ap, Fim);
    return;
  }
  if (x.score > (*Ap)->Reg.score) {
  	IRetira(x, &(*Ap)->Dir, Fim);
    if (!*Fim)
		DirCurto(Ap, Fim);
    return;
  }
  *Fim = FALSE;
  Aux = *Ap;
  if (Aux->Dir == NULL) {
	*Ap = Aux->Esq;
    free(Aux);
    if (*Ap != NULL)
      *Fim = TRUE;
    return;
  }
  if (Aux->Esq == NULL) {
	*Ap = Aux->Dir;
	free(Aux);
    if (*Ap != NULL)
	  *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->Esq, Fim);
  if (!*Fim)
	EsqCurto(Ap, Fim);
}

void IInsere(Player x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim) {
  if (*Ap == NULL) {
  	*Ap = (ApontadorNo)malloc(sizeof(No));
    *IAp = Horizontal;
    (*Ap)->Reg = x;
    (*Ap)->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    (*Ap)->Esq = NULL;
    (*Ap)->Dir = NULL;
    *Fim = FALSE;
    return;
  }
  if (x.score < (*Ap)->Reg.score) {
  	IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
    if (*Fim)
		return;
    if ((*Ap)->BitE != Horizontal) {
    	*Fim = TRUE;
    	return;
	}
    if ((*Ap)->Esq->BitE == Horizontal) {
    	EE(Ap);
    	*IAp = Horizontal;
    	return;
	}
    if ((*Ap)->Esq->BitD == Horizontal) {
    	ED(Ap);
    	*IAp = Horizontal;
	}
    return;
  }
  IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
  if (*Fim)
	return;
  if ((*Ap)->BitD != Horizontal) {
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
  	DD(Ap);
  	*IAp = Horizontal;
  	return;
  }
  if ((*Ap)->Dir->BitE == Horizontal) {
  	DE(Ap);
  	*IAp = Horizontal;
  }
}

void Insere(Player x, ApontadorNo *Ap) {
  short Fim;
  Inclinacao IAp;
  IInsere(x, Ap, &IAp, &Fim);
}

void Retira(Player x, ApontadorNo *Ap) {
  short Fim;
  IRetira(x, Ap, &Fim);
}

void Pesquisa(Player *x, ApontadorNo *p, int *achou) {
    int i;
  if (*p == NULL) {
    system("color F0");
  	printf("\n\n\Erro: Registro nao encontrado!\n");
    achou=0;
    return;
  }

  if (x->score < (*p)->Reg.score) {
  	Pesquisa(x, &(*p)->Esq, achou);
    return;
  }

  if (x->score > (*p)->Reg.score)
	Pesquisa(x, &(*p)->Dir, achou);
  else
    *x = (*p)->Reg;

    if( x->score == (*p)->Reg.score){
        printf("\n\nRegistro Encontrado: \n");
        printf("\nNome: %s",x->nome);
        printf ("\nScore: %d",x->score);
        *achou=1;
        return;
    }
}

void Testa1(ApontadorNo p, int nivel, int *NivelFolhas, short *PrimeiraFolha) {
  if (p == NULL)
	return;
  if (*PrimeiraFolha)
	if (*NivelFolhas < nivel)
	  *NivelFolhas = nivel;
	if (p->Esq == NULL && p->Dir == NULL) {
	  if (*PrimeiraFolha == TRUE)
		*PrimeiraFolha = FALSE;
	  else {
		if (nivel != *NivelFolhas) {
          system("color 4f");
		  printf("\n\n\t Erro: Folhas em niveis diferentes. \n");
		  exit(1);
		}
	  }
	}
  if (p->BitE == Horizontal)
	Testa1(p->Esq, nivel, NivelFolhas, PrimeiraFolha);
  else
    Testa1(p->Esq, nivel + 1, NivelFolhas, PrimeiraFolha);
  if (p->BitD == Horizontal)
	Testa1(p->Dir, nivel, NivelFolhas, PrimeiraFolha);
  else
    Testa1(p->Dir, nivel + 1, NivelFolhas, PrimeiraFolha);
}

void Testa2(ApontadorNo p, int *NivelFolhas, short *PrimeiraFolha) {
  if (p == NULL)
	return;
  if (p->Esq != NULL) {
  	if (p->Reg.score < p->Esq->Reg.score) {
  	  system("color F0");
	  printf("\n Erro: %d < que filho a esquerda \n", p->Reg.score);
      exit(1);
    }
    Testa2(p->Esq, NivelFolhas, PrimeiraFolha);
  }
  if (p->Dir == NULL)
	return;
  if (p->Reg.score > p->Dir->Reg.score) {
    system("color F0");
  	printf("\n Erro: %d > que filho a direita \n", p->Reg.score);
    exit(1);
  }
  Testa2(p->Dir, NivelFolhas, PrimeiraFolha);
}

void Testa(ApontadorNo Arvore) {
  int NivelFolhas = 0;
  short PrimeiraFolha = TRUE;
  Testa1(Arvore, 1, &NivelFolhas, &PrimeiraFolha);
  Testa2(Arvore, &NivelFolhas, &PrimeiraFolha);
}

void Em_Ordem(ApontadorNo No){
    if(No == NULL)
       return;
    Em_Ordem(No->Esq);
    printf("\n%d", No->Reg.score);
    Em_Ordem(No->Dir);
    return;
}

void Pre_Ordem(ApontadorNo No){
    if(No == NULL)
       return;
    printf("\n%d", No->Reg.score);
    Pre_Ordem(No->Esq);
    Pre_Ordem(No->Dir);
    return;
}

void Pos_Ordem(ApontadorNo No){
    if(No == NULL)
       return;
    Pos_Ordem(No->Esq);
    Pos_Ordem(No->Dir);
    printf("\n%d", No->Reg.score);
    return;
}

//--- ARVORE SBB PARA PESQUISA POR NOME
void IInsere_nome(Player x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim) {
  if (*Ap == NULL) {
  	*Ap = (ApontadorNo)malloc(sizeof(No));
    *IAp = Horizontal;
    (*Ap)->Reg = x;
    (*Ap)->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    (*Ap)->Esq = NULL;
    (*Ap)->Dir = NULL;
    *Fim = FALSE;
    return;
  }

  if (strcmpi(x.nome,(*Ap)->Reg.nome)> 0) {
  	IInsere_nome(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
    if (*Fim)
		return;
    if ((*Ap)->BitE != Horizontal) {
    	*Fim = TRUE;
    	return;
	}
    if ((*Ap)->Esq->BitE == Horizontal) {
    	EE(Ap);
    	*IAp = Horizontal;
    	return;
	}
    if ((*Ap)->Esq->BitD == Horizontal) {
    	ED(Ap);
    	*IAp = Horizontal;
	}
    return;
  }

  IInsere_nome(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
  if (*Fim)
	return;
  if ((*Ap)->BitD != Horizontal) {
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
  	DD(Ap);
  	*IAp = Horizontal;
  	return;
  }
  if ((*Ap)->Dir->BitE == Horizontal) {
  	DE(Ap);
  	*IAp = Horizontal;
  }
}

void Insere_nome(Player x, ApontadorNo *Ap) {
  short Fim;
  Inclinacao IAp;
  IInsere_nome(x, Ap, &IAp, &Fim);
}

void IRetira_nome(Player x, ApontadorNo *Ap, short *Fim) {
  No *Aux;
  if (*Ap == NULL) {
    system("cls");
    system("color F0");
	printf("\n\nErro: Registro Nao Presente no Rank\n");
	*Fim = TRUE;
	return;
	}
	
  if (strcmpi(x.nome,(*Ap)->Reg.nome)>0) {
  	IRetira_nome(x, &(*Ap)->Esq, Fim);
    if (!*Fim)
		EsqCurto(Ap, Fim);
    return;
  }

  if (strcmpi(x.nome, (*Ap)->Reg.nome)<0) {
  	IRetira_nome(x, &(*Ap)->Dir, Fim);
    if (!*Fim)
		DirCurto(Ap, Fim);
    return;
  }

  *Fim = FALSE;
  Aux = *Ap;
  if (Aux->Dir == NULL) {
	*Ap = Aux->Esq;
    free(Aux);
    if (*Ap != NULL)
      *Fim = TRUE;
    return;
  }
  if (Aux->Esq == NULL) {
	*Ap = Aux->Dir;
	free(Aux);
    if (*Ap != NULL)
	  *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->Esq, Fim);
  if (!*Fim)
	EsqCurto(Ap, Fim);
}

void Retira_nome(Player x, ApontadorNo *Ap) {
  short Fim;
  IRetira_nome(x, Ap, &Fim);
}

void Pesquisa_nome(Player *x, ApontadorNo *p, int *achou) {
  int i;
  if (*p == NULL) {
    system("color F0");
    system("cls");
  	printf("\n\nErro: Registro Nao Presente no Rank\n");
  	achou=0;
    return;
  }

  if (strcmpi(x->nome, (*p)->Reg.nome)>0) {
  	Pesquisa_nome(x, &(*p)->Esq, achou);
    return;
  }
  if (strcmpi(x->nome, (*p)->Reg.nome)<0)
	Pesquisa_nome(x, &(*p)->Dir, achou);
  else
    *x = (*p)->Reg;

    if( strcmpi(x->nome,(*p)->Reg.nome) == 0){
        printf("\nRegistro encontrado: \n");
        printf("\nNome: %s",x->nome);
        printf("\nScore: %d\t",x->score);
        
        *achou=1;
    }
}

void Testa1_nome(ApontadorNo p, int nivel, int *NivelFolhas, short *PrimeiraFolha) {
  if (p == NULL)
	return;
  if (*PrimeiraFolha)
	if (*NivelFolhas < nivel)
	  *NivelFolhas = nivel;
	if (p->Esq == NULL && p->Dir == NULL) {
	  if (*PrimeiraFolha == TRUE)
		*PrimeiraFolha = FALSE;
	  else {
		if (nivel != *NivelFolhas) {
		  system("color F0");
		  printf("\n Erro: Folhas em niveis diferentes. \n");
		  exit(1);
		}
	  }
	}
  if (p->BitE == Horizontal)
	Testa1_nome(p->Esq, nivel, NivelFolhas, PrimeiraFolha);
  else
    Testa1_nome(p->Esq, nivel + 1, NivelFolhas, PrimeiraFolha);
  if (p->BitD == Horizontal)
	Testa1_nome(p->Dir, nivel, NivelFolhas, PrimeiraFolha);
  else
    Testa1_nome(p->Dir, nivel + 1, NivelFolhas, PrimeiraFolha);
}

void Testa2_nome(ApontadorNo p, int *NivelFolhas, short *PrimeiraFolha) {
  if (p == NULL)
	return;
  if (p->Esq != NULL) {
  	if (strcmpi(p->Reg.nome,p->Esq->Reg.nome)>0) {
  	  system("color F0");
	  printf("\n Erro: %d < que filho a esquerda. \n", p->Reg.nome);
      exit(1);
    }
    Testa2_nome(p->Esq, NivelFolhas, PrimeiraFolha);
  }
  if (p->Dir == NULL)
	return;
  if (strcmpi(p->Reg.nome, p->Dir->Reg.nome)<0) {
    system("color F0");
  	printf("\n Erro: %d > que filho a direita. \n", p->Reg.nome);
    exit(1);
  }
  Testa2_nome(p->Dir, NivelFolhas, PrimeiraFolha);
}

void Testa_nome(ApontadorNo Arvore) {
  int NivelFolhas = 0;
  short PrimeiraFolha = TRUE;
  Testa1_nome(Arvore, 1, &NivelFolhas, &PrimeiraFolha);
  Testa2_nome(Arvore, &NivelFolhas, &PrimeiraFolha);
}

void Em_Ordem_nome(ApontadorNo No){
    if(No == NULL)
       return;
    Em_Ordem_nome(No->Esq);
    printf("\n%s", No->Reg.nome);
    Em_Ordem_nome(No->Dir);
    return;
}

void Pre_Ordem_nome(ApontadorNo No){
    if(No == NULL)
       return;
    printf("\n%s", No->Reg.nome);
    Pre_Ordem_nome(No->Esq);
    Pre_Ordem_nome(No->Dir);
    return;
}

void Pos_Ordem_nome(ApontadorNo No){
    if(No == NULL)
       return;
    Pos_Ordem_nome(No->Esq);
    Pos_Ordem_nome(No->Dir);
    printf("\n%s", No->Reg.nome);
    return;
}

//--- TABELA HASH FUNÇÕES
void PesquisaHash(TipoLista *Hash, Player *x){
    Apontador aux;
    int i;

    if(TesteListaVazia(*Hash) == 1){
        system("cls");
        system("color F0");
        printf("\nPosicao vazia\n");
        return;
    }
    aux = Hash->primeiro->prox;

    while(aux != NULL){

        if(aux->item.score == (*x).score){
            *x = aux -> item;

            printf("\nNome: %s",x->nome);
            printf("\nSocre: %d",x->score);

            return;
        }
        aux = aux -> prox;
    }
    system("cls");
    system("color 4f");
    printf("\nPosicao vazia. \n");
}

int CalculoPosicao(int x){
    int posicao;

    posicao = (x%MAX);
    return(posicao);
}

void DesalocaHash(TipoLista *Hash){
    Apontador aux, aux2;

    if( (TesteListaVazia(*Hash) == 1))
        return;

        aux = Hash->ultimo;
        aux2 = aux -> ant;

        while ( aux2 != Hash -> primeiro ){
            Hash -> ultimo = aux2;
            aux2 = aux2 -> ant;
            free(aux);
            aux = Hash -> ultimo;
        }
        Hash-> ultimo = aux2;
        free(aux);
        aux2 = NULL;
}

int CalculoPosicaoNome(Player x){
    int i, posicao;
    i = atoi(x.nome);
    posicao=i%MAX;
    return(posicao);
}

void PesquisaHashNome(TipoLista *Hash, Player *x){
    Apontador aux;
    int i;

    if(TesteListaVazia(*Hash) == 1){
        system("cls");
        printf("\nErro: Rank Vazio\n");
        return;
    }

    aux = Hash->primeiro->prox;

    while(aux != NULL){


        if(strcmpi(aux->item.nome,(*x).nome)==0){
            *x = aux -> item;

            printf("\nNome: %s",x->nome);
            printf("\nSocre: %d",x->score);
            return;
        }
        aux = aux -> prox;
    }
    system("cls");
    system("color 4f");
    printf("\nPosicao vazia\n");
}

//--- GRAVANDO EM ARQUIVO
void GravarArquivoLista(Player x){
    FILE *arquivo;
    int i;

    fflush(stdin);

    if((arquivo=fopen("Ficha dos Candidatos.txt","a"))!=NULL){

        fprintf(arquivo,"\n%s",x.nome);
        fprintf(arquivo,"\n%d",x.score);
        
        fclose(arquivo);
        return;
    }
    printf("\n Ocorreu Um Erro Inesperado e Seu Score Nao Pode Ser Salvo!\n");
    return;
}

//--LOGO
void Logo ()
{            
printf ("\t\t     J O G O   N U M E R O S  D A\n\n");                                                    
                                                                   
                                                                   
printf ("            #####     ######   #######. ######### #########\n");         
printf ("           #######   ########  ######## ######### #########\n");         
printf ("          #### #### #### ####  ###  ### ######### ###\n");          
printf ("          ####  ### ###   #### ###   ###   ###    ###\n");             
printf ("          #######  ###     ### #########   ###    ########\n");       
printf ("           ####### ###     ### ########    ###    ########\n");        
printf ("              ##### ##     ### #######     ###    ###\n");          
printf ("          ###   ### ###   #### ### ####    ###    ###\n");               
printf ("          #### #### #### ##### ###  ###    ###    #########\n");         
printf ("           ########  ########  ###  ####   ###    #########\n");        
printf ("            ######    ######   ###   ###   ###    #########");   

printf ("\n\n\n\t       Presione Qualquer Tecla Para Continuar");
getch();  
}
