#include "defs.h"






volatile static UInt32 time_ms = 0;


UInt32 MyTime_ms(Void) {
    return time_ms;
}


Void delay_ms(UInt16 _delay_ms) {
    UInt32 t0 = MyTime_ms();

    while (MyTime_ms() < (_delay_ms + t0));
    
}
