// module: mt7915.ko
// function: Set_HTC_Err_TH_Proc @ 0x3410c
// size: 96 bytes
//

undefined4 Set_HTC_Err_TH_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 != 0) {
    *(int *)(param_1 + 0xa7c550) = iVar1;
  }
  if (0 < DebugLevel) {
    printk("@@@ pAd->HTC_ICV_Err_TH=%u\n",*(undefined4 *)(param_1 + 0xa7c550));
  }
  return 1;
}

