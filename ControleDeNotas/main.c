#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "aluno.h"
#include "lista_alunos.h"

void gera_nome(char *nom) {
    // 40 nomes
    char nomes[][12] = {"Aline", "Ana", "Beatriz", "Bernardo", "Bruno", "Camila", "Carlos", "Cec\xa1lia",
         "Davi", "Eduardo", "Felipe", "Francisco", "Gabriel", "G\x82rson", "Heitor", "Henrique",
         "Ingrid", "Isabela", "J\xa3lia", "Larissa", "Laura", "Leonardo", "Lorena", "Marcelo",
         "M\xa0rcia", "Marcos", "Mariana", "Milena", "Patricia", "Pedro", "Priscila", "Renato",
         "Ricardo", "Rodrigo", "Ronaldo", "Samuel", "S\x82rgio", "Sofia", "Tiago", "Vinicius"};
    // 78 sobrenomes
    char sobrenomes[][15] = {"Abreu", "Albuquerque", "Almeida", "Alencar", "Alves", "Amaral", "Amorim",
          "Andrade", "Antunes", "Arantes", "Ara\xa3jo", "Arruda", "Azevedo", "Barros",
          "Bastos", "Batista", "Bezerra", "Brand\xc6o", "Brito", "Cabral", "Campos",
          "Cardoso", "Carneiro", "Carvalho", "Castro", "Cavalcante", "Chagas", "Chaves",
          "Correia", "Costa", "Cruz", "Dantas", "Diniz", "Duarte", "Esteves", "Fagundes",
          "Fernandes", "Ferraz", "Ferreira", "Figueiredo", "Fonseca", "Franco", "Freire",
          "Freitas", "Furtado", "Gomes", "Goncalves", "Guedes", "Guerra", "Guimaraes",
          "Liberato", "Marinho", "Marques", "Martins", "Medeiros", "Melo", "Menezes",
          "Monteiro", "Montenegro", "Moraes", "Moreira", "Moura", "Nogueira", "Noronha",
          "Novaes", "Oliveira", "Pereira", "Pinto", "Resende", "Ribeiro", "Rios",
          "Sampaio", "Santana", "Santos", "Torres", "Trindade", "Vasconcelos", "Vargas"};

    strcpy(nom, nomes[rand()%40]);
    strcat(nom, " ");
    int sn1 = rand()%78;
    int sn2 = rand()%78;
    while(sn1 == sn2)
        sn2 = rand()%78;
    strcat(nom, sobrenomes[sn1]);
    strcat(nom, " ");
    strcat(nom, sobrenomes[sn2]);
}

TData gera_data()
{
    int ndm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    TData d;
    d.ano = 1980 + rand()%21;
    if(e_bissexto(d.ano))
        ndm[2] = 29;
    d.mes = 1+rand()%12;
    d.dia = 1+rand()%ndm[(int)d.mes];
    return d;
}

TAluno gera_aluno(int cod)
{
    TAluno alu;
    char na[41];
    alu.codigo = cod;
    gera_nome(na);
    strcpy(alu.nome, na);
    alu.nascimento = gera_data();
    alu.ap1 = (50+rand()%51) / 10.0;
    alu.ap2 = (50+rand()%51) / 10.0;
    return alu;
}

TListaAlunos gera_lis_aluno(int nal)
{
    TListaAlunos la;
    int i;
    for(i=0; i<nal; i++)
        insere_aluno(&la, gera_aluno(i+1));
    return la;
}

