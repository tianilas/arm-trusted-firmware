/*
 * Copyright (c) 2023, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef JUNO_ETHOSN_TZMP1_DEF_H
#define JUNO_ETHOSN_TZMP1_DEF_H

#define JUNO_ETHOSN_TZC400_NSAID_FW_PROT	7
#define JUNO_ETHOSN_TZC400_NSAID_DATA_RW_PROT	8
#define JUNO_ETHOSN_TZC400_NSAID_DATA_RO_PROT	13

/* 0 is the default NSAID and is included in PLAT_ARM_TZC_NS_DEV_ACCESS */
#define JUNO_ETHOSN_TZC400_NSAID_DATA_RW_NS	0
#define JUNO_ETHOSN_TZC400_NSAID_DATA_RO_NS	14

#define JUNO_ETHOSN_FW_TZC_PROT_DRAM2_SIZE      UL(0x000400000) /* 4 MB */
#define JUNO_ETHOSN_FW_TZC_PROT_DRAM2_BASE      (ARM_DRAM2_BASE)
#define JUNO_ETHOSN_FW_TZC_PROT_DRAM2_END       (ARM_DRAM2_BASE +		    \
						 JUNO_ETHOSN_FW_TZC_PROT_DRAM2_SIZE \
						 - 1U)

#define JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_SIZE    UL(0x004000000) /* 64 MB */
#define JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_BASE    ( \
		JUNO_ETHOSN_FW_TZC_PROT_DRAM2_END + 1)
#define JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_END     (      \
		JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_BASE + \
		JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_SIZE - 1U)

#define JUNO_ETHOSN_NS_DRAM2_BASE       (JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_END + \
					 1)
#define JUNO_ETHOSN_NS_DRAM2_END        (ARM_DRAM2_END)
#define JUNO_ETHOSN_NS_DRAM2_SIZE       (ARM_DRAM2_SIZE - \
					 JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_END)

#define JUNO_FW_TZC_PROT_ACCESS	\
	(TZC_REGION_ACCESS_RDWR(JUNO_ETHOSN_TZC400_NSAID_FW_PROT))
#define JUNO_DATA_TZC_PROT_ACCESS \
	(TZC_REGION_ACCESS_RDWR(JUNO_ETHOSN_TZC400_NSAID_DATA_RW_PROT) | \
	 TZC_REGION_ACCESS_RD(JUNO_ETHOSN_TZC400_NSAID_DATA_RO_PROT))
#define JUNO_DATA_TZC_NS_ACCESS \
	(PLAT_ARM_TZC_NS_DEV_ACCESS | \
	 TZC_REGION_ACCESS_RD(JUNO_ETHOSN_TZC400_NSAID_DATA_RO_NS))

#define JUNO_ETHOSN_TZMP_REGIONS_DEF					  \
	{ ARM_AP_TZC_DRAM1_BASE, ARM_EL3_TZC_DRAM1_END + ARM_L1_GPT_SIZE, \
	  TZC_REGION_S_RDWR, 0 },					  \
	{ ARM_NS_DRAM1_BASE, ARM_NS_DRAM1_END,				  \
	  ARM_TZC_NS_DRAM_S_ACCESS, JUNO_DATA_TZC_NS_ACCESS},		  \
	{ JUNO_ETHOSN_FW_TZC_PROT_DRAM2_BASE,				  \
	  JUNO_ETHOSN_FW_TZC_PROT_DRAM2_END,				  \
	  TZC_REGION_S_RDWR, JUNO_FW_TZC_PROT_ACCESS },			  \
	{ JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_BASE,				  \
	  JUNO_ETHOSN_DATA_TZC_PROT_DRAM2_END,				  \
	  TZC_REGION_S_NONE, JUNO_DATA_TZC_PROT_ACCESS },		  \
	{ JUNO_ETHOSN_NS_DRAM2_BASE, JUNO_ETHOSN_NS_DRAM2_END,		  \
	  ARM_TZC_NS_DRAM_S_ACCESS, JUNO_DATA_TZC_NS_ACCESS}

#endif /* JUNO_ETHOSN_TZMP1_DEF_H */
