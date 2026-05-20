// module: mt7915.ko
// function: vow_display_info_periodic @ 0x48f54
// size: 4668 bytes
//

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void vow_display_info_periodic(int param_1)

{
  uint uVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  undefined4 uVar17;
  int iVar18;
  bool bVar19;
  int local_154;
  int local_150;
  uint local_14c;
  int local_148;
  int local_144;
  uint local_140;
  uint local_13c;
  uint local_138 [4];
  uint local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  int local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
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
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  uint auStack_ac [2];
  undefined1 auStack_a4 [4];
  undefined1 auStack_a0 [4];
  undefined1 auStack_9c [4];
  undefined1 auStack_98 [4];
  undefined1 auStack_94 [4];
  undefined1 auStack_90 [4];
  undefined1 auStack_8c [4];
  undefined1 auStack_88 [4];
  undefined1 auStack_84 [4];
  undefined1 auStack_80 [4];
  undefined1 auStack_7c [4];
  undefined1 auStack_78 [4];
  undefined1 auStack_74 [4];
  undefined1 auStack_70 [4];
  undefined1 auStack_6c [4];
  undefined1 auStack_68 [4];
  undefined1 auStack_64 [4];
  undefined1 auStack_60 [4];
  undefined1 auStack_5c [4];
  undefined1 auStack_58 [4];
  undefined1 auStack_54 [4];
  undefined1 auStack_50 [4];
  undefined1 auStack_4c [4];
  undefined1 auStack_48 [4];
  undefined1 auStack_44 [4];
  undefined1 auStack_40 [4];
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  iVar5 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0xa7a31b) == '\x01') {
    memset(auStack_ac,0,0x84);
    uVar13 = 0;
    vow_idx = vow_idx + 1;
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
    local_bc = 0;
    local_b8 = 0;
    local_b4 = 0;
    local_b0 = 0;
    do {
      uVar9 = uVar13 << 8;
      if (*(char *)(param_1 + 0xa797a4) == '\x03') {
        uVar15 = 0;
        iVar10 = 0;
        iVar12 = 0;
        do {
          uVar16 = uVar15 & 0xffff;
          uVar15 = uVar15 + 1;
          local_154 = (**(code **)(iVar5 + 0x80))(param_1,uVar13,uVar16);
          iVar12 = iVar12 + local_154;
          local_150 = (**(code **)(iVar5 + 0x80))(param_1,uVar13,uVar16,0);
          iVar10 = iVar10 + local_150;
        } while (uVar15 != 4);
      }
      else {
        iVar14 = 0;
        iVar10 = 0;
        iVar12 = 0;
        do {
          iVar18 = (uVar9 | 0x3004c) + iVar14 * 8;
          iVar14 = iVar14 + 1;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar18,&local_154);
          iVar12 = iVar12 + local_154;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar18 + 4,&local_150);
          iVar10 = iVar10 + local_150;
        } while (iVar14 != 4);
      }
      iVar14 = uVar13 * 4;
      cVar2 = *(char *)(param_1 + 0xa797a4);
      iVar18 = *(int *)(vow_last_tx_time + iVar14);
      *(int *)(vow_last_tx_time + iVar14) = iVar12;
      iVar12 = iVar12 - iVar18;
      iVar18 = iVar10 - *(int *)(vow_last_rx_time + iVar14);
      *(int *)(vow_last_rx_time + iVar14) = iVar10;
      vow_sum_tx_rx_time = iVar18 + iVar12 + vow_sum_tx_rx_time;
      vow_avg_sum_time = iVar18 + iVar12 + vow_avg_sum_time;
      *(int *)(vow_tx_time + iVar14) = iVar12 + *(int *)(vow_tx_time + iVar14);
      *(int *)(vow_rx_time + iVar14) = iVar18 + *(int *)(vow_rx_time + iVar14);
      if (cVar2 == '\x03') {
        local_140 = (**(code **)(iVar5 + 0x84))(param_1,uVar13);
        local_140 = local_140 & 0xffff;
        uVar9 = (**(code **)(iVar5 + 0x88))(param_1,uVar13);
        uVar15 = (uVar9 << 0x16) >> 0x1c;
      }
      else {
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar9 | 0x30000,&local_140);
        local_140 = local_140 & 0xffff;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar9 | 0x30018,&local_13c);
        uVar15 = (local_13c << 0x17) >> 0x1d;
        uVar9 = local_13c;
      }
      if (*(uint *)(param_1 + 0xa7a324) < uVar13) {
LAB_00049378:
        sVar3 = vow_idx;
        if (vow_idx == *(short *)(param_1 + 0xa7a320)) {
          if (0 < DebugLevel) {
            uVar17 = *(undefined4 *)(vow_tx_time + iVar14);
            uVar11 = *(undefined4 *)(vow_rx_time + iVar14);
            uVar7 = __aeabi_uidiv(uVar17,vow_idx);
            uVar8 = __aeabi_uidiv(uVar11,sVar3);
            printk("AVG sta%d: tx -> %u(%u), rx -> %u(%u)\n",uVar13,uVar7,uVar17,uVar8,uVar11);
          }
LAB_000493a4:
          vow_avg_sum_time = 0;
          *(undefined4 *)(vow_tx_time + iVar14) = 0;
          *(undefined4 *)(vow_rx_time + iVar14) = 0;
        }
      }
      else if (DebugLevel < 1) {
        if (*(short *)(param_1 + 0xa7a320) == vow_idx) goto LAB_000493a4;
      }
      else {
        printk("sta%d: tx -> %u, rx -> %u, vow_idx %d\n",uVar13,iVar12,iVar18,vow_idx);
        if (0 < DebugLevel) {
          printk("sta%d: addr %x:%x, Mode %d, MCS %d, vow_idx %d\n",uVar13,local_140 & 0xff,
                 local_140 >> 8,uVar15,uVar9 & 0x3f,vow_idx);
          goto LAB_00049378;
        }
        if (*(short *)(param_1 + 0xa7a320) == vow_idx) goto LAB_000493a4;
      }
      uVar13 = uVar13 + 1 & 0xff;
      uVar9 = (uint)*(byte *)(param_1 + 0xa7a31c);
    } while (uVar13 <= uVar9);
    if (0 < DebugLevel) {
      printk("Total Airtime: %u\n",vow_sum_tx_rx_time);
      uVar9 = (uint)*(byte *)(param_1 + 0xa7a31c);
    }
    vow_sum_tx_rx_time = 0;
    if (uVar9 != 0) {
      uVar13 = 1;
      do {
        iVar12 = 0;
        iVar14 = 0;
        iVar10 = 0;
        do {
          if (*(char *)(param_1 + 0xa797a4) == '\x03') {
            local_14c = (**(code **)(iVar5 + 0x8c))(param_1,uVar13,iVar10);
          }
          else {
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar10 * 4 + (uVar13 << 8 | 0x30040),
                          &local_14c);
          }
          bVar19 = iVar10 != 1;
          local_138[iVar10] = local_14c & 0xffff;
          iVar12 = iVar12 + (local_14c & 0xffff);
          iVar14 = iVar14 + (local_14c >> 0x10);
          local_138[iVar10 + 2] = local_14c >> 0x10;
          iVar10 = 1;
        } while (bVar19);
        if ((uVar13 <= *(uint *)(param_1 + 0xa7a324)) && (0 < DebugLevel)) {
          printk("sta%d: tx cnt -> %u/%u, tx fail -> %u/%u, vow_idx %d\n",uVar13,local_138[0],
                 local_138[1],local_138[2],local_138[3],vow_idx);
        }
        sVar4 = vow_idx;
        iVar10 = uVar13 * 4;
        sVar3 = *(short *)(param_1 + 0xa7a320);
        iVar12 = iVar12 + *(int *)(vow_tx_ok + iVar10);
        *(int *)(vow_tx_ok + iVar10) = iVar12;
        iVar14 = iVar14 + *(int *)(vow_tx_fail + iVar10);
        *(int *)(vow_tx_fail + iVar10) = iVar14;
        if (sVar4 == sVar3) {
          if (0 < DebugLevel) {
            uVar7 = __aeabi_uidiv(iVar12,sVar4);
            uVar8 = __aeabi_uidiv(iVar14,sVar4);
            printk("AVG sta%d: tx cnt -> %u(%u), tx fail -> %u(%u)\n",uVar13,uVar7,iVar12,uVar8,
                   iVar14);
          }
          *(undefined4 *)(vow_tx_ok + iVar10) = 0;
          *(undefined4 *)(vow_tx_fail + iVar10) = 0;
        }
        uVar13 = uVar13 + 1 & 0xff;
      } while (uVar13 <= *(byte *)(param_1 + 0xa7a31c));
    }
    uVar13 = 0;
    do {
      iVar10 = uVar13 * 4;
      iVar14 = iVar10 + 0x29000;
      bVar19 = *(char *)(param_1 + 0xa797a4) == '\x03';
      iVar12 = iVar10 + 0x29110;
      if (bVar19) {
        iVar14 = iVar10 + 0x31000;
      }
      if (bVar19) {
        iVar12 = iVar14 + 0x110;
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,&local_120);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar14 + 0x130,&local_114);
      if (0 < DebugLevel) {
        printk("BSS%d: tx byte -> %u, rx byte -> %u\n",uVar13,local_120,local_114);
      }
      sVar3 = vow_idx;
      iVar14 = *(int *)(vow_tx_bss_byte + iVar10) + local_120;
      bVar19 = vow_idx == *(short *)(param_1 + 0xa7a320);
      *(int *)(vow_tx_bss_byte + iVar10) = iVar14;
      iVar12 = *(int *)(vow_rx_bss_byte + iVar10) + local_114;
      *(int *)(vow_rx_bss_byte + iVar10) = iVar12;
      if (bVar19) {
        if (0 < DebugLevel) {
          uVar7 = __aeabi_uidiv(iVar14,sVar3);
          uVar8 = __aeabi_uidiv(iVar12,sVar3);
          printk("AVG bss%d: tx -> %u(%u), rx -> %u(%u)\n",uVar13,uVar7,iVar14,uVar8,iVar12);
        }
        *(undefined4 *)(vow_tx_bss_byte + iVar10) = 0;
        *(undefined4 *)(vow_rx_bss_byte + iVar10) = 0;
      }
      uVar13 = uVar13 + 1 & 0xff;
    } while (uVar13 <= *(byte *)(param_1 + 0xa7a31d));
    uVar13 = 0;
    do {
      iVar10 = uVar13 * 4;
      if (*(char *)(param_1 + 0xa797a4) == '\x03') {
        iVar12 = iVar10 + 0x31000;
      }
      else {
        iVar12 = iVar10 + 0x29000;
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12 + 0x240,&local_120);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12 + 0x2c0,&local_114);
      if ((uVar13 < *(uint *)(param_1 + 0xa7a328)) && (0 < DebugLevel)) {
        printk("MBSS%d: tx byte -> %u, rx byte -> %u\n",uVar13,local_120,local_114);
      }
      sVar3 = vow_idx;
      bVar19 = vow_idx == *(short *)(param_1 + 0xa7a320);
      iVar14 = *(int *)(vow_tx_mbss_byte + iVar10) + local_120;
      *(int *)(vow_tx_mbss_byte + iVar10) = iVar14;
      iVar12 = *(int *)(vow_rx_mbss_byte + iVar10) + local_114;
      *(int *)(vow_rx_mbss_byte + iVar10) = iVar12;
      if (bVar19) {
        if (0 < DebugLevel) {
          uVar7 = __aeabi_uidiv(iVar14,sVar3);
          uVar8 = __aeabi_uidiv(iVar12,sVar3);
          printk("AVG mbss%d: tx -> %u(%u), rx -> %u(%u)\n",uVar13,uVar7,iVar14,uVar8,iVar12);
        }
        *(undefined4 *)(vow_tx_mbss_byte + iVar10) = 0;
        *(undefined4 *)(vow_rx_mbss_byte + iVar10) = 0;
      }
      uVar13 = uVar13 + 1 & 0xff;
    } while (uVar13 <= *(byte *)(param_1 + 0xa7a31e));
    if (*(char *)(param_1 + 0xa797a4) == '\x03') {
      local_144 = (**(code **)(iVar5 + 0x90))(param_1);
    }
    else {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),Set_PreAuth_Proc,&local_144);
    }
    if ((vow_last_free_cnt != 0) &&
       (vow_interval = (local_144 - vow_last_free_cnt) + vow_interval, 0 < DebugLevel)) {
      printk("free count %d\n");
    }
    uVar7 = 0x2d038;
    if (*(char *)(param_1 + 0xa797a4) != '\x03') {
      uVar7 = 0x820fd040;
    }
    vow_last_free_cnt = local_144;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar7,&local_148);
    vow_ampdu_cnt = local_148 + vow_ampdu_cnt;
    if (0 < DebugLevel) {
      printk("AMPDU[Band0] count %d\n");
    }
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd240,&local_148);
      vow_ampdu_cnt = local_148 + vow_ampdu_cnt;
      if (0 < DebugLevel) {
        printk("AMPDU[Band1] count %d\n");
      }
    }
    iVar10 = vow_ampdu_cnt;
    if (vow_idx == *(short *)(param_1 + 0xa7a320)) {
      if (0 < DebugLevel) {
        uVar7 = __aeabi_uidiv(vow_ampdu_cnt);
        printk("total ampdu cnt -> %u, avg ampdu cnt --> %d\n",iVar10,uVar7);
        iVar10 = vow_interval;
        if (0 < DebugLevel) {
          uVar7 = __aeabi_uidiv(vow_interval,*(short *)(param_1 + 0xa7a320));
          printk("total interval -> %u, avg interval --> %d\n",iVar10,uVar7);
        }
      }
      vow_interval = 0;
      vow_idx = 0;
      vow_ampdu_cnt = 0;
    }
    if (*(char *)(param_1 + 0xa797a4) == '\x03') {
      (**(code **)(iVar5 + 0x7c))(param_1,&local_114);
      if (-1 < DebugLevel) {
        printk("nonwifi %u/%u, obss %u/%u.\n",local_114,local_110,local_10c,local_108);
      }
    }
    else {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x215b4,local_138 + 4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x215b8,local_138 + 5);
      if (-1 < DebugLevel) {
        printk("nonwifi: %u, obss: %u.\n",local_128,local_124);
      }
    }
    if (*(char *)(param_1 + 0xa797a4) == '\x03') {
      (**(code **)(iVar5 + 0x6c))(param_1,auStack_ac);
      (**(code **)(iVar5 + 0x74))(param_1,&local_cc);
      (**(code **)(iVar5 + 0x78))(param_1,&local_ec);
      uVar13 = (**(code **)(iVar5 + 100))(param_1,auStack_ac,&local_ec,&local_cc,0);
      (**(code **)(iVar5 + 0x70))(param_1,&local_120);
      (**(code **)(iVar5 + 0x68))(param_1,local_120);
    }
    else {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820600b0,auStack_ac);
      iVar5 = 1;
      uVar13 = 0;
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060300,auStack_ac + 1);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060304,auStack_a4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060308,auStack_a0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206030c,auStack_9c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060310,auStack_98);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060314,auStack_94);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060318,auStack_90);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206031c,auStack_8c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060320,auStack_88);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060324,auStack_84);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060328,auStack_80);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206032c,auStack_7c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060330,auStack_78);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060334,auStack_74);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060338,auStack_70);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206033c,auStack_6c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060600,auStack_68);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060604,auStack_64);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060608,auStack_60);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206060c,auStack_5c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060610,auStack_58);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060614,auStack_54);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060618,auStack_50);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206061c,auStack_4c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060620,auStack_48);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060624,auStack_44);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060628,auStack_40);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206062c,auStack_3c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060630,auStack_38);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060634,auStack_34);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060638,auStack_30);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206063c,auStack_2c);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060100,&local_104);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060104,&local_100);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060110,&local_fc);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060114,&local_f8);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060150,&local_f4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060154,&local_f0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060260,&local_cc);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060264,&local_c8);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060268,&local_c4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206026c,&local_c0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060270,&local_bc);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060274,&local_b8);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060278,&local_b4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206027c,&local_b0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060360,&local_ec);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060364,&local_e8);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060368,&local_e4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206036c,&local_e0);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060660,&local_dc);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060664,&local_d8);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060668,&local_d4);
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8206066c,&local_d0);
      do {
        uVar15 = iVar5 - 1;
        uVar9 = 0;
        uVar16 = ((int)uVar15 >> 4) * 0x80 + (uVar15 & 3) * 0x20;
        do {
          local_120 = 0;
          local_11c = 0;
          local_118 = 0;
          iVar10 = wdev_search_by_wcid(param_1,uVar16 & 0xffff);
          uVar6 = uVar9 & 0xff;
          uVar1 = uVar9 & 0xff;
          uVar9 = uVar9 + 1;
          if ((auStack_ac[iVar5] & 1 << uVar6) >> uVar1 == 0) {
            uVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
            if (uVar6 <= uVar16) break;
            uVar13 = uVar13 + 1;
            uVar6 = uVar15;
            if (0x7f < uVar16) {
              uVar6 = iVar5 - 0x11;
            }
            if (iVar10 != 0) {
              HcGetWmmIdx(param_1,iVar10);
            }
            if (0 < DebugLevel) {
              printk("STA%d AC%d: ",uVar16,(int)uVar6 >> 2);
            }
            local_120 = uVar16 | local_120 | 0x80008000 | ((int)uVar6 >> 2) << 8;
            hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820601b0);
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820601b8,&local_11c);
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820601bc,&local_118);
            if ((uVar13 < 0x15) && (0 < DebugLevel)) {
              printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = %x\n",(local_11c << 4) >> 0x14,
                     local_11c & 0xfff,local_118 & 0xfff);
            }
          }
          uVar16 = uVar16 + 1;
        } while (uVar9 != 0x20);
        iVar5 = iVar5 + 1;
      } while (iVar5 != 0x21);
    }
    if (0 < DebugLevel) {
      printk("**************[nonempty STAs : %d]************************\n",uVar13);
    }
  }
  return;
}

