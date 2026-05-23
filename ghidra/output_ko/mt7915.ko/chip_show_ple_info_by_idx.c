// module: mt7915.ko
// function: chip_show_ple_info_by_idx @ 0x18c0a0
// size: 664 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 chip_show_ple_info_by_idx(int param_1,int param_2)

{
  uint uVar1;
  uint *__s;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 local_dc;
  uint local_c4;
  uint local_c0 [39];
  
  iVar3 = *(int *)(param_1 + 0x4328);
  __s = local_c0 + 0xd;
  memset(__s,0,100);
  local_c0[1] = 0;
  local_c0[2] = 0;
  local_dc = 0;
  local_c0[3] = 0;
  local_c0[4] = 0;
  local_c0[5] = 0;
  local_c0[6] = 0;
  local_c0[7] = 0;
  local_c0[8] = 0;
  local_c0[9] = 0;
  local_c0[10] = 0;
  local_c0[0xb] = 0;
  local_c0[0xc] = 0;
  chip_get_ple_acq_stat(iVar3,__s);
  chip_get_dis_sta_map(iVar3,local_c0 + 7);
  chip_get_sta_pause(iVar3,local_c0 + 1);
  iVar4 = 0;
  do {
    iVar7 = iVar4 + 1;
    uVar5 = 0;
    iVar8 = iVar4 % 6;
    iVar6 = iVar8 * 0x20;
    do {
      uVar1 = 1 << (uVar5 & 0xff);
      local_c4 = (__s[iVar7] & uVar1) >> (uVar5 & 0xff);
      if ((local_c4 == 0) && (param_2 == iVar6)) {
        local_c0[0] = local_c4;
        iVar2 = wdev_search_by_wcid(iVar3,param_2);
        if (iVar2 != 0) {
          local_dc = HcGetWmmIdx(iVar3);
        }
        if (0 < DebugLevel) {
          printk("\tSTA%d AC%d: ",param_2,iVar4 / 6);
        }
        hw_io_write32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c01b0);
        hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c01b8,&local_c4);
        hw_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820c01bc,local_c0);
        if (0 < DebugLevel) {
          printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = 0x%03x",(local_c4 << 4) >> 0x14,
                 local_c4 & 0xfff,local_c0[0] & 0xfff);
        }
        if ((local_c0[iVar8 + 1] & uVar1) >> (uVar5 & 0xff) == 1) {
          iVar2 = 2;
        }
        else {
          iVar2 = 0;
        }
        if ((uVar1 & local_c0[iVar8 + 7]) >> (uVar5 & 0xff) == 1) {
          iVar2 = 1;
        }
        if ((0 < DebugLevel) && (printk(" ctrl = %s",(&DAT_0029c3c8)[iVar2]), 0 < DebugLevel)) {
          printk(" (wmmidx=%d)\n",local_dc);
        }
      }
      uVar5 = uVar5 + 1;
      iVar6 = iVar6 + 1;
    } while (uVar5 != 0x20);
    iVar4 = iVar7;
  } while (iVar7 != 0x18);
  return 1;
}

