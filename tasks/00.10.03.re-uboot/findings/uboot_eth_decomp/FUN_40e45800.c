/* ===== FUN FUN_40e45800 @ 40e45800 =====
 * callers: 40e21d7c:FUN_40e21d7c, 40e241d8:FUN_40e241d8, 40e27cc4:FUN_40e27cc4, 40e2a5a4:FUN_40e2a5a4, 40e2a608:FUN_40e2a608, 40e2aeec:FUN_40e2aeec, 40e2ba50:FUN_40e2ba50, 40e2cad8:FUN_40e2cad8
 * callees: (none)
 */


void FUN_40e45800(uint *param_1,byte param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  if (((uint)param_1 & 3) == 0) {
    iVar3 = 5;
    uVar2 = 0;
    while (iVar3 = iVar3 + -1, puVar1 = param_1, iVar3 != 0) {
      uVar2 = (uint)param_2 | uVar2 << 8;
    }
    for (; (byte *)0x3 < (byte *)((int)param_1 + (param_3 - (int)puVar1)); puVar1 = puVar1 + 1) {
      *puVar1 = uVar2;
    }
    uVar2 = param_3 & 0xfffffffc;
    param_3 = param_3 & 3;
    param_1 = (uint *)((int)param_1 + uVar2);
  }
  puVar1 = (uint *)((int)param_1 + param_3);
  for (; param_1 != puVar1; param_1 = (uint *)((int)param_1 + 1)) {
    *(byte *)param_1 = param_2;
  }
  return;
}
