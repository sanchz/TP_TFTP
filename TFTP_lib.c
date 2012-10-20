/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "TFTP_lib.h"
#include "file_split.h"



// Inicializa el servidor TFTP, que recibe conexiones en el puerto 'port'. Devuelve la nueva conexión. Aloca memoria
// que es liberada en 'closeTFTPserver()'. Si no se puedo establecer la conexión se devuelve NULL.
TFTPconn* startTFTPserver(unsigned short port)
{
    // alocar memoria
    // start listening
    // block number = 0
}

// Devuelve una nueva conexión entrante exitosa en 'connection'.
// Es bloqueante, ya que espera a que la conexión se haya establecido.
// De no poder realizarse la conexión (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve FALSE. Si se pudo establecer devuelve TRUE.
bool getTFTPconnection(TFTPconn* connection)
{
    // get connection
    // is pending
}

// Cierra la conexión 'connection' y deja de recibir conexiones.
void closeTFTPserver(TFTPconn* connection)
{
    // closeConnection
    // stopListening
    // free
}

// La conexión debe estar hecha y activa.
// Si el paquete recibido es un pedido de lectura o escritura del protocolo TFTP, se indica
// con las constantes RRQ o WRQ como valores devueltos por la función, respectivamente.
// En este caso se guarda el nombre del archivo indicado por el paquete en 'fileName' (se corta el mismo si excede los MAX_FILENAME_LENGTH caracteres).
// Cualquier otro paquete es descartado, y se devueve una constante NO_REQ en este caso.
// Si no se recibió un paquete de lectura o de escritura se devuelve NO_REQ.
Requests getRequest(TFTPconn* currentConnection, char fileName[MAX_FILENAME_LENGTH + 1])
{
    // verificar isConnected
    // verificar opcode
    // copiar nombre
}


// Devuelve una nueva conexión exitosa al servidor.
// Es bloqueante, ya que espera a que la conexión se haya establecido.
// De no poder realizarse la conexión (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve NULL.
TFTPconn* connectToTFTPserver(const char *hostname, unsigned short port)
{
    long timeout;
    bool statusConnection = FALSE;

    TFTPconn* clientConnection;

    clientConnection = malloc(sizeof(TFTPconn));

    if(clientConnection != NULL)                /// Verificar que se alocó memoria
    {
        clientConnection->blockNumber = 0;

        clientConnection->currentConnection = openConnection(hostname, port);

        if(clientConnection->currentConnection != 0)
        {
            timeout = clock() + TFTP_TIMEOUT ;

            while( clock() < timeout )
            {
                if (isConnected(clientConnection->currentConnection) == 1)
                {
                    statusConnection = TRUE;
                    break;
                }
            }
        }
        if (statusConnection == FALSE)
        {
            free(clientConnection);             /// Liberar memoria
            clientConnection = NULL;
        }
    }

    return clientConnection;
}

// Cierra una conexión activa del cliente con el servidor TFTP
void closeTFTPclientConnection(TFTPconn* clientConnection)
{
    closeConnection(clientConnection->currentConnection);

    free(clientConnection);
}

// Envía por la conexión 'clientConnection' un paquete/pedido de escritura del protocolo TFTP al servidor.
// El nombre del archivo a escribir está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
/*
 2 bytes     string    1 byte     string   1 byte
 ------------------------------------------------
| Opcode |  Filename  |   0  |    Mode    |   0  |
 ------------------------------------------------
*/
bool sendWriteRequest(TFTPconn* clientConnection, char* fileName)
{
    // verificar isConnected
    // verificar num bytes enviados

    bool status = FALSE;

    unsigned int i;

    char* mode = MODE_RRQWRQ;

    unsigned int nSend;

    unsigned int bufferSize = sizeof(char)*2+sizeof(char)*strlen(fileName)+sizeof(char)*strlen(mode);

    char * buffer = malloc(bufferSize);

    //Completo el buffer con el prototipo del paquete:

    /*
    2 bytes     string    1 byte     string   1 byte
    ------------------------------------------------
    | Opcode |  Filename  |   0  |    Mode    |   0  |
    ------------------------------------------------
    */
    //Opcode:
    *buffer = 0;
    *(buffer+1) = WRQ;

    //Filename
    strcpy((buffer+2), fileName);
    i = sizeof(char)*strlen(fileName)+sizeof(char)*2;

    //Mode
    strcpy((buffer+i), mode);

//DEBUG
/*
    printf("\n\nBuffer: %d",(int)*buffer);
    printf("%d",(int)*(buffer+1));
    printf("%s",buffer+2);
    printf("%d",(int)*(buffer+i-1));
    printf("%s",buffer+i);
    printf("%d\n\n",(int)*(buffer+bufferSize));
*/

    if (isConnected(clientConnection->currentConnection) == 1)
    {
        nSend = sendData(clientConnection->currentConnection, buffer, bufferSize);

        if (nSend == bufferSize)
            status = TRUE;
    }

    return status;
}

