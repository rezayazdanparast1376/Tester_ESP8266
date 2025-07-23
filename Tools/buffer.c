#include "buffer.h"
#include <stdlib.h>
#include "defs.h"




/**
 * @brief Initialize buffer.
*/
Void InitSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* mem_addr, UInt16 mem_size) {
    if (serial_buffer == NULL) {
        return;
    }
    if (mem_addr == NULL) {
        return;
    }
    if (serial_buffer->_inited == 1) {
        return;
    }
    
    serial_buffer->_buffer    = mem_addr;
    serial_buffer->_WrIndex   = 0;
    serial_buffer->_ReadIndex = 0;
    serial_buffer->_len       = 0;
    serial_buffer->_cap       = mem_size;
    serial_buffer->_inited    = 1;
    serial_buffer->_err       = 0;
}




/**
 * @brief Push in buffer
*/
Void PushSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* data, UInt16 data_size) {
    if (serial_buffer == NULL)       return;
    if (data == NULL)                return;
    if (serial_buffer->_inited == 0) return;
    
    volatile UInt8* _buff    = serial_buffer->_buffer;
    // uint16_t WR_Index = serial_buffer->_WrIndex;
    // uint16_t RD_Index = serial_buffer->_ReadIndex;
    UInt16 _cap     = serial_buffer->_cap;
    // uint16_t _len     = serial_buffer->_len;

    if (serial_buffer->_len > _cap) {
        serial_buffer->_err++;
//        return;
    }
    
    /**
     * Saving data[save_counter] in serial buffer.
    */
    for (UInt16 save_counter = 0; save_counter < data_size; save_counter++) { // Save data in buffer ...
        if (serial_buffer->_len < _cap) {                              /* buffer is empty */
            *(_buff + serial_buffer->_WrIndex) = data[save_counter];   /* save in empty index */
            serial_buffer->_WrIndex = (serial_buffer->_WrIndex + 1) % _cap;           /* update WR_Index */
            serial_buffer->_len++;                                     /* update buffer len */
        } 
        else if (serial_buffer->_len == _cap ) {                       /* buffer is full */
            *(_buff + serial_buffer->_WrIndex) = data[save_counter];   /* over write in buffer */
            serial_buffer->_WrIndex = (serial_buffer->_WrIndex + 1) % _cap;           /* update WR_Index */
            serial_buffer->_ReadIndex = (serial_buffer->_ReadIndex + 1) % _cap;

        } 
    }

    if (serial_buffer->_len > _cap) {
        serial_buffer->_err++;
//        return;
    }
    
    UInt32 new_len = LenSerialBuffer(serial_buffer);
    if ((new_len > serial_buffer->_len) && (new_len < serial_buffer->_cap) && (new_len > 0)) {
        serial_buffer->_len = new_len;
    }
    // serial_buffer->_WrIndex   = WR_Index;
    // serial_buffer->_ReadIndex = RD_Index;
    serial_buffer->_cap       = _cap;
    // serial_buffer->_len       = _len;
}




/**
 * pull from buffer.
*/
Int16 PullSerialBuffer(volatile SERIAL_BUFFER* serial_buffer, UInt8* buffer, UInt16 data_size) {
    if (serial_buffer == NULL) return 0;
    if (buffer == NULL) return 0;
    if (serial_buffer->_inited == 0) return 0;

    volatile UInt8* _buff    = serial_buffer->_buffer;
    UInt32 _len     = serial_buffer->_len;
    UInt32 new_len = LenSerialBuffer(serial_buffer);
    if ((new_len > _len) && (new_len < serial_buffer->_cap) && (new_len > 0)) {
        // _len = new_len;
    }
    
    
    
    if (_len > serial_buffer->_cap) serial_buffer->_err++;
    
    if (_len == 0) {/* Buffer is empty. Noting pull any data. */
        return 0; 
    }

    else if (_len > data_size) {                                                       /* Saved data is enough. pull data as much as data size*/
        for (UInt32 pull_counter = 0; pull_counter < data_size; pull_counter++) {       // pull data as much as data size ...
            *(buffer + pull_counter) = *(_buff + serial_buffer->_ReadIndex);
            serial_buffer->_ReadIndex = (serial_buffer->_ReadIndex + 1) % serial_buffer->_cap;
            serial_buffer->_len--;
            
            if (serial_buffer->_len > serial_buffer->_cap) serial_buffer->_err++;
            
        }
    }
    else if (_len <= data_size) {                                                            /* Saved data is less than data size. pull data as much as saved data*/
        for (UInt32 pull_counter = 0; pull_counter < _len; pull_counter++) {       // pull data as much as data size ...

            *(buffer + pull_counter) = *(_buff + serial_buffer->_ReadIndex);
            serial_buffer->_ReadIndex = (serial_buffer->_ReadIndex + 1) % serial_buffer->_cap;
            serial_buffer->_len--;
            
            if (serial_buffer->_len > serial_buffer->_cap) serial_buffer->_err++;
            
        }
    }

    if (serial_buffer->_len > serial_buffer->_cap) serial_buffer->_err++;

    return _len;
}


