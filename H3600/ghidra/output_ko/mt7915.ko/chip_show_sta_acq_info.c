// module: mt7915.ko
// function: chip_show_sta_acq_info @ 0x18d304
// size: 672 bytes
//

int chip_show_sta_acq_info(int param_1,uint *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_64;
  undefined4 local_58;
  int local_54;
  uint local_30;
  uint local_2c [2];
  
  local_64 = 0;
  local_54 = 0;
  do {
    param_2 = param_2 + 1;
    uVar4 = 0;
    iVar1 = (local_54 % 6) * 4;
    uVar5 = (local_54 % 9) * 0x20;
    do {
      while( true ) {
        uVar2 = 1 << (uVar4 & 0xff);
        local_30 = (*param_2 & uVar2) >> (uVar4 & 0xff);
        if (local_30 == 0) break;
LAB_0018d3ac:
        uVar4 = uVar4 + 1;
        uVar5 = uVar5 + 1;
        if (uVar4 == 0x20) goto LAB_0018d4f8;
      }
      local_2c[0] = local_30;
      iVar3 = wdev_search_by_wcid(param_1,uVar5 & 0xffff);
      if (iVar3 == 0) {
        local_58 = 0;
      }
      else {
        local_58 = HcGetWmmIdx(param_1);
      }
      if (0 < DebugLevel) {
        printk("\tSTA%d AC%d: ",uVar5,local_54 / 9);
      }
      hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01b0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01b8,&local_30);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820c01bc,local_2c);
      uVar7 = local_30 & 0xfff;
      uVar6 = local_2c[0] & 0xfff;
      if (0 < DebugLevel) {
        printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = 0x%03x",(local_30 << 4) >> 0x14,uVar7,uVar6
              );
      }
      if ((*(uint *)(param_3 + iVar1) & uVar2) >> (uVar4 & 0xff) == 1) {
        iVar3 = 2;
      }
      else {
        iVar3 = 0;
      }
      if ((uVar2 & *(uint *)(param_4 + iVar1)) >> (uVar4 & 0xff) == 1) {
        iVar3 = 1;
      }
      if ((0 < DebugLevel) && (printk(" ctrl = %s",(&DAT_0029c3c8)[iVar3]), 0 < DebugLevel)) {
        printk(" (wmmidx=%d)\n",local_58);
      }
      local_64 = local_64 + 1;
      if (param_5 == 0 || uVar6 == 0) goto LAB_0018d3ac;
      uVar4 = uVar4 + 1;
      ShowTXDInfo(param_1,uVar7);
      uVar5 = uVar5 + 1;
    } while (uVar4 != 0x20);
LAB_0018d4f8:
    local_54 = local_54 + 1;
    if (local_54 == 0x24) {
      return local_64;
    }
  } while( true );
}

