/* ===== FUN FUN_40e4fda4 @ 40e4fda4 =====
 * callers: 40e4fe04:FUN_40e4fe04
 * callees: 40e50384:FUN_40e50384, 40e50b0c:FUN_40e50b0c, 40e50f20:FUN_40e50f20
 */


undefined4 FUN_40e4fda4(void)

{
  FUN_40e50384();
  FUN_40e50b0c();
  FUN_40e50f20();
  *(undefined4 *)(DAT_40e4fdc8/*=0x923a0000[ETH_TM2]*/ + 0xe0) = 0x11;
  return 0;
}
