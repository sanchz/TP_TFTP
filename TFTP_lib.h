#ifndef TFTP_LIB_H_INCLUDED
#define TFTP_LIB_H_INCLUDED

#include "bool_def.h"
#include "polonet.h"

#define MAX_FILENAME_LENGTH 100
#define DATA_SIZE   512

typedef enum requests {RRQ, WRQ, NO_REQ} Requests;

//typedef struct
//{
//    PolonetConn currentConnection;
//    unsigned tid;
//    unsigned long blockNumber;
//} TFTPconn;

typedef PolonetConn TFTPconn;

// bkbjkb
Requests getRequest(TFTPconn* currentConnection, char fileName[MAX_FILENAME_LENGTH]);

void sendWriteRequest(TFTPconn* currentConnection, char* fileName);

void sendReadRequest(TFTPconn* currentConnection, char* fileName);

bool getDataPacket(TFTPconn* currentConnection, char data[512], int* dataBytes);

bool sendDataPacket(TFTPconn* currentConnection, char data[512], int dataBytes);


#endif // TFTP_LIB_H_INCLUDED
