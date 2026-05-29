/* ===== FUN FUN_40e2a5a4 @ 40e2a5a4 =====
 * callers: 40e2a6ec:FUN_40e2a6ec, 40e2a914:FUN_40e2a914
 * callees: 40e45800:FUN_40e45800
 */


uint FUN_40e2a5a4(int param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = DAT_40e2a604/*=0x47f52890*/;
  uVar2 = *DAT_40e2a604/*=0x47f52890*/;
  uVar3 = param_1 + uVar2;
  if (param_1 < 0) {
    FUN_40e45800(uVar3,0,-param_1);
  }
  if ((puVar1[1] <= uVar3) && (uVar3 <= DAT_40e2a604/*=0x47f52890*/[2])) {
    *DAT_40e2a604/*=0x47f52890*/ = uVar3;
    return uVar2;
  }
  return 0xffffffff;
}
