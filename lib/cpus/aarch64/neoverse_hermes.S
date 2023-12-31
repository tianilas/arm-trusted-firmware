/*
 * Copyright (c) 2023, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <common/bl_common.h>
#include <neoverse_hermes.h>
#include <cpu_macros.S>
#include <plat_macros.S>

/* Hardware handled coherency */
#if HW_ASSISTED_COHERENCY == 0
#error "Neoverse Hermes must be compiled with HW_ASSISTED_COHERENCY enabled"
#endif

/* 64-bit only core */
#if CTX_INCLUDE_AARCH32_REGS == 1
#error "Neoverse Hermes supports only AArch64. Compile with CTX_INCLUDE_AARCH32_REGS=0"
#endif

cpu_reset_func_start neoverse_hermes
	/* Disable speculative loads */
	msr	SSBS, xzr
cpu_reset_func_end neoverse_hermes

	/* ----------------------------------------------------
	 * HW will do the cache maintenance while powering down
	 * ----------------------------------------------------
	 */
func neoverse_hermes_core_pwr_dwn
	/* ---------------------------------------------------
	 * Enable CPU power down bit in power control register
	 * ---------------------------------------------------
	 */
	sysreg_bit_set NEOVERSE_HERMES_CPUPWRCTLR_EL1, NEOVERSE_HERMES_CPUPWRCTLR_EL1_CORE_PWRDN_BIT
	isb
	ret
endfunc neoverse_hermes_core_pwr_dwn

errata_report_shim neoverse_hermes

	/* ---------------------------------------------
	 * This function provides Neoverse Hermes specific
	 * register information for crash reporting.
	 * It needs to return with x6 pointing to
	 * a list of register names in ascii and
	 * x8 - x15 having values of registers to be
	 * reported.
	 * ---------------------------------------------
	 */
.section .rodata.neoverse_hermes_regs, "aS"
neoverse_hermes_regs:  /* The ascii list of register names to be reported */
	.asciz	"cpuectlr_el1", ""

func neoverse_hermes_cpu_reg_dump
	adr	x6, neoverse_hermes_regs
	mrs	x8, NEOVERSE_HERMES_CPUECTLR_EL1
	ret
endfunc neoverse_hermes_cpu_reg_dump

declare_cpu_ops neoverse_hermes, NEOVERSE_HERMES_MIDR, \
	neoverse_hermes_reset_func, \
	neoverse_hermes_core_pwr_dwn
