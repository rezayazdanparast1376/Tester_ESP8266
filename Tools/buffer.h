#ifndef _SERIAL_BUFFER_H_
#define _SERIAL_BUFFER_H_

#include <stdint.h>
#include "defs.h"



// UInt8 buffer[BUFFER_SIZE] = {0};


typedef struct SERIAL_BUFFER_t {
    volatile UInt32  _WrIndex;
    volatile UInt32  _ReadIndex;
    volatile UInt8* _buffer;
    volatile UInt32 _cap;
    volatile UInt32 _len;
    volatile UInt8   _inited;
    volatile UInt8  _err;
}SERIAL_BUFFER;


extern volatile SERIAL_BUFFER ublox_buffer;
extern SERIAL_BUFFER pc_buffer;


Void InitSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* mem_addr, UInt16 mem_size);
Void PushSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* data, UInt16 data_size);
Int16 PullSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* buffer, UInt16 data_size);
Void ResetSerialBuffer(volatile SERIAL_BUFFER* serial_buffer);
UInt16 CapSerialBuffer(volatile SERIAL_BUFFER* serial_buffer);
UInt16 LenSerialBuffer(volatile SERIAL_BUFFER* serial_buffer);
Void DeinitSerialBuffer(volatile SERIAL_BUFFER* serial_buffer);




















#endif //_SERIAL_BUFFER_H_