/**
 * pull from buffer.
*/
Int16 PullSerialBuffer_dep(SERIAL_BUFFER* serial_buffer, UInt8* buffer, UInt16 data_size) {
    if (serial_buffer == NULL) {
        return 0;
    }
    if (buffer == NULL) {
        return 0;
    }
    if (serial_buffer->_inited == 0) {
        return 0;
    }

    volatile UInt8* _buff    = serial_buffer->_buffer;
    UInt16 RD_Index = serial_buffer->_ReadIndex;
    UInt16 _cap     = serial_buffer->_cap;
    UInt16 _len     = serial_buffer->_len;
    UInt16 WR_Index = serial_buffer->_WrIndex;

    if (_len > _cap) {
        serial_buffer->_err++;
        return 0;
    }

    if (_len == 0) {/* Buffer is empty. Noting pull any data. */
        return 0; 
    }
    else if (_len > data_size) {                                                       /* Saved data is enough. pull data as much as data size*/
        for (UInt16 pull_counter = 0; pull_counter < data_size; pull_counter++) {       // pull data as much as data size ...
            *(buffer + pull_counter) = *(_buff + RD_Index);
            RD_Index                 = (RD_Index + 1) % _cap;
            if (_len == 0) {
                serial_buffer->_err++;
            }
            
            _len--;
        }
    }
    else if (_len <= data_size) {                                                            /* Saved data is less than data size. pull data as much as saved data*/
        for (UInt16 pull_counter = 0; pull_counter < serial_buffer->_len; pull_counter++) {       // pull data as much as data size ...

            *(buffer + pull_counter) = *(_buff + RD_Index);
            RD_Index                 = (RD_Index + 1) % _cap;
            if (_len == 0) {
                serial_buffer->_err++;
            }
            
            _len--;
        }
    }

    if (_len > _cap) {
        serial_buffer->_err++;
        // return;
    }

    serial_buffer->_ReadIndex = RD_Index;
    serial_buffer->_cap       = _cap;
    serial_buffer->_len       = _len;

    return _len;
}


/**
 * reset buffer parameter.
*/
Void ResetSerialBuffer(volatile SERIAL_BUFFER* serial_buffer) {
    if (serial_buffer == NULL) {
        return;
    }
    if (serial_buffer->_inited == 0) {
        return;
    }
    serial_buffer->_WrIndex   = 0;
    serial_buffer->_ReadIndex = 0;
    serial_buffer->_len       = 0;
}




/**
 * return buffer capacity.
*/
UInt16 CapSerialBuffer(volatile SERIAL_BUFFER* serial_buffer) {
    if (serial_buffer == NULL) {
        return 0;
    }
    if (serial_buffer->_inited == 0) {
        return 0;
    }

    return serial_buffer->_cap;
}




UInt16 LenSerialBuffer(volatile SERIAL_BUFFER* serial_buffer) {
    if (serial_buffer == NULL) {
        return 0;
    }
    if (serial_buffer->_inited == 0) {
        return 0;
    }

    if (serial_buffer->_WrIndex > serial_buffer->_ReadIndex) {
        return serial_buffer->_WrIndex - serial_buffer->_ReadIndex;
    }
    else if (serial_buffer->_WrIndex > serial_buffer->_ReadIndex) {
        return serial_buffer->_cap - serial_buffer->_ReadIndex + serial_buffer->_WrIndex;
    }

    return 0;
}




Void DeinitSerialBuffer(volatile SERIAL_BUFFER* serial_buffer) {
    if (serial_buffer == NULL) {
        return;
    }
    if (serial_buffer->_inited == 0) {
        return;
    }

    serial_buffer->_buffer    = 0;
    serial_buffer->_WrIndex   = 0;
    serial_buffer->_ReadIndex = 0;
    serial_buffer->_len       = 0;
    serial_buffer->_cap       = 0;
    serial_buffer->_inited    = 0;
}
