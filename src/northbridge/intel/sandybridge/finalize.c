/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 The Chromium OS Authors. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/pci_ops.h>
#include "sandybridge.h"

#define PCI_DEV_SNB PCI_DEV(0, 0, 0)

void intel_sandybridge_finalize_smm(void)
{
	pci_or_config16(PCI_DEV_SNB, GGC, 1 << 0);
	pci_or_config16(PCI_DEV_SNB, PAVPC, 1 << 2);
	pci_or_config32(PCI_DEV_SNB, DPR, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, MESEG_MASK, MELCK);
	pci_or_config32(PCI_DEV_SNB, REMAPBASE, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, REMAPLIMIT, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, TOM, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, TOUUD, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, BDSM, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, BGSM, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, TSEGMB, 1 << 0);
	pci_or_config32(PCI_DEV_SNB, TOLUD, 1 << 0);

	MCHBAR32_OR(0x5500, 1 << 0);	/* PAVP */
	MCHBAR32_OR(0x5f00, 1 << 31);	/* SA PM */
	MCHBAR32_OR(0x6020, 1 << 0);	/* UMA GFX */
	MCHBAR32_OR(0x63fc, 1 << 0);	/* VTDTRK */
	MCHBAR32_OR(0x6800, 1 << 31);
	MCHBAR32_OR(0x7000, 1 << 31);
	MCHBAR32_OR(0x77fc, 1 << 0);

	/* Memory Controller Lockdown */
	MCHBAR8(0x50fc) = 0x8f;

	/* Read+write the following */
	MCHBAR32(0x6030) = MCHBAR32(0x6030);
	MCHBAR32(0x6034) = MCHBAR32(0x6034);
	MCHBAR32(0x6008) = MCHBAR32(0x6008);
}
