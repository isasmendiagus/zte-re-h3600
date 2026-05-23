// module: mt7915.ko
// function: MT_ATELogOnOff @ 0x281e24
// size: 860 bytes
//

undefined4 MT_ATELogOnOff(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined1 local_48;
  uint local_2c [2];
  
  iVar6 = param_2 + -1;
  switch(iVar6) {
  case 0:
    local_48 = 1;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5380,local_2c);
    uVar7 = 2;
    local_2c[0] = local_2c[0] & 0xbfffffff;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5380);
    break;
  case 1:
    uVar7 = 4;
    local_48 = 0;
    break;
  case 2:
    uVar7 = 8;
    local_48 = 1;
    break;
  default:
    if (DebugLevel < 2) {
      return 0xffffffff;
    }
    printk("%s log type %d not supported\n","MT_ATELogOnOff",param_2);
    goto LAB_00282080;
  case 4:
    uVar7 = 0x20;
    goto LAB_00281e6c;
  case 5:
    uVar7 = 0x40;
    goto LAB_00281e6c;
  case 6:
    uVar7 = 0x80;
    if (param_3 == 1) goto LAB_00281f4c;
    iVar4 = 0;
    goto LAB_00281e78;
  case 7:
    uVar7 = 0x100;
LAB_00281e6c:
    if (param_3 == 1) goto LAB_00281f4c;
    iVar4 = 0;
    goto LAB_00281e78;
  }
  iVar1 = iVar6 * 0x18;
  iVar5 = param_1 + 0xa39fd0 + iVar1 + 0x1880;
  iVar4 = iVar5 + 4;
  if (param_3 != 1) {
LAB_00281e78:
    if (param_3 == 0) {
      *(uint *)(param_1 + 0xa39ffc) = *(uint *)(param_1 + 0xa39ffc) & ~uVar7;
      cVar2 = *(char *)(param_1 + 0xa7cbdb);
      goto joined_r0x00281f68;
    }
    if (param_3 != 2) goto LAB_00282038;
    if (iVar4 == 0) {
      return 0;
    }
    iVar6 = MT_ATEDumpLog(param_1,iVar4,param_2);
    if (iVar6 == 0) {
      return 0;
    }
LAB_00282080:
    if (DebugLevel < 2) {
      return 0xffffffff;
    }
    printk("%s log type %d init logCB fail\n","MT_ATELogOnOff",param_2);
LAB_00282038:
    if (1 < DebugLevel) {
      printk("%s log ctrl %d not supported\n","MT_ATELogOnOff",param_3);
    }
    return 0xffffffff;
  }
  if (iVar4 != 0) {
    iVar3 = param_1 + 0xa39000 + iVar1;
    if (*(int *)(iVar3 + 0x2868) == 0) {
      __memzero(iVar4,0x18);
      iVar4 = os_alloc_mem(param_1,param_1 + 0xa39fd0 + iVar1 + 0x1898,param_4 * 0x2c);
      if (iVar4 != 0) {
        if (DebugLevel < 2) {
          return 0xffffffff;
        }
        printk("%s: Alcated memory fail! size %u\n","MT_ATEInitLogCB",param_4);
        goto LAB_00282080;
      }
      os_zero_mem(*(undefined4 *)(iVar3 + 0x2868),param_4 * 0x2c);
      *(int *)(iVar3 + 0x2860) = param_4;
      *(undefined4 *)(iVar5 + 4) = 0;
      if (2 < DebugLevel) {
        printk("%s-v4, init log cb size %u, log_cb->len:%u\n","MT_ATEInitLogCB",param_4);
      }
    }
    iVar6 = param_1 + 0xa39000 + iVar6 * 0x18;
    *(undefined1 *)(iVar6 + 0x2858) = local_48;
    *(undefined1 *)(iVar6 + 0x285a) = 0;
    *(undefined4 *)(iVar6 + 0x285c) = 0;
  }
LAB_00281f4c:
  *(uint *)(param_1 + 0xa39ffc) = uVar7 | *(uint *)(param_1 + 0xa39ffc);
  cVar2 = *(char *)(param_1 + 0xa7cbdb);
joined_r0x00281f68:
  if (cVar2 == '\0') {
    return 0;
  }
  *(undefined2 *)(param_1 + 0xa7cbd8) = 0;
  return 0;
}

