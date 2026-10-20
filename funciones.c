#include "funciones.h"
//Ejer 1
int leerArchivoTransferencias(Operacion v[])
{
    FILE *f = fopen(RUTAT, "r");
    if (f == NULL) { printf("No se pudo abrir el archivo\n"); return 0; }

    char linea[256];
    char campos[6][64];
    int n = 0;

    fgets(linea, sizeof(linea), f);
    while (n < MAX && fgets(linea, sizeof(linea), f) != NULL) {
        separar(linea, campos);

        v[n].anio = 0; v[n].trimestre = 0; v[n].monto = 0;
        sscanf(campos[0], "%d", &v[n].anio);
        sscanf(campos[1], "%d", &v[n].trimestre);
        sscanf(campos[5], "%f",  &v[n].monto);

        if (strlen(campos[2]) == 0) strcpy(v[n].paisCod, "??");
        else                        strcpy(v[n].paisCod, campos[2]);
        if (strlen(campos[3]) == 0) strcpy(v[n].paisDesc, "SIN_DATO");
        else                        strcpy(v[n].paisDesc, campos[3]);
        if (strlen(campos[4]) == 0) v[n].operacion = '?';
        else                        v[n].operacion = campos[4][0];
        n++;
    }
    fclose(f);
    return n;
}

void separar(char *linea, char campos[][64])
{
    char *p = strchr(linea, '\n');
    if (p != NULL) *p = '\0';
    p = strchr(linea, '\r');
    if (p != NULL) *p = '\0';

    char *inicio = linea;
    for (int c = 0; c < 6; c++) {
        char *fin = strchr(inicio, ';');
        if (fin == NULL) fin = inicio + strlen(inicio);
        int largo = fin - inicio;
        if (largo > 63) largo = 63;
        strncpy(campos[c], inicio, largo);
        campos[c][largo] = '\0';
        if (*fin == '\0') {
            for (int j = c + 1; j < 6; j++) campos[j][0] = '\0';
            break;
        }
        inicio = fin + 1;
    }
}


void mostrar(Operacion v[], int cant)
{
    for (int i = 0; i < cant; i++)
        printf("%d | T%d | %s | %s | %c | %.2f\n",
               v[i].anio, v[i].trimestre, v[i].paisCod,
               v[i].paisDesc, v[i].operacion, v[i].monto);
}


int FuncionAgruparPais(Operacion ops [], int  cant, OperacionTotales AgrupadoXpais[])
{
   int x=0;
   int pos = 0;
   Operacion aux [MAX];


    for (x = 0; x < cant; x++)
    {
      aux[x] = ops[x];
    }


    for (x = 0; x < cant; x++)
    {
        if (strcmp(aux[x].paisDesc, "null") != 0)      /* todavia no fue leido */
        {
            float acumCredito = 0;
            float acumDebito  = 0;
            int cantReg = 0;

            for (int z = x; z < cant; z++)             /* arranca en x: cuenta al propio registro */
            {
                if (strcmp(aux[x].paisDesc, aux[z].paisDesc) == 0)
                {
                    cantReg++;
                    if (aux[z].operacion == 'C') acumCredito += aux[z].monto;
                    else                         acumDebito  += aux[z].monto;

                    if (z != x) strcpy(aux[z].paisDesc, "null");
                }
            }

            strcpy(AgrupadoXpais[pos].paisCod,  aux[x].paisCod);
            strcpy(AgrupadoXpais[pos].paisDesc, aux[x].paisDesc);
            AgrupadoXpais[pos].registros    = cantReg;
            AgrupadoXpais[pos].totalCredito = acumCredito;
            AgrupadoXpais[pos].totalDebito  = acumDebito;
            pos++;
        }

}
    return pos;
}
void ordenarPorMonto(OperacionTotales v[], int cant )

