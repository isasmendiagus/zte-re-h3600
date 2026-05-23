// module: mt7915.ko
// function: hqa_mps_set_payload_length @ 0x2482d0
// size: 456 bytes
//

undefined4 hqa_mps_set_payload_length(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  
  local_30 = param_2 + 0xc;
  local_2c = 0;
  FUN_002474f4(1,4,&local_30,&local_28);
  uVar4 = (uint)(*(ushort *)(param_2 + 8) >> 2);
  if (uVar4 - 2 < 0x400) {
    uVar4 = uVar4 - 1 & 0xffff;
    iVar2 = sys_ad_alloc_mem(&local_2c,uVar4 << 2);
    if (iVar2 == 0) {
      uVar6 = 0;
      do {
        FUN_002474f4(1,4,&local_30,&local_24);
        *(undefined4 *)(local_2c + uVar6 * 4) = local_24;
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar4);
      *(char *)(param_1 + 0x4cc) = (char)local_28;
      iVar2 = param_1 + local_28 * 0xd18;
      if ((*(uint *)(iVar2 + 0x4e0) & 0x40) == 0) {
        iVar7 = *(int *)(iVar2 + 0x11c8);
        if ((iVar7 == 0) && (*(int *)(iVar2 + 0x11b8) == 0)) {
          *(uint *)(iVar2 + 0x11b8) = uVar4;
          iVar7 = (uVar4 + 1) * 0x20;
          iVar3 = sys_ad_alloc_mem(param_1 + local_28 * 0xd18 + 0x11c8,iVar7);
          if (iVar3 != 0) goto LAB_00248364;
          sys_ad_zero_mem(*(undefined4 *)(iVar2 + 0x11c8),iVar7);
          iVar7 = *(int *)(iVar2 + 0x11c8);
        }
        iVar2 = 0;
        iVar3 = iVar7;
        uVar6 = 1;
        do {
          if (*(uint *)(local_2c + iVar2) < 0x5d9) {
            if (*(uint *)(local_2c + iVar2) < 0x19) {
              *(undefined4 *)(local_2c + iVar2) = 0x19;
            }
          }
          else {
            *(undefined4 *)(local_2c + iVar2) = 0x5d8;
          }
          if (iVar7 != 0) {
            *(undefined4 *)(iVar3 + 0x2c) = *(undefined4 *)(local_2c + iVar2);
          }
          iVar2 = iVar2 + 4;
          bVar1 = uVar6 < uVar4;
          iVar3 = iVar3 + 0x20;
          uVar6 = uVar6 + 1;
        } while (bVar1);
        sys_ad_free_mem();
        local_2c = 0;
        uVar5 = 0;
        goto LAB_0024832c;
      }
      uVar5 = 0x104;
    }
    else {
LAB_00248364:
      uVar5 = 0x101;
    }
  }
  else {
    uVar5 = 0x103;
  }
  if (local_2c != 0) {
    sys_ad_free_mem();
  }
LAB_0024832c:
  FUN_00246b90(param_2,2,uVar5);
  return uVar5;
}

