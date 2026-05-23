// module: mt7915.ko
// function: MtUpdateBcnToMcu @ 0x1a778c
// size: 360 bytes
//

undefined4 MtUpdateBcnToMcu(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  void *__src;
  size_t __n;
  undefined1 local_238;
  undefined1 local_237;
  undefined1 local_236;
  undefined1 local_235;
  undefined1 local_234;
  undefined1 local_233;
  short local_232;
  undefined2 local_230;
  short local_22e;
  undefined1 auStack_22c [512];
  undefined1 local_2c;
  undefined1 local_2b;
  short local_2a;
  
  iVar5 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *(byte *)(iVar5 + 2);
  __memzero(&local_238,0x210);
  if (param_2 == 0) {
    uVar6 = 0;
    if (-1 < DebugLevel) {
      printk("%s(): wdev is NULL!\n","MtUpdateBcnToMcu");
    }
  }
  else {
    local_237 = *(undefined1 *)(param_2 + 0x950);
    sVar2 = *(short *)(param_2 + 0x980);
    sVar3 = *(short *)(param_2 + 0x982);
    sVar4 = *(short *)(param_2 + 0x98a);
    if (*(int *)(param_2 + 0x954) == 0) {
      uVar6 = 0;
      if (-1 < DebugLevel) {
        printk("%s(): BeaconPkt is NULL!\n","MtUpdateBcnToMcu");
      }
    }
    else {
      local_238 = *(undefined1 *)(param_2 + 0x29);
      __src = *(void **)(*(int *)(param_2 + 0x954) + 0xcc);
      __n = (uint)*(ushort *)(param_2 + 0x958) + (uint)bVar1;
      local_236 = 0;
      local_235 = HcGetBandByWdev(param_2);
      local_2c = *(undefined1 *)(param_2 + 0x944);
      local_233 = *(undefined1 *)(iVar5 + 0x14e);
      local_232 = (ushort)bVar1 + sVar3;
      local_2a = (ushort)bVar1 + sVar4;
      local_234 = 0;
      if (sVar4 != 0) {
        local_2b = *(undefined1 *)(param_2 + 0xa44);
      }
      local_230 = (undefined2)__n;
      local_22e = (ushort)bVar1 + sVar2;
      memcpy(auStack_22c,__src,__n);
      MtCmdBcnOffloadSet(param_1,&local_238);
      uVar6 = 1;
    }
  }
  return uVar6;
}

