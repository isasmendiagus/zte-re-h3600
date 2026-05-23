// module: mt7915.ko
// function: AsicNotSupportFunc @ 0x131b60
// size: 88 bytes
//

void AsicNotSupportFunc(int param_1,undefined4 param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 < 3) {
    pcVar2 = (&_LANCHOR0)[iVar1];
  }
  else {
    pcVar2 = "HIF_MT";
  }
  if (2 < DebugLevel) {
    printk("%s(): NotSupportedFunc for this arch(%s)!\n",param_2,pcVar2);
    return;
  }
  return;
}

