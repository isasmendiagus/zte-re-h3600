// module: mt7915.ko
// function: set_skip_ageout @ 0x1d55c4
// size: 88 bytes
//

undefined4 set_skip_ageout(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7d080) = uVar2;
  if (0 < iVar1) {
    printk("set verification mode skip_ageout = %d\n",uVar2);
  }
  return 1;
}

