/* ===== FUN FUN_40e51164 @ 40e51164 =====
 * callers: 40e38d84:FUN_40e38d84, 40e3b384:FUN_40e3b384, 40e3b480:FUN_40e3b480, 40e3b7f8:FUN_40e3b7f8, 40e3b990:FUN_40e3b990, 40e3bb04:FUN_40e3bb04, 40e3c514:FUN_40e3c514, 40e3c90c:FUN_40e3c90c
 * callees: (none)
 */


undefined8 FUN_40e51164(uint param_1,int param_2,uint param_3)

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
