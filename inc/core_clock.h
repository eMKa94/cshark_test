#ifndef CORE_CLOCK_H
#define CORE_CLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum e_clkErr_t
    {
        CLK_OK   = 0,
        CLK_FAIL = 1,

    } e_clkErr_t;

    e_clkErr_t coreClockInit(void);

    void coreMcoEnable(void);
    void coreMcoDisable(void);

#ifdef __cplusplus
}
#endif

#endif
