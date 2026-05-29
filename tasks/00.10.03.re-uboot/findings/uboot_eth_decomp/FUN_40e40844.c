/* ===== FUN FUN_40e40844 @ 40e40844 =====
 * callers: 40e21050:FUN_40e21050
 * callees: 40e20e74:FUN_40e20e74, 40e2a1b4:FUN_40e2a1b4
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_40e40844(void)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 extraout_r1;
  undefined4 in_r3;
  
  uVar2 = _DAT_9400004c;
  FUN_40e2a1b4(DAT_40e40894/*=0x47f3d81f*/,_DAT_9400004c);
  _DAT_9400004c = ~(~(uVar2 >> 9) << 9);
  FUN_40e2a1b4(DAT_40e40898/*=0x47f3d844*/,_DAT_9400004c);
  FUN_40e20e74(200);
  uVar1 = DAT_40e408a0/*=0x0001381b*/;
  *(undefined4 *)(DAT_40e4089c/*=0x9a100000*/ + 4) = DAT_40e408a0/*=0x0001381b*/;
  FUN_40e20e74(200,extraout_r1,uVar1,in_r3);
  return;
}
