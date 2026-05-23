// module: mt7915.ko
// function: Set_HT_BssCoexRssiThr_Proc @ 0xdf6b4
// size: 88 bytes
//

undefined4 Set_HT_BssCoexRssiThr_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  
  cVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(char *)(param_1 + 0x795651) = cVar2;
  if (2 < iVar1) {
    printk("Set BssCoexRssiThr=%d!\n",(int)cVar2);
  }
  return 1;
}

