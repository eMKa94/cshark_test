#pragma once

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"
{
#endif


    typedef enum e_lpuartErr_t
    {
        LPU_OK   = 0,
        LPU_FAIL = 1,
    } e_lpuartErr_t;

    e_lpuartErr_t coreLpuartInit(void);

    e_lpuartErr_t coreLpuartSendByte(uint8_t byte);
    char          coreLpuartReceiveByte(void);
    bool          coreLpuartIsByteReceived(void);


#ifdef __cplusplus
}
#endif