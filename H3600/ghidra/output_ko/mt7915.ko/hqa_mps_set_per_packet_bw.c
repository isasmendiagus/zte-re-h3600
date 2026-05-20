// module: mt7915.ko
// function: hqa_mps_set_per_packet_bw @ 0x247bf4
// size: 504 bytes
//

undefined4 hqa_mps_set_per_packet_bw(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int local_38;
  undefined4 *local_34;
  int local_30;
  undefined4 local_2c [2];
  
  local_38 = param_2 + 0xc;
  local_34 = (undefined4 *)0x0;
  FUN_002474f4(1,4,&local_38,&local_30);
  uVar5 = (uint)(*(ushort *)(param_2 + 8) >> 2);
  if (uVar5 - 2 < 0x400) {
    uVar5 = uVar5 - 1 & 0xffff;
    iVar2 = sys_ad_alloc_mem(&local_34,uVar5 << 2);
    if (iVar2 == 0) {
      uVar8 = 0;
      do {
        FUN_002474f4(1,4,&local_38,local_2c);
        uVar6 = local_2c[0];
        switch(local_2c[0]) {
        case 1:
          local_2c[0] = 1;
          break;
        case 2:
          local_2c[0] = 2;
          break;
        case 3:
          local_2c[0] = 3;
          break;
        case 4:
          local_2c[0] = 4;
          break;
        case 5:
          local_2c[0] = 5;
          break;
        case 6:
          local_2c[0] = 6;
          break;
        default:
          local_2c[0] = 0;
        case 0:
          uVar6 = local_2c[0];
          local_2c[0] = 0;
        }
        local_34[uVar8] = uVar6;
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar5);
      *(char *)(param_1 + 0x4cc) = (char)local_30;
      iVar2 = param_1 + local_30 * 0xd18;
      if ((*(uint *)(iVar2 + 0x4e0) & 0x40) == 0) {
        iVar7 = *(int *)(iVar2 + 0x11c8);
        if ((iVar7 == 0) && (*(int *)(iVar2 + 0x11b8) == 0)) {
          *(uint *)(iVar2 + 0x11b8) = uVar5;
          iVar7 = (uVar5 + 1) * 0x20;
          iVar3 = sys_ad_alloc_mem(param_1 + local_30 * 0xd18 + 0x11c8,iVar7);
          if (iVar3 != 0) goto LAB_00247c88;
          sys_ad_zero_mem(*(undefined4 *)(iVar2 + 0x11c8),iVar7);
          iVar7 = *(int *)(iVar2 + 0x11c8);
        }
        iVar2 = iVar7;
        puVar4 = local_34;
        uVar8 = 1;
        do {
          if (iVar7 != 0) {
            *(undefined4 *)(iVar2 + 0x3c) = *puVar4;
          }
          bVar1 = uVar8 < uVar5;
          iVar2 = iVar2 + 0x20;
          puVar4 = puVar4 + 1;
          uVar8 = uVar8 + 1;
        } while (bVar1);
        sys_ad_free_mem();
        local_34 = (undefined4 *)0x0;
        uVar6 = 0;
        goto LAB_00247c50;
      }
      uVar6 = 0x104;
    }
    else {
LAB_00247c88:
      uVar6 = 0x101;
    }
  }
  else {
    uVar6 = 0x103;
  }
  if (local_34 != (undefined4 *)0x0) {
    sys_ad_free_mem();
  }
LAB_00247c50:
  FUN_00246b90(param_2,2,uVar6);
  return uVar6;
}

