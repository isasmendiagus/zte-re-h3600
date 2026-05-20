// module: mt7915.ko
// function: Set_ApCli_Steer_Proc @ 0x2a6e0
// size: 108 bytes
//

undefined4
Set_ApCli_Steer_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *param_1;
  if (*(int *)(iVar2 + 0x38) != 0x400) {
    return 0;
  }
  uVar3 = *(uint *)(iVar2 + 0x3c);
  uVar1 = os_str_tol(param_2,0,10,iVar2,param_4);
  if (1 < uVar1) {
    return 1;
  }
  *(char *)(param_1 + (uVar3 & 0xff) * 0x84dec + 0x1603b5) = (char)uVar1;
  return 1;
}

