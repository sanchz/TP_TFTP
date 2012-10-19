#include <stdio.h>
#include <stdlib.h>

#include "polonet.h"

#include "TFTP_lib.h"

int main()
{
    return 0;
}





//    PolonetConn receivedConnection, forwConnection;
//
//    if(startListening(69))
//        printf("Listened!\n");
//    while((receivedConnection = getAvailableConnection()) == 0)
//    {
//        printf("No available connection\n\n");
//        if(getchar()=='n')
//            if((forwConnection = openConnection("127.0.0.1", 69)) != 0)
//                printf("Connection request successful\n\n");
//
//        if(isPending(forwConnection))
//            printf("Pending\n");
//        else
//            printf("Not pending\n");
//
//        if(isConnected(forwConnection))
//            printf("Connected\n");
//        else
//            printf("Not Connected\n");
//    }
//    while(isConnected(forwConnection)==0)
//        printf("not connected!!!!\n\n");