// Envía por la conexión 'clientConnection' un paquete/pedido de lectura del protocolo TFTP al servidor.
// El nombre del archivo a leer está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
/*
 2 bytes     string    1 byte     string   1 byte
 ------------------------------------------------
| Opcode |  Filename  |   0  |    Mode    |   0  |
 ------------------------------------------------
*/
bool sendReadRequest(TFTPconn* clientConnection, char* fileName)
{
    // verificar isConnected
    // verificar num bytes enviados

    bool status = FALSE;

    unsigned int i;

    char* mode = MODE_RRQWRQ;

    unsigned int nSend;

    unsigned int bufferSize = sizeof(char)*2+sizeof(char)*strlen(fileName)+sizeof(char)*strlen(mode);

    char * buffer = malloc(bufferSize);

    //Completo el buffer con el prototipo del paquete:

    /*
    2 bytes     string    1 byte     string   1 byte
    ------------------------------------------------
    | Opcode |  Filename  |   0  |    Mode    |   0  |
    ------------------------------------------------
    */
    //Opcode:
    *buffer = 0;
    *(buffer+1) = RRQ;

    //Filename
    strcpy((buffer+2), fileName);
    i = sizeof(char)*strlen(fileName)+sizeof(char)*2;

    //Mode
    strcpy((buffer+i), mode);


/*DEBUG
    printf("\n\nBuffer: %d",(int)*buffer);
    printf("%d",(int)*(buffer+1));
    printf("%s",buffer+2);
    printf("%d",(int)*(buffer+i-1));
    printf("%s",buffer+i);
    printf("%d\n\n",(int)*(buffer+bufferSize));
*/

    if (isConnected(clientConnection->currentConnection) == 1)
     {
        nSend = sendData(clientConnection->currentConnection, buffer, bufferSize);

        if (nSend == bufferSize)
            status = TRUE;
     }

    return status;
}


// Envía por 'currentConnection' un paquete de datos del protocolo TFTP, de largo 'dataBytes'. Los bytes enviados no pueden exceder TFTP_DATA_SIZE.
// Se devueve FALSE en si se indica 'dataBytes' incorrectamente, o si la conexión no se pudo realizar. TRUE es devuelto en caso de éxito.
bool sendDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int dataBytes)
{
    // verificar isConnected
    // veificar dataBytes
    // alocar memoria para buffer, enviar el buffer
    // verificar que num bytes enviados == numb bytes indicados
    // liberar memoria de buffer
}

// Recibe por 'currentConnection' un paquete de datos del protocolo TFTP, de largo indicado en 'dataBytes'.
// En caso de no estar activa la conexión, o de no recibirse dicho paquete, se devuelve FALSE. Si se recibió exitosamente el paquete, se devuelve TRUE.
bool getDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int* dataBytes)
{
    // verificar isConnected
    // verificar opCode
    // copiar a dataBytes
    // copiar datos a TFTP_DATA_SIZE
    // verificar blocknumber == al recibido
}

// Envía un paquete ACK por la conexión 'connection'. Devuelve TRUE si se envió, FALSE si hubo problemas en la conexión.
bool sendAcknowledgement(TFTPconn* connection)      /// Verificar los block#
{
    // isConnected
    // verificar núm bytes enviados
    // luego incrementar block number
}

// Verifica si se recibió un parquete ACK por 'connection'. Devuelve TRUE si se recibió y es la respuesta esperada (respuesta al último paquete enviado).
// Devuelve FALSE si no se recibió un paquete ACK válido, o si la conexión caducó.
bool getAcknowledgement(TFTPconn* connection)
{
    // is connected
    // block number válido
    // incrementar block number
}

// Devuelve TRUE si la conexión se mantiene activa, FASLE en caso contrario.
bool isTFTPconnActive(TFTPconn* connection);




