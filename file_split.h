#ifndef FILE_SPLIT_H_INCLUDED
#define FILE_SPLIT_H_INCLUDED

typedef

void validateFileName(char* fileName);

void getNextFileBlock(FILE* sourceFile, char* dest, unsigned blockSize);

void saveNextFileBlock(const char* source, FILE* destFile, unsigned blockSize);

#endif // FILE_SPLIT_H_INCLUDED
