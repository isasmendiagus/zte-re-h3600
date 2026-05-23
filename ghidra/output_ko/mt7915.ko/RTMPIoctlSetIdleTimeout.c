// module: mt7915.ko
// function: RTMPIoctlSetIdleTimeout @ 0x37dc8
// size: 316 bytes
//

void RTMPIoctlSetIdleTimeout(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_20 [6];
  undefined1 auStack_1a [6];
  undefined4 local_14;
  
  if (*(short *)(param_2 + 0x14) == 10) {
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    if (*(uint *)(param_2 + 0x10) < 0xfffffff6 && *(uint *)(param_2 + 0x10) + 10 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      iVar2 = __copy_from_user(auStack_1a);
      if (iVar2 == 0) {
        iVar2 = MacTableLookup(param_1,auStack_1a);
        if (iVar2 == 0) {
          if (DebugLevel < 0) {
            return;
          }
          printk("%s : the entry is empty\n","RTMPIoctlSetIdleTimeout");
          return;
        }
        *(undefined4 *)(iVar2 + 0xae8) = 0;
        iVar1 = DebugLevel;
        *(undefined4 *)(param_1 + (uint)*(ushort *)(iVar2 + 0xe0) * 0x620 + 0x2f954) = 0;
        *(undefined4 *)(iVar2 + 0xb08) = local_14;
        if (iVar1 < 3) {
          return;
        }
        printk("%s : Update Idle-Timeout(%d) from dot1x daemon\n","RTMPIoctlSetIdleTimeout");
        return;
      }
    }
    else {
      __memzero(auStack_1a,10);
    }
    if (-1 < DebugLevel) {
      printk("%s : copy from user failed\n","RTMPIoctlSetIdleTimeout");
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s : the length is mis-match\n","RTMPIoctlSetIdleTimeout");
  }
  return;
}

