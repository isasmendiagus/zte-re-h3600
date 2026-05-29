/* ===== FUN FUN_40e4f894 @ 40e4f894 =====
 * callers: (none)
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45ac0:FUN_40e45ac0
 */


void FUN_40e4f894(uint *param_1,int param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  *param_1 = *param_1 | 0x80000000;
  param_1[2] = param_1[2] | 0x800;
  param_1[2] = param_1[2] & 0xfffffffd;
  *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  *param_1 = *param_1 & 0xfffffff8 | param_6;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  param_1[2] = param_1[2] & 0xffffff83 | 0x10;
  param_1[2] = param_1[2] | 1;
  *param_1 = *param_1 & 0xf7ffffff;
  param_1[1] = param_1[1] & 0xf7ffffff;
  FUN_40e45ac0(10);
  *param_1 = *param_1 & 0x7fffffff;
  do {
  } while ((param_1[1] & 0x10000000) == 0);
  FUN_40e2a1b4(DAT_40e4fa04/*=0x47f3eb56*/);
  return;
}
