#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RUTAT "/Users/evelyn/Projects/TPprogramacion/transferencias_personales_clean.csv"
#define RUTAC "/Users/evelyn/Projects/TPprogramacion/paises_continentes.csv"
#define MAX 6000
#define MAXC 200


typedef struct {
    int   anio;
    int   trimestre;
    char  paisCod[8];
    char  paisDesc[64];
    char  operacion;
    float monto;
} Operacion;

typedef struct {
    char  paisCod[8];
    char  paisDesc[64];
    int   registros;
    float totalCredito;
    float totalDebito;
} OperacionTotales;

typedef struct {
    char paisCod[8];
    char paisDesc[50];
    char continente[30];
} Continente;

// Tu struct actual (ajustalo a como lo tengas) con un campo nuevo
typedef struct {
    char continente[64];
    int registros;
    float totalCredito;
    float totalDebito;
} ContinenteConOperaciones;

typedef struct {
    char  paisDesc[64];
    float t1;
    float t2;
    float t3;
    float t4;
} Trimestral;

typedef struct {
    int   anio;
    float credito;
    float debito;
    float saldo;
    float varPct;
} totVariaxAnio;

typedef struct {
    int puesto;
    char  paisCod[8];
    char  paisDesc[64];
    float monto;
} ranking;


int leerArchivoTransferencias(Operacion v[]);
int FuncionAgruparPais(Operacion ops [], int , OperacionTotales AgrupadoXpais[]);

void separar(char *linea, char campos[][64]);

void mostrarTotales(OperacionTotales v[],int);

void mostrar(Operacion v[], int);
void ordenarPorMonto(OperacionTotales v[], int );
int leerArchivoContinente(Continente v[]);
void separarC(char *linea, char campos[][64]);
void mostrarContinentes(Continente v[], int);
int CrearVectorConContinente(Continente v[], OperacionTotales AgrupadoXpais [],int, int, ContinenteConOperaciones vContXop[]);
void mostrarOpXContinentes(ContinenteConOperaciones vContXop[], int);
int FuncionMontoxTrimestre(Operacion ops[],int,Trimestral vTrimestral[],int);
void ordenarPorPais(Trimestral vTrimestral[], int);
void mostrarMontoxPais(Trimestral vTrimestral[], int);
int exportarMontoxPais(Trimestral vTrimestral[], int , int);
int FuncionMontoxAnio(Operacion ops[],int,totVariaxAnio totVaria[]);
void ordenarxAnio(totVariaxAnio totVaria[], int);
void FuncionVariacionxAnio(totVariaxAnio totVaria[], int);
void mostrarTotalVaria(totVariaxAnio totVaria[], int );
int FuncionRanking(OperacionTotales AgrupadoXpais[],int,ranking vranking[]);
void mostrarRanking(ranking vranking[], int);

















#endif // FUNCIONES_H_INCLUDED
