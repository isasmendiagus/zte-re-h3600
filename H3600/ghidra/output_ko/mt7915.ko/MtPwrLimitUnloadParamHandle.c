// module: mt7915.ko
// function: MtPwrLimitUnloadParamHandle @ 0x151298
// size: 256 bytes
//

/* WARNING: Removing unreachable block (ram,0x001512c8) */
/* WARNING: Removing unreachable block (ram,0x001512e4) */
/* WARNING: Removing unreachable block (ram,0x001512f4) */
/* WARNING: Removing unreachable block (ram,0x001512f8) */
/* WARNING: Removing unreachable block (ram,0x00151300) */
/* WARNING: Removing unreachable block (ram,0x00151308) */
/* WARNING: Removing unreachable block (ram,0x00151310) */
/* WARNING: Removing unreachable block (ram,0x00151348) */

undefined4 MtPwrLimitUnloadParamHandle(undefined4 param_1,undefined4 param_2)

{
  MtPwrGetPwrLimitInstance(param_1,param_2,0);
  if (-1 < DebugLevel) {
    printk("%s: null pointer for link list!!\n","MtPwrLimitUnloadParamHandle");
  }
  return 1;
}

