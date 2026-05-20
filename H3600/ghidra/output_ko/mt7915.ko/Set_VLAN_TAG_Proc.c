// module: mt7915.ko
// function: Set_VLAN_TAG_Proc @ 0x2c0d8
// size: 568 bytes
//

undefined4 Set_VLAN_TAG_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  bool bVar9;
  code *pcVar10;
  int iVar11;
  undefined1 auStack_1d0 [204];
  int *local_104;
  undefined4 local_fc;
  undefined4 local_f8;
  int local_f4;
  undefined4 local_f0 [36];
  int *local_60;
  
  iVar7 = *param_1;
  iVar4 = os_str_tol(param_2,0,10);
  iVar11 = *(int *)(iVar7 + 0x38);
  iVar7 = *(int *)(iVar7 + 0x3c);
  if ((iVar11 - 0x100U & 0xfffffeff) == 0) {
    bVar9 = true;
    iVar3 = iVar7 * 0x160d + 0xadc92;
  }
  else {
    bVar9 = false;
    if (iVar11 != 0x400) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("Unexpected if_type\n");
      return 0;
    }
    iVar3 = iVar7 * 0x84dec + 0xdb6d6;
  }
  piVar8 = param_1 + iVar3;
  if (piVar8 == (int *)0x0) {
    uVar6 = 0;
  }
  else {
    *(bool *)(piVar8 + 0x23e) = iVar4 != 0;
    uVar5 = hc_get_asic_cap(param_1[0x29e5e8]);
    if ((uVar5 & 0x400) != 0) {
      iVar4 = hc_get_arch_ops(param_1[0x29e5e8]);
      if (bVar9) {
        os_zero_mem(&local_fc,0xd4);
        local_60 = param_1 + (uint)*(ushort *)(piVar8 + 4) * 0x530 + 0x28748;
        pcVar10 = *(code **)(iVar4 + 0x34);
        local_fc = CONCAT22(*(ushort *)(piVar8 + 4),(undefined2)local_fc);
        local_fc = CONCAT31(local_fc._1_3_,*(undefined1 *)((int)piVar8 + 0x999));
        local_f8 = CONCAT22(local_f8._2_2_,0xe00);
        local_f4 = 0x10020;
        local_f8 = CONCAT31(local_f8._1_3_,2);
        local_f0[0] = 0x100;
        if (pcVar10 != (code *)0x0) {
          memcpy(auStack_1d0,local_f0,200);
          uVar6 = (*pcVar10)(param_1,local_fc,local_f8,local_f4);
          return uVar6;
        }
      }
      else if (iVar11 == 0x400) {
        uVar1 = *(undefined1 *)((int)piVar8 + 0xd);
        bVar2 = *(byte *)(param_1 + iVar7 * 0x84dec + 0x16038e);
        local_104 = param_1 + (uint)bVar2 * 0x530 + 0x28748;
        os_zero_mem(&local_fc,0xd4);
        local_f4 = param_1[(uint)bVar2 * 0x530 + 0x28c51];
        local_60 = local_104;
        pcVar10 = *(code **)(iVar4 + 0x34);
        local_fc = CONCAT31(CONCAT12(bVar2,(undefined2)local_fc) >> 8,uVar1);
        local_f8 = CONCAT31(CONCAT21(local_f8._2_2_,*(undefined1 *)((int)piVar8 + 0x29)),
                            *(undefined1 *)((int)param_1 + iVar7 * 0x2137b0 + 0x580e8e));
        local_f0[0] = 0x100;
        if (pcVar10 != (code *)0x0) {
          memcpy(auStack_1d0,local_f0,200);
          uVar6 = (*pcVar10)(param_1,local_fc,local_f8,local_f4);
          return uVar6;
        }
      }
    }
    uVar6 = 1;
  }
  return uVar6;
}

