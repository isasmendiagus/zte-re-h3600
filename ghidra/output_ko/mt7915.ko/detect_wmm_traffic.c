// module: mt7915.ko
// function: detect_wmm_traffic @ 0xc8818
// size: 508 bytes
//

void detect_wmm_traffic(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  uint uVar4;
  int local_18;
  int local_14;
  
  iVar2 = jiffies;
  iVar1 = DebugLevel;
  if (param_1 == 0) {
    return;
  }
  if (((*(char *)(param_1 + 0x795071) == '\0') && (*(char *)(param_1 + 0x79507d) == '\0')) &&
     (param_4 == 1 && *(char *)(param_1 + 0x795951) == '\0')) {
    if (*(char *)((int)&WMM_UP2AC_MAP + param_3) == '\0') {
      if (*(char *)(param_1 + 0xa77c35) == '\0') {
        *(undefined1 *)(param_1 + 0xa77c35) = 1;
        *(int *)(param_1 + 0xa77c38) = iVar2;
        if (2 < iVar1) {
          printk("wmm> adjust be!\n");
        }
      }
    }
    else if (*(char *)(param_1 + 0xa77c35) != '\0') {
      if (*(int *)(param_1 + 0x2862c8) == 0) {
        if ((100 < (uint)(jiffies - *(int *)(param_1 + 0xa77c38))) &&
           (*(undefined1 *)(param_1 + 0xa77c35) = 0, 2 < DebugLevel)) {
          printk("wmm> recover be!\n");
        }
      }
      else {
        *(int *)(param_1 + 0xa77c38) = jiffies;
      }
    }
  }
  if (3 < param_3) {
    uVar4 = *(int *)(param_1 + 0xa77c2c) + 1;
    *(uint *)(param_1 + 0xa77c2c) = uVar4;
    if ((uVar4 < 0x65) || (*(char *)(param_1 + 0x285946) == '\0')) {
      if (*(char *)(param_1 + 0xa77c34) != '\0') {
        mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1380,0x2400ca);
        uVar3 = 0;
        goto LAB_000c88e0;
      }
    }
    else if (*(char *)(param_1 + 0xa77c34) == '\0') {
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1380,&DAT_005400ca);
      uVar3 = 1;
LAB_000c88e0:
      *(undefined1 *)(param_1 + 0xa77c34) = uVar3;
      local_14 = param_1 + 0xa77c34;
      local_18 = param_1;
      mt_notify_call_chain(param_1 + 0xa18fc,6,&local_18);
      return;
    }
  }
  return;
}

