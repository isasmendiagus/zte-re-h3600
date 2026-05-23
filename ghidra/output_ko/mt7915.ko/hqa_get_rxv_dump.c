// module: mt7915.ko
// function: hqa_get_rxv_dump @ 0x249424
// size: 964 bytes
//

int hqa_get_rxv_dump(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  void *pvVar5;
  uint uVar6;
  int iVar7;
  void *__dest;
  int local_50;
  ushort local_46;
  int local_44;
  uint local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  uint *local_30;
  byte local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  
  local_44 = param_2 + 0xc;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = (uint *)0x0;
  local_46 = 0;
  FUN_002474f4(1,4,&local_44,&local_40);
  FUN_002474f4(1,4,&local_44,&local_3c);
  if (local_3c == 0) {
    FUN_002474f4(1,4,&local_44,&local_38);
  }
  else if (2 < local_3c) {
    printk("%s: invalid action type.\n","hqa_get_rxv_dump");
LAB_002494a8:
    FUN_00246b90(param_2,2,0);
    return 0x105;
  }
  if (local_3c < 2) {
    iVar7 = mt_serv_rxv_dump_action(param_1,local_3c,local_38);
    if (iVar7 != 0) {
      printk("%s: rxv dump action fail for action(%d), type_mask(%d).\n","hqa_get_rxv_dump",local_3c
             ,local_38);
      FUN_00246b90(param_2,2,iVar7);
      return 0x100;
    }
  }
  else if (local_3c == 2) {
    local_34 = local_40 << 0x18 | (local_40 >> 8 & 0xff) << 0x10 | (local_40 >> 0x10 & 0xff) << 8 |
               local_40 >> 0x18;
    sys_ad_move_mem((void *)(param_2 + 0xe),&local_34,4);
    iVar7 = mt_serv_get_rxv_dump_ring_attr(param_1,&local_2c);
    if (iVar7 != 0) {
      printk("%s: rxv dump ring attr fail.\n","hqa_get_rxv_dump");
      FUN_00246b90(param_2,2,iVar7);
      return 0x100;
    }
    uVar4 = 0;
    local_50 = 0;
    do {
      uVar1 = uVar4 & 0xff;
      uVar6 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      if ((local_2c >> uVar6 & 1) != 0) {
        mt_serv_get_rxv_content_len(param_1,uVar1,1,&local_46);
        local_50 = local_50 + (uint)local_46;
      }
    } while (uVar4 != 4);
    iVar7 = sys_ad_alloc_mem(&local_30,local_50);
    if (iVar7 != 0) {
      printk("%s: memory allocation fail for rxv content.\n","hqa_get_rxv_dump");
      FUN_00246b90(param_2,2,iVar7);
      return iVar7;
    }
    uVar4 = (uint)local_2b - (uint)local_2a;
    __dest = (void *)(param_2 + 0x1a);
    iVar2 = (int)(char)uVar4;
    if (iVar2 < (int)(uint)local_2b) {
      iVar7 = 0xc;
      uVar6 = 0;
      uVar1 = 0;
      do {
        uVar4 = uVar4 & 0xff;
        uVar3 = uVar4;
        if (iVar2 < 0) {
          uVar3 = uVar4 + local_29 & 0xff;
        }
        iVar2 = mt_serv_get_rxv_dump_content(param_1,uVar3,local_30,&local_46);
        if (iVar2 != 0) {
          printk("%s: query rxv content fail.\n","hqa_get_rxv_dump");
          sys_ad_free_mem(local_30);
          FUN_00246b90(param_2,2,iVar2);
          return iVar2;
        }
        if (1000 < uVar6) {
          printk("%s: rxv content length is larger than max buffer size.\n","hqa_get_rxv_dump");
          sys_ad_free_mem(local_30);
          goto LAB_002494a8;
        }
        if (local_46 >> 2 != 0) {
          pvVar5 = (void *)((int)__dest + ((ushort)((local_46 >> 2) - 1) + 1) * 4);
          do {
            uVar3 = *local_30;
            local_34 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                       uVar3 >> 0x18;
            sys_ad_move_mem(__dest,&local_34,4);
            __dest = (void *)((int)__dest + 4);
            local_30 = local_30 + 1;
          } while (__dest != pvVar5);
        }
        uVar6 = uVar6 + local_46;
        iVar7 = iVar7 + (uint)local_46;
        sys_ad_zero_mem(local_30,local_50);
        uVar4 = uVar4 + 1;
        uVar1 = uVar1 + 1;
        iVar2 = (int)(char)uVar4;
      } while (iVar2 < (int)(uint)local_2b);
      uVar4 = uVar6 * 0x1000000 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
      sys_ad_free_mem(local_30);
      iVar7 = iVar7 + 2;
      local_34 = uVar1 * 0x1000000 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                 uVar1 >> 0x18;
    }
    else {
      sys_ad_free_mem(local_30);
      iVar7 = 0xe;
      uVar4 = 0;
      local_34 = 0;
    }
    local_30 = (uint *)0x0;
    sys_ad_move_mem((void *)(param_2 + 0x12),&local_34,4);
    local_34 = uVar4;
    sys_ad_move_mem((void *)(param_2 + 0x16),&local_34,4);
    mt_serv_rxv_dump_action(param_1,3,local_38);
    goto LAB_002494f0;
  }
  iVar7 = 2;
LAB_002494f0:
  FUN_00246b90(param_2,iVar7,0);
  return 0;
}

