/* ===== FUN FUN_40e2a200 @ 40e2a200 =====
 * callers: 40e46958:FUN_40e46958
 * callees: 40e2a184:FUN_40e2a184, 40e4692c:thunk_FUN_40e45fd8
 */


undefined4 FUN_40e2a200(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int unaff_r8;
  undefined1 auStack_11c [276];
  
  uVar1 = 0;
  if (*(int *)(unaff_r8 + 0x1c) != 0) {
    uVar1 = thunk_FUN_40e45fd8(auStack_11c,param_1,param_2);
    FUN_40e2a184(auStack_11c);
  }
  return uVar1;
}
