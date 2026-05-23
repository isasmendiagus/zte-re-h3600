// module: mt7915.ko
// function: HQA_SetBandMode @ 0x273fa0
// size: 220 bytes
//

undefined4 HQA_SetBandMode(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar2 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (uVar1 == 1) {
    if (uVar2 == 2) {
      uVar3 = 0;
      Set_WirelessMode_Proc(param_1,&_LC82,param_3,param_1,1,2);
    }
    else if (uVar2 == 1) {
      uVar3 = 0;
      Set_WirelessMode_Proc(param_1,&_LC83,param_3,param_1,1,1);
    }
    else {
      uVar3 = 0xffffffff;
    }
  }
  else {
    uVar3 = 0;
  }
  if (0 < DebugLevel) {
    printk("%s: band_mode:%x, band_type:%x\n","HQA_SetBandMode",uVar1,uVar2);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

