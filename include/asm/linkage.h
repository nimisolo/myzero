#ifndef _ASM_LINKAGE_H
#define _ASM_LINKAGE_H

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#undef notrace
#define notrace __attribute__((no_instrument_function))

#ifdef CONFIG_X86_32
#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#endif /* CONFIG_X86_32 */

#ifdef __ASSEMBLY__

#define GLOBAL(name)	\
	.globl name;	\
	name:

#if defined(CONFIG_X86_64) || defined(CONFIG_X86_ALIGNMENT_16)
#define __ALIGN		.p2align 4, 0x90
#define __ALIGN_STR	__stringify(__ALIGN)
#endif

#ifndef ASM_NL
#define ASM_NL		 ;
#endif

#ifndef LINKER_SCRIPT
#define ALIGN __ALIGN
#define ALIGN_STR __ALIGN_STR

#ifndef ENTRY
#define ENTRY(name) \
	.globl name ASM_NL \
	ALIGN ASM_NL \
	name:
#endif
#endif /* LINKER_SCRIPT */

#ifndef WEAK
#define WEAK(name)	   \
	.weak name ASM_NL   \
	name:
#endif

#ifndef END
#define END(name) \
	.size name, .-name
#endif

/* If symbol 'name' is treated as a subroutine (gets called, and returns)
 *  * then please use ENDPROC to mark 'name' as STT_FUNC for the benefit of
 *   * static analysis tools such as stack depth analyzer.
 *    */
#ifndef ENDPROC
#define ENDPROC(name) \
	.type name, @function ASM_NL \
	END(name)
#endif

#endif /* __ASSEMBLY__ */

#endif
