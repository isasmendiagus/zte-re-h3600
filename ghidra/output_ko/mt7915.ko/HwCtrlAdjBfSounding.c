// module: mt7915.ko
// function: HwCtrlAdjBfSounding @ 0xaf750
// size: 36 bytes
//

undefined4 HwCtrlAdjBfSounding(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_2 + 8);
  if (puVar1 != (undefined4 *)0x0) {
    mt_BfSoundingAdjust(param_1,*(undefined1 *)(puVar1 + 1),*puVar1,puVar1,param_4);
  }
  return 0;
}

