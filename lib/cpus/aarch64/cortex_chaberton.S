/*
 * Copyright (c) 2023, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <common/bl_common.h>
#include <cortex_chaberton.h>
#include <cpu_macros.S>
#include <plat_macros.S>

/* Hardware handled coherency */
#if HW_ASSISTED_COHERENCY == 0
#error "Cortex Chaberton must be compiled with HW_ASSISTED_COHERENCY enabled"
#endif

/* 64-bit only core */
#if CTX_INCLUDE_AARCH32_REGS == 1
#error "Cortex Chaberton supports only AArch64. Compile with CTX_INCLUDE_AARCH32_REGS=0"
#endif

func cortex_chaberton_reset_func
	/* Disable speculative loads */
	msr	SSBS, xzr
	isb
	ret
endfunc cortex_chaberton_reset_func

	/* ----------------------------------------------------
	 * HW will do the cache maintenance while powering down
	 * ----------------------------------------------------
	 */
func cortex_chaberton_core_pwr_dwn
	/* ---------------------------------------------------
	 * Enable CPU power down bit in power control register
	 * ---------------------------------------------------
	 */
	mrs	x0, CORTEX_CHABERTON_CPUPWRCTLR_EL1
	orr	x0, x0, #CORTEX_CHABERTON_CPUPWRCTLR_EL1_CORE_PWRDN_BIT
	msr	CORTEX_CHABERTON_CPUPWRCTLR_EL1, x0
	isb
	ret
endfunc cortex_chaberton_core_pwr_dwn

#if REPORT_ERRATA
/*
 * Errata printing function for Cortex Chaberton. Must follow AAPCS.
 */
func cortex_chaberton_errata_report
	ret
endfunc cortex_chaberton_errata_report
#endif

	/* ---------------------------------------------
	 * This function provides Cortex Chaberton specific
	 * register information for crash reporting.
	 * It needs to return with x6 pointing to
	 * a list of register names in ascii and
	 * x8 - x15 having values of registers to be
	 * reported.
	 * ---------------------------------------------
	 */
.section .rodata.cortex_chaberton_regs, "aS"
cortex_chaberton_regs:  /* The ascii list of register names to be reported */
	.asciz	"cpuectlr_el1", ""

func cortex_chaberton_cpu_reg_dump
	adr	x6, cortex_chaberton_regs
	mrs	x8, CORTEX_CHABERTON_CPUECTLR_EL1
	ret
endfunc cortex_chaberton_cpu_reg_dump

declare_cpu_ops cortex_chaberton, CORTEX_CHABERTON_MIDR, \
	cortex_chaberton_reset_func, \
	cortex_chaberton_core_pwr_dwn
