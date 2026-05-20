// module: mt7915.ko
// function: mt_ate_off_ch_scan @ 0x27d9d4
// size: 864 bytes
//

undefined4 mt_ate_off_ch_scan(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  byte local_56 [4];
  uint local_52;
  undefined4 local_4e;
  undefined4 local_4a;
  undefined1 local_46;
  undefined4 local_45;
  undefined4 local_41;
  undefined4 local_3d;
  undefined1 local_39;
  byte local_38;
  undefined1 local_37;
  byte local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  byte local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  
  iVar14 = param_1 + 0xa39fd0;
  uVar12 = 0;
  local_45 = 0x40383028;
  local_41 = 0x80787068;
  local_3d = 0xa1999088;
  local_39 = 0;
  local_52 = 0x3c342c24;
  local_4e = 0x7c746c64;
  local_4a = 0x9d958c84;
  local_46 = 0;
  local_56[0] = 0;
  local_56[1] = 0;
  local_56[2] = 0;
  local_56[3] = 0;
  if (iVar14 != 0 && param_2 != 0) {
    bVar1 = *(byte *)(param_1 + 0xa3ae36);
    iVar8 = net_ad_wrap_service();
    iVar13 = (uint)bVar1 * 0xd18;
    uVar2 = *(undefined1 *)(iVar8 + iVar13 + 0x113f);
    iVar8 = net_ad_wrap_service(param_1);
    uVar3 = *(undefined1 *)(iVar8 + iVar13 + 0x1140);
    iVar8 = net_ad_wrap_service(param_1);
    bVar1 = *(byte *)(iVar8 + iVar13 + 0x1130);
    iVar8 = net_ad_wrap_service(param_1);
    uVar10 = *(undefined4 *)(param_2 + 8);
    bVar4 = *(byte *)(param_2 + 0x10);
    local_56[1] = bVar4;
    bVar5 = *(byte *)(iVar8 + iVar13 + 0x1136);
    local_56[0] = bVar5;
    uVar12 = (uint)(iVar14 == 0 || param_2 == 0);
    bVar7 = bVar5;
    bVar6 = bVar1;
LAB_0027daf8:
    uVar15 = (uint)bVar6;
    switch(bVar7) {
    case 0:
      goto switchD_0027db00_caseD_0;
    case 1:
      uVar9 = local_52 & 0xff;
      if (uVar9 == 0) goto switchD_0027db00_caseD_0;
      uVar11 = 0;
      do {
        if (uVar15 == uVar9) {
          uVar15 = uVar15 + 2 & 0xff;
        }
        else if (*(byte *)((int)&local_45 + uVar11) == uVar15) {
          uVar15 = uVar15 - 2 & 0xff;
        }
        uVar11 = uVar11 + 1 & 0xff;
        uVar9 = (uint)*(byte *)((int)&local_52 + uVar11);
      } while (uVar9 != 0);
      local_56[uVar12 + 2] = (byte)uVar15;
      bVar7 = local_56[1];
      break;
    case 2:
    case 6:
      bVar6 = vht_cent_ch_freq(uVar15,1,1);
      goto switchD_0027db00_caseD_0;
    default:
      goto switchD_0027db00_caseD_3;
    case 5:
      bVar7 = vht_cent_ch_freq(uVar15,2,1);
      local_56[uVar12 + 2] = bVar7;
      bVar7 = local_56[1];
    }
    goto joined_r0x0027dc58;
  }
  uVar10 = 0;
  goto LAB_0027dbf8;
switchD_0027db00_caseD_0:
  local_56[uVar12 + 2] = bVar6;
  bVar7 = local_56[1];
joined_r0x0027dc58:
  local_56[1] = bVar7;
  if (uVar12 == 1) {
    os_zero_mem(&local_38,0x10);
    local_30 = *(undefined1 *)(param_2 + 0x14);
    local_33 = (undefined1)*(uint *)(param_2 + 8);
    local_32 = local_56[3];
    local_37 = local_56[2];
    local_2d = (undefined1)*(undefined4 *)(param_2 + 4);
    local_2e = (undefined1)*(undefined4 *)(param_2 + 0x18);
    local_2b = (undefined1)*(undefined4 *)(param_2 + 0xc);
    local_2c = 2;
    local_38 = bVar1;
    local_36 = bVar5;
    local_35 = uVar2;
    local_34 = uVar3;
    local_31 = bVar4;
    local_2f = local_30;
    if ((2 < DebugLevel) &&
       (printk("%s: mntr_ch:%d mntr_bw:%d mntr_central_ch:%d\n","mt_ate_off_ch_scan",
               *(uint *)(param_2 + 8) & 0xff,bVar4,local_56[3]), 2 < DebugLevel)) {
      printk("%s: work_prim_ch:%d work_bw:%d work_central_ch:%d\n","mt_ate_off_ch_scan",local_38,
             local_36,local_37);
    }
    uVar10 = mt_cmd_off_ch_scan(param_1,&local_38);
    return uVar10;
  }
  uVar12 = 1;
  bVar6 = (byte)uVar10;
  goto LAB_0027daf8;
switchD_0027db00_caseD_3:
  if (DebugLevel < 0) {
    return 1;
  }
  uVar10 = 1;
  printk("%s: off_ch_idx %d, BW is invalid %d\n","mt_ate_off_ch_scan",uVar12);
LAB_0027dbf8:
  if (-1 < DebugLevel) {
    printk("%s: NULL entry ate_ctrl %p, param %p, or invalid BW %d\n","mt_ate_off_ch_scan",iVar14,
           param_2,local_56[uVar12]);
  }
  return uVar10;
}

