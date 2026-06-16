/**
 * @file    prv_io_map.h
 * @brief   Maps peripheral registers.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PRV_IO_MAP_H_
#define _PRV_IO_MAP_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "prv_device.h"

#define _PLIC_ORIGIN_ __plic_origin
#define _INT0_ISR_VECTOR_ADDR_ __int0_isr_vector_addr
#define _INT1_ISR_VECTOR_ADDR_ __int1_isr_vector_addr
#define _INT2_ISR_VECTOR_ADDR_ __int2_isr_vector_addr
#define _INT3_ISR_VECTOR_ADDR_ __int3_isr_vector_addr
#define _INT4_ISR_VECTOR_ADDR_ __int4_isr_vector_addr
#define _INT5_ISR_VECTOR_ADDR_ __int5_isr_vector_addr
#define _INT6_ISR_VECTOR_ADDR_ __int6_isr_vector_addr
#define _INT7_ISR_VECTOR_ADDR_ __int7_isr_vector_addr
#define _INT0_PRIORITY_ __int0_priority
#define _INT1_PRIORITY_ __int1_priority
#define _INT2_PRIORITY_ __int2_priority
#define _INT3_PRIORITY_ __int3_priority
#define _INT4_PRIORITY_ __int4_priority
#define _INT5_PRIORITY_ __int5_priority
#define _INT6_PRIORITY_ __int6_priority
#define _INT7_PRIORITY_ __int7_priority
#define _INT_CONFIG_ __int_config
#if PRV_FAMILY == PRV32
#define _INT_RETURN_ADDR_ __int_return_addr
#elif PRV_FAMILY == PRVX3
#define _INT_IRQ_ID_ __irq_id
#define _INT_SRC_ __int_src
#define _INT_CLR_ __int_clr
#define _INT_STAT_ __int_stat
#endif

#define _IO_ORIGIN_ __io_origin
#define _DDRA_ __ddra
#define _PORTA_ __porta
#define _LATA_ __lata
#define _DDRB_ __ddrb
#define _PORTB_ __portb
#define _LATB_ __latb
#define _LATD_ __latd
#define _ALTOUTACON_ __altoutacon
#define _ALTOUTBCON_ __altoutbcon
#define _T0CON_ __t0con
#define _T0L_ __t0l
#define _T0H_ __t0h
#define _T0ABUF_ __t0abuf
#define _T0BBUF_ __t0bbuf
#define _T1CON_ __t1con
#define _T1L_ __t1l
#define _T1H_ __t1h
#define _T1ABUF_ __t1abuf
#define _T1BBUF_ __t1bbuf
#define _T2CON_ __t2con
#define _T2L_ __t2l
#define _T2H_ __t2h
#define _T2ABUF_ __t2abuf
#define _T2BBUF_ __t2bbuf
#define _T3CON_ __t3con
#define _T3L_ __t3l
#define _T3H_ __t3h
#define _T3ABUF_ __t3abuf
#define _T3BBUF_ __t3bbuf
#define _T4CON_ __t4con
#define _T4L_ __t4l
#define _T4H_ __t4h
#define _T4BUF_ __t4buf
#define _TC0BUF_ __tc0buf
#define _T5CON_ __t5con
#define _T5L_ __t5l
#define _T5H_ __t5h
#define _T5BUF_ __t5buf
#define _TC1BUF_ __tc1buf
#define _TFREG_ __tfreg
#define _INT0MAP_ __int0map
#define _INT1MAP_ __int1map
#define _INT2MAP_ __int2map
#define _INT3MAP_ __int3map
#define _INT4MAP_ __int4map
#define _INT5MAP_ __int5map
#define _INT6MAP_ __int6map
#define _INT7MAP_ __int7map
#define _ALTOUTEN_ __altouten
#define _URT0CON_ __urt0con
#define _URT0BRG_ __urt0brg
#define _URT0TX_ __urt0tx
#define _URT0RX_ __urt0rx
#define _URT1CON_ __urt1con
#define _URT1BRG_ __urt1brg
#define _URT1TX_ __urt1tx
#define _URT1RX_ __urt1rx
#define _I2C0CON0_ __i2c0con0
#define _I2C0CON1_ __i2c0con1
#define _I2C0CON2_ __i2c0con2
#define _I2C0TX_ __i2c0tx
#define _I2C0RX_ __i2c0rx
#define _EXT0CON_ __ext0con
#define _EXT1CON_ __ext1con
#define _EXT2CON_ __ext2con
#define _EXT3CON_ __ext3con
#define _PWM0CON_ __pwm0con
#define _PWM0DC_ __pwm0dc
#define _PWM1CON_ __pwm1con
#define _PWM1DC_ __pwm1dc
#define _PWM2CON_ __pwm2con
#define _PWM2DC_ __pwm2dc
#define _PWM3CON_ __pwm3con
#define _PWM3DC_ __pwm3dc
#define _PWM4CON_ __pwm4con
#define _PWM4DC_ __pwm4dc
#define _PWM5CON_ __pwm5con
#define _PWM5DC_ __pwm5dc
#define _SPI0CON0_ __spi0con0
#define _SPI0CON1_ __spi0con1
#define _SPI0TX_ __spi0tx
#define _SPI0RX_ __spi0rx

#define _PLIC_ __plic
#define _PLIC_PRIORITY_ __plic_prio
#define _GPIO_PORTA_ __gpio_porta
#define _GPIO_PORTB_ __gpio_portb
#define _GPIO_LED_ __gpio_led
#define _GPIO_ALTOUTACON_ __gpio_altoutacon
#define _GPIO_ALTOUTBCON_ __gpio_altoutbcon
#define _TIMER0_ __timer0
#define _TIMER1_ __timer1
#define _TIMER2_ __timer2
#define _TIMER3_ __timer3
#define _TIMER4_ __timer4
#define _TIMER5_ __timer5
#define _TIMER_TFREG_ __timer_tfreg
#define _INTMAP_ __intmap
#define _GPIO_ALTEN_ __gpio_alten
#define _URT0_ __urt0
#define _URT1_ __urt1
#define _I2C0_ __i2c0
#define _EXT_INT_ __ext_int
#define _PWM0_ __pwm0
#define _PWM1_ __pwm1
#define _PWM2_ __pwm2
#define _PWM3_ __pwm3
#define _PWM4_ __pwm4
#define _PWM5_ __pwm5
#define _SPI0_ __spi0

extern volatile uint32_t __plic[];             // base of PLIC: contains int[0..7]_isr_vector_addr and int[0..7]_priority.
extern volatile uint32_t __plic_prio[];        // base of PLIC_PRIORITY: int[0..7]_priority.
extern volatile uint32_t __gpio_porta[];       // base of GPIO_PORTA: contains ddra, porta and lata.
extern volatile uint32_t __gpio_portb[];       // base of GPIO_PORTB: contains ddrb, portb and latb.
extern volatile uint32_t __gpio_led[];         // base of GPIO_LED: contains latd.
extern volatile uint32_t __gpio_altoutacon[];  // base of ALTOUTACON: contains altoutacon.
extern volatile uint32_t __gpio_altoutbcon[];  // base of ALTOUTACON: contains altoutacon.
extern volatile uint32_t __timer0[];           // base of TIMER0: contains t0con, t0l and t0h.
extern volatile uint32_t __timer1[];           // base of TIMER1: contains t1con, t1l and t0h.
extern volatile uint32_t __timer2[];           // base of TIMER2: contains t2con, t2l and t0h.
extern volatile uint32_t __timer3[];           // base of TIMER3: contains t3con, t3l and t0h.
extern volatile uint32_t __timer4[];           // base of TIMER4: contains t4con, t4l and t0h.
extern volatile uint32_t __timer5[];           // base of TIMER5: contains t5con, t5l and t0h.
extern volatile uint32_t __timer_tfreg[];      // base of TFREG: contains tfreg.
extern volatile uint32_t __intmap[];           // base of INTMAP: contains int[0..7]map.
extern volatile uint32_t __gpio_alten[];       // base of ALTOUTEN: contains altouten.
extern volatile uint32_t __urt0[];             // base of URT0: contains urt0con, urt0brg, urt0tx and urt0rx.
extern volatile uint32_t __urt1[];             // base of URT1: contains urt1con, urt1brg, urt1tx and urt1rx.
extern volatile uint32_t __i2c0[];             // base of I2C0: contains i2c0con[0..2], i2c0tx and i2c0rx.
extern volatile uint32_t __ext_int[];          // base of EXTCON: contains ext[0..3]con.
extern volatile uint32_t __pwm0[];             // base of PWM0: contains pwm0con and pwm0dc.
extern volatile uint32_t __pwm1[];             // base of PWM1: contains pwm1con and pwm1dc.
extern volatile uint32_t __pwm2[];             // base of PWM2: contains pwm2con and pwm2dc.
extern volatile uint32_t __pwm3[];             // base of PWM3: contains pwm3con and pwm3dc.
extern volatile uint32_t __pwm4[];             // base of PWM4: contains pwm4con and pwm4dc.
extern volatile uint32_t __pwm5[];             // base of PWM5: contains pwm5con and pwm5dc.
extern volatile uint32_t __spi0[];             // base of spi0: contains spi0con[0..1], spi0tx, spi0rx.

extern volatile uint32_t __plic_origin;
extern volatile uint32_t __int0_isr_vector_addr;
extern volatile uint32_t __int1_isr_vector_addr;
extern volatile uint32_t __int2_isr_vector_addr;
extern volatile uint32_t __int3_isr_vector_addr;
extern volatile uint32_t __int4_isr_vector_addr;
extern volatile uint32_t __int5_isr_vector_addr;
extern volatile uint32_t __int6_isr_vector_addr;
extern volatile uint32_t __int7_isr_vector_addr;
extern volatile uint32_t __int0_priority;
extern volatile uint32_t __int1_priority;
extern volatile uint32_t __int2_priority;
extern volatile uint32_t __int3_priority;
extern volatile uint32_t __int4_priority;
extern volatile uint32_t __int5_priority;
extern volatile uint32_t __int6_priority;
extern volatile uint32_t __int7_priority;
extern volatile uint32_t __int_config;
#if PRV_FAMILY == PRV32
extern volatile uint32_t __int_return_addr;
#elif PRV_FAMILY == PRVX3
extern volatile uint32_t __irq_id;
extern volatile uint32_t __int_src;
extern volatile uint32_t __int_clr;
extern volatile uint32_t __int_stat;
#endif

extern volatile uint32_t __io_origin;
extern volatile uint32_t __ddra;
extern volatile uint32_t __porta;
extern volatile uint32_t __lata;
extern volatile uint32_t __ddrb;
extern volatile uint32_t __portb;
extern volatile uint32_t __latb;
extern volatile uint32_t __latd;
extern volatile uint32_t __altoutacon;
extern volatile uint32_t __altoutbcon;
extern volatile uint32_t __t0con;
extern volatile uint32_t __t0l;
extern volatile uint32_t __t0h;
extern volatile uint32_t __t0abuf;
extern volatile uint32_t __t0bbuf;
extern volatile uint32_t __t1con;
extern volatile uint32_t __t1l;
extern volatile uint32_t __t1h;
extern volatile uint32_t __t1abuf;
extern volatile uint32_t __t1bbuf;
extern volatile uint32_t __t2con;
extern volatile uint32_t __t2l;
extern volatile uint32_t __t2h;
extern volatile uint32_t __t2abuf;
extern volatile uint32_t __t2bbuf;
extern volatile uint32_t __t3con;
extern volatile uint32_t __t3l;
extern volatile uint32_t __t3h;
extern volatile uint32_t __t3abuf;
extern volatile uint32_t __t3bbuf;
extern volatile uint32_t __t4con;
extern volatile uint32_t __t4l;
extern volatile uint32_t __t4h;
extern volatile uint32_t __t4buf;
extern volatile uint32_t __tc0buf;
extern volatile uint32_t __t5con;
extern volatile uint32_t __t5l;
extern volatile uint32_t __t5h;
extern volatile uint32_t __t5buf;
extern volatile uint32_t __tc1buf;
extern volatile uint32_t __tfreg;
extern volatile uint32_t __int0map;
extern volatile uint32_t __int1map;
extern volatile uint32_t __int2map;
extern volatile uint32_t __int3map;
extern volatile uint32_t __int4map;
extern volatile uint32_t __int5map;
extern volatile uint32_t __int6map;
extern volatile uint32_t __int7map;
extern volatile uint32_t __altouten;
extern volatile uint32_t __urt0con;
extern volatile uint32_t __urt0brg;
extern volatile uint32_t __urt0tx;
extern volatile uint32_t __urt0rx;
extern volatile uint32_t __urt1con;
extern volatile uint32_t __urt1brg;
extern volatile uint32_t __urt1tx;
extern volatile uint32_t __urt1rx;
extern volatile uint32_t __i2c0con0;
extern volatile uint32_t __i2c0con1;
extern volatile uint32_t __i2c0con2;
extern volatile uint32_t __i2c0tx;
extern volatile uint32_t __i2c0rx;
extern volatile uint32_t __ext0con;
extern volatile uint32_t __ext1con;
extern volatile uint32_t __ext2con;
extern volatile uint32_t __ext3con;
extern volatile uint32_t __pwm0con;
extern volatile uint32_t __pwm0dc;
extern volatile uint32_t __pwm1con;
extern volatile uint32_t __pwm1dc;
extern volatile uint32_t __pwm2con;
extern volatile uint32_t __pwm2dc;
extern volatile uint32_t __pwm3con;
extern volatile uint32_t __pwm3dc;
extern volatile uint32_t __pwm4con;
extern volatile uint32_t __pwm4dc;
extern volatile uint32_t __pwm5con;
extern volatile uint32_t __pwm5dc;
extern volatile uint32_t __spi0con0;
extern volatile uint32_t __spi0con1;
extern volatile uint32_t __spi0tx;
extern volatile uint32_t __spi0rx;

#endif /* _PRV_IO_MAP_H_ */