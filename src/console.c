#include <sys/stat.h>
#include <sys/unistd.h>

#include "stm32f4xx.h"

#include "console.h"

void console_setup(void) {
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);

    USART_Cmd(UART4, ENABLE);

    // USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    // NVIC_EnableIRQ(UART4_IRQn);
}

int _isatty(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    return 0;
}

int _fstat(int fd, struct stat *pStat) {
    pStat->st_mode = S_IFCHR;
    return 0;
}

int _read(int fd, char *pBuffer, int size) {
    for (int i = 0; i < size; i++) {
        while ((UART4->SR & USART_SR_RXNE) == 0) {}
        char c = USART_ReceiveData(UART4);
        while (!(UART4->SR & USART_SR_TXE)) {}
        USART_SendData(UART4, c);
        pBuffer[i] = c;
    }
    return size;
}

int _lseek(int fd, int ptr, int dir) {
    return -1;
}

int _close(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    return -1;
}

int _write (int fd, char *pBuffer, int size) {
    for (int i = 0; i < size; i++) {
        while (!(UART4->SR & USART_SR_TXE)) {}
        USART_SendData(UART4, pBuffer[i]);
    }
    return size;
}

caddr_t _sbrk(int increment) {
    extern char end asm("end");
    register char *pStack asm("sp");

    static char *s_pHeapEnd;

    if (!s_pHeapEnd)
        s_pHeapEnd = &end;

    if (s_pHeapEnd + increment > pStack)
        return (caddr_t)-1;

    char *pOldHeapEnd = s_pHeapEnd;
    s_pHeapEnd += increment;
    return (caddr_t)pOldHeapEnd;
}
