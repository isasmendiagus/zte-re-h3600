// module: mt7915.ko
// function: SetATETxSEnable @ 0x260950
// size: 92 bytes
//

undefined4 SetATETxSEnable(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATETxSEnable",param_2,DebugLevel,param_4);
  }
  uVar1 = simple_strtol(param_2,0,10);
  *(undefined1 *)(param_1 + 0xa3b8b5) = uVar1;
  return 1;
}