{
    OperacionTotales aux;

    for (int i = 0; i < cant - 1; i++)              /* pasadas */
    {
        for (int j = 0; j < cant - 1 - i; j++)      /* compara vecinos */
        {
            if (v[j].totalCredito < v[j+1].totalCredito)
            {
                aux    = v[j];                      /* intercambio de a tres */
                v[j]   = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}


void mostrarTotales(OperacionTotales v[], int cant)
{
    printf("%-5s %-30s %9s %14s %14s\n", "COD", "PAIS", "REGISTROS", "CREDITO", "DEBITO");
    for (int i = 0; i < cant; i++)
        printf("%-5s %-30s %9d %14.2f %14.2f\n",
               v[i].paisCod, v[i].paisDesc, v[i].registros, v[i].totalCredito, v[i].totalDebito);
}
//Ejer 2
int leerArchivoContinente(Continente v[])

{
  FILE *f = fopen(RUTAC, "r");
    if (f == NULL) { printf("No se pudo abrir el archivo\n"); return 0; }

    char linea[256];
    char campos[6][64];
    int n = 0;

    fgets(linea, sizeof(linea), f);
    while (n < MAXC && fgets(linea, sizeof(linea), f) != NULL) {
        separarC(linea, campos);


        if (strlen(campos[0]) == 0) strcpy(v[n].paisCod, "??");
        else                        strcpy(v[n].paisCod, campos[0]);
        if (strlen(campos[1]) == 0) strcpy(v[n].paisDesc, "SIN_DATO");
        else                        strcpy(v[n].paisDesc, campos[1]);
        if (strlen(campos[2]) == 0) strcpy(v[n].continente, "SIN_DATO");
        else                        strcpy(v[n].continente, campos[2]);
        n++;
    }
    fclose(f);
    return n;



}
void separarC(char *linea, char campos[][64])
{
    char *p = strchr(linea, '\n');
    if (p != NULL) *p = '\0';
    p = strchr(linea, '\r');
    if (p != NULL) *p = '\0';

    char *inicio = linea;
    for (int c = 0; c < 3; c++) {
        char *fin = strchr(inicio, ';');
        if (fin == NULL) fin = inicio + strlen(inicio);
        int largo = fin - inicio;
        if (largo > 63) largo = 63;
        strncpy(campos[c], inicio, largo);
        campos[c][largo] = '\0';
        if (*fin == '\0') {
            for (int j = c + 1; j < 3; j++) campos[j][0] = '\0';
            break;
        }
        inicio = fin + 1;
    }
}


void mostrarContinentes(Continente v[], int cantPaises)
{
    for (int i = 0; i < cantPaises; i++)
        printf("%s | %s | %s \n",
              v[i].paisCod, v[i].paisDesc, v[i].continente);
}

int CrearVectorConContinente(Continente v[], OperacionTotales AgrupadoXpais [],int cant, int cantContinente, ContinenteConOperaciones vContXop[])

{
    int num = 0;
    int existe=0;


    for (int i = 0; i < cant; i++)
    {

        for (int j = 0; j < cantContinente; j++)
        {

            if(strcmp(AgrupadoXpais[i].paisDesc, v[j].paisDesc)==0)

              {

               for(int k = 0; k < num; k++)

                    {
                        if(strcmp(v[j].continente,vContXop[k].continente)==0)

                        {
                            vContXop[k].registros+=AgrupadoXpais[i].registros;
                            vContXop[k].totalCredito+=AgrupadoXpais[i].totalCredito;
                            vContXop[k].totalDebito+=AgrupadoXpais[i].totalDebito;
                            existe = 1;
                        }
                    }

                if (existe == 0)
                {
                            strcpy(vContXop[num].continente,v[j].continente);
                            vContXop[num].registros=AgrupadoXpais[i].registros;
                            vContXop[num].totalCredito=AgrupadoXpais[i].totalCredito;
                            vContXop[num].totalDebito=AgrupadoXpais[i].totalDebito;
                            num++;


                }

                        existe = 0;

                   }


        }




    } return num;
}

void mostrarOpXContinentes(ContinenteConOperaciones vContXop[], int num)

{
    printf("%s %s %s %s \n", "CONTINENTE", "REGISTROS", "CREDITO", "DEBITO");
     for (int i = 0; i < num; i++)
        printf("%s | %d | %.2f | %.2f\n",
               vContXop[i].continente, vContXop[i].registros, vContXop[i].totalCredito,vContXop[i].totalDebito);

printf( "num:%d", num);

}
//Ejer 3
int FuncionMontoxTrimestre(Operacion ops[],int cant,Trimestral vTrimestral[], int anio)

{

    int cantTrimestre=0;
    float varCredito=0;
    float varDebito=0;
    int existe=0;

     for (int i = 0; i < cant; i++)
     {

         if(ops[i].anio==anio)

         {

            for(int j = 0; j < cantTrimestre; j++)
             {
              if(strcmp(vTrimestral[j].paisDesc,ops[i].paisDesc)==0)

             {
                existe=1;
               if(ops[i].trimestre==1)

                 {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                    vTrimestral[j].t1+=varCredito-varDebito;
                 }
                  else if(ops[i].trimestre==2)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[j].t2+=varCredito-varDebito;
                 }

                 else if(ops[i].trimestre==3)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[j].t3+=varCredito-varDebito;
                 }

             else if(ops[i].trimestre==4)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[j].t4+=varCredito-varDebito;
                 }



            }


            }
if(existe==0)

         {
             strcpy(vTrimestral[cantTrimestre].paisDesc,ops[i].paisDesc);
             vTrimestral[cantTrimestre].t1=0;
                vTrimestral[cantTrimestre].t2=0;
                vTrimestral[cantTrimestre].t3=0;
                vTrimestral[cantTrimestre].t4=0;

            if(ops[i].trimestre==1)

                 {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[cantTrimestre].t1=varCredito-varDebito;
                 }
                  else if(ops[i].trimestre==2)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                   vTrimestral[cantTrimestre].t2=varCredito-varDebito;
                 }

                 else if(ops[i].trimestre==3)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[cantTrimestre].t3=varCredito-varDebito;
                 }

             else if(ops[i].trimestre==4)

                  {
                  if(ops[i].operacion=='C')
                   {
                      varCredito+=ops[i].monto;
                   }
                  else

                   {
                      varDebito+=ops[i].monto;
                   }
                  vTrimestral[cantTrimestre].t4=varCredito-varDebito;
                 }

            cantTrimestre++;





         }

         existe=0;
         varCredito=0;
         varDebito=0;

         }

}
return cantTrimestre;

     }

