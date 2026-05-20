// module: mt7915.ko
// function: hqa_icap_ctrl @ 0x249c54
// size: 1052 bytes
//

undefined4 hqa_icap_ctrl(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 local_94;
  int local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  undefined4 local_7c;
  int local_78;
  uint *local_74;
  byte local_6e;
  byte local_6d;
  byte local_6c;
  byte local_6b;
  byte local_6a;
  byte local_69;
  undefined1 auStack_68 [4];
  undefined1 auStack_64 [4];
  undefined1 auStack_60 [4];
  undefined1 auStack_5c [4];
  undefined1 auStack_58 [4];
  undefined1 auStack_54 [4];
  undefined1 auStack_50 [4];
  uint local_4c;
  uint local_48;
  undefined1 auStack_44 [4];
  undefined1 auStack_40 [12];
  undefined1 auStack_34 [16];
  undefined1 auStack_24 [16];
  
  local_90 = param_2 + 0xc;
  local_94 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = (uint *)0x0;
  FUN_002474f4(1,4,&local_90,&local_84);
  if (local_84 == 2) {
    iVar2 = mt_serv_get_icap_status(param_1,&local_94);
    if (iVar2 == 0) {
      FUN_00246b90(param_2,2,local_94);
      return 0;
    }
    printk("%s : mt_serv_get_icap_status is failed!!\n","hqa_icap_ctrl");
    goto LAB_0024a028;
  }
  if (local_84 != 3) {
    if (local_84 == 1) {
      sys_ad_zero_mem(auStack_68,0x50);
      FUN_002474f4(1,4,&local_90,auStack_68);
      FUN_002474f4(1,4,&local_90,auStack_64);
      FUN_002474f4(1,4,&local_90,auStack_60);
      FUN_002474f4(1,4,&local_90,auStack_5c);
      FUN_002474f4(1,4,&local_90,auStack_58);
      FUN_002474f4(1,4,&local_90,auStack_54);
      FUN_002474f4(1,4,&local_90,auStack_40);
      FUN_002474f4(1,4,&local_90,auStack_50);
      FUN_002474f4(0,6,&local_90,&local_6e);
      FUN_002474f4(1,4,&local_90,auStack_44);
      FUN_002474f4(1,4,&local_90,auStack_34);
      FUN_002474f4(1,4,&local_90,auStack_24);
      local_4c = local_6e | local_4c | (uint)local_6d << 8 | (uint)local_6c << 0x10 |
                 (uint)local_6b << 0x18;
      local_48 = local_48 | 0x10000 | (uint)local_6a | (uint)local_69 << 8;
      iVar2 = mt_serv_set_icap_start(param_1,auStack_68);
      if (iVar2 != 0) {
        printk("%s : mt_serv_set_icap_start is failed!!\n","hqa_icap_ctrl");
        goto LAB_0024a028;
      }
    }
    iVar2 = 2;
LAB_00249cc4:
    uVar6 = 0;
    goto LAB_00249cc8;
  }
  FUN_002474f4(1,4,&local_90,&local_8c);
  FUN_002474f4(1,4,&local_90,&local_88);
  iVar2 = sys_ad_alloc_mem(&local_74,4);
  if (iVar2 == 0) {
    sys_ad_zero_mem(local_74,4);
    iVar2 = mt_serv_get_icap_max_data_len(param_1,&local_7c);
    if (iVar2 == 0) {
      iVar2 = sys_ad_alloc_mem(&local_78,local_7c);
      if (iVar2 != 0) goto LAB_0024a034;
      sys_ad_zero_mem(local_78,local_7c);
      iVar2 = mt_serv_get_icap_data(param_1,local_74,local_78,local_8c,local_88);
      if (iVar2 == 0) {
        local_80 = local_84 << 0x18 | (local_84 >> 8 & 0xff) << 0x10 |
                   (local_84 >> 0x10 & 0xff) << 8 | local_84 >> 0x18;
        sys_ad_move_mem((void *)(param_2 + 0xe),&local_80,4);
        local_80 = local_8c << 0x18 | (local_8c >> 8 & 0xff) << 0x10 |
                   (local_8c >> 0x10 & 0xff) << 8 | local_8c >> 0x18;
        sys_ad_move_mem((void *)(param_2 + 0x12),&local_80,4);
        local_80 = local_88 << 0x18 | (local_88 >> 8 & 0xff) << 0x10 |
                   (local_88 >> 0x10 & 0xff) << 8 | local_88 >> 0x18;
        sys_ad_move_mem((void *)(param_2 + 0x16),&local_80,4);
        uVar3 = *local_74;
        local_80 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                   uVar3 >> 0x18;
        sys_ad_move_mem((void *)(param_2 + 0x1a),&local_80,4);
        if (*local_74 == 0) {
          iVar2 = 0x12;
        }
        else {
          iVar2 = 0x12;
          uVar3 = 0;
          do {
            iVar1 = iVar2 + 0xc;
            iVar4 = local_78 + iVar2;
            iVar2 = iVar2 + 4;
            uVar3 = uVar3 + 1;
            uVar5 = *(uint *)(iVar4 + -0x12);
            local_80 = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                       uVar5 >> 0x18;
            sys_ad_move_mem((void *)(param_2 + iVar1),&local_80,4);
          } while (uVar3 < *local_74);
        }
        goto LAB_00249cc4;
      }
      printk("%s : mt_serv_get_icap_data is not supported!!\n","hqa_icap_ctrl");
    }
    else {
      printk("%s : mt_serv_get_icap_max_data_len is failed!!\n","hqa_icap_ctrl");
    }
  }
  else {
LAB_0024a034:
    printk("%s : Not enough memory for dynamic allocating!!\n","hqa_icap_ctrl");
  }
LAB_0024a028:
  iVar2 = 2;
  uVar6 = 0x105;
LAB_00249cc8:
  FUN_00246b90(param_2,iVar2,uVar6);
  if (local_74 != (uint *)0x0) {
    sys_ad_free_mem();
  }
  if (local_78 != 0) {
    sys_ad_free_mem(local_78);
  }
  return uVar6;
}

