// module: mt7915.ko
// function: Set_Entry_HTC_Err_Cnt_Proc @ 0x346a8
// size: 196 bytes
//

undefined4
Set_Entry_HTC_Err_Cnt_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if ((param_1 != -0xa31e0) && (*(int *)(param_1 + 0xa31e0) == 0x20001)) {
    *(uint *)(param_1 + 0xa4610) = uVar1 + 1;
    if (*(uint *)(param_1 + 0xa7c550) < uVar1) {
      *(undefined4 *)(param_1 + 0xa4610) = 0;
      bVar2 = *(char *)(param_1 + 0xa4614) != '\0';
      if (bVar2) {
        *(undefined1 *)(param_1 + 0xa4614) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0xa4614) = 1;
      }
      HW_SET_ASIC_WCID_AAD_OM(param_1,1,!bVar2);
    }
    if (0 < DebugLevel) {
      printk("@@@ pEntry->HTC_ICVErrCnt=%u\n",*(undefined4 *)(param_1 + 0xa4610));
    }
  }
  return 1;
}

