// module: mt7915.ko
// function: D_SetFrmChkFlag @ 0x9b66c
// size: 60 bytes
//

undefined4 D_SetFrmChkFlag(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  if (2 < DebugLevel) {
    printk("%s(): FrameCheck = 0x%x\n","D_SetFrmChkFlag",param_2,DebugLevel,param_4);
  }
  return 1;
}

