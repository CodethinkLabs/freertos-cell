
/*
 * This is used to enable the fpu in the cortex A15. This is gotten directly from the tech
 * manual: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0438i/CDEDBHDD.html
 * Section: Using the Advanced SIMD and VFP in Hyp mode
 *
 */

    .section ".start"
    .globl   fpu_enable

fpu_enable:
    /* Enable Non-secure access to CP10 and CP11 and clear the NSASEDIS bit in the NSACR: */
    MRC p15, 0, r0, c1, c0, 2
    ORR r0, r0, #(3<<10)        /* Enable Non-secure access to CP10 and CP11 */
    BIC r0, r0, #(3<<14)        /* Clear the NSASEDIS bit */
    MCR p15, 0, r0, c1, c0, 2
    ISB

    /*Clear the TCP10, TCP11, and TASE bits in the HCPTR:*/
    MRC p15, 4, r0, c1, c0, 2
    BIC r0, r0, #(3<<10)        /*Clear the TCP10 and TCP11 bits*/
    BIC r0, r0, #(3<<14);       /*Clear the TASE bit*/
    MCR p15, 4, r0, c1, c0, 2
    ISB

    /* Set the FPEXC.EN bit to enable Advanced SIMD and VFP: */
    MOV r0, #0x40000000
    VMSR FPEXC, r0

    bx      lr

