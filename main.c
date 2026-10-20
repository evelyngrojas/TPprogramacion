#include "funciones.h"
#include <stdio.h>
#include <string.h>


int menu(void)
{
    int opcion;

    printf("\n===== MENU =====\n");
    printf("100. Mostrar todos los registros\n");
    printf("1. Totales por pais (credito y debito)\n");
    printf("2. Totales por continente\n");
    printf("3. Totales por trimestre\n");
    printf("4. Totales anuales y variacion interanual\n");
    printf("5. Ranking de pa’ses por tipo de operaci—n\n");
    printf("5. Totales por \n");
    printf("7. Totales por \n");
    printf("8. Totales por \n");
    printf("9. Totales por \n");
    printf("10. Totales por \n");

    printf("0. Salir\n");
    printf("Elija una opcion: ");

    if (scanf("%d", &opcion) != 1) {          /* si escribio una letra */
        opcion = -1;
        while (getchar() != '\n');            /* limpio lo que quedo escrito */
    }
    return opcion;
}

int main(void)
{

    Operacion ops[MAX];
    int cant;
    OperacionTotales AgrupadoXpais[MAX];
    Operacion aux[MAX];
    int opcion;
    int cantPaises;
    int cantContinente;
    Continente vContinente [MAXC];
    ContinenteConOperaciones vContXop [MAXC];
    int num;
    Trimestral vTrimestral [MAX];
    int cantTrimestre;
    int anio=0;
    totVariaxAnio totVaria[MAX];
    int cantVar=0;
    ranking vranking[MAX];
    int cantIngresada=0;



//Ejercicio 1
        cant = leerArchivoTransferencias(ops);
        cantPaises = FuncionAgruparPais(ops, cant, AgrupadoXpais);
        ordenarPorMonto(AgrupadoXpais, cantPaises);
//Ejercicio 2

       cantContinente = leerArchivoContinente(vContinente);
       num = CrearVectorConContinente(vContinente,AgrupadoXpais,cant,cantContinente,vContXop);

//Ejercicio 3


     do
    {
        opcion = menu();
        switch (opcion)
        {
            case 100:
                mostrarContinentes(vContinente, cantContinente);
                printf( "/n");
                mostrar(ops, cant);
                break;

            case 1:
//                cantPaises = agruparPorPais(ops, cant, AgrupadoXpais);


        mostrarTotales(AgrupadoXpais, cantPaises);
        int suma = 0;
        for (int i = 0; i < cantPaises; i++) suma += AgrupadoXpais[i].registros;
        printf("\nPaises: %d | suma de registros: %d (de %d leidos)\n", cantPaises, suma, cant);

             case 2:
                    mostrarOpXContinentes(vContXop, num);


             case 3:
                    printf("Ingresar anio que desea ver: ");
                   scanf("%d",&anio);

                   cantTrimestre= FuncionMontoxTrimestre(ops,cant,vTrimestral,anio);
                   ordenarPorPais(vTrimestral,cantTrimestre);

                   mostrarMontoxPais(vTrimestral,cantTrimestre);
                 if (exportarMontoxPais(vTrimestral,cantTrimestre, anio))
                 printf("Archivo generado: montos_por_pais.txt\n");


             case 4:
                int cantVar=FuncionMontoxAnio(ops,cant,totVaria);
                ordenarxAnio(totVaria,cantVar);
                FuncionVariacionxAnio(totVaria,cantVar);
                mostrarTotalVaria(totVaria,cantVar);


             case 5:

                cantIngresada=FuncionRanking(AgrupadoXpais,cant,vranking);
                mostrarRanking(vranking,cantIngresada);

             case 6:


             case 7:


             case 8:


             case 9:


             case 10:



                break;

            case 0:
                printf("Hasta luego\n");
                break;

            default:
                printf("Opcion invalida, intente de nuevo\n");
        }
    } while (opcion != 0);


    return 0;
}
