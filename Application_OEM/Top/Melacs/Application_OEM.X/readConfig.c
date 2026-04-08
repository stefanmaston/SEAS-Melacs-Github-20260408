#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _READ_CONFIG_FUNC_

#include <sys.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include "main.h"
#include "stdlib.h"
#include <string.h>
#include <stdbool.h>
#include "readConfig.h"

//int atoi(const char *);

char variableNames[NUM_OF_PARAMETERS][LENGTH_VARIABLE_NAME];
char variableValues[NUM_OF_PARAMETERS][LENGTH_VARIABLE_VALUES];

int readConfig(char * filename)
{
    int file;
    char str[PARAMETER_FILE_SIZE] = {0};
    int numChar;
    int fileSize = 0;
    struct stat fileStat;
    char varName[LENGTH_VARIABLE_NAME] = {0};
    char varValue[LENGTH_VARIABLE_VALUES] = {0};
    int i = 0;
    int varCounter = 0;
    int varNameCounter = 0;
    int varValueCounter = 0;
    bool ifEqualSymbol = 0;
    /* opening file for reading */

    file = open(filename, O_RDONLY, 0);
    if(file == -1)
    {
        xprintf("configuration file open error = %d, files should be %d\n", errno);
        return(-1);
    }

    if(fstat(file,&fileStat) < 0)
    {
        xprintf("fstat read error = %d\n", errno);
        return(-1);
    }

    fileSize = fileStat.st_size;
    
    if(fileSize > PARAMETER_FILE_SIZE)
    {
        xprintf("Not enough buffer for reading the parameter file\n");
        return -1;
    }

    if(-1 == lseek(file,0,SEEK_SET))
    {
        xprintf("files seek to end failed, fileno = %d, errno = %d\n", file, errno);
        return -1;
    }

    if((numChar = read(file, str, fileSize)) == -1)
    {
        xprintf("number of bytes read = %d, file = %d, errno = %d\n", numChar, file, errno);
        if(-1 == close(file))
        {
            xprintf("File Close failed");
        }
        return -1;
    }

    for(i = 0; i < fileSize; i++)
    {
        if(str[i] == '\n')
        {
            varValue[varValueCounter] = 0;
            varName[varNameCounter] = 0;
            if(varCounter < NUM_OF_PARAMETERS)
            {
                strcpy(variableNames[varCounter],varName);
                strcpy(variableValues[varCounter++],varValue);
            }
            ifEqualSymbol = 0;
            varValueCounter = 0;
            varNameCounter = 0;
        }
        else if((str[i] == '\r') || (str[i] == ' '))
        {
            //Just Skip it
        }
        else if(str[i] == '=')
        {
            ifEqualSymbol = 1;
        }
        else
        {
            if(1 == ifEqualSymbol)
            {
                varValue[varValueCounter++] = str[i];
            }
            else
            {
                varName[varNameCounter++] = str[i];
            }
        }
    }

    if(varNameCounter > 0)
    {
        varValue[varValueCounter] = 0;
        varName[varNameCounter] = 0;
        if(varCounter < NUM_OF_PARAMETERS)
        {
            strcpy(variableNames[varCounter],varName);
            strcpy(variableValues[varCounter++],varValue);
        }
        ifEqualSymbol = 0;
        varValueCounter = 0;
        varNameCounter = 0;
    }
    
    close(file);

    return (1);
}


int writeConfig(char * filename)
{
    int file;
    /* opening file for reading */

    file = open(filename, O_WRONLY | O_CREAT, 14);
    if(file == -1)
    {
        xprintf("configuration file open error = %d, files should be %d\n", errno);
        return(-1);
    }
    
    //TODO: Check how to handle write error
    (void)write(file, "Write_Date = 0", 14);            

    close(file);

    return (1);
}



void readConfigTest()
{
    readConfig("/dev/sd/d1/parameters.txt");
}

#endif