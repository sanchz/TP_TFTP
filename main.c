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
#define WAIT_INTERVAL   100 // Milisegundos
#define WAIT_TRIES      15
#define MAX_CHARS       255


// Portable sleep functions
#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif


// Recibe un archivo completo desde una conexión TFTP 'link' y lo guarda como "filename".
// Devuelve TRUE sólo en caso de que se haya recibido cy podido escribir satisfactoriamente.
// Devuelve FALSE si no se pudo completar la transacción.
bool receiveFileOverTFTP(TFTPconn* link, const char* filename)      /// Ver dónde ubicar a estas dos funciones
{
    bool returnVal = TRUE;
    bool received;
    FILE* writeFile = fopen(filename, "wb");
    char buffer[TFTP_DATA_SIZE];
    int receivedBytes;
    int i;

    // Si se abrió el archivo
    if(writeFile != NULL)
    {
        do
        {
            receivedBytes = 0;
            // Intenta buscar el paquete y, si no se recibe, espera un intervalo antes de volver a buscarlo. Intenta una cantidad WAIT_TRIES de veces.
            for(i=0; !(received = getDataPacket(link, buffer, &receivedBytes)) && (i < WAIT_TRIES); i++)
            {
                sleep(WAIT_INTERVAL);
            }
            // Si se recibió un paquete
            if(received)
            {
                // Envío la confirmación al emisor
                if(sendAcknowledgement(link))
                {
                    // Lo guardo en el archivo
                    if(saveNextFileBlock(buffer, writeFile, receivedBytes) != receivedBytes)
                        returnVal = FALSE;
                }
                else
                    returnVal = FALSE;
            }
            else
                returnVal = FALSE;
        }
        // Sigo hasta que se produzca un error, o se haya recibido el último paquete
        while((receivedBytes == TFTP_DATA_SIZE) && (returnVal == TRUE));

        fclose(writeFile);
    }
    else
        returnVal = FALSE;

    return returnVal;
}

// Envía el archivo completo especificado por la conexión activa "link".
// Devuelve TRUE sólo en el caso de que el archivo se haya podido abrir, leer, y
// enviar, y que el receptor haya confirmado su recepción.
// Se devuelve FALSE en caso contrario.
bool sendFileOverTFTP(TFTPconn* link, const char* filename)
{
    bool returnVal = TRUE;
    bool sent;
    FILE* readFile = fopen(filename, "rb");
    char buffer[TFTP_DATA_SIZE];
    int blockBytes;
    int i;

    // Si se abrió el archivo
    if(readFile != NULL)
    {
        do
        {
            blockBytes = readNextFileBlock(readFile, buffer, TFTP_DATA_SIZE);

            if(sendDataPacket(link, buffer, blockBytes))
            {
                // Verifica que se haya recibido el paquete. Intenta WAIT_TRIES veces, con WAIT_INTERVAL intervalo de polling.
                for(i=0; !(sent = getAcknowledgement(link)) && (i < WAIT_TRIES); i++)
                {
                    sleep(WAIT_INTERVAL);
                }
                // Si no se recibió el ACK
                if(!sent)
                {
                    returnVal = FALSE;
                }
            }
            else
                returnVal = FALSE;
        }
        while((blockBytes == TFTP_DATA_SIZE) && (returnVal == TRUE));

        fclose(readFile);
    }
    else
        returnVal = FALSE;

    return returnVal;
}


#include <ctype.h>
void str2Lower(char string[])
{
    int i=0;

    while (string[i])
    {
        string[i] = tolower(string[i]);
        i++;
    }
}


#define __SERVER
//#define __CLIENT
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
            sleep(WAIT_INTERVAL);
        }

        // Espera pedido del cliente
        while( (currentRequest = getRequest(currentConn, currentFileName)) == NO_REQ )
        {
            sleep(WAIT_INTERVAL);
        }

        if(validateFileName(currentFileName))
        {
            if(currentRequest == WRQ)
            {
                printf("Se ha pedido la escritura de <%s>\n\n", currentFileName);

                // Confirmo el pedido de escritura
                if(sendAcknowledgement(currentConn))
                {
                    if(receiveFileOverTFTP(currentConn, currentFileName))
                    {
                        printf("Archivo <%s> recibido correctamente\n\n", currentFileName);
                    }
                    else
                        printf("No se pudo recibir el archivo <%s>\n\n", currentFileName);
                }
                else
                {
                    printf("No se pudo recibir el archivo <%s>\n\n", currentFileName);
                }
            }
            else if(currentRequest == RRQ)
            {
                printf("Se ha pedido la lectura de <%s>\n\n", currentFileName);

                if(sendFileOverTFTP(currentConn, currentFileName))
                {
                    printf("Archivo <%s> enviado correctamente\n\n", currentFileName);
                }
                else
                    printf("No se pudo enviar el archivo <%s>\n\n", currentFileName);
            }
            else
                printf("Error: paquete de pedido invalido\n\n");
        }

        closeTFTPserver(currentConn);
    }

    printf("Server could NOT be started\n\n");
    printf("Exiting program...\n\n");

    return 0;
}

#elif defined __CLIENT
int main(int argc, char* argv[])
{
    bool quit = FALSE;
    TFTPconn* clientConn;
    char command[MAX_CHARS];
    char currentFileName[MAX_FILENAME_LENGTH+1];

    if(argc >= 2)
    {
        while(!quit)
        {
            clientConn =  connectToTFTPserver(argv[1], TFTP_PORT);
            if(clientConn == NULL)
            {
                quit = TRUE;
                printf("Could not connect to server at ip: <%s>\n\n", argv[1])
            }
            else
            {
                printf("tftp>");

                scanf("%s",command);    //Leo el comando ingresado.

                str2Lower(command);

                if(strcmp(command,"put") == 0)
                {
                    scanf("%s",filename);    //Leo el nombre del archivo.
                    if(sendFileOverTFTP(clientConn, filename)
                    {
                        printf("File sent successfully\n\n");
                    }
                    else
                    {
                        printf("File could not be sent\n\n");
                    }
                }
                else if(strcmp(command,"get") == 0)
                {
                    scanf("%s",filname);    //Leo el nombre del archivo.
                    if(receiveFileOverTFTP(clientConn, filename)
                    {
                        printf("File sent successfully\n\n");
                    }
                    else
                    {
                        printf("File could not be sent\n\n");
                    }
                }
                else if(strcmp(command,"quit") == 0)
                {
                    quit = TRUE;
                }
                else
                    printf("Command not recognized\n\n");

                while(getchar() != '\n');
            }
        }
    }
    else
        printf("No ip address specified\n\n");

    return 0;
    // conexión
    // entrada
    // transferencia
    // volver a entrada


    return 0;
}
#endif

