// module: mt7915.ko
// function: mt7915_get_efuse_free_blk_num @ 0x17e804
// size: 144 bytes
//

undefined1 mt7915_get_efuse_free_blk_num(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined1 uStack_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_14 [8];
  
  __memzero(&uStack_18,4);
  __memzero(local_14,4);
  local_17 = 1;
  local_16 = param_2;
  iVar1 = MtCmdEfuseFreeBlockCount(param_1,&uStack_18,local_14);
  if (iVar1 != 0) {
    if (-1 < DebugLevel) {
      printk("(%s) cmd failed!\n","mt7915_get_efuse_free_blk_num");
    }
    return 0;
  }
  return local_14[0];
}

