// module: mt7915.ko
// function: MacTableSetEntryRaCap @ 0x148b14
// size: 588 bytes
//

void MacTableSetEntryRaCap(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar4 = *param_3;
  uVar5 = param_3[1];
  uVar6 = param_3[2];
  if (3 < DebugLevel) {
    printk("vendor_ie_cap for ra_cap=%08x, mtk_cap=%08x\n",uVar4,uVar5);
  }
  uVar2 = *param_3;
  uVar3 = param_3[3];
  uVar7 = param_3[1];
  *(uint *)(param_2 + 0xc98) = param_3[2];
  *(uint *)(param_2 + 0xc9c) = uVar3;
  *(uint *)(param_2 + 0xc90) = uVar2;
  *(uint *)(param_2 + 0xc94) = uVar7;
  uVar3 = *(uint *)(param_2 + 0xb4) & 0xffeffdf9;
  *(uint *)(param_2 + 0xca0) = param_3[4];
  uVar2 = *(uint *)(param_2 + 0xb8) & 0xffeffdf9;
  *(uint *)(param_2 + 0xb4) = uVar3;
  *(uint *)(param_2 + 0xb8) = uVar2;
  if (*(char *)((int)param_3 + 0xe) == '\x01') {
    *(uint *)(param_2 + 0xb8) = uVar2 | 0x100000;
    *(uint *)(param_2 + 0xb4) = uVar3 | 0x100000;
    if ((uVar4 & 1) != 0) {
      *(uint *)(param_2 + 0xb8) = uVar2 | 0x100002;
      iVar1 = DebugLevel;
      if (*(char *)(param_1 + 0x795072) != '\0') {
        *(uint *)(param_2 + 0xb4) = uVar3 | 0x100002;
        if (3 < iVar1) {
          printk("RaAggregate= 1\n");
        }
      }
    }
    if (((uVar4 & 2) != 0) &&
       (*(uint *)(param_2 + 0xb8) = *(uint *)(param_2 + 0xb8) | 4, iVar1 = DebugLevel,
       *(char *)(param_1 + 0x795073) != '\0')) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 4;
      if (3 < iVar1) {
        printk("PiggyBack= 1\n");
      }
    }
    if (((uVar4 & 4) != 0) &&
       (*(uint *)(param_2 + 0xb8) = *(uint *)(param_2 + 0xb8) | 0x200, iVar1 = DebugLevel,
       *(char *)(param_1 + 0x79507d) != '\0')) {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x200;
      if (3 < iVar1) {
        printk("Rdg = 1\n");
      }
    }
    if ((uVar4 & 8) == 0) {
      return;
    }
    if (*(char *)(param_1 + 0x79505f) == '\0') {
      return;
    }
    if (3 < DebugLevel) {
      printk("RALINK_256QAM_CAP for 2.4G\n");
    }
  }
  else if ((uVar5 & 8) == 0) {
    if ((uVar6 & 1) == 0) {
      return;
    }
    if (*(char *)(param_1 + 0x79505f) == '\0') {
      return;
    }
    if (3 < DebugLevel) {
      printk("BROADCOM_256QAM_CAP for 2.4G\n");
    }
  }
  else {
    if (*(char *)(param_1 + 0x79505f) == '\0') {
      return;
    }
    if (3 < DebugLevel) {
      printk("MEDIATEK_256QAM_CAP for 2.4G\n");
    }
  }
  *(undefined1 *)(param_2 + 0xbfd) = 1;
  return;
}

