// module: mt7915.ko
// function: chip_show_pse_info @ 0x18b5b4
// size: 2792 bytes
//

undefined4 chip_show_pse_info(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c [2];
  
  iVar5 = *(int *)(param_1 + 0x4328);
  memset(&local_70,0,0x58);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8014,&local_84);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c80b0,&local_80);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8100,&local_70);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8104,&local_6c);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8110,&local_68);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8114,&local_64);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8118,&local_60);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c811c,&local_5c);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8150,&local_58);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8154,&local_54);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8170,&local_50);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8174,&local_4c);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8178,&local_48);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c817c,&local_44);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8180,&local_40);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8184,&local_3c);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8160,&local_38);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8164,&local_34);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8188,&local_30);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c818c,&local_2c);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8198,&local_28);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c819c,&local_24);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c8168,&local_20);
  hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c816c,local_1c);
  if (((0 < DebugLevel) && (printk("PSE Configuration Info:\n"), 0 < DebugLevel)) &&
     (printk("\tPacket Buffer Control(0x82068014): 0x%08x\n",local_84), 0 < DebugLevel)) {
    if ((int)local_84 < 0) {
      uVar1 = 0x100;
    }
    else {
      uVar1 = 0x80;
    }
    printk("\t\tPage Size=%d(%d bytes per page)\n",local_84 >> 0x1f,uVar1);
    if (((0 < DebugLevel) &&
        (printk("\t\tPage Offset=%d(in unit of 64KB)\n",(local_84 << 6) >> 0x17), 0 < DebugLevel))
       && ((printk("\t\tTotal page numbers=%d pages\n",local_84 & 0xfff), 0 < DebugLevel &&
           (printk("PSE Page Flow Control:\n"), 0 < DebugLevel)))) {
      printk("\tFree page counter(0x82068100): 0x%08x\n",local_70);
      if (((0 < DebugLevel) &&
          (printk("\t\tThe toal page number of free=0x%03x\n",local_70 & 0xfff), 0 < DebugLevel)) &&
         ((printk("\t\tThe free page numbers of free for all=0x%03x\n",(local_70 << 4) >> 0x14),
          0 < DebugLevel &&
          (((printk("\tFree page head and tail(0x82068104): 0x%08x\n",local_6c), 0 < DebugLevel &&
            (printk("\t\tThe tail/head page of free page list=0x%03x/0x%03x\n",
                    (local_6c << 4) >> 0x14,local_6c & 0xfff), 0 < DebugLevel)) &&
           (printk("\tReserved page counter of HIF0 group(0x82068110): 0x%08x\n",local_68),
           0 < DebugLevel)))))) {
        printk("\tHIF0 group page status(0x82068114): 0x%08x\n",local_64);
        if (((0 < DebugLevel) &&
            (printk("\t\tThe max/min quota pages of HIF0 group=0x%03x/0x%03x\n",
                    (local_68 << 4) >> 0x14,local_68 & 0xfff), 0 < DebugLevel)) &&
           ((printk("\t\tThe used/reserved pages of HIF0 group=0x%03x/0x%03x\n",
                    (local_64 << 4) >> 0x14,local_64 & 0xfff), 0 < DebugLevel &&
            (printk("\tReserved page counter of HIF1 group(0x82068118): 0x%08x\n",local_60),
            0 < DebugLevel)))) {
          printk("\tHIF1 group page status(0x8206811c): 0x%08x\n",local_5c);
          if (((0 < DebugLevel) &&
              (printk("\t\tThe max/min quota pages of HIF1 group=0x%03x/0x%03x\n",
                      (local_60 << 4) >> 0x14,local_60 & 0xfff), 0 < DebugLevel)) &&
             ((printk("\t\tThe used/reserved pages of HIF1 group=0x%03x/0x%03x\n",
                      (local_5c << 4) >> 0x14,local_5c & 0xfff), 0 < DebugLevel &&
              (printk("\tReserved page counter of CPU group(0x82068150): 0x%08x\n",local_58),
              0 < DebugLevel)))) {
            printk("\tCPU group page status(0x82068154): 0x%08x\n",local_54);
            if ((((0 < DebugLevel) &&
                 (printk("\t\tThe max/min quota pages of CPU group=0x%03x/0x%03x\n",
                         (local_58 << 4) >> 0x14,local_58 & 0xfff), 0 < DebugLevel)) &&
                (printk("\t\tThe used/reserved pages of CPU group=0x%03x/0x%03x\n",
                        (local_54 << 4) >> 0x14,local_54 & 0xfff), 0 < DebugLevel)) &&
               (printk("\tReserved page counter of LMAC0 group(0x82068170): 0x%08x\n",local_50),
               0 < DebugLevel)) {
              printk("\tLMAC0 group page status(0x82068174): 0x%08x\n",local_4c);
              if (((0 < DebugLevel) &&
                  (printk("\t\tThe max/min quota pages of LMAC0 group=0x%03x/0x%03x\n",
                          (local_50 << 4) >> 0x14,local_50 & 0xfff), 0 < DebugLevel)) &&
                 ((printk("\t\tThe used/reserved pages of LMAC0 group=0x%03x/0x%03x\n",
                          (local_4c << 4) >> 0x14,local_4c & 0xfff), 0 < DebugLevel &&
                  (printk("\tReserved page counter of LMAC1 group(0x82068178): 0x%08x\n",local_48),
                  0 < DebugLevel)))) {
                printk("\tLMAC1 group page status(0x8206817c): 0x%08x\n",local_44);
                if (((0 < DebugLevel) &&
                    (printk("\t\tThe max/min quota pages of LMAC1 group=0x%03x/0x%03x\n",
                            (local_48 << 4) >> 0x14,local_48 & 0xfff), 0 < DebugLevel)) &&
                   ((printk("\t\tThe used/reserved pages of LMAC1 group=0x%03x/0x%03x\n",
                            (local_44 << 4) >> 0x14,local_44 & 0xfff), 0 < DebugLevel &&
                    (printk("\tReserved page counter of LMAC2 group(0x82068180): 0x%08x\n",local_44)
                    , 0 < DebugLevel)))) {
                  printk("\tLMAC2 group page status(0x82068184): 0x%08x\n",local_40);
                  if ((((0 < DebugLevel) &&
                       (printk("\t\tThe max/min quota pages of LMAC2 group=0x%03x/0x%03x\n",
                               (local_40 << 4) >> 0x14,local_40 & 0xfff), 0 < DebugLevel)) &&
                      (printk("\t\tThe used/reserved pages of LMAC2 group=0x%03x/0x%03x\n",
                              (local_3c << 4) >> 0x14,local_3c & 0xfff), 0 < DebugLevel)) &&
                     (printk("\tReserved page counter of LMAC3 group(0x82068188): 0x%08x\n",local_30
                            ), 0 < DebugLevel)) {
                    printk("\tLMAC3 group page status(0x8206818c): 0x%08x\n",local_2c);
                    if (((0 < DebugLevel) &&
                        (printk("\t\tThe max/min quota pages of LMAC3 group=0x%03x/0x%03x\n",
                                (local_30 << 4) >> 0x14,local_30 & 0xfff), 0 < DebugLevel)) &&
                       ((printk("\t\tThe used/reserved pages of LMAC3 group=0x%03x/0x%03x\n",
                                (local_2c << 4) >> 0x14,local_2c & 0xfff), 0 < DebugLevel &&
                        (printk("\tReserved page counter of PLE group(0x82068160): 0x%08x\n",
                                local_38), 0 < DebugLevel)))) {
                      printk("\tPLE group page status(0x82068164): 0x%08x\n",local_34);
                      if (((0 < DebugLevel) &&
                          (printk("\t\tThe max/min quota pages of PLE group=0x%03x/0x%03x\n",
                                  (local_38 << 4) >> 0x14,local_38 & 0xfff), 0 < DebugLevel)) &&
                         ((printk("\t\tThe used/reserved pages of PLE group=0x%03x/0x%03x\n",
                                  (local_34 << 4) >> 0x14,local_34 & 0xfff), 0 < DebugLevel &&
                          (printk("\tReserved page counter of PLE1 group(0x82068168): 0x%08x\n",
                                  local_38), 0 < DebugLevel)))) {
                        printk("\tPLE1 group page status(0x8206816c): 0x%08x\n",local_34);
                        if ((((0 < DebugLevel) &&
                             (printk("\t\tThe max/min quota pages of PLE1 group=0x%03x/0x%03x\n",
                                     (local_20 << 4) >> 0x14,local_20 & 0xfff), 0 < DebugLevel)) &&
                            (printk("\t\tThe used/reserved pages of PLE1 group=0x%03x/0x%03x\n",
                                    (local_1c[0] << 4) >> 0x14,local_1c[0] & 0xfff), 0 < DebugLevel)
                            ) && (printk("\tReserved page counter of MDP group(0x82068198): 0x%08x\n"
                                         ,local_28), 0 < DebugLevel)) {
                          printk("\tMDP group page status(0x8206819c): 0x%08x\n",local_24);
                          if (((0 < DebugLevel) &&
                              (printk("\t\tThe max/min quota pages of MDP group=0x%03x/0x%03x\n",
                                      (local_28 << 4) >> 0x14,local_28 & 0xfff), 0 < DebugLevel)) &&
                             ((printk("\t\tThe used/reserved pages of MDP group=0x%03x/0x%03x\n",
                                      (local_24 << 4) >> 0x14,local_24 & 0xfff), 0 < DebugLevel &&
                              ((printk("PSE Queue Empty Status:\n"), 0 < DebugLevel &&
                               (printk("\tQUEUE_EMPTY(0x820680b0): 0x%08x\n",local_80),
                               0 < DebugLevel)))))) {
                            printk("\t\tCPU Q0/1/2/3 empty=%d/%d/%d/%d\n",local_80 & 1,
                                   (local_80 << 0x1e) >> 0x1f,(local_80 << 0x1d) >> 0x1f,
                                   (local_80 << 0x1c) >> 0x1f);
                            if (0 < DebugLevel) {
                              uVar6 = (local_80 << 0x14) >> 0x1f;
                              uVar3 = (local_80 << 0x13) >> 0x1f;
                              uVar2 = (local_80 << 0x12) >> 0x1f;
                              printk("\t\tHIF Q0/1/2/3/4/5 empty=%d/%d/%d/%d/%d/%d\n",
                                     (local_80 << 0x17) >> 0x1f,(local_80 << 0x16) >> 0x1f,
                                     (local_80 << 0x15) >> 0x1f,uVar6,uVar3,uVar2);
                              if (((((0 < DebugLevel) &&
                                    (printk("\t\tLMAC TX Q empty=%d\n",(local_80 << 0xf) >> 0x1f),
                                    0 < DebugLevel)) &&
                                   (printk("\t\tMDP TX Q/RX Q empty=%d/%d\n",
                                           (local_80 << 0xe) >> 0x1f,(local_80 << 0xd) >> 0x1f,
                                           DebugLevel,uVar6,uVar3,uVar2), 0 < DebugLevel)) &&
                                  ((printk("\t\tSEC TX Q/RX Q empty=%d/%d\n",
                                           (local_80 << 0xc) >> 0x1f,(local_80 << 0xb) >> 0x1f,
                                           DebugLevel,uVar6,uVar3,uVar2), 0 < DebugLevel &&
                                   (printk("\t\tSFD PARK Q empty=%d\n",(local_80 << 10) >> 0x1f),
                                   0 < DebugLevel)))) &&
                                 ((printk("\t\tMDP TXIOC Q/RXIOC Q empty=%d/%d\n",
                                          (local_80 << 9) >> 0x1f,(local_80 << 8) >> 0x1f),
                                  0 < DebugLevel &&
                                  (printk("\t\tRLS Q empty=%d\n",local_80 >> 0x1f), 0 < DebugLevel))
                                 )) {
                                printk("Nonempty Q info:\n");
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  piVar4 = &DAT_0029c248;
  uVar3 = 0;
  do {
    uVar6 = 0x80000000;
    local_7c = (local_80 & 1 << (uVar3 & 0xff)) >> (uVar3 & 0xff);
    if ((local_7c == 0) && (*piVar4 != 0)) {
      local_78 = local_7c;
      local_74 = local_7c;
      if (0 < DebugLevel) {
        printk("\t%s: ");
        uVar6 = local_7c | 0x80000000;
      }
      local_7c = piVar4[1] << 10 | piVar4[2] << 0x18 | uVar6;
      hw_io_write32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c81b0);
      hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c81b8,&local_78);
      hw_io_read32(*(undefined4 *)(iVar5 + 0xa797a0),0x820c81bc,&local_74);
      if (0 < DebugLevel) {
        printk("tail/head fid = 0x%03x/0x%03x, pkt cnt = 0x%03x\n",(local_78 << 4) >> 0x14,
               local_78 & 0xfff,local_74 & 0xfff);
      }
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 3;
  } while (uVar3 != 0x1f);
  return 1;
}

