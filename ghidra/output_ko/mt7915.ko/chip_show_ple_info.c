// module: mt7915.ko
// function: chip_show_ple_info @ 0x18d5a4
// size: 1884 bytes
//

undefined4 chip_show_ple_info(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_r1;
  int extraout_r1_00;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint local_13c;
  undefined4 local_138;
  undefined4 local_134;
  uint local_130;
  uint local_12c;
  uint local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  uint local_bc [38];
  
  iVar10 = *(int *)(param_1 + 0x4328);
  memset(local_bc,0,0x94);
  local_124 = 0;
  local_120 = 0;
  local_11c = 0;
  local_118 = 0;
  local_114 = 0;
  local_110 = 0;
  local_10c = 0;
  local_108 = 0;
  local_104 = 0;
  local_100 = 0;
  local_fc = 0;
  local_f8 = 0;
  local_f4 = 0;
  local_f0 = 0;
  local_ec = 0;
  local_e8 = 0;
  local_e4 = 0;
  local_e0 = 0;
  local_dc = 0;
  local_d8 = 0;
  local_d4 = 0;
  local_d0 = 0;
  local_cc = 0;
  local_c8 = 0;
  local_c4 = 0;
  local_c0 = 0;
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = os_str_toul(param_2,0,0x10);
  }
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0014,&local_13c);
  chip_get_ple_acq_stat(iVar10,local_bc);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0230,&local_134);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c022c,&local_138);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0100,&local_124);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0104,&local_120);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0110,&local_11c);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0114,&local_118);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0150,&local_114);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0154,&local_110);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0120,&local_10c);
  hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c0124,&local_108);
  chip_get_dis_sta_map(iVar10,&local_e0);
  chip_get_sta_pause(iVar10,&local_104);
  if (((DebugLevel < 1) || (printk("PLE Configuration Info:\n"), DebugLevel < 1)) ||
     (printk("\tPacket Buffer Control(0x82060014): 0x%08x\n",local_13c), DebugLevel < 1)) {
LAB_0018d76c:
    if ((local_bc[0] & 0x1000000) != 0) goto LAB_0018d7f0;
LAB_0018d778:
    iVar7 = 0;
    iVar3 = DebugLevel;
    do {
      iVar2 = iVar7 / 9;
      iVar5 = iVar7 % 9;
      if ((iVar5 == 0) && (0 < iVar3)) {
        printk("\n\tNonempty AC%d Q of STA#: ",iVar2,iVar7 * 0x38e38e39);
        iVar3 = DebugLevel;
        iVar2 = extraout_r1_00;
      }
      iVar7 = iVar7 + 1;
      uVar6 = 0;
      do {
        if (((local_bc[iVar7] & 1 << (uVar6 & 0xff)) >> (uVar6 & 0xff) == 0) && (0 < iVar3)) {
          printk(&_LC102,uVar6 + iVar5 * 0x20);
          iVar3 = DebugLevel;
          iVar2 = extraout_r1;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 != 0x24);
    } while (iVar7 != 0x24);
    if (iVar3 < 1) goto LAB_0018d7f0;
    printk(&_LC12,iVar2);
  }
  else {
    if ((int)local_13c < 0) {
      uVar4 = 0x80;
    }
    else {
      uVar4 = 0x40;
    }
    printk("\t\tPage Size=%d(%d bytes per page)\n",local_13c >> 0x1f,uVar4);
    if (((DebugLevel < 1) ||
        (printk("\t\tPage Offset=%d(in unit of 2KB)\n",(local_13c << 6) >> 0x17), DebugLevel < 1))
       || ((printk("\t\tTotal Page=%d pages\n",local_13c & 0xfff), DebugLevel < 1 ||
           (printk("PLE Page Flow Control:\n"), DebugLevel < 1)))) goto LAB_0018d76c;
    printk("\tFree page counter(0x820c0100): 0x%08x\n",local_124);
    if (((DebugLevel < 1) ||
        (printk("\t\tThe toal page number of free=0x%03x\n",local_124 & 0xfff), DebugLevel < 1)) ||
       ((printk("\t\tThe free page numbers of free for all=0x%03x\n",(local_124 << 4) >> 0x14),
        DebugLevel < 1 ||
        (((printk("\tFree page head and tail(0x820c0104): 0x%08x\n",local_120), DebugLevel < 1 ||
          (printk("\t\tThe tail/head page of free page list=0x%03x/0x%03x\n",
                  (local_120 << 4) >> 0x14,local_120 & 0xfff), DebugLevel < 1)) ||
         (printk("\tReserved page counter of HIF group(0x820c0110): 0x%08x\n",local_11c),
         DebugLevel < 1)))))) goto LAB_0018d76c;
    printk("\tHIF group page status(0x820c0114): 0x%08x\n",local_118);
    if (((DebugLevel < 1) ||
        (printk("\t\tThe max/min quota pages of HIF group=0x%03x/0x%03x\n",(local_11c << 4) >> 0x14,
                local_11c & 0xfff), DebugLevel < 1)) ||
       ((printk("\t\tThe used/reserved pages of HIF group=0x%03x/0x%03x\n",(local_118 << 4) >> 0x14,
                local_118 & 0xfff), DebugLevel < 1 ||
        (printk("\tReserved page counter of HIF_TXCMD group(0x820c0118): 0x%08x\n",local_10c),
        DebugLevel < 1)))) goto LAB_0018d76c;
    printk("\tHIF_TXCMD group page status(0x820c011c): 0x%08x\n",local_108);
    if (((DebugLevel < 1) ||
        (printk("\t\tThe max/min quota pages of HIF_TXCMD group=0x%03x/0x%03x\n",
                (local_10c << 4) >> 0x14,local_10c & 0xfff), DebugLevel < 1)) ||
       ((printk("\t\tThe used/reserved pages of HIF_TXCMD group=0x%03x/0x%03x\n",
                (local_108 << 4) >> 0x14,local_108 & 0xfff), DebugLevel < 1 ||
        (printk("\tReserved page counter of CPU group(0x820c0150): 0x%08x\n",local_114),
        DebugLevel < 1)))) goto LAB_0018d76c;
    printk("\tCPU group page status(0x820c0154): 0x%08x\n",local_110);
    if ((DebugLevel < 1) ||
       (printk("\t\tThe max/min quota pages of CPU group=0x%03x/0x%03x\n",(local_114 << 4) >> 0x14,
               local_114 & 0xfff), DebugLevel < 1)) goto LAB_0018d76c;
    printk("\t\tThe used/reserved pages of CPU group=0x%03x/0x%03x\n",(local_110 << 4) >> 0x14,
           local_110 & 0xfff);
    if ((local_bc[0] & 0x1000000) == 0) goto LAB_0018d778;
  }
  if ((0 < DebugLevel) &&
     (printk("non-native/native txcmd queue empty = %d/%d\n",local_134,local_138), 0 < DebugLevel))
  {
    printk("Nonempty Q info:\n");
  }
LAB_0018d7f0:
  piVar8 = &DAT_0029c418;
  uVar6 = 0;
  while( true ) {
    uVar9 = (local_bc[0] & 1 << (uVar6 & 0xff)) >> (uVar6 & 0xff);
    if ((uVar9 == 0) && (local_130 = 0, local_12c = uVar9, local_128 = uVar9, *piVar8 != 0)) {
      if (DebugLevel < 1) {
        local_130 = 0x80000000;
      }
      else {
        local_130 = uVar9;
        printk("\t%s: ");
        local_130 = local_130 | 0x80000000;
      }
      iVar3 = piVar8[2];
      local_130 = piVar8[1] << 10 | iVar3 << 0x18 | local_130;
      if (iVar3 - 0x10U < 4) {
        hw_io_write32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c01b4,0);
      }
      else if (iVar3 - 0x14U < 4) {
        hw_io_write32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c01b4,0x80000000);
      }
      hw_io_write32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c01b0,local_130);
      hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c01b8,&local_12c);
      hw_io_read32(*(undefined4 *)(iVar10 + 0xa797a0),0x820c01bc,&local_128);
      uVar11 = local_12c & 0xfff;
      uVar9 = local_128 & 0xfff;
      if (0 < DebugLevel) {
        printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = 0x%03x\n",(local_12c << 4) >> 0x14,uVar11,
               uVar9);
      }
      if (iVar1 != 0 && uVar9 != 0) {
        ShowTXDInfo(iVar10,uVar11);
      }
    }
    if (uVar6 == 0x1f) break;
    piVar8 = piVar8 + 3;
    uVar6 = uVar6 + 1;
  }
  chip_show_sta_acq_info(iVar10,local_bc,&local_104,&local_e0,iVar1);
  chip_show_txcmdq_info(iVar10,local_138);
  return 1;
}

