/* ===== FUN FUN_40e2a1b4 @ 40e2a1b4 =====
 * callers: 40e21478:FUN_40e21478, 40e219e0:FUN_40e219e0, 40e21bd4:FUN_40e21bd4, 40e21c68:FUN_40e21c68, 40e21ecc:FUN_40e21ecc, 40e222f0:FUN_40e222f0, 40e223d8:FUN_40e223d8, 40e2400c:FUN_40e2400c
 * callees: 40e2a184:FUN_40e2a184, 40e4692c:thunk_FUN_40e45fd8
 */


undefined4 FUN_40e2a1b4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int unaff_r8;
  undefined1 auStack_12c [276];
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uVar1 = 0;
  if (*(int *)(unaff_r8 + 0x1c) != 0) {
    uStack_c = param_2;
    uStack_8 = param_3;
    uStack_4 = param_4;
    uVar1 = thunk_FUN_40e45fd8(auStack_12c,param_1,&uStack_c,param_4,&uStack_c);
    FUN_40e2a184(auStack_12c);
  }
  return uVar1;
}
