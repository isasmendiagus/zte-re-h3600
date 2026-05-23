// module: mt7915.ko
// function: mtf_update_raw_counters @ 0x19d1f8
// size: 1752 bytes
//

void mtf_update_raw_counters(int param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_a0;
  uint *local_9c;
  int *local_98;
  uint local_94;
  int local_90;
  int *local_8c;
  uint *local_88;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  int local_4c;
  int local_48;
  uint local_44;
  uint local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  
  uVar2 = IsStopingPdma(param_1 + 0xa7bf04);
  if (uVar2 == 0) {
    local_8c = (int *)(param_1 + 0xa39cb8);
    local_98 = (int *)(param_1 + 0xa39cc0);
    local_9c = (uint *)(param_1 + 0xa39cc8);
    local_88 = (uint *)(param_1 + 0xa39cf8);
    iVar6 = 0;
    iVar7 = 0;
    local_a0 = 0;
    local_94 = 0;
    local_90 = param_1;
    do {
      iVar5 = param_1 + local_a0;
      local_70 = uVar2;
      local_6c = uVar2;
      local_64 = uVar2;
      local_60 = uVar2;
      local_5c = uVar2;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02fc0,&local_70);
      local_70 = local_70 & 0xffffff;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02fbc,&local_6c);
      local_6c = local_6c & 0xffffff;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02f58,&local_68);
      uVar3 = local_68;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02f54,&local_68);
      *(int *)(iVar5 + 0xa39ca0) = *(int *)(iVar5 + 0xa39ca0) + local_6c;
      *(int *)(iVar5 + 0xa39c98) = *(int *)(iVar5 + 0xa39c98) + (local_70 - local_6c);
      *(int *)(iVar5 + 0xa39c78) = *(int *)(iVar5 + 0xa39c78) + (uVar3 & 0xffff);
      *(int *)(iVar5 + 0xa39c80) = *(int *)(iVar5 + 0xa39c80) + (uVar3 >> 0x10);
      *(int *)(iVar5 + 0xa39c88) = *(int *)(iVar5 + 0xa39c88) + (local_68 & 0xffff);
      *(int *)(iVar5 + 0xa39c90) = *(int *)(iVar5 + 0xa39c90) + (local_68 >> 0x10);
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
        if ((*(uint *)(local_90 + 0xa7c474) & 0x20) == 0) {
          cVar1 = *(char *)(param_1 + 0xa7c3d8);
        }
        else {
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df1a938,&local_50);
          *(int *)(local_90 + 0xa7c46c) =
               *(int *)(local_90 + 0xa7c46c) - ((int)(local_50 << 5) >> 0x1f);
          *(int *)(local_90 + 0xa7c470) =
               *(int *)(local_90 + 0xa7c470) - ((int)(local_50 << 7) >> 0x1f);
          local_50 = 0xdf000000;
          mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df1a960,0xdf000000);
          local_50 = 0x1f000000;
          mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df1a960,0x1f000000);
          cVar1 = *(char *)(param_1 + 0xa7c3d8);
        }
        if (cVar1 == '\x01') {
          MtCmdGetPartialMibInfoCnt(param_1,local_94 & 0xff,&local_50);
          *local_8c = *local_8c + local_4c;
          *local_98 = *local_98 + local_48;
          uVar3 = *local_9c;
          *local_9c = uVar3 + local_44;
          local_9c[1] = local_9c[1] + (uint)CARRY4(uVar3,local_44);
          uVar3 = *(uint *)(iVar5 + 0xa39cd0);
          *(uint *)(iVar5 + 0xa39cd0) = uVar3 + local_40;
          *(uint *)(iVar5 + 0xa39cd4) = *(int *)(iVar5 + 0xa39cd4) + (uint)CARRY4(uVar3,local_40);
          *(undefined4 *)(iVar5 + 0xa39cdc) = 0;
          *(undefined4 *)(iVar5 + 0xa39cd8) = local_3c;
          uVar3 = *(uint *)(iVar5 + 0xa39ce0);
          *(uint *)(iVar5 + 0xa39ce0) = uVar3 + local_38;
          *(uint *)(iVar5 + 0xa39ce4) = *(int *)(iVar5 + 0xa39ce4) + (uint)CARRY4(uVar3,local_38);
          *(undefined4 *)(iVar5 + 0xa39ce8) = local_34;
          *(undefined4 *)(iVar5 + 0xa39cec) = 0;
          *(undefined4 *)(iVar5 + 0xa39cf0) = local_30;
          *(undefined4 *)(iVar5 + 0xa39cf4) = 0;
          uVar3 = *local_88;
          *local_88 = uVar3 + local_2c;
          local_88[1] = local_88[1] + (uint)CARRY4(uVar3,local_2c);
        }
        else {
          local_58 = uVar2;
          local_54 = uVar2;
          local_50 = uVar2;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12fe4,&local_58);
          uVar3 = *local_9c;
          *local_9c = uVar3 + local_58;
          local_9c[1] = local_9c[1] + (uint)CARRY4(uVar3,local_58);
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12f9c,&local_54);
          uVar3 = *local_88;
          *local_88 = uVar3 + local_54;
          local_88[1] = local_88[1] + (uint)CARRY4(uVar3,local_54);
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12fec,&local_64);
          local_64 = local_64 & 0xffff;
          *local_8c = *local_8c + local_64;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12fe8,&local_60);
          local_60 = local_60 & 0xffff;
          *local_98 = *local_98 + local_60;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12fd0,&local_5c);
          local_5c = local_5c & 0x3ffffff;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + -0x7df12fd4,&local_50);
          *(uint *)(iVar5 + 0xa39cd8) = local_50 & 0xffffff;
          *(undefined4 *)(iVar5 + 0xa39cdc) = 0;
        }
