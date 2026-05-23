// module: mt7915.ko
// function: HwCtrlSetSlotTime @ 0xaf200
// size: 32 bytes
//

undefined4 HwCtrlSetSlotTime(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_2 + 8);
  AsicSetSlotTime(param_1,*puVar1,puVar1[1],*(undefined4 *)(puVar1 + 4),param_4);
  return 0;
}

