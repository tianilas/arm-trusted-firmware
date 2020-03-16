/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <lib/utils_def.h>

#define PLATFORM_LINKER_FORMAT		"elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH		aarch64

#define PLATFORM_STACK_SIZE		0X400
#define CACHE_WRITEBACK_GRANULE		64

#define PLAT_PRIMARY_CPU		U(0x0)
#define PLATFORM_MAX_CPU_PER_CLUSTER	U(4)
#define PLATFORM_CLUSTER_COUNT		U(2)
#define PLATFORM_CLUSTER0_CORE_COUNT	U(4)
#define PLATFORM_CLUSTER1_CORE_COUNT	U(2)
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT + \
					 PLATFORM_CLUSTER1_CORE_COUNT)

#define IMX_PWR_LVL0			MPIDR_AFFLVL0
#define IMX_PWR_LVL1			MPIDR_AFFLVL1
#define IMX_PWR_LVL2			MPIDR_AFFLVL2

#define PWR_DOMAIN_AT_MAX_LVL		U(1)
#define PLAT_MAX_PWR_LVL		U(2)
#define PLAT_MAX_OFF_STATE		U(2)
#define PLAT_MAX_RET_STATE		U(1)

#define BL31_BASE			0x80000000
#define BL31_LIMIT			0x80020000

#define PLAT_GICD_BASE			0x51a00000
#define PLAT_GICR_BASE			0x51b00000
#define PLAT_CCI_BASE			0x52090000
#define CLUSTER0_CCI_SLVAE_IFACE	3
#define CLUSTER1_CCI_SLVAE_IFACE	4

/* UART */
#if defined(IMX_USE_UART0)
#define IMX_BOOT_UART_BASE		0x5a060000
#elif defined(IMX_USE_UART1)
#define IMX_BOOT_UART_BASE		0x5a070000
#else
#error "Provide proper UART number in IMX_DEBUG_UART"
#endif

#define IMX_BOOT_UART_BAUDRATE		115200
#define IMX_BOOT_UART_CLK_IN_HZ		24000000
#define PLAT_CRASH_UART_BASE		IMX_BOOT_UART_BASE
#define PLAT__CRASH_UART_CLK_IN_HZ	24000000
#define IMX_CONSOLE_BAUDRATE		115200

#define SC_IPC_BASE			0x5d1b0000
#define IMX_GPT_LPCG_BASE		0x5d540000
#define IMX_GPT_BASE			0x5d140000
#define IMX_WUP_IRQSTR_BASE		0x51090000
#define IMX_REG_BASE			0x50000000
#define IMX_REG_SIZE			0x10000000

#define COUNTER_FREQUENCY		8000000 /* 8MHz */

/* non-secure uboot base */
#define PLAT_NS_IMAGE_OFFSET		0x80020000

#define PLAT_VIRT_ADDR_SPACE_SIZE	(1ull << 32)
#define PLAT_PHY_ADDR_SPACE_SIZE	(1ull << 32)

#define MAX_XLAT_TABLES			8
#define MAX_MMAP_REGIONS		12

#define DEBUG_CONSOLE_A53		0

#endif /* PLATFORM_DEF_H */
