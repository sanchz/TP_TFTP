/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */
#ifndef TFTP_LIB_H_INCLUDED
#define TFTP_LIB_H_INCLUDED


#include <stdio.h>

#include "bool_def.h"
#include "polonet.h"


#define MAX_FILENAME_LENGTH     255
#define TFTP_DATA_SIZE          512
#define TFTP_TIMEOUT            3000    // Milisegundos

#define MODE_RRQWRQ            "octet"

typedef enum requests {RRQ, WRQ, NO_REQ} Requests;

typedef struct
{
    PolonetConn currentConnection;
    unsigned short blockNumber;
} TFTPconn;



////////////////////////////
// Funciones del SERVIDOR //
////////////////////////////

// Inicializa el servidor TFTP, que recibe conexiones en el puerto 'port'. Devuelve la nueva conexión. Aloca memoria
// que es liberada en 'closeTFTPserver()'. Si no se puedo establecer la conexión se devuelve NULL.
TFTPconn* startTFTPserver(unsigned short port);

// Devuelve una nueva conexión entrante exitosa en 'connection'.
// Es bloqueante, ya que espera a que la conexión se haya establecido.
// De no poder realizarse la conexión (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve FALSE. Si se pudo establecer devuelve TRUE.
bool getTFTPconnection(TFTPconn* connection);

// Cierra la conexión 'connection' y deja de recibir conexiones.
void closeTFTPserver(TFTPconn* connection);

// Verifica en 'currentConnection' si se produjo un nuevo pedido.
// La conexión debe estar hecha y activa.
// Si el paquete recibido es un pedido de lectura o escritura del protocolo TFTP, se indica
// con las constantes RRQ o WRQ como valores devueltos por la función, respectivamente.
// En este caso se guarda el nombre del archivo indicado por el paquete en 'fileName' (se corta el mismo si excede los MAX_FILENAME_LENGTH caracteres).
// Cualquier otro paquete es descartado, y se devueve una constante NO_REQ en este caso.
// Si no se recibió un paquete de lectura o de escritura se devuelve NO_REQ.
Requests getRequest(TFTPconn* currentConnection, char fileName[MAX_FILENAME_LENGTH + 1]);


///////////////////////////
// Funciones del CLIENTE //
///////////////////////////

// Devuelve una nueva conexión exitosa al servidor.
// Es bloqueante, ya que espera a que la conexión se haya establecido.
// De no poder realizarse la conexión (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve NULL.
TFTPconn* connectToTFTPserver(const char *hostname, unsigned short port);

// Cierra una conexión activa del cliente con el servidor TFTP
void closeTFTPclientConnection(TFTPconn* clientConnection);

// Envía por la conexión 'clientConnection' un paquete/pedido de escritura del protocolo TFTP al servidor.
// El nombre del archivo a escribir está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
bool sendWriteRequest(TFTPconn* clientConnection, char* fileName);

// Envía por la conexión 'clientConnection' un paquete/pedido de lectura del protocolo TFTP al servidor.
// El nombre del archivo a leer está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
bool sendReadRequest(TFTPconn* clientConnection, char* fileName);


///////////////////////
// Fucniones COMUNES //
///////////////////////

// Envía por 'currentConnection' un paquete de datos del protocolo TFTP, de largo 'dataBytes'. Los bytes enviados no pueden exceder TFTP_DATA_SIZE.
// Se devueve FALSE en si se indica 'dataBytes' incorrectamente, o si la conexión no se pudo realizar. TRUE es devuelto en caso de éxito.
bool sendDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int dataBytes);

// Verifica si se recibió por 'currentConnection' un paquete de datos del protocolo TFTP, de largo indicado en 'dataBytes'.
// En caso de no estar activa la conexión, o de no recibirse dicho paquete, se devuelve FALSE. Si se recibió exitosamente el paquete, se devuelve TRUE.
bool getDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int* dataBytes);

// Envía un paquete ACK por la conexión 'connection'. Devuelve TRUE si se envió, FALSE si hubo problemas en la conexión.
bool sendAcknowledgement(TFTPconn* connection);

// Verifica si se recibió un parquete ACK por 'connection'. Devuelve TRUE si se recibió y es la respuesta esperada (respuesta al último paquete enviado).
// Devuelve FALSE si no se recibió un paquete ACK válido, o si la conexión caducó.
bool getAcknowledgement(TFTPconn* connection);

// Devuelve TRUE si la conexión se mantiene activa, FASLE en caso contrario.
bool isTFTPconnActive(TFTPconn* connection);

#endif // TFTP_LIB_H_INCLUDED
