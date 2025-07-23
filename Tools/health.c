#include "health.h"
#include "buffer.h"






Void check_health(Void) {
    check_health_serial_buffer();

}




















UInt32 max_len_ublox_buffer = 0;
UInt32 max_factor_ublox_buf = 0;
Void check_health_serial_buffer(Void) {
    UInt16 len = LenSerialBuffer(&ublox_buffer);
    UInt16 cap = CapSerialBuffer(&ublox_buffer);
    if (len > max_len_ublox_buffer) {
        max_len_ublox_buffer = len;
    }

    max_factor_ublox_buf = (max_len_ublox_buffer / cap) * 100;
}

