// module: mt7915.ko
// function: SetLoadFwMethod @ 0xc4060
// size: 144 bytes
//

undefined4 SetLoadFwMethod(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if (iVar3 == 0) {
    *(undefined4 *)(iVar2 + 0x118) = 1;
    if (0 < iVar1) {
      printk("Load from header\n");
    }
  }
  else {
    *(undefined4 *)(iVar2 + 0x118) = 2;
    if (0 < iVar1) {
      printk("Load from bin\n");
    }
  }
  return 1;
}

