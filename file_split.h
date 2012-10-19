/*
TRABAJO PRÁCTICO No 8 - TFTP
EDA 2012
ITBA

GRUPO 3:
        Bracco, José Maria	jbracco@alu.itba.edu.ar
        Herrero, Santiago	saherrer@alu.itba.edu.ar
        Seeber, Lucas       lseeber@alu.itba.edu.ar
 */


#ifndef FILE_SPLIT_H_INCLUDED
#define FILE_SPLIT_H_INCLUDED

typedef

void validateFileName(char* fileName);

void getNextFileBlock(FILE* sourceFile, char* dest, unsigned blockSize);

void saveNextFileBlock(const char* source, FILE* destFile, unsigned blockSize);

#endif // FILE_SPLIT_H_INCLUDED
