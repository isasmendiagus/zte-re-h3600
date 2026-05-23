// module: mt7915.ko
// function: mtf_txpower_all_rate_info @ 0x1a3708
// size: 1476 bytes
//

void mtf_txpower_all_rate_info(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 local_3d;
  undefined4 local_39;
  undefined4 local_35;
  undefined4 local_31;
  undefined4 local_2d;
  undefined4 local_29;
  undefined4 local_25;
  undefined1 local_21;
  
  local_39 = 0x120c0906;
  local_35 = 0x36302418;
  local_31 = 0x3020100;
  local_2d = 0x7060504;
  local_3d = 0xb050201;
  local_29 = 0x3020100;
  local_25 = 0x7060504;
  local_21 = 0x20;
  if (0 < DebugLevel) {
    printk("=============================================================================\n");
    if (0 < DebugLevel) {
      printk("\t\t\t\t\t\t\t  TX POWER INFO \t\t\t\t\t\t\t \n");
      if (0 < DebugLevel) {
        printk("=============================================================================\n");
        if (0 < DebugLevel) {
          puVar2 = &_LC333;
          if (*(char *)(param_2 + 2) == '\0') {
            puVar2 = &_LC334;
          }
          printk("\tBand Index: %d,  Channel Band: %s\n",*(undefined1 *)(param_2 + 1),puVar2);
          if (0 < DebugLevel) {
            printk("-----------------------------------------------------------------------------\n"
                  );
          }
        }
      }
    }
  }
  iVar3 = 0;
  iVar1 = DebugLevel;
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [CCK_%02dM]: 0x%02x (%03d)\n",*(undefined1 *)((int)&local_3d + iVar3),iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 4);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [OFDM_%02dM]: 0x%02x (%03d)\n",*(undefined1 *)((int)&local_3d + iVar3),iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xc);
  iVar3 = 0xc;
  if (0 < iVar1) {
    printk("-----------------------------------------------------------------------------\n");
    iVar1 = DebugLevel;
  }
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HT20_M%02d]: 0x%02x (%03d)\n",*(undefined1 *)((int)&local_3d + iVar3),iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x14);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HT40_M%02d]: 0x%02x (%03d)\n",*(undefined1 *)((int)&local_3d + iVar3),iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x1d);
  iVar3 = 0x1d;
  if (0 < iVar1) {
    printk("-----------------------------------------------------------------------------\n");
    iVar1 = DebugLevel;
  }
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [VHT20_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x1d,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x29);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [VHT40_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x29,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x35);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [VHT80_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x35,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x41);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [VHT160_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x41,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x4d);
  iVar3 = 0x4d;
  if (0 < iVar1) {
    printk("-----------------------------------------------------------------------------\n");
    iVar1 = DebugLevel;
  }
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE26_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x4d,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x59);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE52_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x59,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x65);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE106_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x65,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x71);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE242_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x71,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x7d);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE484_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x7d,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x89);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE996_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x89,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x95);
  do {
    if (0 < iVar1) {
      iVar1 = (int)*(char *)(param_2 + (uint)*(byte *)(param_2 + 1) + iVar3 * 2 + 4);
      printk("  [HE996X2_M%02d]: 0x%02x (%03d)\n",iVar3 + -0x95,iVar1,iVar1);
      iVar1 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xa1);
  if (((0 < iVar1) &&
      (printk("-----------------------------------------------------------------------------\n"),
      0 < DebugLevel)) &&
     (printk("  [MAX][Bound]: 0x%02x (%03d)\n",(int)*(char *)(param_2 + 0x146),
             (int)*(char *)(param_2 + 0x146)), 0 < DebugLevel)) {
    printk("  [MIN][Bound]: 0x%02x (%03d)\n",(int)*(char *)(param_2 + 0x147),
           (int)*(char *)(param_2 + 0x147));
    if (0 < DebugLevel) {
      printk("=============================================================================\n");
      return;
    }
  }
  return;
}

