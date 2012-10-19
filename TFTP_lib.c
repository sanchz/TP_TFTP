/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */

#include "TFTP_lib.h"
#include "file_split.h"



// Inicializa el servidor TFTP, que recibe conexiones en el puerto 'port'.
void startTFTPserver(unsigned short port)
{
    // start listening
}

// Devuelve una nueva conexión exitosa al servidor.
// Es bloqueante, ya que espera a que la conexión se haya establecido.
// De no poder realizarse la conexión (o de producirse un timeout de TFTP_TIMEOUT milisegundos),
// se devuelve NULL.
TFTPconn* getTFTPconnection()
{
    // alocar memoria
    // get connection
    // is pending
    // block number = 0

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
    // alocar
    // openConnection
    // block number = 0
}

// Cierra una conexión activa del cliente con el servidor TFTP
void closeTFTPclientConnection(TFTPconn* clientConnection)
{
    // closeConnection
    // free
}

// Envía por la conexión 'currentConnection' un paquete/pedido de escritura del protocolo TFTP al servidor.
// El nombre del archivo a escribir está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
bool sendWriteRequest(TFTPconn* currentConnection, char* fileName)
{
    // verificar isConnected
    // verificar num bytes enviados
}

// Envía por la conexión 'currentConnection' un paquete/pedido de lectura del protocolo TFTP al servidor.
// El nombre del archivo a leer está indicado por 'fileName', cadena terminada en '\0'.
// Si no se pudo enviar el paquete (conexión caduca), se devuelve FALSE.
// Si no hublo problemas de conexión, devuelve TRUE.
bool sendReadRequest(TFTPconn* currentConnection, char* fileName)
{
    // verificar isConnected
    // verificar num bytes enviados
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

// Envía un paquete ACK por la conección 'connection'. Devuelve TRUE si se envió, FALSE si hubo problemas en la conexión.
bool sendAcknowledgement(TFTPconn* connection)
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




