// module: mt7915.ko
// function: chip_show_dmasch_info @ 0x18a0d4
// size: 2448 bytes
//

undefined4 chip_show_dmasch_info(int param_1)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  uint local_a4;
  int local_a0;
  int local_9c;
  uint local_94;
  uint local_90;
  uint local_6c;
  uint local_68 [17];
  
  iVar4 = *(int *)(param_1 + 0x4328);
  uVar6 = 0;
  uVar13 = 0xf;
  uVar8 = 0;
  memset(local_68,0,0x40);
  iVar14 = 0x7c0260d0;
  while( true ) {
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),iVar14,&local_6c);
    uVar5 = local_6c & uVar13;
    uVar13 = 0xf;
    uVar5 = uVar5 >> (uVar8 & 0xff);
    uVar8 = uVar8 + 4;
    uVar7 = uVar6 & 0xff;
    uVar6 = uVar6 + 1;
    local_68[uVar5] = local_68[uVar5] | 1 << uVar7;
    if (uVar6 == 0x20) break;
    if ((uVar6 & 7) == 0) {
      iVar14 = iVar14 + 4;
      uVar8 = 0;
    }
    else {
      uVar13 = 0xf << (uVar8 & 0xff);
    }
  }
  if (0 < DebugLevel) {
    printk("Dma scheduler info:\n");
  }
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x7c026018,&local_6c);
  uVar13 = local_6c;
  uVar8 = (local_6c << 0xf) >> 0x1f;
  if (((((0 < DebugLevel) &&
        (printk("DMASHDL Ctrl Signal(0x5000A018): 0x%08x\n",local_6c), 0 < DebugLevel)) &&
       (printk("\twacpu mode en(BIT0) = %d\n",uVar13 & 1), 0 < DebugLevel)) &&
      ((printk("\thif_ask_sub_ena(BIT16) = %d\n",uVar8), 0 < DebugLevel &&
       (printk("\tple_sub_ena(BIT17) = %d\n",(uVar13 << 0xe) >> 0x1f), 0 < DebugLevel)))) &&
     ((printk("\tple_add_int_refill_ena(BIT29) = %d\n",(uVar13 << 2) >> 0x1f), 0 < DebugLevel &&
      (printk("\tpdma_add_int_refill_ena(BIT30) = %d\n",(uVar13 << 1) >> 0x1f), 0 < DebugLevel)))) {
    printk("\tpktin_int_refill(BIT31)_ena = %d\n",uVar13 >> 0x1f);
  }
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x7c02601c,&local_6c);
  uVar13 = local_6c;
  if ((0 < DebugLevel) &&
     (printk("DMASHDL Packet_max_size(0x5000A01c): 0x%08x\n",local_6c), 0 < DebugLevel)) {
    printk("PLE/PSE packet max size=0x%03x/0x%03x\n",uVar13 & 0xfff,(uVar13 << 4) >> 0x14);
  }
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x7c02609c,&local_6c);
  if (0 < DebugLevel) {
    printk("DMASHDL ERR FLAG CTRL(0x5000A09c): 0x%08x\n",local_6c);
  }
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x7c026100,&local_6c);
  uVar13 = local_6c & 0xfff;
  uVar6 = (local_6c << 4) >> 0x14;
  if ((0 < DebugLevel) && (printk("DMASHDL Status_RD(0x5000A100): 0x%08x\n"), 0 < DebugLevel)) {
    printk("free page cnt = 0x%03x, ffa cnt = 0x%03x\n",uVar6,uVar13);
  }
  uVar7 = 0;
  bVar2 = false;
  local_a0 = 0;
  local_a4 = 0;
  local_90 = 0;
  local_94 = 0;
  local_9c = 0x7c026180;
  iVar14 = DebugLevel;
  do {
    iVar1 = (uVar7 + 0x1f009850) * 4;
    if (0 < iVar14) {
      printk("Group %d info:",uVar7);
    }
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),iVar1,&local_6c);
    uVar15 = (local_6c << 4) >> 0x14;
    uVar5 = local_6c & 0xfff;
    if (2 < DebugLevel) {
      printk("\tDMASHDL Status_RD_GP%d(0x%08x): 0x%08x\n",uVar7,iVar1);
    }
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),iVar1 + -0x120,&local_6c);
    uVar10 = local_6c;
    if (2 < DebugLevel) {
      printk("\tDMASHDL Group%d control(0x%08x): 0x%08x\n",uVar7,iVar1 + -0x120,local_6c);
    }
    uVar12 = uVar7 & 1;
    uVar11 = local_94;
    uVar9 = local_90;
    if (uVar12 == 0) {
      hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),local_9c,&local_6c);
      if (2 < DebugLevel) {
        printk("\tDMASHDL RD_group_pkt_cnt_%d(0x%08x): 0x%08x\n",uVar7 >> 1,local_9c,local_6c);
      }
      local_90 = (local_6c << 8) >> 0x18;
      local_94 = local_6c >> 0x18;
      uVar11 = (local_6c << 0x10) >> 0x18;
      uVar9 = local_6c & 0xff;
    }
    if (DebugLevel < 1) {
LAB_0018a2f4:
      uVar10 = uVar8;
      if (uVar11 == uVar9) {
        uVar10 = 0;
      }
      if (uVar10 != 0) {
LAB_0018a30c:
        bVar2 = true;
        goto LAB_0018a314;
      }
LAB_0018a46c:
      if (uVar7 == 0xf) goto LAB_0018a474;
LAB_0018a324:
      uVar10 = local_68[uVar7];
      iVar14 = DebugLevel;
      if (uVar10 != 0) {
LAB_0018a330:
        cVar3 = '\0';
        iVar14 = DebugLevel;
        do {
          uVar11 = uVar10 & 1;
          uVar10 = uVar10 >> 1;
          if ((uVar11 != 0) && (0 < iVar14)) {
            printk(&_LC54,cVar3);
            iVar14 = DebugLevel;
          }
          local_68[uVar7] = uVar10;
          cVar3 = cVar3 + '\x01';
        } while (uVar10 != 0);
        goto LAB_0018a358;
      }
    }
    else {
      printk("\trsv_cnt = 0x%03x, src_cnt = 0x%03x\n",uVar15,uVar5);
      if (DebugLevel < 1) {
        uVar10 = uVar8;
        if (uVar11 == uVar9) {
          uVar10 = 0;
        }
        if (uVar10 == 0) goto LAB_0018a46c;
        goto LAB_0018a30c;
      }
      printk("\tmax/min quota = 0x%03x/ 0x%03x\n",(uVar10 << 4) >> 0x14,uVar10 & 0xfff);
      if (DebugLevel < 1) goto LAB_0018a2f4;
      printk("\tpktin_cnt = 0x%02x, ask_cnt = 0x%02x",uVar11,uVar9);
      uVar10 = uVar8;
      if (uVar11 == uVar9) {
        uVar10 = 0;
      }
      if (uVar10 != 0) {
        if (DebugLevel < 1) {
          bVar2 = true;
          goto LAB_0018a46c;
        }
        bVar2 = true;
        printk(", mismatch!");
      }
      if (DebugLevel < 1) goto LAB_0018a46c;
      printk(&_LC12);
LAB_0018a314:
      if (uVar7 == 0xf) {
LAB_0018a474:
        iVar14 = DebugLevel;
        if (local_68[0xf] == 0) goto LAB_0018a39c;
      }
      if (DebugLevel < 1) goto LAB_0018a324;
      printk("\tMapping Qidx:");
      uVar10 = local_68[uVar7];
      iVar14 = DebugLevel;
      if (uVar10 != 0) goto LAB_0018a330;
LAB_0018a358:
      if (0 < iVar14) {
        printk(&_LC12);
        iVar14 = DebugLevel;
      }
    }
    uVar7 = uVar7 + 1;
    local_a4 = local_a4 + uVar5;
    local_a0 = local_a0 + uVar15;
    if (uVar12 != 0) {
      local_9c = local_9c + 4;
    }
  } while (uVar7 != 0x10);
  uVar5 = 0;
  uVar15 = 0;
