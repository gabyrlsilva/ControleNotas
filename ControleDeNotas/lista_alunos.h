struct lista_alunos
{
    int nal;
    TAluno lis_alu[200];
};
typedef struct lista_alunos TListaAlunos;

void insere_aluno(TListaAlunos *lis, TAluno alu)
{
    lis->lis_alu[lis->nal] = alu;
    lis->nal++;
}

void mostre_lis_alu(TListaAlunos *lis)
{
    int i;
    printf("\n------ ------------------------------ ---------- ----- ----- -----\n");
    printf("C%cDIGO NOME                           DATA NASC   AP1   AP2  M%cDIA\n",224,144);
    printf("------ ------------------------------ ---------- ----- ----- -----\n");
    for(i=0; i<lis->nal; i++)
    {
        mostre_aluno(lis->lis_alu[i]);
        printf("\n");
    }
    printf("\n");
}



