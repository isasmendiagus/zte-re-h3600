// module: mt7915.ko
// function: mt_serv_set_txbf_chan_profile_update @ 0x253864
// size: 548 bytes
//

undefined4 mt_serv_set_txbf_chan_profile_update(int *param_1,ushort *param_2)

{
  char cVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int *unaff_r8;
  ushort uVar12;
  ushort local_48;
  ushort local_46;
  ushort local_44;
  ushort local_40;
  ushort local_3c;
  
  uVar3 = param_2[1];
  uVar4 = *param_2;
  uVar8 = (int)((uint)param_2[4] << 0x13) >> 0x13 & 0xffff;
  uVar9 = (int)((uint)param_2[6] << 0x13) >> 0x13 & 0xffff;
  uVar7 = (int)((uint)param_2[8] << 0x13) >> 0x13 & 0xffff;
  cVar1 = (char)param_1[(uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x44a];
  cVar2 = (char)param_2[2];
  if (cVar1 == '\x02') {
    uVar8 = uVar9 - uVar8 & 0xffff;
    if (cVar2 != '\0') {
      uVar10 = 0;
      iVar6 = *param_1;
      uVar7 = uVar10;
      goto LAB_00253a1c;
    }
    unaff_r8 = param_1 + 0x400;
    sys_ad_zero_mem(&local_48,0x10);
LAB_002539f4:
    local_44 = (ushort)((uVar8 << 0x14) >> 0x14);
  }
  else {
    if (cVar1 == '\x03') {
      uVar8 = uVar7 - uVar8 & 0xffff;
      uVar10 = uVar7 - uVar9 & 0xffff;
      if (cVar2 != '\0') {
        iVar6 = *param_1;
        uVar7 = 0;
        goto LAB_00253a1c;
      }
      unaff_r8 = param_1 + 0x400;
      sys_ad_zero_mem(&local_48,0x10);
      uVar11 = uVar10;
    }
    else {
      iVar6 = *param_1;
      if (*(char *)(iVar6 + 0x34) == '\0') {
        if (cVar2 == '\0') {
          unaff_r8 = param_1 + 0x400;
        }
        uVar11 = (int)((uint)param_2[10] << 0x13) >> 0x13 & 0xffff;
        uVar8 = uVar11 - uVar8 & 0xffff;
        uVar10 = uVar11 - uVar9 & 0xffff;
        uVar7 = uVar11 - uVar7 & 0xffff;
        uVar11 = uVar10;
        if (cVar2 != '\0') {
LAB_00253a1c:
          uVar12 = uVar4 & 0xff;
          unaff_r8 = param_1 + 0x400;
          net_ad_set_txbf_profile_tag_read(iVar6,uVar12,1);
          iVar6 = param_1[0x7c4];
          if (*(code **)(iVar6 + 0x1a0) != (code *)0x0) {
            (**(code **)(iVar6 + 0x1a0))(*param_1,1);
            iVar6 = param_1[0x7c4];
          }
          uVar11 = uVar10;
          if (*(code **)(iVar6 + 0x19c) != (code *)0x0) {
            (**(code **)(iVar6 + 0x19c))(*param_1,uVar12);
          }
        }
      }
      else {
        uVar11 = 0;
        if (cVar2 == '\0') {
          unaff_r8 = param_1 + 0x400;
        }
        uVar10 = 0;
        uVar8 = uVar9 - uVar8 & 0xffff;
        uVar7 = uVar11;
        if (cVar2 != '\0') goto LAB_00253a1c;
      }
      sys_ad_zero_mem(&local_48,0x10);
      if (cVar1 == '\x02') goto LAB_002539f4;
      if (cVar1 != '\x03') {
        local_44 = (ushort)((uVar8 << 0x14) >> 0x14);
        local_40 = (ushort)((uVar11 << 0x14) >> 0x14);
        local_3c = (ushort)((uVar7 << 0x14) >> 0x14);
        goto LAB_00253918;
      }
    }
    local_44 = (ushort)((uVar8 << 0x14) >> 0x14);
    local_40 = (ushort)((uVar11 << 0x14) >> 0x14);
  }
LAB_00253918:
  if (*(code **)(unaff_r8[0x3c4] + 0x1e4) == (code *)0x0) {
    uVar5 = 0x100;
  }
  else {
    local_48 = uVar4;
    local_46 = uVar3;
    uVar5 = (**(code **)(unaff_r8[0x3c4] + 0x1e4))(*param_1,&local_48);
  }
  return uVar5;
}

