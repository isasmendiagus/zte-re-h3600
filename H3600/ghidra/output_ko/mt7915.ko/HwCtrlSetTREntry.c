// module: mt7915.ko
// function: HwCtrlSetTREntry @ 0xaf71c
// size: 28 bytes
//

undefined4 HwCtrlSetTREntry(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  TRTableInsertEntry(param_1,*puVar1,*(undefined4 *)(puVar1 + 2),puVar1,param_4);
  return 0;
}

