/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _QUEUEHANDLER_H    /* Guard against multiple inclusion */
#define _QUEUEHANDLER_H

typedef enum
{   
    NONELED,            //0
    DISPLAYONELED,      //1
    DISPLAYTWOLED,      //2 
    DISPLAYTHREELED,    //3
    DISPLAYFOURLED,     //4
    TIMEUPDATE,         //5
    IOCONTROL,          //6
    MODBUSSEQUENCE,     //7
    RECEIVEPACKET, //8
} QUEUE_t;


typedef enum
{   
    TEST1,
    TEST2,
    TEST3,
            
} QUEUE_SEND_t;

void QueueMain();
        
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
