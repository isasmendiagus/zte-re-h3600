/* ===== FUN FUN_40e51148 @ 40e51148 =====
 * callers: 40e2d10c:FUN_40e2d10c, 40e37f04:FUN_40e37f04, 40e37fcc:FUN_40e37fcc, 40e38248:FUN_40e38248, 40e38544:FUN_40e38544, 40e38bac:FUN_40e38bac, 40e38ec8:FUN_40e38ec8, 40e39034:FUN_40e39034, 40e3b7f8:FUN_40e3b7f8, 40e3c90c:FUN_40e3c90c
 * callees: (none)
 */


undefined8 FUN_40e51148(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  if ((int)(param_3 - 0x20) < 0) {
    uVar1 = param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = param_2 >> (param_3 - 0x20 & 0xff);
  }
  return CONCAT44(param_2 >> (param_3 & 0xff),uVar1);
}
