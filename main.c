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


#define TFTP_PORT   69


#define __SERVER
#ifdef __SERVER
int main()
{
    TFTPconn* = currentConn;

    if( (currentConn = startTFTPserver(TFTP_PORT)) != NULL)
    {
        if(getTFTPconnection(currentConn))
        {

        }
    }


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
void wait(long milliseconds)
{
  long timeout = clock() + milliseconds;
  while( clock() < timeout ) continue;
}


