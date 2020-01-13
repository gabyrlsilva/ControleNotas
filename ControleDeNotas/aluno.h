struct aluno
{
    unsigned codigo;
    char nome[41];
    TData nascimento;
    float ap1;
    float ap2;
};
typedef struct aluno TAluno;


float media(TAluno alu)
{
    return (2*alu.ap1 + 3*alu.ap2)/ 5;
}

int compara_nome(const void *a, const void *b)
{
    TAluno *alu1 = (TAluno *) a;
    TAluno *alu2 = (TAluno *) b;
    return strcmp(alu1->nome, alu2->nome);
}

int compara_codigo(const void *a, const void *b)
{
    TAluno *alu1 = (TAluno *) a;
    TAluno *alu2 = (TAluno *) b;
    return alu1->codigo - alu2->codigo;
}

int compara_nasc(const void *a, const void *b)
{
    TAluno *alu1 = (TAluno *) a;
    TAluno *alu2 = (TAluno *) b;
    return compara_data(&alu1->nascimento, &alu2->nascimento);
}

int compara_media(const void *a, const void *b)
{
    TAluno *alu1 = (TAluno *) a;
    TAluno *alu2 = (TAluno *) b;
    if(media(*alu1) < media(*alu2))
        return 1;
    else
        return -1;
}

void mostre_aluno(TAluno alu)
{
    if(strlen(alu.nome) > 30)
        alu.nome[30] = '\0';

    printf("%06u %-30s %02d/%02d/%d ",alu.codigo, alu.nome,
           alu.nascimento.dia, alu.nascimento.mes, alu.nascimento.ano);
    if(alu.ap1 < 10.5)
        printf("%5.1f ", alu.ap1);
    else
        printf("      ");
    if(alu.ap2 < 10.5)
        printf("%5.1f ", alu.ap2);
    else
        printf("      ");
    if(alu.ap1 < 10.5 && alu.ap2 < 10.5)
        printf("%5.1f ", media(alu));

}







