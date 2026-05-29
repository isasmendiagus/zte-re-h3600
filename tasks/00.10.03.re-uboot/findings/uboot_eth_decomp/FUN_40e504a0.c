// FUN_40e504a0 @ 40e504a0

void FUN_40e504a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)((int)param_1 + 7);
  bVar2 = *(byte *)(param_1 + 2);
  FUN_40e2a1b4(uRam40e50504,param_1,*param_1,param_1[1],param_1[2],param_1[3],param_3);
  FUN_40e2a1b4(uRam40e5050c,(uint)(bVar1 >> 1) | (uint)bVar2 << 7,*(undefined2 *)(param_1 + 1),
               *(ushort *)(param_1 + 3) >> 2,*puRam40e50508);
  return;
}
