// module: mt7915.ko
// function: HwCtrlSetPartWmmParam @ 0xaeaf4
// size: 56 bytes
//

undefined4 HwCtrlSetPartWmmParam(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_2 + 8);
  if (puVar1 != (undefined1 *)0x0) {
    AsicSetWmmParam(param_1,*puVar1,*(undefined4 *)(puVar1 + 4),*(undefined4 *)(puVar1 + 8),
                    *(undefined4 *)(puVar1 + 0xc));
    return 0;
  }
  return 1;
}

