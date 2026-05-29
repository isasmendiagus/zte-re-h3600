/* ===== FUN FUN_40e40c20 @ 40e40c20 =====
 * callers: 40e2a184:FUN_40e2a184, 40e2fa24:FUN_40e2fa24
 * callees: 40e408a4:FUN_40e408a4
 */


void FUN_40e40c20(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_40e408a4();
                    /* WARNING: Could not recover jumptable at 0x40e40c38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x28))(param_1);
  return;
}
