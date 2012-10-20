/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */
#include <stdio.h>
#include <stdlib.h>

#include "polonet.h"
#include "TFTP_lib.h"
#include "file_split.h"


#define TFTP_PORT   69
#define WAIT_INTERVAL   500 // Milisegundos
#define MAX_FILENAME_LENGTH     100



// Función de espera
void wait(long milliseconds);
// Recibe un archivo completo y lo guarda como "filename".
// Devuelve TRUE sólo en caso de que se haya recibido completamente.
// Devuelve FALSE si no se pudo completar la transacción.
bool receiveFileOverTFTP(TFTPconn* link, const char* filename)      /// Ver dónde ubicar a estas dos funciones
{
    bool returnVal = FALSE;
    FILE* writeFile = fopen(filename, "w");
    int i;

    // Si se abrió el archivo
    if(writeFile != NULL)
    {
        /// Esperar un parquete un timeout
    }



}
// Envía el archivo completo especificado por la conexión activa.
// Devuelve TRUE sólo en el caso
// de que se haya podido enviar completamente el archivo, y que el receptor haya confirmado su recepción.
// Se devuelve FALSE en caso contrario.
bool sendFileOverTFTP(TFTPconn* link, const char* filename);


#define __SERVER
#ifdef __SERVER
int main()
{
    TFTPconn* currentConn;
    Requests currentRequest;
    char currentFileName[MAX_FILENAME_LENGTH+1];

    while((currentConn = startTFTPserver(TFTP_PORT)) != NULL)
    {
        printf("Server started\n\n");

        // Espera conexión
        while(!getTFTPconnection(currentConn))      /// Verificar si bloquea HASTA que se haya conectado
        {
            wait(WAIT_INTERVAL);
        }

        // Espera pedido del cliente
        while( (currentRequest = getRequest(currentConn, currentFileName, MAX_FILENAME_LENGTH)) == NO_REQ )
        {
            wait(WAIT_INTERVAL);
        }

        if(validateFileName(currentFileName))
        {
            if(currentRequest == WRQ)
            {
                // Confirmo el pedido de escritura
                if(sendAcknowledgement(currentConn))
                {

                }
            }
            else if(currentRequest == RRQ)
            {

            }
            else
                printf("Error: paquete de pedido invalido\n\n");
        }

        closeTFTPserver(currentConn);
    }

    printf("Server could NOT be started\n\n");
    printf("Exiting program...\n\n");


    // esperar contacto

    // establecer transferencia

    // volver a esperar contacto

    // salir si así se pide


    return 0;
}

#elif defined __CLIENT
int main()
{
    // conexión
    // entrada
    // transferencia
    // volver a entrada


    return 0;
}
#endif


#include <time.h>
// Función de espera portable (y MUY pesada para el CPU)
void wait(long milliseconds)
{
  long timeout = clock() + milliseconds;
  while( clock() < timeout ) continue;
}


