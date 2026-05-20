// module: mt7915.ko
// function: Dot1xIoctlStaticWepCopy @ 0x115614
// size: 480 bytes
//

void Dot1xIoctlStaticWepCopy(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_a8 [2];
  undefined1 auStack_a6 [6];
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined2 local_94;
  undefined1 local_92;
  byte local_91;
  undefined1 auStack_90 [114];
  undefined1 auStack_1e [10];
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk("RTMPIoctlStaticWepCopy-IF(ra%d)\n",uVar3 & 0xff);
  }
  if (*(short *)(param_2 + 0x14) == 6) {
    uVar4 = *(uint *)(param_2 + 0x10);
    uVar2 = *(uint *)(((uint)auStack_a8 & 0xffffe000) + 8);
    if (uVar4 < 0xfffffffa && uVar4 + 6 <= uVar2) {
      uVar2 = 0;
    }
    if (uVar2 == 0) {
      __copy_from_user(auStack_a6,uVar4);
    }
    else {
      __memzero(auStack_a6,6);
    }
    iVar1 = MacTableLookup(param_1,auStack_a6);
    if (iVar1 != 0) {
      uVar3 = uVar3 & 0xff;
      memset(&local_a0,0,0x88);
      *(char *)(iVar1 + 0x2c8) = (char)param_1[uVar3 * 0x160d + 0xadcf0];
      *(int *)(iVar1 + 0x2c4) = param_1[uVar3 * 0x160d + 0xadcef];
      os_move_mem((void *)(iVar1 + 0x180),param_1 + uVar3 * 0x160d + 0xadc9e,0x144);
      os_zero_mem(&local_a0,0x88);
      local_91 = *(byte *)(iVar1 + 0x2c8);
      local_92 = *(undefined1 *)(iVar1 + 0xe4);
      local_98 = *(undefined4 *)(iVar1 + 0x2c4);
      local_94 = *(undefined2 *)(iVar1 + 0xe0);
      local_9c = 2;
      local_a0 = 0;
      os_move_mem(auStack_90,(void *)(iVar1 + (uint)local_91 * 0x51 + 0x180),0x51);
      os_move_mem(auStack_1e,(void *)(iVar1 + 0xec),6);
      *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar1 + 0xe0) * 0x620 + 0x2f762) = 1;
      *(undefined4 *)(iVar1 + 0xadc) = 0;
      WifiSysUpdatePortSecur(param_1,iVar1,&local_a0);
      return;
    }
    if (-1 < DebugLevel) {
      printk("RTMPIoctlStaticWepCopy: the mac address isn\'t match\n");
    }
  }
  else if (-1 < DebugLevel) {
    printk("RTMPIoctlStaticWepCopy: the length isn\'t match (%d)\n",*(short *)(param_2 + 0x14));
  }
  return;
}

