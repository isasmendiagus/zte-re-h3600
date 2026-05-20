// module: idmfdb.ko
// function: idm_proc_forbidIdm_write @ 0x11ccc
// size: 232 bytes
//

uint idm_proc_forbidIdm_write(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte local_20 [12];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  local_20[4] = 0;
  local_20[5] = 0;
  local_20[6] = 0;
  local_20[7] = 0;
  iVar1 = PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  uVar5 = *(uint *)(((uint)local_20 & 0xffffe000) + 8);
  if (param_3 < 8) {
    uVar3 = param_2 + param_3;
    uVar4 = uVar3;
    if (!CARRY4(param_2,param_3)) {
      uVar4 = uVar3 - (uVar5 + 1);
    }
    if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
      uVar5 = 0;
    }
    if (uVar5 != 0) {
      if (param_3 != 0) goto LAB_00011d24;
      goto LAB_00011d5c;
    }
  }
  else {
    uVar3 = param_2 + 7;
    uVar4 = uVar3;
    if (param_2 < 0xfffffff9) {
      uVar4 = uVar3 - (uVar5 + 1);
    }
    if (param_2 < 0xfffffff9 && uVar3 <= uVar5) {
      uVar5 = 0;
    }
    param_3 = 7;
    if (uVar5 != 0) {
LAB_00011d24:
      __memzero(local_20,param_3,uVar4);
      return 0xfffffff2;
    }
  }
  iVar2 = __copy_from_user(local_20,param_2,param_3);
  if (iVar2 != 0) {
    return 0xfffffff2;
  }
LAB_00011d5c:
  iVar2 = 0;
  pbVar6 = local_20;
  while( true ) {
    if (9 < *pbVar6 - 0x30) break;
    iVar2 = (*pbVar6 - 0x30) + iVar2 * 10;
    pbVar6 = pbVar6 + 1;
  }
  *(int *)(iVar1 + 8) = iVar2;
  return param_3;
}

