// FUN_40e504a4 @ 40e504a4

void FUN_40e504a4(undefined4 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 2);
  FUN_40e2a1b4(uRam40e50504,param_1,*param_1,param_1[1],param_1[2],param_1[3],param_3);
  FUN_40e2a1b4(uRam40e5050c,param_4 >> 1 | (uint)bVar1 << 7,*(undefined2 *)(param_1 + 1),
               *(ushort *)(param_1 + 3) >> 2,*puRam40e50508);
  return;
}
