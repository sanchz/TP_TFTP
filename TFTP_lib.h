#ifndef TFTP_LIB_H_INCLUDED
#define TFTP_LIB_H_INCLUDED




#include "bool_def.h"
#include "polonet.h"

#define MAX_FILENAME_LENGTH     100
#define TFTP_DATA_SIZE          512
#define TFTP_TIMEOUT            3000    // Milisegundos

typedef enum requests {RRQ, WRQ, NO_REQ} Requests;

typedef struct
{
    PolonetConn currentConnection;
    unsigned tid;
    unsigned long blockNumber;
} TFTPconn;


// Verifica en 'currentConnection' si se produjo un nuevo pedido.
// La conexi�n debe estar hecha y activa.
// Si el paquete recibido es un pedido de lectura o escritura del protocolo TFTP, se indica
// con las constantes RRQ o WRQ como valores devueltos por la funci�n, respectivamente.
// En este caso se guarda el nombre del archivo indicado por el paquete en 'fileName' (se corta el mismo si excede los MAX_FILENAME_LENGTH caracteres).
// Cualquier otro paquete es descartado, y se devueve una constante NO_REQ en este caso.
// Si no se recibi� un paquete de lectura o de escritura se devuelve NO_REQ.
Requests getRequest(PolonetConn* currentConnection, char fileName[MAX_FILENAME_LENGTH + 1]);

void sendAcknowledgement();

// Env�a por la conexi�n 'currentConnection' un paquete/pedido de escritura del protocolo TFTP al servidor.
// El nombre del archivo a escribir est� indicado por 'fileName', cadena terminada en '\0'.
// La funci�n es bloqueante, ya que espera la confirmaci�n del servidor. En caso de que no haya
// respuesta luego de 'TFTP_TIMEOUT' milisegundos, se devuelve FALSE.
// Si el pedido fue reconocido, se devuelve TRUE.
bool sendWriteRequest(PolonetConn* currentConnection, char* fileName);

// Env�a por la conexi�n 'currentConnection' un paquete/pedido de lectura del protocolo TFTP al servidor.
// El nombre del archivo a leer est� indicado por 'fileName', cadena terminada en '\0'.
void sendReadRequest(PolonetConn* currentConnection, char* fileName);


// Env�a por 'currentConnection' un paquete de datos del protocolo TFTP, de largo 'dataBytes'. Los bytes enviados no pueden exceder TFTP_DATA_SIZE,
// se devueve FALSE en si se indica un n�mero mayor.
// S�lo en caso de que se haya enviado correctamente el paquete y el receptor indique que lo recibi� se devuelve TRUE.
// Si, luego de un timeout de 'TFTP_TIMEOUT' milisegundos no se logr� enviarlo exitosamente, se devuelve FALSE.
// Si se pretenden enviar una cantidad mayor a
bool sendDataPacket(PolonetConn* currentConnection, char data[TFTP_DATA_SIZE], int dataBytes);

// Recibe por 'currentConnection' un paquete de datos del protocolo TFTP. Los bytes enviados no pueden exceder TFTP_DATA_SIZE.
// S�lo en caso de que se haya enviado correctamente el paquete y el receptor indique que lo recib�o se devuelve TRUE.
// Si, luego de un timeout de 'TFTP_TIMEOUT' milisegundos no se logr� enviarlo exitosamente, se devuelve FALSE.
// La funci�n es bloqueante.
bool getDataPacket(PolonetConn* currentConnection, char data[TFTP_DATA_SIZE], int* dataBytes);



#endif // TFTP_LIB_H_INCLUDED
