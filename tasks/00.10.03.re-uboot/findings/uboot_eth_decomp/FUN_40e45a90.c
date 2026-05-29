/* ===== FUN FUN_40e45a90 @ 40e45a90 =====
 * callers: 40e219e0:FUN_40e219e0, 40e220e8:FUN_40e220e8, 40e2fa24:FUN_40e2fa24, 40e30498:FUN_40e30498, 40e31854:FUN_40e31854, 40e344cc:FUN_40e344cc, 40e3c514:FUN_40e3c514, 40e3c90c:FUN_40e3c90c
 * callees: 40e2176c:FUN_40e2176c
 */


void FUN_40e45a90(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_40e45abc/*=0x000493e0*/;
  do {
    uVar2 = param_1;
    if (uVar1 <= param_1) {
      uVar2 = uVar1;
    }
    FUN_40e2176c(uVar2);
    param_1 = param_1 - uVar2;
  } while (param_1 != 0);
  return;
}
