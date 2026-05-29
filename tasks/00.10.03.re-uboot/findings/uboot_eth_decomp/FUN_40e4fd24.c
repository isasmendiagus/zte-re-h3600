/* ===== FUN FUN_40e4fd24 @ 40e4fd24 =====
 * callers: 40e50978:FUN_40e50978
 * callees: (none)
 */


undefined4 FUN_40e4fd24(uint param_1,undefined1 *param_2)

{
  if (param_1 < 4 && param_2 != (undefined1 *)0x0) {
    *(uint *)((short)param_1 * 8 + DAT_40e4fd9c/*=0x923a0078*/) =
         (uint)(byte)param_2[3] << 0x10 | (uint)(byte)param_2[2] << 0x18 | (uint)(byte)param_2[5] |
         (uint)(byte)param_2[4] << 8;
    *(uint *)((short)param_1 * 8 + DAT_40e4fda0/*=0x923a007c*/) = (uint)CONCAT11(*param_2,param_2[1]);
    return 0;
  }
  return 0xffffffff;
}
