/* ===== FUN FUN_40e50384 @ 40e50384 =====
 * callers: 40e4fda4:FUN_40e4fda4
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e4fe5c:FUN_40e4fe5c, 40e4ff74:FUN_40e4ff74, 40e501f8:FUN_40e501f8, 40e50348:FUN_40e50348, 40e50978:FUN_40e50978, 40e50a4c:FUN_40e50a4c
 */


int FUN_40e50384(void)

{
  int iVar1;
  
  FUN_40e501f8();
  FUN_40e50348();
  iVar1 = FUN_40e4fe5c();
  if (iVar1 < 0) {
    FUN_40e2a1b4(DAT_40e503d8/*=0x47f3ec20*/,iVar1);
    return iVar1;
  }
  FUN_40e4ff74();
  iVar1 = DAT_40e503dc/*=0x92340000[TM]*/;
  *(undefined4 *)(DAT_40e503dc/*=0x92340000[TM]*/ + 0xf0) = DAT_40e503e0/*=0x41a00000[RAM]*/;
  *(undefined4 *)(iVar1 + 4) = 0x10;
  FUN_40e50978();
  FUN_40e50a4c();
  return 0;
}
