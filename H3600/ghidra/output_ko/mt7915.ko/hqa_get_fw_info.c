// module: mt7915.ko
// function: hqa_get_fw_info @ 0x26d838
// size: 128 bytes
//

undefined4 hqa_get_fw_info(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"hqa_get_fw_info",param_3,param_1 + 0xa39000,param_4);
  }
  pcVar1 = *(code **)(iVar3 + 0xb4);
  if (pcVar1 == (code *)0x0) {
    uVar2 = 1;
  }
  else {
    uVar2 = (*pcVar1)(param_1,param_3 + 0xe);
  }
  FUN_0026cdd0(param_3,param_2,0x20,uVar2);
  return uVar2;
}

