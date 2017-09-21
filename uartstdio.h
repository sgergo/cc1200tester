#ifndef UARTSTDIO_H
#define UARTSTDIO_H

#include <stdarg.h>

#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE     128
#endif

#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE     1024
#endif

extern void uartstdio_config(uint32_t port, uint32_t baud, uint32_t clockfreq);
extern int uartstdio_gets(char *buf, uint32_t len);
extern unsigned char uartstdio_getc(void);
extern void uartstdio_printf(const char *char_ptr, ...);
extern void uartstdio_vprintf(const char *char_ptr, va_list vaArgP);
extern int uartstdio_write(const char *buf, uint32_t len);

extern int uartstdio_peek(unsigned char character);
extern void uartstdio_flushtx(bool is_discard);
extern void uartstdio_flushrx(void);
extern int uartstdio_rxbytesavail(void);
extern int uartstdio_txbytesfree(void);
extern void uartstdio_echoset(bool enable);
extern void uartstdio_isr(void);


#endif // UARTSTDIO_H
