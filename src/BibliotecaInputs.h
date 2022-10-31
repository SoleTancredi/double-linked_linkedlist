/*
 * BibliotecaInputs.h
 *
 *  Created on: 15 dic. 2021
 *      Author: stanc
 */

#ifndef BIBLIOTECAINPUTS_H_
#define BIBLIOTECAINPUTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int utn_getNumber(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumberFloat(float* pResultadoF, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getCharacter(char* pResultado, char mensaje[] , char* mensajeError, int reintentos);
int utn_nombreOapellido(char* string, char* pMensaje, char *pMensajeError, int tam, int reintentos);
int utn_cargarArrayNumeros(int arrayNumeros[], int tam, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_ordenarArrayCreciente(int* array, int tam);
int utn_ordenarArrayDecreciente(int* array, int tam);
int utn_mostrarNumeros(int* array, char* mensaje, int tam);
int inicializacionArray(int array[], int tam);
int utn_promedio(int numerador, int denominador, float* pResultadoF);
int utn_telephoneNumber(char* string, char* mensaje, char* mensajeError, int tam, int reintentos);
int systemPause(char* message);






#endif /* BIBLIOTECAINPUTS_H_ */
