/*
TRABAJO PR�CTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, Jos� Maria	jbracco@alu.itba.edu.ar
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

// Inicializa el servidor TFTP, que recibe conexiones en el puerto 'port'. Devuelve la nueva conexi�n. Aloca memoria
// que es liberada en 'closeTFTPserver()'. Si no se puedo establecer la conexi�n se devuelve NULL.
TFTPconn* startTFTPserver(unsigned short port);

// Devuelve una nueva conexi�n entrante exitosa en 'connection'.
// Es bloqueante, ya que espera a que la conexi�n se haya establecido.
// De no poder realizarse la conexi�n (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve FALSE. Si se pudo establecer devuelve TRUE.
bool getTFTPconnection(TFTPconn* connection);

// Cierra la conexi�n 'connection' y deja de recibir conexiones.
void closeTFTPserver(TFTPconn* connection);

// Verifica en 'currentConnection' si se produjo un nuevo pedido.
// La conexi�n debe estar hecha y activa.
// Si el paquete recibido es un pedido de lectura o escritura del protocolo TFTP, se indica
// con las constantes RRQ o WRQ como valores devueltos por la funci�n, respectivamente.
// En este caso se guarda el nombre del archivo indicado por el paquete en 'fileName' (se corta el mismo si excede los MAX_FILENAME_LENGTH caracteres).
// Cualquier otro paquete es descartado, y se devueve una constante NO_REQ en este caso.
// Si no se recibi� un paquete de lectura o de escritura se devuelve NO_REQ.
Requests getRequest(TFTPconn* currentConnection, char fileName[MAX_FILENAME_LENGTH + 1]);


///////////////////////////
// Funciones del CLIENTE //
///////////////////////////

// Devuelve una nueva conexi�n exitosa al servidor.
// Es bloqueante, ya que espera a que la conexi�n se haya establecido.
// De no poder realizarse la conexi�n (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve NULL.
TFTPconn* connectToTFTPserver(const char *hostname, unsigned short port);

// Cierra una conexi�n activa del cliente con el servidor TFTP
void closeTFTPclientConnection(TFTPconn* clientConnection);

// Env�a por la conexi�n 'clientConnection' un paquete/pedido de escritura del protocolo TFTP al servidor.
// El nombre del archivo a escribir est� indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexi�n caduca), se devuelve FALSE.
// Si no hublo problemas de conexi�n, devuelve TRUE.
bool sendWriteRequest(TFTPconn* clientConnection, char* fileName);

// Env�a por la conexi�n 'clientConnection' un paquete/pedido de lectura del protocolo TFTP al servidor.
// El nombre del archivo a leer est� indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexi�n caduca), se devuelve FALSE.
// Si no hublo problemas de conexi�n, devuelve TRUE.
bool sendReadRequest(TFTPconn* clientConnection, char* fileName);


///////////////////////
// Fucniones COMUNES //
///////////////////////

// Env�a por 'currentConnection' un paquete de datos del protocolo TFTP, de largo 'dataBytes'. Los bytes enviados no pueden exceder TFTP_DATA_SIZE.
// Se devueve FALSE en si se indica 'dataBytes' incorrectamente, o si la conexi�n no se pudo realizar. TRUE es devuelto en caso de �xito.
bool sendDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int dataBytes);

// Verifica si se recibi� por 'currentConnection' un paquete de datos del protocolo TFTP, de largo indicado en 'dataBytes'.
// En caso de no estar activa la conexi�n, o de no recibirse dicho paquete, se devuelve FALSE. Si se recibi� exitosamente el paquete, se devuelve TRUE.
bool getDataPacket(TFTPconn* currentConnection, char data[TFTP_DATA_SIZE], int* dataBytes);

// Env�a un paquete ACK por la conexi�n 'connection'. Devuelve TRUE si se envi�, FALSE si hubo problemas en la conexi�n.
bool sendAcknowledgement(TFTPconn* connection);

// Verifica si se recibi� un parquete ACK por 'connection'. Devuelve TRUE si se recibi� y es la respuesta esperada (respuesta al �ltimo paquete enviado).
// Devuelve FALSE si no se recibi� un paquete ACK v�lido, o si la conexi�n caduc�.
bool getAcknowledgement(TFTPconn* connection);

// Devuelve TRUE si la conexi�n se mantiene activa, FASLE en caso contrario.
bool isTFTPconnActive(TFTPconn* connection);

#endif // TFTP_LIB_H_INCLUDED
