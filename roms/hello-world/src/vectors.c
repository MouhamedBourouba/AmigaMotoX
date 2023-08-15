
#include <stdint.h>

#define STACK_POINTER_INIT	0x0100000
 
extern void _start();
extern void _error();

//my serial console
extern void init_tty();
extern void myputs(const char*);
//+ putchar and getchar

// cpu int's just for debug !!!
void fatal_error_entry();
void fatal_isr_bus_error(void);
void fatal_isr_address_error(void);
void fatal_isr_illegal_instruction(void);
void fatal_isr_DividebyZero(void);
void fatal_isr_CHKInstruction(void);
void fatal_isr_TRAPVInstruction(void);
void fatal_isr_PrivilegeViolation(void);
void fatal_isr_Trace(void);
void fatal_isr_LineA(void);
void fatal_isr_LineF(void);
void fatal_isr_ReservedC(void);
void fatal_isr_ReservedD(void);
void fatal_isr_FormatError(void);
void fatal_isr_UninitializedVector(void);

// my IRQ int's
void fatal_isr_SpuriousInterrupt(void) __attribute__ ((interrupt_handler));
void int2_serial(void) __attribute__ ((interrupt_handler));
void int5_timer(void)  __attribute__ ((interrupt_handler));
void int7_NMI(void)    __attribute__ ((interrupt_handler));

typedef void (*interrupt_handler_t)();

interrupt_handler_t boot_vectors[256] 
__attribute__((section(".vectors"))) 
= {
	(interrupt_handler_t) STACK_POINTER_INIT,
	_start,
	fatal_isr_bus_error,  
	fatal_isr_address_error,
	fatal_isr_illegal_instruction,
	fatal_isr_DividebyZero,
	fatal_isr_CHKInstruction,
	fatal_isr_TRAPVInstruction,
	fatal_isr_PrivilegeViolation,
	fatal_isr_Trace,
	fatal_error_entry,
	fatal_error_entry,
	fatal_isr_LineA,
	fatal_isr_LineF,
	fatal_isr_FormatError,
	fatal_isr_UninitializedVector,
	
	[0x10 ... 0x17] = fatal_error_entry,
	
	fatal_isr_SpuriousInterrupt,
	fatal_error_entry,	
	int2_serial,
	fatal_error_entry,
	fatal_error_entry,
	int5_timer,
	fatal_error_entry,
	int7_NMI,
	
};

//funtion to save all register for future dump 
asm(
"fatal_error_entry:\n"
//	move.b	#0x01, %d0
//	lea	0x201d, %a0
//	move.b	%d0, (%a0)		| set the arduino led as an error indicator

"	move.l	%a6, -(%sp)\n"
"	move.l	%a5, -(%sp)\n"
"	move.l	%a4, -(%sp)\n"
"	move.l	%a3, -(%sp)\n"
"	move.l	%a2, -(%sp)\n"
"	move.l	%a1, -(%sp)\n"
"	move.l	%a0, -(%sp)\n"
"	move.l	%d7, -(%sp)\n"
"	move.l	%d6, -(%sp)\n"
"	move.l	%d5, -(%sp)\n"
"	move.l	%d4, -(%sp)\n"
"	move.l	%d3, -(%sp)\n"
"	move.l	%d2, -(%sp)\n"
"	move.l	%d1, -(%sp)\n"
"	move.l	%d0, -(%sp)\n"
"\n"
"	move.l	%sp, -(%sp)\n"
"	bsr	fatal_error\n"
"	stop	#0x2700\n"
"	|stopping\n"
"	|jmp	0x400\n"
"	rte\n"
);

static inline void _loop(void)
{
	while(1);
}

void fatal_isr_bus_error(void)
{
	 myputs("\nbus_error");
	 
	 //__asm__ volatile("stop	#0x2700");
}
void fatal_isr_address_error (void)
{
	 myputs("\nAdr_error");
	 
	 //__asm__ volatile("stop	#0x2700");
}
void fatal_isr_illegal_instruction (void)
{
	 myputs("\nillegal_instruction");
	 
	 _loop();
	 //__asm__ volatile("stop	#0x2700");
}
void fatal_isr_DividebyZero(void)
{
	 myputs("\nDividebyZero");
}
void fatal_isr_CHKInstruction(void)
{
	 myputs("\nCHKInstruction");
}
void fatal_isr_TRAPVInstruction(void)
{
	 myputs("\nTRAPV Instruction");
}
void fatal_isr_PrivilegeViolation(void)
{
	 myputs("\nPrivilege Violation");
}
void fatal_isr_Trace(void)
{
	 myputs("\nTrace");
}
void fatal_isr_LineA(void)
{
	 myputs("\nLine A");
}
void fatal_isr_LineF(void)
{
	 myputs("\nLine F");
}
void fatal_isr_ReservedC(void)
{
	 myputs("\nReserved C");
}
void fatal_isr_ReservedD(void)
{
	 myputs("\nReserved D");
}
void fatal_isr_FormatError(void)
{
	 myputs("\nFormatError");
}
void fatal_isr_UninitializedVector(void)
{
	 myputs("\nUninitialized Vector");
}

void fatal_isr_SpuriousInterrupt(void)
{
	 myputs("\nSpurious Interrupt");
}

void int2_serial(void)
{
/*
#define M68KATY_SERIAL_IN            (*(volatile uint8_t *)  0x078000)

	 int c = M68KATY_SERIAL_IN ;
	 
	 printf("\nint2_serial c=%d",c);
*/
}

int volatile timer_counter =0;

void int5_timer  (void) 
{
	//myputs("\nint5_timer");
	//timer_counter++;
}
void int7_NMI(void)
{
	myputs("\nint7_NMI");
}

// ----------------------------------------------------------------

void fatal_error(uint8_t *sp)
{
	 //printf("\n\nFatal Error with SP: %08x and PC: %08x", sp , *((uint32_t *) &sp[15 * 4 + 2]));
	 //no printf for now (haha)
}
