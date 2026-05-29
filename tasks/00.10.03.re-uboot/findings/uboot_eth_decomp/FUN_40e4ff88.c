/* ===== FUN FUN_40e4ff88 @ 40e4ff88 =====
 * callers: 40e50730:FUN_40e50730
 * callees: (none)
 */


uint FUN_40e4ff88(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_40e4fff0/*=0x92348000[TM]*/;
  if (*(int *)(DAT_40e4fff0/*=0x92348000[TM]*/ + 0x14) == 0) {
    *(undefined4 *)(DAT_40e4fff0/*=0x92348000[TM]*/ + 0x14) = 1;
    iVar3 = 4;
    do {
      if (*(int *)(iVar2 + 0x14) == 0) {
        puVar1 = (uint *)(DAT_40e4fff0/*=0x92348000[TM]*/ + 0xc);
        if ((int)*puVar1 < 0) {
          *(undefined4 *)(DAT_40e4fff0/*=0x92348000[TM]*/ + 0x14) = 0;
          return *puVar1 & 0xffff;
        }
        break;
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  *(int *)(DAT_40e4fff4/*=0x47f59610*/ + 0x14) = *(int *)(DAT_40e4fff4/*=0x47f59610*/ + 0x14) + 1;
  return 0xfffffff5;
}
