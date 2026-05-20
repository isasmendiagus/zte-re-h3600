// module: mt7915.ko
// function: mt_op_set_off_ch_scan @ 0x25871c
// size: 676 bytes
//

undefined4 mt_op_set_off_ch_scan(int param_1,int param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 uVar12;
  int iVar13;
  undefined1 local_5c;
  byte local_54 [2];
  uint local_52;
  undefined4 local_4e;
  undefined4 local_4a;
  undefined1 local_46;
  undefined4 local_45;
  undefined4 local_41;
  undefined4 local_3d;
  undefined1 local_39;
  byte local_38;
  byte local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  
  local_4a = 0x9d958c84;
  local_45 = 0x40383028;
  local_52 = 0x3c342c24;
  local_4e = 0x7c746c64;
  local_41 = 0x80787068;
  local_46 = 0;
  local_39 = 0;
  iVar13 = 0;
  local_3d = 0xa1999088;
  local_54[0] = 0;
  local_54[1] = 0;
  printk(&_LC15,"mt_op_set_off_ch_scan");
  iVar7 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar7 == 0) {
    return 0x503;
  }
  bVar1 = *(byte *)(param_2 + 0xc50);
  uVar2 = *(undefined1 *)(param_2 + 0xc56);
  uVar10 = *(undefined4 *)(param_4 + 8);
  uVar3 = *(undefined1 *)(param_4 + 0x10);
  uVar12 = *(undefined4 *)(param_2 + 0xc48);
  uVar4 = *(undefined1 *)(param_2 + 0xc60);
  bVar6 = bVar1;
  uVar5 = uVar2;
  do {
    uVar8 = (uint)bVar6;
    switch(uVar5) {
    case 0:
      break;
    case 1:
      uVar9 = local_52 & 0xff;
      if (uVar9 != 0) {
        uVar11 = 0;
        do {
          if (uVar8 == uVar9) {
            uVar8 = uVar8 + 2 & 0xff;
          }
          else if (*(byte *)((int)&local_45 + uVar11) == uVar8) {
            uVar8 = uVar8 - 2 & 0xff;
          }
          bVar6 = (byte)uVar8;
          uVar11 = uVar11 + 1 & 0xff;
          uVar9 = (uint)*(byte *)((int)&local_52 + uVar11);
        } while (uVar9 != 0);
      }
      break;
    case 2:
    case 6:
      bVar6 = vht_cent_ch_freq(uVar8,1,1);
      break;
    default:
      printk("%s: off_ch_idx %d, BW is invalid %d\n","mt_op_set_off_ch_scan",iVar13);
      printk("%s: invalid parameters\n","mt_op_set_off_ch_scan");
      return 1;
    case 5:
      bVar6 = vht_cent_ch_freq(uVar8,2,1);
      local_54[iVar13] = bVar6;
      goto joined_r0x00258938;
    }
    local_54[iVar13] = bVar6;
joined_r0x00258938:
    if (iVar13 == 1) {
      sys_ad_zero_mem(&local_38,0x10);
      local_30 = *(undefined1 *)(param_4 + 0x14);
      local_37 = local_54[0];
      local_5c = (undefined1)*(undefined4 *)(param_4 + 4);
      local_2d = local_5c;
      local_32 = local_54[1];
      local_35 = (undefined1)uVar12;
      local_33 = (undefined1)*(uint *)(param_4 + 8);
      local_2e = (undefined1)*(undefined4 *)(param_4 + 0x18);
      local_2b = (undefined1)*(undefined4 *)(param_4 + 0xc);
      local_2c = 2;
      local_38 = bVar1;
      local_36 = uVar2;
      local_34 = uVar4;
      local_31 = uVar3;
      local_2f = local_30;
      printk("%s: mntr_ch:%d mntr_bw:%d mntr_central_ch:%d\n","mt_op_set_off_ch_scan",
             *(uint *)(param_4 + 8) & 0xff,uVar3,local_54[1]);
      printk("%s: work_prim_ch:%d work_bw:%d work_central_ch:%d\n","mt_op_set_off_ch_scan",local_38,
             local_36,local_37);
      printk("%s: scan_mode:%d dbdc_idx:%d is_aband:%d\n","mt_op_set_off_ch_scan",local_2e,local_2d,
             local_2b);
      iVar7 = mt_cmd_off_ch_scan(iVar7,&local_38);
      if (iVar7 == 0) {
        return 0;
      }
      return 0x501;
    }
    iVar13 = 1;
    bVar6 = (byte)uVar10;
    uVar5 = uVar3;
  } while( true );
}

