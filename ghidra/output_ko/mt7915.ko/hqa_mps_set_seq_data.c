// module: mt7915.ko
// function: hqa_mps_set_seq_data @ 0x24a800
// size: 464 bytes
//

undefined4 hqa_mps_set_seq_data(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  
  local_30 = param_2 + 0xc;
  local_2c = 0;
  FUN_002474f4(1,4,&local_30,&local_28);
  uVar7 = (uint)(*(ushort *)(param_2 + 8) >> 2);
  if (0x3ff < uVar7 - 2) {
    uVar6 = 0x103;
    goto LAB_0024a84c;
  }
  uVar7 = uVar7 - 1 & 0xffff;
  iVar3 = sys_ad_alloc_mem(&local_2c,uVar7 << 2);
  if (iVar3 == 0) {
    uVar8 = 0;
    do {
      FUN_002474f4(1,4,&local_30,&local_24);
      *(undefined4 *)(local_2c + uVar8 * 4) = local_24;
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar7);
    *(char *)(param_1 + 0x4cc) = (char)local_28;
    iVar3 = param_1 + local_28 * 0xd18;
    if ((*(uint *)(iVar3 + 0x4e0) & 0x40) != 0) {
      uVar6 = 0x104;
      goto LAB_0024a84c;
    }
    if ((*(int *)(iVar3 + 0x11c8) == 0) && (*(int *)(iVar3 + 0x11b8) == 0)) {
      *(uint *)(iVar3 + 0x11b8) = uVar7;
      iVar2 = (uVar7 + 1) * 0x20;
      iVar4 = sys_ad_alloc_mem(param_1 + local_28 * 0xd18 + 0x11c8,iVar2);
      if (iVar4 != 0) goto LAB_0024a894;
      sys_ad_zero_mem(*(undefined4 *)(iVar3 + 0x11c8),iVar2);
    }
    iVar3 = local_28 * 0xd18 + param_1;
    *(uint *)(iVar3 + 0x11b8) = uVar7;
    puVar9 = *(uint **)(iVar3 + 0x11c8);
    iVar3 = 0;
    uVar8 = 1;
    puVar5 = puVar9;
    do {
      if (puVar9 != (uint *)0x0) {
        puVar5[8] = (uint)(*(int *)(local_2c + iVar3) << 4) >> 0x1c;
        puVar5[9] = (uint)(*(int *)(local_2c + iVar3) << 8) >> 0x10;
        puVar5[10] = (uint)*(byte *)(local_2c + iVar3);
      }
      iVar3 = iVar3 + 4;
      bVar1 = uVar8 < uVar7;
      uVar8 = uVar8 + 1;
      puVar5 = puVar5 + 8;
    } while (bVar1);
    sys_ad_free_mem();
    local_2c = 0;
    uVar6 = mt_serv_mps_set_seq_data(param_1);
  }
  else {
LAB_0024a894:
    uVar6 = 0x101;
  }
LAB_0024a84c:
  if (local_2c != 0) {
    sys_ad_free_mem();
  }
  FUN_00246b90(param_2,2,uVar6);
  return uVar6;
}

