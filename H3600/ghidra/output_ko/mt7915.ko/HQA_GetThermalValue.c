// module: mt7915.ko
// function: HQA_GetThermalValue @ 0x27528c
// size: 192 bytes
//

undefined4 HQA_GetThermalValue(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (DebugLevel < 3) {
    MtCmdGetThermalSensorResult(param_1,0,uVar1,param_1 + 0xa3ad8c);
    uVar2 = *(uint *)(param_1 + 0xa3ad8c);
  }
  else {
    printk(&_LC11,"HQA_GetThermalValue");
    MtCmdGetThermalSensorResult(param_1,0,uVar1,param_1 + 0xa3ad8c);
    uVar2 = *(uint *)(param_1 + 0xa3ad8c);
  }
  *(uint *)(param_3 + 0xe) =
       uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

