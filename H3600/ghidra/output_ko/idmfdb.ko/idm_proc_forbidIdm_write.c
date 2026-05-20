// module: idmfdb.ko
// function: idm_proc_forbidIdm_write @ 0x11b70
// size: 252 bytes
//

uint idm_proc_forbidIdm_write(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte local_20 [8];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  local_20[4] = 0;
  local_20[5] = 0;
  local_20[6] = 0;
  local_20[7] = 0;
  iVar1 = PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  uVar6 = *(uint *)(((uint)local_20 & 0xffffe000) + 8);
  if (param_3 < 8) {
    uVar3 = param_2 + param_3;
    uVar4 = uVar3;
    if (!CARRY4(param_2,param_3)) {
      uVar4 = uVar3 - (uVar6 + 1);
    }
    if (!CARRY4(param_2,param_3) && uVar3 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 != 0) {
      if (param_3 != 0) {
        __memzero(local_20,param_3,uVar4);
      }
      goto LAB_00011c04;
    }
  }
  else {
    uVar3 = param_2 + 7;
    uVar4 = uVar3;
    if (param_2 < 0xfffffff9) {
      uVar4 = uVar3 - (uVar6 + 1);
    }
    if (param_2 < 0xfffffff9 && uVar3 <= uVar6) {
      uVar6 = 0;
    }
    param_3 = 7;
    if (uVar6 != 0) {
      __memzero(local_20,7,uVar4);
      goto LAB_00011c04;
    }
  }
  __copy_from_user(local_20,param_2,param_3);
LAB_00011c04:
  iVar5 = 0;
  pbVar2 = local_20;
  while( true ) {
    if (9 < *pbVar2 - 0x30) break;
    iVar5 = (*pbVar2 - 0x30) + iVar5 * 10;
    pbVar2 = pbVar2 + 1;
  }
  *(int *)(iVar1 + 8) = iVar5;
  return param_3;
}

