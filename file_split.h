/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */


#ifndef FILE_SPLIT_H_INCLUDED
#define FILE_SPLIT_H_INCLUDED

#include "stdio.h"

// Verifica que el nombre 'fileName' no contenga secuencias "\\". Es decir, que no indique una ruta de acceso.
bool validateFileName(char* fileName);

// Copia de 'sourceFile' una cantidad 'blockSize' de bytes, escribiéndolos en 'dest'.
// Comienza a copiar desde 'sourceFile' en la posición en la que se encuentre el stream indicator del archivo.
// Devuelve en 'dest' un puntero al byte siguiente al último copiado.
// Si no se pudo copiar, devuelve NULL en dicho puntero.
// El valor de retorno es la cantidad de bytes que pudo copiar con éxito.
unsigned int readNextFileBlock(FILE* sourceFile, char** dest, unsigned blockSize);

// Guarda en el archivo 'destFile' una cantidad 'blockSize' de bytes obtenidos de 'source'.
// Devuelve en 'source' un puntero al byte siguiente al último copiado.
// Devuelve la cantidad de bytes guardados satisfactoriamente.
unsigned int saveNextFileBlock(char** source, FILE* destFile, unsigned blockSize);


#endif // FILE_SPLIT_H_INCLUDED
