/*
 *  File name: App_DataRec.h
 *
 *  Description: High level function declarations for Data Recording processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_DATA_REC_H
#define APP_DATA_REC_H

extern volatile uint8_t		DataRecState;
extern volatile uint32_t	DataRecAddr;
extern volatile uint8_t		DataRecCfg1;

void App_DataRec_Init(void *Parameters);
void App_DataRec_Process(void *Parameters);
void App_DataRec_Set(uint8_t Parameters);
inline void App_DataRec_Store_8bit(uint8_t Data);
inline void App_DataRec_Store_16bit(uint16_t Data);
inline void App_DataRec_Store_32bit(uint32_t Data);
uint32_t App_DataRec_Get_Length(void);
bool App_DataRec_Load_Buffer(void *Data, uint16_t Size);
bool App_DataRec_Load_Word(void *Data);

#endif // APP_DATA_REC_H
