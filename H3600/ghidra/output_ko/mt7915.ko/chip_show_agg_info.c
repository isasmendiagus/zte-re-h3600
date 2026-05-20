// module: mt7915.ko
// function: chip_show_agg_info @ 0x18e1b4
// size: 3104 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 chip_show_agg_info(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint *puVar11;
  uint *puVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  uint uVar22;
  undefined4 local_94;
  uint uStack_88;
  uint local_84 [8];
  uint local_64 [15];
  uint uStack_28;
  
  iVar13 = *(int *)(param_1 + 0x4328);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar13 + 0xa797a0));
  if (*(char *)(iVar2 + 0x1c4) != '\0') {
    uVar15 = 0;
    iVar14 = 0;
    do {
      iVar17 = uVar15 * 0x10000;
      if (0 < DebugLevel) {
        printk("Band %d AGG Status\n",uVar15);
        if (0 < DebugLevel) {
          printk("===============================\n");
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfb8,&local_94);
      if (0 < DebugLevel) {
        printk("AC00 Agg limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("AC01 Agg limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("AC02 Agg limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("AC03 Agg limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfb4,&local_94);
      if (0 < DebugLevel) {
        printk("AC10 Agg limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("AC11 Agg limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("AC12 Agg limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("AC13 Agg limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfb0,&local_94);
      if (0 < DebugLevel) {
        printk("AC20 Agg limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("AC21 Agg limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("AC22 Agg limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("AC23 Agg limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfac,&local_94);
      if (0 < DebugLevel) {
        printk("AC30 Agg limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("AC31 Agg limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("AC32 Agg limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("AC33 Agg limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfa8,&local_94);
      if (0 < DebugLevel) {
        printk("ALTX Agg limit = %d\n",local_94 & 0xff);
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfa4,&local_94);
      if (0 < DebugLevel) {
        printk("Winsize0 limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("Winsize1 limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("Winsize2 limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("Winsize3 limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1dfa0,&local_94);
      if (0 < DebugLevel) {
        printk("Winsize4 limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("Winsize5 limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("Winsize6 limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("Winsize7 limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1df9c,&local_94);
      if (0 < DebugLevel) {
        printk("Winsize8 limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("Winsize9 limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("WinsizeA limit = %d\t",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("WinsizeB limit = %d\n",local_94._3_1_);
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df1df98,&local_94);
      if (0 < DebugLevel) {
        printk("WinsizeC limit = %d\t",local_94 & 0xff);
        if (0 < DebugLevel) {
          printk("WinsizeD limit = %d\t",local_94._1_1_);
          if (0 < DebugLevel) {
            printk("WinsizeE limit = %d\n",local_94._2_1_);
            if (0 < DebugLevel) {
              printk("===AMPDU Related Counters===\n");
            }
          }
        }
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12b48,&local_94);
      local_64[1] = (local_94 << 0x10) >> 0x18;
      uVar16 = local_94 & 0xff;
      local_64[2] = (local_94 << 8) >> 0x18;
      local_64[3] = local_94 >> 0x18;
      local_64[0] = uVar16;
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12b44,&local_94);
      local_64[4] = local_94 & 0xff;
      local_64[5] = (local_94 << 0x10) >> 0x18;
      local_64[6] = (local_94 << 8) >> 0x18;
      local_64[7] = local_94 >> 0x18;
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12b40,&local_94);
      local_64[8] = local_94 & 0xff;
      local_64[9] = (local_94 << 0x10) >> 0x18;
      local_64[10] = (local_94 << 8) >> 0x18;
      local_64[0xb] = local_94 >> 0x18;
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12b3c,&local_94);
      local_64[0xc] = local_94 & 0xff;
      local_64[0xd] = (local_94 << 0x10) >> 0x18;
      local_64[0xe] = (local_94 << 8) >> 0x18;
      puVar11 = local_64;
      while( true ) {
        puVar12 = puVar11 + 1;
        *puVar11 = uVar16 + 1;
        if (puVar12 == &uStack_28) break;
        uVar16 = *puVar12;
        puVar11 = puVar12;
      }
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12f58,local_84);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12f54,local_84 + 1);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12f50,local_84 + 2);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12f4c,local_84 + 3);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12e9c,local_84 + 4);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12e98,local_84 + 5);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12e94,local_84 + 6);
      mac_io_read32(*(undefined4 *)(iVar13 + 0xa797a0),iVar17 + -0x7df12e90,local_84 + 7);
      if (0 < DebugLevel) {
        printk("\tTx Agg Range: \t%d \t%d~%d \t%d~%d \t%d~%d \t%d~%d \t%d~%d \t%d~%d \t%d~%d\n",
               local_64[0],local_64[0] + 1,local_64[1],local_64[1] + 1,local_64[2],local_64[2] + 1,
               local_64[3],local_64[3] + 1,local_64[4],local_64[4] + 1,local_64[5],local_64[5] + 1,
               local_64[6],local_64[6] + 1,local_64[7]);
      }
      puVar11 = &uStack_88;
      do {
        puVar11 = puVar11 + 1;
        iVar14 = iVar14 + (*puVar11 & 0xffff) + (*puVar11 >> 0x10);
      } while (puVar11 != local_84 + 7);
      if (0 < DebugLevel) {
        printk("\t\t\t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x\n",local_84[0] & 0xffff,
               local_84[0] >> 0x10,local_84[1] & 0xffff,local_84[1] >> 0x10,local_84[2] & 0xffff,
               local_84[2] >> 0x10,local_84[3] & 0xffff,local_84[3] >> 0x10);
        uVar1 = local_84[3];
        uVar22 = local_84[2];
        uVar21 = local_84[1];
        uVar16 = local_84[0];
        if (iVar14 != 0) {
          if (DebugLevel < 1) goto LAB_0018e544;
          uVar3 = __aeabi_uidiv((local_84[0] & 0xffff) * 100,iVar14);
          uVar4 = __aeabi_uidiv((uVar16 >> 0x10) * 100,iVar14);
          uVar5 = __aeabi_uidiv((uVar21 & 0xffff) * 100,iVar14);
          uVar6 = __aeabi_uidiv((uVar21 >> 0x10) * 100,iVar14);
          uVar7 = __aeabi_uidiv((uVar22 & 0xffff) * 100,iVar14);
          uVar8 = __aeabi_uidiv((uVar22 >> 0x10) * 100,iVar14);
          uVar9 = __aeabi_uidiv((uVar1 & 0xffff) * 100,iVar14);
          uVar10 = __aeabi_uidiv((uVar1 >> 0x10) * 100,iVar14);
          printk("\t\t\t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%)\n",
                 uVar3,uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10);
        }
        if (0 < DebugLevel) {
          iVar18 = local_64[0xb] + 1;
          iVar19 = local_64[0xc] + 1;
          iVar20 = local_64[0xd] + 1;
          iVar17 = local_64[0xe] + 1;
          uVar16 = local_64[0xc];
          uVar21 = local_64[0xd];
          uVar22 = local_64[0xe];
          printk("\t\t\t%d~%d\t%d~%d\t%d~%d\t%d~%d\t%d~%d\t%d~%d\t%d~%d\t%d~256\n",local_64[7] + 1,
                 local_64[8],local_64[8] + 1,local_64[9],local_64[9] + 1,local_64[10],
                 local_64[10] + 1,local_64[0xb],iVar18,local_64[0xc],iVar19,local_64[0xd],iVar20,
                 local_64[0xe],iVar17);
          if (DebugLevel < 1) goto LAB_0018e544;
          printk("\t\t\t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x \t0x%x\n",
                 local_84[4] & 0xffff,local_84[4] >> 0x10,local_84[5] & 0xffff,local_84[5] >> 0x10,
                 local_84[6] & 0xffff,local_84[6] >> 0x10,local_84[7] & 0xffff,local_84[7] >> 0x10,
                 iVar18,uVar16,iVar19,uVar21,iVar20,uVar22,iVar17);
        }
        uVar1 = local_84[7];
        uVar22 = local_84[6];
        uVar21 = local_84[5];
        uVar16 = local_84[4];
        if ((iVar14 != 0) && (0 < DebugLevel)) {
          uVar3 = __aeabi_uidiv((local_84[4] & 0xffff) * 100,iVar14);
          uVar4 = __aeabi_uidiv((uVar16 >> 0x10) * 100,iVar14);
          uVar5 = __aeabi_uidiv((uVar21 & 0xffff) * 100,iVar14);
          uVar6 = __aeabi_uidiv((uVar21 >> 0x10) * 100,iVar14);
          uVar7 = __aeabi_uidiv((uVar22 & 0xffff) * 100,iVar14);
          uVar8 = __aeabi_uidiv((uVar22 >> 0x10) * 100,iVar14);
          uVar9 = __aeabi_uidiv((uVar1 & 0xffff) * 100,iVar14);
          uVar10 = __aeabi_uidiv((uVar1 >> 0x10) * 100,iVar14);
          printk("\t\t\t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%) \t(%d%%)\n",
                 uVar3,uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10);
        }
      }
LAB_0018e544:
      uVar15 = uVar15 + 1 & 0xff;
    } while (uVar15 < *(byte *)(iVar2 + 0x1c4));
  }
  return 0;
}

