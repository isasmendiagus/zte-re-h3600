// module: mt7915.ko
// function: Set_HT_BssCoexApCntThr_Proc @ 0xdf65c
// size: 88 bytes
//

undefined4 Set_HT_BssCoexApCntThr_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0x79564f) = uVar2;
  if (2 < iVar1) {
    printk("Set BssCoexApCntThr=%d!\n",uVar2);
  }
  return 1;
}

