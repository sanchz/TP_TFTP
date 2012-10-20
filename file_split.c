/*
TRABAJO PR�CTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, Jos� Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */
#include <string.h>

#include "file_split.h"


// Verifica que el nombre 'fileName' no contenga secuencias "\\". Es decir, que no indique una ruta de acceso.
// Devuelve TRUE si pasa la validaci�n, FALSE en caso contrario.
bool validateFileName(char* fileName)
{
    char cInvalido = '\\';

    bool status = FALSE;

    if( strchr(fileName, cInvalido) == NULL)
        status = TRUE;

    return status;
}

// Copia de 'sourceFile' una cantidad 'blockSize' de bytes, escribi�ndolos en 'dest'.
// Comienza a copiar desde 'sourceFile' en la posici�n en la que se encuentre el stream indicator del archivo.
// El valor de retorno es la cantidad de bytes que se copiaron con �xito.
unsigned int readNextFileBlock(FILE* sourceFile, char* dest, unsigned blockSize)
{
    unsigned int cantRead = fread(dest, sizeof(char), blockSize, sourceFile);

    return cantRead;
}

// Guarda en el archivo 'destFile' una cantidad 'blockSize' de bytes obtenidos de 'source'.
// Devuelve la cantidad de bytes guardados satisfactoriamente.
unsigned int saveNextFileBlock(char* source, FILE* destFile, unsigned blockSize){

    unsigned int cantWrite = fwrite(source, sizeof(*source), blockSize, destFile);

    return cantWrite;
}




