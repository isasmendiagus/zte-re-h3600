// module: mt7915.ko
// function: HQA_MPSStop @ 0x26d4f0
// size: 164 bytes
//

undefined4 HQA_MPSStop(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_MPSStop");
  }
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  uVar1 = (**(code **)(iVar2 + 0xd4))(param_1);
  if (param_2 != 0) {
    FUN_0026cdd0(param_3,param_2,2,uVar1);
  }
  return uVar1;
}