LAB_0018a39c:
  if (0 < iVar14) {
    printk("\nCounter Check:\n");
  }
  mac_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0114,&local_6c);
  uVar7 = local_6c & 0xfff;
  uVar8 = (local_6c << 4) >> 0x14;
  if (0 < DebugLevel) {
    printk("PLE:\n\tThe used/reserved pages of PLE HIF group=0x%03x/0x%03x\n",uVar8,uVar7);
  }
  mac_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c811c,&local_6c);
  uVar11 = local_6c & 0xfff;
  uVar10 = (local_6c << 4) >> 0x14;
  if ((DebugLevel < 1) ||
     (printk("PSE:\n\tThe used/reserved pages of PSE HIF group=0x%03x/0x%03x\n",uVar10,uVar11),
     DebugLevel < 1)) {
    if (uVar8 == local_a4) goto LAB_0018a530;
LAB_0018a418:
    bVar2 = true;
LAB_0018a420:
    if (local_a0 + uVar13 != uVar6) goto LAB_0018a438;
LAB_0018a5dc:
    if (uVar6 != uVar7) {
      if (DebugLevel < 1) goto LAB_0018a438;
      bVar2 = true;
      printk(", mismatch(reserved pages in PLE)");
    }
    if ((0 < DebugLevel) && (printk(&_LC12), 0 < DebugLevel)) {
      printk("\tThe used pages of group15=0x%03x",uVar5);
      if (uVar10 == uVar5) goto LAB_0018a6c0;
      if (0 < DebugLevel) {
        bVar2 = true;
        printk(", mismatch!");
        goto LAB_0018a6c0;
      }
      goto LAB_0018a448;
    }
    if (uVar10 != uVar5) {
      bVar2 = true;
    }
  }
  else {
    printk("DMASHDL:\n\tThe total used pages of group0~14=0x%03x",local_a4);
    if (uVar8 != local_a4) {
      if (DebugLevel < 1) goto LAB_0018a418;
      bVar2 = true;
      printk(", mismatch!");
    }
LAB_0018a530:
    if ((((DebugLevel < 1) || (printk(&_LC12), DebugLevel < 1)) ||
        (printk("\tThe total reserved pages of group0~14=0x%03x\n",local_a0), DebugLevel < 1)) ||
       (printk("\tThe total ffa pages of group0~14=0x%03x\n",uVar13), DebugLevel < 1))
    goto LAB_0018a420;
    printk("\tThe total free pages of group0~14=0x%03x",uVar6);
    if (local_a0 + uVar13 == uVar6) goto LAB_0018a5dc;
    if (0 < DebugLevel) {
      bVar2 = true;
      printk(", mismatch(total_rsv_cnt + ffa_cnt in DMASHDL)");
      goto LAB_0018a5dc;
    }
LAB_0018a438:
    bVar2 = true;
    if (uVar10 == uVar5) {
LAB_0018a6c0:
      if (DebugLevel < 1) {
        return 1;
      }
      printk(&_LC12);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("\tThe reserved pages of group15=0x%03x",uVar15);
      if (uVar11 != uVar15) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk(", mismatch!");
        if (DebugLevel < 1) {
          return 1;
        }
        printk(&_LC12);
        return 1;
      }
      goto LAB_0018a628;
    }
LAB_0018a448:
    bVar2 = true;
  }
  if (uVar11 != uVar15) {
    return 1;
  }
LAB_0018a628:
  if (((0 < DebugLevel) && (printk(&_LC12), !bVar2)) && (0 < DebugLevel)) {
    printk("DMASHDL: no counter mismatch\n");
  }
  return 1;
}

