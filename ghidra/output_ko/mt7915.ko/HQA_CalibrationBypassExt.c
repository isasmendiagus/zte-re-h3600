// module: mt7915.ko
// function: HQA_CalibrationBypassExt @ 0x274828
// size: 172 bytes
//

undefined4 HQA_CalibrationBypassExt(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar2 >> 0x18);
  MtCmdDoCalibration(param_1,2,uVar3,uVar1,uVar3,uVar1);
  if (2 < DebugLevel) {
    printk("%s: item:%x, band_idx:%x\n","HQA_CalibrationBypassExt",uVar3,uVar1);
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

