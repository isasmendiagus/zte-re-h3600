// module: mt7915.ko
// function: hqa_mps_set_packet_count @ 0x248138
// size: 408 bytes
//

undefined4 hqa_mps_set_packet_count(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int local_30;
  undefined4 *local_2c;
  int local_28;
  undefined4 local_24 [2];
  
  local_30 = param_2 + 0xc;
  local_2c = (undefined4 *)0x0;
  FUN_002474f4(1,4,&local_30,&local_28);
  uVar5 = (uint)(*(ushort *)(param_2 + 8) >> 2);
  if (uVar5 - 2 < 0x400) {
    uVar5 = uVar5 - 1 & 0xffff;
    iVar2 = sys_ad_alloc_mem(&local_2c,uVar5 << 2);
    if (iVar2 == 0) {
      uVar7 = 0;
      do {
        FUN_002474f4(1,4,&local_30,local_24);
        local_2c[uVar7] = local_24[0];
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar5);
      *(char *)(param_1 + 0x4cc) = (char)local_28;
      iVar2 = param_1 + local_28 * 0xd18;
      if ((*(uint *)(iVar2 + 0x4e0) & 0x40) == 0) {
        iVar8 = *(int *)(iVar2 + 0x11c8);
        if ((iVar8 == 0) && (*(int *)(iVar2 + 0x11b8) == 0)) {
          *(uint *)(iVar2 + 0x11b8) = uVar5;
          iVar8 = (uVar5 + 1) * 0x20;
          iVar3 = sys_ad_alloc_mem(param_1 + local_28 * 0xd18 + 0x11c8,iVar8);
          if (iVar3 != 0) goto LAB_002481cc;
          sys_ad_zero_mem(*(undefined4 *)(iVar2 + 0x11c8),iVar8);
          iVar8 = *(int *)(iVar2 + 0x11c8);
        }
        iVar2 = iVar8;
        puVar4 = local_2c;
        uVar7 = 1;
        do {
          if (iVar8 != 0) {
            *(undefined4 *)(iVar2 + 0x30) = *puVar4;
          }
          bVar1 = uVar7 < uVar5;
          iVar2 = iVar2 + 0x20;
          puVar4 = puVar4 + 1;
          uVar7 = uVar7 + 1;
        } while (bVar1);
        sys_ad_free_mem();
        local_2c = (undefined4 *)0x0;
        uVar6 = 0;
        goto LAB_00248194;
      }
      uVar6 = 0x104;
    }
    else {
LAB_002481cc:
      uVar6 = 0x101;
    }
  }
  else {
    uVar6 = 0x103;
  }
  if (local_2c != (undefined4 *)0x0) {
    sys_ad_free_mem();
  }
LAB_00248194:
  FUN_00246b90(param_2,2,uVar6);
  return uVar6;
}

