#ifndef __ACPRINTF_H__
#define __ACPRINTF_H__
#include <Arduino.h>
namespace ACross
{
int printf_out_serial( char c, FILE * );
void printf_serial_init(void);


};
#endif // __ACPRINTF_H__