char menu_principal()
{
    printf("\n********************************\n");
    printf("* SISTEMA DE CONTROLE DE NOTAS *\n");
    printf("********************************\n");
    printf("  1 - Listar de alunos\n");
    printf("  2 - Matricular alunos\n");
    printf("  3 - Buscar pelo nome\n");
    printf("  0 - Sair do aplicativo\n\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);
    return getchar();
}

char menu_listagem()
{
    printf("\n********************************\n");
    printf("*      LISTAGEM DE ALUNOS      *\n");
    printf("********************************\n");
    printf("  1 - Ordenados pelo c%cdigo\n",162);
    printf("  2 - Ordenados pelo nome\n");
    printf("  3 - Ordenados pela idade\n");
    printf("  4 - Ordenados pela m%cdia\n",130);
    printf("  0 - Voltar ao menu principal\n\n");
    printf("  ESCOLHA UM OP%c%cO: ",128,199);
    return getchar();
}


int main()
{
    srand(time(NULL));
    FILE *fp;
    TListaAlunos la;
    la.nal = 0;
    int alterado = 0;
    TAluno alu;
    char op, op2;
    unsigned pro_cod;
    fp = fopen("alunos.arq", "rb");
    fread(&pro_cod, sizeof(unsigned), 1, fp);
    fread(&la.nal, sizeof(int), 1, fp);
    fread(la.lis_alu, sizeof(TAluno), la.nal, fp);
    fclose(fp);
//    pro_cod = 21;
//    la = gera_lis_aluno(20);

    while(1) {
        op = menu_principal();
        printf("\n");
        if(op == '0') {
            if(alterado)
            {
                printf("Arquivo alterado. Deseja salva-lo (S/N): ");
                op = getchar();
                while(op != 'S' && op != 's' && op != 'N' && op != 'n');
                {
                    printf("\n  Digite S ou N: ");
                    op = getchar();
                }
                if(op == 'S' || op == 's') {
                    fp = fopen("alunos.arq", "wb");
                    fwrite(&pro_cod, sizeof(int), 1, fp);
                    fwrite(&la.nal, sizeof(int), 1, fp);
                    fwrite(la.lis_alu, sizeof(TAluno), la.nal, fp);
                    fclose(fp);
                }
            }
            break;
        }
        switch(op)
        {
            case '1':
                while(1) {
                    op2 = menu_listagem();
                    if(op2 == '0')
                        break;
                    switch(op2)
                    {
                        case '1':
                            printf("\n\n------------------------------------------------------------------");
                            printf("\n       Lista de alunos ordenados pelo c%cdigo",162);
                            qsort(la.lis_alu, la.nal, sizeof(TAluno), compara_codigo);
                            mostre_lis_alu(&la);
                            printf("------------------------------------------------------------------\n\n");
                            break;
                        case '2':
                            printf("\n\n------------------------------------------------------------------");
                            printf("\n       Lista de alunos ordenados pelo nome");
                            qsort(la.lis_alu, la.nal, sizeof(TAluno), compara_nome);
                            mostre_lis_alu(&la);
                            printf("------------------------------------------------------------------\n\n");
                            break;
                        case '3':
                            printf("\n\n------------------------------------------------------------------");
                            printf("\n       Lista de alunos ordenados pela idade");
                            qsort(la.lis_alu, la.nal, sizeof(TAluno), compara_nasc);
                            mostre_lis_alu(&la);
                            printf("------------------------------------------------------------------\n\n");
                            break;
                        case '4':
                            printf("\n\n------------------------------------------------------------------");
                            printf("\n       Lista de alunos ordenados pela m%cdia",130);
                            qsort(la.lis_alu, la.nal, sizeof(TAluno), compara_media);
                            mostre_lis_alu(&la);
                            printf("------------------------------------------------------------------\n\n");
                            break;
                        default:
                            printf("\n\n  Op%c%co Inv%clida\n\n",135,198,160);
                    }
                }
                break;
            case '2':
                printf("\n  Nome: ");
                alu.codigo = pro_cod;
                fflush(stdin);
                puts(alu.nome);
                printf("  Data de nascimento (dd/mm/aaaa): ");
                alu.nascimento = le_data();
                alu.ap1 = 11.0;
                alu.ap2 = 11.0;
                insere_aluno(&la, alu);
                pro_cod++;
                alterado = 1;
                break;
            case '3':
                break;
            default:
                printf("Entrada inv%clida\n\n",160);
        }
        printf("\n\n");
    }

    return 0;
}











