/* ===== FUN FUN_40e4f700 @ 40e4f700 =====
 * callers: 40e4fa08:FUN_40e4fa08
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45ac0:FUN_40e45ac0
 */


void FUN_40e4f700(uint *param_1,int param_2,uint param_3,uint param_4,int param_5,uint param_6)

{
  FUN_40e2a1b4(DAT_40e4f88c/*=0x47f3eb18*/);
  if (param_3 < 0x14) {
    FUN_40e2a1b4(DAT_40e4f890/*=0x47f3eb32*/,param_3);
  }
  *param_1 = *param_1 | 0x80000000;
  *param_1 = *param_1 & 0xf7ffffff;
  *param_1 = *param_1 & 0xfeffffff;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  if (param_5 != 0) {
    *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  }
  if (param_6 != 0) {
    *param_1 = *param_1 & 0xfffffff8 | param_6;
  }
  param_1[1] = param_1[1] & 0xf7ffffff;
  param_1[1] = param_1[1] | 0x4000000;
  param_1[1] = param_1[1] & 0xfdffffff;
  param_1[1] = param_1[1] & 0xfeffffff;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  FUN_40e45ac0(100);
  *param_1 = *param_1 & 0x7fffffff;
  return;
}