void mostrarMontoxPais(Trimestral vTrimestral[], int cantTrimestre)

{
    printf("%s %s %s %s \n", "PAIS", "T1", "T2", "T3");
     for (int i = 0; i < cantTrimestre; i++)
        printf("%s | %.2f | %.2f | %.2f | %.2f\n",
               vTrimestral[i].paisDesc, vTrimestral[i].t1, vTrimestral[i].t2,vTrimestral[i].t3, vTrimestral[i].t4);

printf( "num:%d", cantTrimestre);

}

void ordenarPorPais(Trimestral vTrimestral[], int cantTrimestre)
{
    Trimestral aux;

    for (int i = 0; i < cantTrimestre - 1; i++)
    {
        for (int j = 0; j < cantTrimestre - 1 - i; j++)
        {
            if (strcmp(vTrimestral[j].paisDesc, vTrimestral[j + 1].paisDesc) > 0)
            {
                aux = vTrimestral[j];
                vTrimestral[j] = vTrimestral[j + 1];
                vTrimestral[j + 1] = aux;
            }
        }
    }
}

int exportarMontoxPais(Trimestral vTrimestral[], int cantTrimestre, int anio)
{
    FILE *archivo = fopen("/Users/evelyn/Projects/TPprogramacion/montos_por_pais.txt", "w");
    if (archivo == NULL)
    {
        printf("No se pudo crear el archivo\n");
        return 0;
    }

    fprintf(archivo, "MONTO POR PAIS Y TRIMESTRE - ANIO %d\n", anio);
    fprintf(archivo, "------------------------------------------------------------------------\n");
    fprintf(archivo, "%-20s | %12s | %12s | %12s | %12s\n", "PAIS", "T1", "T2", "T3", "T4");
    fprintf(archivo, "------------------------------------------------------------------------\n");

    for (int i = 0; i < cantTrimestre; i++)
        fprintf(archivo, "%-20s | %12.2f | %12.2f | %12.2f | %12.2f\n",
                vTrimestral[i].paisDesc, vTrimestral[i].t1, vTrimestral[i].t2,
                vTrimestral[i].t3, vTrimestral[i].t4);

    fprintf(archivo, "------------------------------------------------------------------------\n");
    fprintf(archivo, "Total de paises: %d\n", cantTrimestre);

    fclose(archivo);
    return 1;
}