LAB_0019d568:
        if (*(int *)(param_1 + 0xa7c228) != 0) {
          if (local_94 == 0) {
            *(uint *)(param_1 + 0xa7c22c) = local_64 + *(int *)(param_1 + 0xa7c22c);
            *(uint *)(param_1 + 0xa7c230) = local_5c + *(int *)(param_1 + 0xa7c230);
          }
          else {
            *(uint *)(param_1 + 0xa7c234) = local_64 + *(int *)(param_1 + 0xa7c234);
            *(uint *)(param_1 + 0xa7c238) = local_5c + *(int *)(param_1 + 0xa7c238);
          }
        }
      }
      else {
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02fec,&local_64);
        local_64 = local_64 & 0xffff;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02fe8,&local_60);
        if (*(int *)(param_1 + 0xa7c228) != 0) {
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + -0x7df02fd0,&local_5c);
          goto LAB_0019d568;
        }
      }
      uVar3 = *(uint *)(iVar5 + 0xa39c58);
      uVar4 = local_64 + uVar3;
      *(uint *)(iVar5 + 0xa39c58) = uVar4;
      if (uVar4 < uVar3) {
        *(int *)(iVar5 + 0xa39c5c) = *(int *)(iVar5 + 0xa39c5c) + 1;
      }
      iVar6 = iVar6 + 0x200;
      local_94 = local_94 + 1;
      iVar7 = iVar7 + 0x10000;
      local_a0 = local_a0 + 0x108;
      local_8c = local_8c + 0x42;
      *(uint *)(param_1 + 0xa39bf4) = local_60 + *(int *)(param_1 + 0xa39bf4);
      local_98 = local_98 + 0x42;
      local_9c = local_9c + 0x42;
      local_88 = local_88 + 0x42;
      local_90 = local_90 + 0x70;
    } while (iVar6 != 0x400);
    if (*(char *)(param_1 + 0xa3b8b6) == '\x01') {
      MT_ATEUpdateRxStatistic(param_1,3,param_1 + 0xa39bf8);
    }
  }
  return;
}

