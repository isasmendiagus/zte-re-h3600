/* ===== FUN FUN_40e50060 @ 40e50060 =====
 * callers: 40e501f8:FUN_40e501f8
 * callees: (none)
 */


undefined4 FUN_40e50060(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_40e500cc/*=0x92344000[TM]*/;
  iVar2 = 0x14;
  do {
    if ((*(uint *)(DAT_40e500cc/*=0x92344000[TM]*/ + 0x18) & 1) != 0) {
      *(uint *)(DAT_40e500cc/*=0x92344000[TM]*/ + 0x14) = param_1 | param_3 << 0x16;
      *(undefined4 *)(iVar1 + 0x28) = param_2[3];
      *(undefined4 *)(iVar1 + 0x24) = param_2[2];
      *(undefined4 *)(iVar1 + 0x20) = param_2[1];
      *(undefined4 *)(iVar1 + 0x1c) = *param_2;
      return 0;
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(int *)(DAT_40e500d0/*=0x47f5962c*/ + 8) = *(int *)(DAT_40e500d0/*=0x47f5962c*/ + 8) + 1;
  return 0xfffffff5;
}