//Ejer 4

int FuncionMontoxAnio(Operacion ops[],int cant,totVariaxAnio totVaria[]) {

    int existe=0;
    int cantVar=0;

    for (int i = 0; i < cant; i++) {
        for(int j = 0; j < cantVar; j++) {

            if(totVaria[j].anio==ops[i].anio) {

                existe=1;
                if(ops[i].operacion=='C')
                {
                      totVaria[j].credito+=ops[i].monto;
                }
                  else

                   {
                      totVaria[j].debito+=ops[i].monto;
                   }
                    totVaria[j].saldo=totVaria[j].credito-totVaria[j].debito;
                 }

                    }

                  if(existe==0)
                  {
                  totVaria[cantVar].anio=ops[i].anio;
                  totVaria[cantVar].credito=0;
                  totVaria[cantVar].debito=0;
                  totVaria[cantVar].saldo=0;

                  if(ops[i].operacion=='C')
                           {
                              totVaria[cantVar].credito+=ops[i].monto;
                           }
                          else

                           {
                              totVaria[cantVar].debito+=ops[i].monto;
                           }
                            totVaria[cantVar].saldo=totVaria[cantVar].credito-totVaria[cantVar].debito;


                  cantVar++;
                  }

                 existe=0;


             }


  return cantVar;

     }

void ordenarxAnio(totVariaxAnio totVaria[], int cantVar)
{
    totVariaxAnio aux;

    for (int i = 0; i < cantVar - 1; i++)
    {
        for (int j = 0; j < cantVar - 1 - i; j++)
        {
            if (totVaria[j].anio >totVaria[j + 1].anio)
            {
                aux = totVaria[j];
                totVaria[j] = totVaria[j + 1];
                totVaria[j + 1] = aux;
            }
        }
    }
}
void FuncionVariacionxAnio(totVariaxAnio totVaria[], int cantVar) {
    for (int i = 0; i < cantVar; i++)
    {if(i!=0)
        {
        totVaria[i].varPct=((totVaria[i].saldo-totVaria[i-1].saldo)/totVaria[i-1].saldo)* 100 ;
        }

    }
}


void mostrarTotalVaria(totVariaxAnio totVaria[], int cantVar)

{
    printf("%s %s %s %s %s\n", "ANIO", "C", "D", "SALDO", "VAR_PCT_SALDO");
     for (int i = 0; i < cantVar; i++)

        {printf("%d | %.2f | %.2f | %.2f|",
               totVaria[i].anio, totVaria[i].credito, totVaria[i].debito,totVaria[i].saldo);
               if (i == 0)
                printf("-\n");                      // primer año: guion
               else
               printf("%.2f\n", totVaria[i].varPct);
}

printf( "num:%d", cantVar);

}


int FuncionRanking(OperacionTotales AgrupadoXpais[],int cant,ranking vranking[])

{
    int cantIngresada;
    char operacionIngresada;

    printf("Ingresar cantidad de paises que desea ver: ");
    scanf("%d",&cantIngresada);
    printf("Ingresar operacion que desea ver(C o D): ");
    scanf(" %c",&operacionIngresada);

    for(int i=0;i<cantIngresada;i++)
    {
       vranking[i].puesto=i+1;
       strcpy(vranking[i].paisCod,AgrupadoXpais[i].paisCod);
       strcpy(vranking[i].paisDesc,AgrupadoXpais[i].paisDesc);

        if(operacionIngresada=='C')
        {
           vranking[i].monto=AgrupadoXpais[i].totalCredito;
        }
        else
        {
            vranking[i].monto=AgrupadoXpais[i].totalDebito;
        }
    }
   return cantIngresada;
}


void mostrarRanking(ranking vranking[], int cantIngresada)
{
    printf("%-8s | %-10s | %-20s | %12s\n", "PUESTO", "COD PAIS", "NOMBRE", "MONTOs");
    printf("---------+------------+----------------------+-------------\n");

    for (int i = 0; i < cantIngresada; i++)
        printf("%-8d | %-10s | %-20s | %12.2f\n",
               vranking[i].puesto, vranking[i].paisCod,
               vranking[i].paisDesc, vranking[i].monto);
}

