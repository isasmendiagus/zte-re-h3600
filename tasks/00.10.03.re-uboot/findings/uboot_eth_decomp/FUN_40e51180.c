/* ===== FUN FUN_40e51180 @ 40e51180 =====
 * callers: 40e37cd0:FUN_40e37cd0, 40e38248:FUN_40e38248, 40e38bac:FUN_40e38bac, 40e38ec8:FUN_40e38ec8, 40e39034:FUN_40e39034, 40e3cc0c:FUN_40e3cc0c, 40e437d8:FUN_40e437d8
 * callees: (none)
 */


undefined8 FUN_40e51180(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  if ((int)(param_3 - 0x20) < 0) {
    uVar1 = param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = param_1 << (param_3 - 0x20 & 0xff);
  }
  return CONCAT44(uVar1,param_1 << (param_3 & 0xff));
}
