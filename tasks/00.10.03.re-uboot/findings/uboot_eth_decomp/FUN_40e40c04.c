/* ===== FUN FUN_40e40c04 @ 40e40c04 =====
 * callers: 40e21164:FUN_40e21164, 40e2a154:FUN_40e2a154
 * callees: 40e408a4:FUN_40e408a4
 */


void FUN_40e40c04(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_40e408a4();
                    /* WARNING: Could not recover jumptable at 0x40e40c1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x24))(param_1);
  return;
}
