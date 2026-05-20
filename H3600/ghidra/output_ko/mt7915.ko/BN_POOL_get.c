// module: mt7915.ko
// function: BN_POOL_get @ 0x20ee04
// size: 292 bytes
//

undefined4 * BN_POOL_get(int *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *local_1c [2];
  
  uVar3 = param_1[3];
  if (uVar3 != param_1[4]) {
    if (uVar3 == 0) {
      iVar4 = *param_1;
      param_1[1] = iVar4;
      uVar6 = 0;
    }
    else {
      iVar4 = param_1[1];
      uVar6 = uVar3 & 0xf;
      if (uVar6 == 0) {
        iVar4 = *(int *)(iVar4 + 0x144);
        param_1[1] = iVar4;
      }
    }
    param_1[3] = uVar3 + 1;
    return (undefined4 *)(iVar4 + uVar6 * 0x14);
  }
  os_alloc_mem(0,local_1c,0x148);
  if (local_1c[0] != (undefined4 *)0x0) {
    puVar7 = local_1c[0];
    do {
      uVar6 = DAT_005f4ad8;
      uVar3 = DAT_005f4ad4;
      uVar2 = DAT_005f4ad0;
      uVar1 = DAT_005f4acc;
      uVar5 = (uint)(param_2 << 0x1c) >> 0x1f;
      if (puVar7 == (undefined4 *)0x0) {
        uVar5 = 0;
      }
      puVar8 = puVar7 + 5;
      *puVar7 = DAT_005f4ac8;
      puVar7[1] = uVar1;
      puVar7[2] = uVar2;
      puVar7[3] = uVar3;
      if (uVar5 != 0) {
        uVar3 = uVar6;
      }
      puVar7[4] = uVar6;
      if (uVar5 != 0) {
        puVar7[4] = uVar3 | 8;
      }
      puVar7 = puVar8;
    } while (puVar8 != local_1c[0] + 0x50);
    iVar4 = param_1[2];
    local_1c[0][0x51] = 0;
    local_1c[0][0x50] = iVar4;
    iVar4 = *param_1;
    if (iVar4 == 0) {
      param_1[2] = (int)local_1c[0];
      param_1[1] = (int)local_1c[0];
      *param_1 = (int)local_1c[0];
    }
    else {
      *(undefined4 **)(param_1[2] + 0x144) = local_1c[0];
      param_1[2] = (int)local_1c[0];
    }
    if (iVar4 != 0) {
      param_1[1] = (int)local_1c[0];
    }
    param_1[4] = param_1[4] + 0x10;
    param_1[3] = param_1[3] + 1;
  }
  return local_1c[0];
}

