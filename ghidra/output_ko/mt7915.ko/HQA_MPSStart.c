// module: mt7915.ko
// function: HQA_MPSStart @ 0x26d598
// size: 156 bytes
//

undefined4 HQA_MPSStart(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = DebugLevel;
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  *(char *)(param_1 + 0xa3ae36) = (char)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  if (2 < iVar1) {
    printk(&_LC11,"HQA_MPSStart");
  }
  uVar2 = (**(code **)(iVar3 + 0xd0))(param_1);
  if (param_2 != 0) {
    FUN_0026cdd0(param_3,param_2,2,uVar2);
  }
  return uVar2;
}

