// module: mt7915.ko
// function: SrMbssInit @ 0x16be04
// size: 440 bytes
//

undefined4 SrMbssInit(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 local_24 [2];
  undefined1 local_22;
  uint local_1c;
  
  if (param_2 == 0) {
    return 1;
  }
  iVar2 = HcGetBandByWdev(param_2);
  if (0 < DebugLevel) {
    printk("%s: Spatial Reuse initialize via profile.\n","SrMbssInit");
  }
  iVar4 = param_1 + iVar2;
  *(undefined1 *)(iVar4 + 0x795b1c) = *(undefined1 *)(iVar4 + 0x795b16);
  os_zero_mem(local_24,0xc);
  local_1c = (uint)*(byte *)(iVar4 + 0x795b16);
  uVar1 = (undefined1)iVar2;
  local_24[0] = 0xf;
  local_22 = uVar1;
  iVar3 = SrCmd(param_1,local_24);
  if ((iVar3 == 1) && (-1 < DebugLevel)) {
    printk("%s: Set SREnable[%d]=%d Fail!\n","SrMbssInit",iVar2,*(undefined1 *)(iVar4 + 0x795b16));
  }
  os_zero_mem(local_24,0xc);
  local_1c = (uint)*(byte *)(iVar4 + 0x795b18);
  local_24[0] = 0x13;
  local_22 = uVar1;
  iVar3 = SrCmd(param_1,local_24);
  if ((iVar3 == 1) && (-1 < DebugLevel)) {
    printk("%s: Set SRMode[%d]=%d Fail!\n","SrMbssInit",iVar2,*(undefined1 *)(iVar4 + 0x795b18));
  }
  os_zero_mem(local_24,0xc);
  local_1c = (uint)*(byte *)(iVar4 + 0x795b1a);
  local_24[0] = 0x10;
  local_22 = uVar1;
  iVar3 = SrCmd(param_1,local_24);
  if ((iVar3 == 1) && (-1 < DebugLevel)) {
    printk("%s: Set SRSDEnable[%d]=%d Fail!\n","SrMbssInit",iVar2,*(undefined1 *)(iVar4 + 0x795b1a))
    ;
  }
  return 0;
}

