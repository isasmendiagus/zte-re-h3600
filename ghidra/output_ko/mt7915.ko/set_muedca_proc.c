// module: mt7915.ko
// function: set_muedca_proc @ 0x23b4ec
// size: 100 bytes
//

undefined4 set_muedca_proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = os_str_tol(param_2,0,10);
  bVar3 = -1 < DebugLevel;
  *(undefined1 *)(iVar2 + 0x1f5) = uVar1;
  if (bVar3) {
    printk("set chip cap MU_EDCA timer to %d\n",uVar1);
  }
  return 1;
}

