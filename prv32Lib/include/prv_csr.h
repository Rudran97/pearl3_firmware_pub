/**
 * @file prv_csr.h
 * @brief Defines useful csr-access functions. This is modified version of
 * https://github.com/five-embeddev/riscv-csr-access/blob/master/include/riscv-csr.h 
 * @version 0.1
 * @date 2025-12-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PRV_CSR_H
#define PRV_CSR_H

#include <stdint.h>

#if __riscv_xlen==32
#else
#error "prv_csr.h : Unknown XLEN. Expected __riscv_xlen = 32"
#endif

typedef uint32_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint32_t uint_csr64_t;

/*******************************************
 * misa - MRW - Machine ISA 
 */
static inline uint_xlen_t csr_read_misa(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, misa" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mvendorid - MRO - Machine Vendor ID 
 */
static inline uint32_t csr_read_mvendorid(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mvendorid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * marchid - MRO - Machine Architecture ID 
 */
static inline uint_xlen_t csr_read_marchid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, marchid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mimpid - MRO - Machine Implementation ID 
 */
static inline uint_xlen_t csr_read_mimpid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mimpid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mhartid - MRO - Hardware Thread ID 
 */
static inline uint_xlen_t csr_read_mhartid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhartid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mstatus - MRW - Machine Status 
 */
static inline uint_xlen_t csr_read_mstatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mstatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mstatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    mstatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mstatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mstatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mstatus, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mstatus, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mstatus, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MSTATUS(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mstatus, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mstatus, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MSTATUS(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mstatus, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mstatus, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MSTATUS(MASK)               \
    __asm__ volatile ("csrrci    zero, mstatus, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MSTATUS_MIE_BIT_OFFSET   3
#define MSTATUS_MIE_BIT_WIDTH    1
#define MSTATUS_MIE_BIT_MASK     0x8
#define MSTATUS_MIE_ALL_SET_MASK 0x1
#define MSTATUS_MPIE_BIT_OFFSET   7
#define MSTATUS_MPIE_BIT_WIDTH    1
#define MSTATUS_MPIE_BIT_MASK     0x80
#define MSTATUS_MPIE_ALL_SET_MASK 0x1

/*******************************************
 * mtvec - MRW - Machine Trap Vector Base Address 
 */
static inline uint_xlen_t csr_read_mtvec(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtvec" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtvec(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtvec, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtvec(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtvec, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mtvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mtvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mtvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mtvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mtvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mtvec, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mtvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mtvec, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mtvec, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MTVEC(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mtvec, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mtvec, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MTVEC(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mtvec, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mtvec, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MTVEC(MASK)               \
    __asm__ volatile ("csrrci    zero, mtvec, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MTVEC_BASE_BIT_OFFSET   2
#define MTVEC_BASE_BIT_WIDTH    ((__riscv_xlen-1)-(2) + 1)
#define MTVEC_BASE_BIT_MASK     ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (2))
#define MTVEC_BASE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (0))
#define MTVEC_MODE_BIT_OFFSET   0
#define MTVEC_MODE_BIT_WIDTH    2
#define MTVEC_MODE_BIT_MASK     0x3
#define MTVEC_MODE_ALL_SET_MASK 0x3

/*******************************************
 * mip - MRW - Machine Interrupt Pending 
 */
static inline uint_xlen_t csr_read_mip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mip(uint_xlen_t value) {
    __asm__ volatile ("csrw    mip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mip(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mip(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mip, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mip, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mip, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MIP(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mip, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mip, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MIP(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mip, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mip, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MIP(MASK)               \
    __asm__ volatile ("csrrci    zero, mip, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MIP_MSI_BIT_OFFSET   3
#define MIP_MSI_BIT_WIDTH    1
#define MIP_MSI_BIT_MASK     0x8
#define MIP_MSI_ALL_SET_MASK 0x1
#define MIP_MTI_BIT_OFFSET   7
#define MIP_MTI_BIT_WIDTH    1
#define MIP_MTI_BIT_MASK     0x80
#define MIP_MTI_ALL_SET_MASK 0x1
#define MIP_MEI_BIT_OFFSET   11
#define MIP_MEI_BIT_WIDTH    1
#define MIP_MEI_BIT_MASK     0x800
#define MIP_MEI_ALL_SET_MASK 0x1
#define MIP_PLATFORM_DEFINED_BIT_OFFSET   16
#define MIP_PLATFORM_DEFINED_BIT_WIDTH    ((__riscv_xlen)-(16) + 1)
#define MIP_PLATFORM_DEFINED_BIT_MASK     ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (16))
#define MIP_PLATFORM_DEFINED_ALL_SET_MASK ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (0))

/*******************************************
 * mie - MRW - Machine Interrupt Enable 
 */
static inline uint_xlen_t csr_read_mie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mie(uint_xlen_t value) {
    __asm__ volatile ("csrw    mie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mie(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mie(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mie, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mie, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mie, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MIE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mie, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mie, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MIE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mie, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mie, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MIE(MASK)               \
    __asm__ volatile ("csrrci    zero, mie, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MIE_MSI_BIT_OFFSET   3
#define MIE_MSI_BIT_WIDTH    1
#define MIE_MSI_BIT_MASK     0x8
#define MIE_MSI_ALL_SET_MASK 0x1
#define MIE_MTI_BIT_OFFSET   7
#define MIE_MTI_BIT_WIDTH    1
#define MIE_MTI_BIT_MASK     0x80
#define MIE_MTI_ALL_SET_MASK 0x1
#define MIE_MEI_BIT_OFFSET   11
#define MIE_MEI_BIT_WIDTH    1
#define MIE_MEI_BIT_MASK     0x800
#define MIE_MEI_ALL_SET_MASK 0x1
#define MIE_PLATFORM_DEFINED_BIT_OFFSET   16
#define MIE_PLATFORM_DEFINED_BIT_WIDTH    ((__riscv_xlen)-(16) + 1)
#define MIE_PLATFORM_DEFINED_BIT_MASK     ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (16))
#define MIE_PLATFORM_DEFINED_ALL_SET_MASK ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (0))

/*******************************************
 * minstret - MRW - Number of Instructions Retired Counter 
 */
static inline uint64_t csr_read_minstret(void) {
    uint_csr64_t value;        
    __asm__ volatile ("csrr    %0, minstret" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_minstret(uint_csr64_t value) {
    __asm__ volatile ("csrw    minstret, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_minstret(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, minstret, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mscratch - MRW - Machine Mode Scratch Register 
 */
static inline uint_xlen_t csr_read_mscratch(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mscratch" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mscratch(uint_xlen_t value) {
    __asm__ volatile ("csrw    mscratch, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mscratch(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mscratch, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mepc - MRW - Machine Exception Program Counter 
 */
static inline uint_xlen_t csr_read_mepc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mepc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mepc(uint_xlen_t value) {
    __asm__ volatile ("csrw    mepc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mepc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mepc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mcause - MRW - Machine Exception Cause 
 */
static inline uint_xlen_t csr_read_mcause(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mcause" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcause(uint_xlen_t value) {
    __asm__ volatile ("csrw    mcause, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mcause(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mcause, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mcause(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mcause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mcause(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mcause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mcause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mcause, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mcause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mcause, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mcause, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MCAUSE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mcause, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcause, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MCAUSE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mcause, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcause, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MCAUSE(MASK)               \
    __asm__ volatile ("csrrci    zero, mcause, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MCAUSE_INTERRUPT_BIT_OFFSET   (__riscv_xlen-1)
#define MCAUSE_INTERRUPT_BIT_WIDTH    1
#define MCAUSE_INTERRUPT_BIT_MASK     (0x1UL << ((__riscv_xlen-1)))
#define MCAUSE_INTERRUPT_ALL_SET_MASK 0x1
#define MCAUSE_EXCEPTION_CODE_BIT_OFFSET   0
#define MCAUSE_EXCEPTION_CODE_BIT_WIDTH    ((__riscv_xlen-2)-(0) + 1)
#define MCAUSE_EXCEPTION_CODE_BIT_MASK     ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))
#define MCAUSE_EXCEPTION_CODE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))

/*******************************************
 * mtval - MRW - Machine Trap Value 
 */
static inline uint_xlen_t csr_read_mtval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtval(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tselect - MRW - Debug/Trace trigger register select. 
 */
static inline uint_xlen_t csr_read_tselect(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tselect" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tselect(uint_xlen_t value) {
    __asm__ volatile ("csrw    tselect, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tselect(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tselect, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tdata1 - MRW - First Debug/Trace trigger data register. 
 */
static inline uint_xlen_t csr_read_tdata1(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tdata1" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tdata1(uint_xlen_t value) {
    __asm__ volatile ("csrw    tdata1, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tdata1(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tdata1, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tdata2 - MRW - Second Debug/Trace trigger data register. 
 */
static inline uint_xlen_t csr_read_tdata2(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tdata2" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tdata2(uint_xlen_t value) {
    __asm__ volatile ("csrw    tdata2, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tdata2(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tdata2, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

#endif // #define PRV_CSR_H