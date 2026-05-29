/* ===== FUN FUN_40e4f580 @ 40e4f580 =====
 * callers: 40e4fa08:FUN_40e4fa08
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45ac0:FUN_40e45ac0
 */


void FUN_40e4f580(uint *param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  if (param_3 < 0x10) {
    FUN_40e2a1b4(DAT_40e4f6fc/*=0x47f3eaf4*/,param_3);
  }
  *param_1 = *param_1 | 0x80000000;
  *param_1 = *param_1 | 0x8000000;
  *param_1 = *param_1 & 0xfeffffff;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  if (param_4 != 0) {
    *param_1 = *param_1 & 0xffffffc7 | param_4 << 3;
  }
  if (param_5 != 0) {
    *param_1 = *param_1 & 0xfffffff8 | param_5;
  }
  param_1[1] = param_1[1] & 0xf7ffffff;
  param_1[1] = param_1[1] | 0x4000000;
  param_1[1] = param_1[1] & 0xfdffffff;
  param_1[1] = param_1[1] & 0xfeffffff;
  param_1[1] = param_1[1] & 0xff000000;
  FUN_40e45ac0(100);
  *param_1 = *param_1 & 0x7fffffff;
  return;
}
