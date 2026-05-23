// module: mt7915.ko
// function: veri_mode_switch @ 0x1d742c
// size: 88 bytes
//

undefined4 veri_mode_switch(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7d07e) = uVar2;
  if (0 < iVar1) {
    printk("set verify_mode_on = %d\n",uVar2);
  }
  return 1;
}

