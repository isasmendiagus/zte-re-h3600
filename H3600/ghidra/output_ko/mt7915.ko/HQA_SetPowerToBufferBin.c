// module: mt7915.ko
// function: HQA_SetPowerToBufferBin @ 0x273e98
// size: 260 bytes
//

undefined4 HQA_SetPowerToBufferBin(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = *(uint *)(param_3 + 0xc);
  uVar3 = *(uint *)(param_3 + 0x10);
  uVar4 = *(uint *)(param_3 + 0x14);
  uVar6 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  uVar5 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar4 >> 0x18);
  uVar3 = MtATEGetTxPwrGroup(uVar6,uVar5,0);
  if (uVar3 < *(ushort *)(iVar1 + 0xf6)) {
    uVar7 = 0;
    *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar3) = (char)(uVar2 >> 0x18);
  }
  else {
    uVar7 = 0xffffffff;
  }
  if (0 < DebugLevel) {
    printk("%s: power:%x, channel:%x, band_idx:%x, offset:%x, antenna_idx:%x\n",
           "HQA_SetPowerToBufferBin",
           uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18
           ,uVar6,uVar5,uVar3,0);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar7);
  return uVar7;
}

