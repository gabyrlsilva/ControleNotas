#include <time.h>

struct data
{
    char dia;
    char mes;
    short ano;
};
typedef struct data TData;


int e_bissexto(short ano)
{
    return ano%4 == 0 && (ano%100 != 0 || ano%400 == 0);
}

int compara_data(const void *a, const void *b)
{
    TData *d1 = (TData *) a;
    TData *d2 = (TData *) b;
    if(d1->ano != d2->ano)
        return d1->ano - d2->ano;
    else
        if(d1->mes != d2->mes)
            return d1->mes - d2->mes;
        else
            return d1->dia - d2->dia;
}

void mais_um_dia(TData *data)
{
    int ndm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(e_bissexto(data->ano))
        ndm[2] = 29;
    data->dia++;
    if(data->dia > ndm[(int)data->mes])
    {
        data->dia = 1;
        data->mes++;
        if(data->mes > 12)
        {
            data->mes = 1;
            data->ano++;
        }
    }
}

unsigned no_dias_desde_1_1_1900(TData d)
{
    int ndm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(e_bissexto(d.ano))
        ndm[2] = 29;
    unsigned nd = 0;
    short ano = 1900;
    char mes = 1;

    while(ano < d.ano)
    {
        if(e_bissexto(ano))
            nd = nd + 366;
        else
            nd = nd + 365;
        ano++;
    }

    while(mes < d.mes)
    {
        nd = nd + ndm[(int)mes];
        mes++;
    }

    return nd + d.dia - 1;
}

int dia_da_semana(TData d)
{
    return no_dias_desde_1_1_1900(d)%7;
}

TData no_dias_para_data(unsigned nd)
{
    TData d;
    int nda = 365;
    int ndm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    d.ano = 1900;
    while(nd >= nda)
    {
        nd = nd - nda;
        d.ano++;
        if(e_bissexto(d.ano))
            nda = 366;
        else
            nda = 365;
    }
    d.mes = 1;
    if(e_bissexto(d.ano))
        ndm[2] = 29;
    while(nd >= ndm[(int)d.mes])
    {
        nd = nd - ndm[(int)d.mes];
        d.mes++;
        if(d.mes > 12)
            d.mes = 1;
    }
    d.dia = nd + 1;
    return d;
}

TData soma_dias(TData d, int nd)
{
    int i;
    for(i=0; i<nd; i++)
        mais_um_dia(&d);
    return d;
}

TData diminui_dias(TData d, int nd)
{
    return no_dias_para_data(no_dias_desde_1_1_1900(d)-nd);
}

int num_dias_entre(TData d1, TData d2)
{
    return no_dias_desde_1_1_1900(d2) - no_dias_desde_1_1_1900(d1);
}

TData data_atual()
{
    TData d;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    d.dia = tm.tm_mday;
    d.mes = tm.tm_mon+1;
    d.ano = tm.tm_year+1900;
    return d;
}

TData le_data()
{
    TData res;
    scanf("%d/%d/%d", &res.dia, &res.mes, &res.ano);
    return res;
}

void mostre_data(TData d)
{
    printf("%02d/%02d/%d", d.dia, d.mes, d.ano);
}

void mostre_data_ext(TData d)
{
    char nm[][10] = {"","janeiro","fevereiro","mar\x87o","abril","maio","junho",
            "julho","agosto","setembro","outubro","novembro","dezembro"};
    char nds[][20] = {"segunda-feira","ter\x87 \ba-feira","quarta-feira",
        "quinta-feira","sexta-feira","s\xa0 \bbado","domingo"};
    printf("%2d de %s de %d, %s", d.dia, nm[(int)d.mes], d.ano, nds[dia_da_semana(d)]);
}
