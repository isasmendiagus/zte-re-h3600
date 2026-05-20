// module: mt7915.ko
// function: load_fw_v2_compressimg @ 0x1c0668
// size: 988 bytes
//

int load_fw_v2_compressimg(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint local_90;
  uint *local_88;
  undefined4 local_84;
  uint local_80;
  int local_74;
  int local_68;
  int local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  
  bVar1 = false;
  local_68 = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((char)param_3[1] == '\0') {
    *(undefined4 *)(param_1 + 0xa7861c) = 1;
    local_84 = 0;
    local_80 = 0;
  }
  else {
    local_88 = &local_60;
    local_74 = 0;
    local_84 = 0;
    local_80 = 0;
    local_90 = 0;
    do {
      iVar6 = *param_3;
      iVar7 = iVar6 + local_90 * 0x1c;
      local_68 = *(int *)(iVar6 + local_90 * 0x1c);
      iVar5 = *(int *)(iVar7 + 8);
      if ((*(byte *)(iVar7 + 0xc) & 0x20) != 0) {
        local_84 = *(undefined4 *)(iVar7 + 4);
        local_80 = 1;
      }
      if ((*(byte *)(iVar7 + 0xc) & 8) == 0) {
        *(undefined4 *)(param_1 + 0xa7861c) = 1;
        if ((*(byte *)(iVar7 + 0xc) & 1) == 0) {
          uVar4 = 0;
        }
        else {
          uVar4 = 8;
        }
        if (param_2 == 1) {
          uVar8 = 0x10;
        }
        else {
          uVar8 = 0;
        }
        iVar3 = MtCmdAddressLenReq(param_1,*(undefined4 *)(iVar7 + 4),*(undefined4 *)(iVar7 + 8),
                                   *(byte *)(iVar7 + 0xc) & 7 | 0x80000000 | uVar4 | uVar8);
        if (iVar3 == 0) {
          *(undefined4 *)(param_1 + 0xa7861c) = 2;
          iVar3 = FUN_001bfba4(param_1,*(undefined4 *)(iVar6 + local_90 * 0x1c),
                               *(undefined4 *)(iVar7 + 8));
          if (iVar3 == 0) goto LAB_001c08ac;
        }
LAB_001c07f4:
        os_free_mem(*param_3);
        *param_3 = 0;
        *(undefined1 *)(param_3 + 1) = 0;
        goto LAB_001c0814;
      }
      if (0 < DebugLevel) {
        printk("REGION[%d] COMPRESSED IMAGE DOWNLOAD\n",local_90);
      }
      if (iVar5 != 0) {
        iVar6 = 0;
        do {
          *(undefined4 *)(param_1 + 0xa7861c) = 1;
          local_64 = 0;
          FUN_001c062c(&local_64,&local_68);
          if ((*(byte *)(iVar7 + 0xc) & 1) == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = 8;
          }
          iVar3 = *(int *)(iVar7 + 0x18) * iVar6;
          if (param_2 == 1) {
            uVar8 = 0x10;
          }
          else {
            uVar8 = 0;
          }
          iVar6 = iVar6 + 1;
          iVar3 = MtCmdAddressLenReq(param_1,iVar3 + *(int *)(iVar7 + 4),local_64,
                                     *(byte *)(iVar7 + 0xc) & 7 | 0x80000000 | uVar4 | uVar8);
          if (iVar3 != 0) goto LAB_001c07f4;
          *(undefined4 *)(param_1 + 0xa7861c) = 2;
          iVar3 = FUN_001bfba4(param_1,local_68,local_64);
          if (iVar3 != 0) goto LAB_001c07f4;
          iVar5 = iVar5 + (-4 - local_64);
          local_68 = local_68 + local_64;
        } while (iVar5 != 0);
      }
      bVar1 = true;
      local_74 = local_74 + 1;
      local_88[5] = *(uint *)(iVar7 + 4);
      local_88[6] = *(uint *)(iVar7 + 0x14);
      local_88[7] = *(uint *)(iVar7 + 0x10);
      local_54 = *(undefined4 *)(iVar7 + 0x18);
LAB_001c08ac:
      local_90 = local_90 + 1;
      local_88 = local_88 + 3;
    } while (local_90 < *(byte *)(param_3 + 1));
    *(undefined4 *)(param_1 + 0xa7861c) = 1;
    if (bVar1) {
      local_5c = local_84;
      if (0 < DebugLevel) {
        printk("Start CMD Jump Address 0x%x\n",local_84);
      }
      local_58 = *(undefined4 *)(iVar2 + 0x120);
      local_50 = local_74;
      if (param_2 == 1) {
        local_60 = 4;
      }
      else {
        local_60 = 0;
      }
      local_60 = local_80 | 0x10 | local_60;
      iVar3 = MtCmdFwDecompressStart(param_1,&local_60);
      goto LAB_001c0940;
    }
  }
  if (param_2 == 1) {
    uVar4 = 4;
  }
  else {
    uVar4 = 0;
  }
  iVar3 = MtCmdFwStartReq(param_1,uVar4 | local_80,local_84);
LAB_001c0940:
  os_free_mem(*param_3);
  *param_3 = 0;
  *(undefined1 *)(param_3 + 1) = 0;
  if (iVar3 != 0) {
LAB_001c0814:
    iVar2 = DebugLevel;
    *(undefined4 *)(param_1 + 0xa7861c) = 0;
    if (0 < iVar2) {
      printk("%s: load fw fail\n","load_fw_v2_compressimg");
    }
  }
  return iVar3;
}

