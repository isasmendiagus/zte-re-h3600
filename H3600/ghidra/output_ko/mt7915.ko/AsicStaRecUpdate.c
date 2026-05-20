// module: mt7915.ko
// function: AsicStaRecUpdate @ 0x13494c
// size: 764 bytes
//

undefined4 AsicStaRecUpdate(int param_1,undefined1 *param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  byte bVar9;
  int local_1c8 [51];
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  uint local_f0;
  undefined1 local_ec;
  undefined1 auStack_e8 [136];
  int *local_60;
  undefined1 auStack_58 [52];
  
  uVar1 = *(ushort *)(param_2 + 2);
  uVar8 = (uint)uVar1;
  iVar2 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar2 + 0x34) == 0) {
    AsicNotSupportFunc(param_1,"AsicStaRecUpdate");
    return 0;
  }
  os_zero_mem(&local_fc,0xd4);
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar8 < uVar3) {
    piVar7 = (int *)(uVar8 * 0x14c0 + param_1 + 0xa1d20);
    if (3 < DebugLevel) goto LAB_00134c2c;
LAB_00134a78:
    if (piVar7 != (int *)0x0) {
      iVar6 = *piVar7;
      if (iVar6 == 0) {
        local_f0 = *(uint *)(param_2 + 0xc);
        local_f8._0_2_ = CONCAT11(0xe,(undefined1)local_f8);
        goto joined_r0x00134ad0;
      }
      iVar5 = piVar7[2];
      if (iVar5 == 0) {
        printk(&_LC33,0x82e);
        dump_stack();
        return 0xffffffff;
      }
      local_f8._0_2_ = CONCAT11(*(undefined1 *)(iVar5 + 0x29),(undefined1)local_f8);
      if (iVar6 == 2 || (iVar6 - 0x20001U & 0xfffdffff) == 0) {
        bVar9 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
        if (*(char *)(param_1 + 0x79504d) != '\0') {
          iVar6 = HcGetBandByWdev();
          iVar5 = piVar7[2];
          if (iVar6 == 0) {
            bVar9 = "SetPartProfileParameters"[param_1 + 0x1a];
          }
          else {
            bVar9 = "rtmp_read_vow_parms_from_file"[param_1];
          }
        }
        iVar6 = HcIsBfCapSupport(iVar5);
        local_f0 = *(uint *)(param_2 + 0xc);
        if (iVar6 != 1) goto joined_r0x00134ad0;
        if ((local_f0 & 0x10) != 0) {
          if (1 < bVar9) {
            AsicBfStaRecUpdate(param_1,*(undefined1 *)(piVar7[2] + 0x18),*param_2,uVar8);
          }
          txbf_dyn_mech(param_1);
          local_f0 = *(uint *)(param_2 + 0xc);
        }
        if ((local_f0 & 0x100000) == 0) goto joined_r0x00134ad0;
        AsicBfeeStaRecUpdate(param_1,*(undefined1 *)(piVar7[2] + 0x18),*param_2,uVar8);
      }
      local_f0 = *(uint *)(param_2 + 0xc);
      goto joined_r0x00134ad0;
    }
  }
  else if (3 < DebugLevel) {
    piVar7 = (int *)0x0;
LAB_00134c2c:
    printk("%s::Wcid(%d), u4EnableFeature(%d)\n","AsicStaRecUpdate",*(undefined2 *)(param_2 + 2),
           *(undefined4 *)(param_2 + 0xc));
    goto LAB_00134a78;
  }
  local_f0 = *(uint *)(param_2 + 0xc);
  piVar7 = (int *)0x0;
  local_f8._0_2_ = CONCAT11(0xe,(undefined1)local_f8);
joined_r0x00134ad0:
  if ((local_f0 & 0x4000) != 0) {
    os_move_mem(auStack_58,param_2 + 0x9c,0x30);
    local_f0 = *(uint *)(param_2 + 0xc);
  }
  local_ec = param_2[0x10];
  local_f4 = *(undefined4 *)(param_2 + 4);
  local_fc = CONCAT31(local_fc._1_3_,*param_2);
  local_fc = CONCAT22(uVar1,(undefined2)local_fc);
  local_f8 = CONCAT31(local_f8._1_3_,param_2[8]);
  local_60 = piVar7;
  os_move_mem(auStack_e8,param_2 + 0x14,0x88);
  memcpy(local_1c8,&local_f0,200);
  uVar4 = (**(code **)(iVar2 + 0x34))(param_1,local_fc,local_f8,local_f4);
  if (((piVar7 != (int *)0x0) && (*piVar7 == 0x20001)) &&
     (local_1c8[0] = piVar7[2], local_1c8[0] != 0)) {
    if ((*(char *)(local_1c8[0] + 0x405c) != '\0') &&
       ((*(byte *)((int)piVar7 + 0xbf) >> 5) - 5 < 0xfffffffa)) {
      ap_set_he_fixed_gi_ltf_by_wcid_or_bss
                (param_1,*(char *)(local_1c8[0] + 0x405c) + -1,0,(short)piVar7[0x38]);
    }
  }
  return uVar4;
}

