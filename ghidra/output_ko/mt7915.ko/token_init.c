// module: mt7915.ko
// function: token_init @ 0x1d40c8
// size: 1812 bytes
//

undefined4 token_init(undefined4 *param_1,int param_2)

{
  undefined2 uVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  undefined2 *puVar9;
  uint uVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  byte *pbVar14;
  int iVar15;
  undefined4 uVar16;
  byte *local_2c [2];
  
  os_alloc_mem(param_2,local_2c,0x168);
  if (local_2c[0] == (byte *)0x0) {
    if (DebugLevel < 0) {
      uVar16 = 0xffffffff;
    }
    else {
      printk("%s os_alloc_mem fail\n","token_init");
      uVar16 = 0xffffffff;
    }
  }
  else {
    __memzero(local_2c[0],0x168);
    pbVar2 = local_2c[0];
    *(int *)(local_2c[0] + 0x160) = param_2;
    *param_1 = local_2c[0];
    iVar3 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
    if ((*(char *)(param_2 + 0x79504d) == '\0') || (*(char *)(iVar3 + 0x20) == '\0')) {
      pbVar6 = pbVar2 + 4;
      *pbVar2 = 1;
      iVar4 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
      iVar7 = DebugLevel;
      if (pbVar6 == (byte *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s(): token que is NULL!\n","token_tx_queue_init");
        }
      }
      else if (pbVar2[4] == 0) {
        iVar15 = *(int *)(iVar4 + 0xc) + -1;
        *(int *)(pbVar2 + 0x14) = iVar15;
        if (0 < iVar7) {
          printk("%s(): ct sw token number = %d\n","token_tx_queue_init");
          iVar15 = *(int *)(pbVar2 + 0x14);
        }
        iVar7 = iVar15 + 1;
        *(int *)(pbVar2 + 0x20) = iVar15 + 2;
        *(int *)(pbVar2 + 0x18) = iVar7;
        *(int *)(pbVar2 + 0x1c) = iVar7;
        *(short *)(pbVar2 + 0x12) = (short)iVar7;
        pbVar2[8] = 0;
        pbVar2[9] = 0;
        pbVar2[10] = 0;
        pbVar2[0xb] = 0;
        pbVar2[0xc] = 0;
        pbVar2[0xd] = 0;
        pbVar2[0xe] = 0;
        pbVar2[0xf] = 0;
        pbVar2[0x10] = 0;
        pbVar2[0x11] = 0;
        os_alloc_mem(param_2,pbVar2 + 0x24,(iVar15 + 2) * 2);
        if (*(int *)(pbVar2 + 0x24) != 0) {
          os_zero_mem(*(int *)(pbVar2 + 0x24),*(int *)(pbVar2 + 0x20) << 1);
        }
        os_alloc_mem(param_2,pbVar2 + 0x28,*(int *)(pbVar2 + 0x1c) << 5);
        if (*(int *)(pbVar2 + 0x28) != 0) {
          os_zero_mem(*(int *)(pbVar2 + 0x28),*(int *)(pbVar2 + 0x1c) << 5);
        }
        iVar7 = *(int *)(pbVar2 + 0x24);
        if (iVar7 != 0) {
          iVar15 = 0;
          if (*(int *)(pbVar2 + 0x1c) != 0) {
            uVar13 = 0;
            do {
              *(short *)(iVar7 + uVar13 * 2) = (short)uVar13;
              uVar13 = uVar13 + 1;
              iVar7 = *(int *)(pbVar2 + 0x24);
            } while (uVar13 < *(uint *)(pbVar2 + 0x1c));
            iVar15 = *(uint *)(pbVar2 + 0x1c) << 1;
          }
          *(short *)(iVar7 + iVar15) = (short)*(undefined4 *)(pbVar2 + 0x18);
        }
        uVar16 = *(undefined4 *)(pbVar2 + 0x1c);
        pbVar2[0x40] = 0;
        pbVar2[0x41] = 0;
        pbVar2[0x42] = 0;
        pbVar2[0x43] = 0;
        pbVar2[0x44] = 0;
        pbVar2[0x45] = 0;
        pbVar2[0x46] = 0;
        pbVar2[0x47] = 0;
        *(undefined4 *)(pbVar2 + 0x3c) = uVar16;
        pbVar2[0x48] = 0;
        pbVar2[0x49] = 0;
        pbVar2[0x4a] = 0;
        pbVar2[0x4b] = 0;
        *(undefined4 *)(pbVar2 + 0x2c) = *(undefined4 *)(iVar4 + 0x10);
        *(int *)(pbVar2 + 0x30) = *(int *)(pbVar2 + 0x30) + 10;
        _clear_bit(0,pbVar2 + 0x34);
        puVar9 = &DAT_002a08f4;
        pbVar14 = pbVar2;
        do {
          uVar1 = *puVar9;
          pbVar12 = pbVar14 + 8;
          pbVar14[0x50] = 0;
          pbVar14[0x51] = 0;
          pbVar14[0x52] = 0;
          pbVar14[0x53] = 0;
          *(undefined2 *)(pbVar14 + 0x4c) = uVar1;
          iVar7 = DebugLevel;
          puVar9 = puVar9 + 1;
          pbVar14 = pbVar12;
        } while (pbVar12 != pbVar2 + 0x60);
        pbVar2[4] = 1;
        if ((0 < iVar7) &&
           (printk("%s(): token que inited done!id_head/tail=%d/%d\n","token_tx_queue_init",
                   (int)*(short *)(pbVar2 + 0x10),(int)*(short *)(pbVar2 + 0x12)), 0 < DebugLevel))
        {
          printk("%s(): %p,%p\n","token_tx_queue_init",pbVar6,pbVar6);
        }
      }
      else if ((-1 < DebugLevel) &&
              (printk("%s(): token que already inited!shall not happened!\n","token_tx_queue_init"),
              -1 < DebugLevel)) {
        printk("\ttoken que id_head=%d, list.id_tail=%d\n",(int)*(short *)(pbVar2 + 0x10),
               (int)*(short *)(pbVar2 + 0x12));
      }
    }
    else {
      uVar13 = 0;
      *pbVar2 = 2;
      do {
        iVar4 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
        iVar7 = DebugLevel;
        pbVar6 = pbVar2 + uVar13 * 0xa8 + 4;
        pbVar14 = pbVar2 + uVar13 * 0xa8;
        if (pbVar14[4] == 0) {
          if (uVar13 == 0) {
            *(int *)(pbVar2 + 0x14) = *(int *)(iVar4 + 0x14) + -1;
            *(undefined4 *)(pbVar2 + 0x1c) = *(undefined4 *)(iVar4 + 0x14);
            *(undefined4 *)(pbVar2 + 0x18) = *(undefined4 *)(iVar4 + 0xc);
joined_r0x001d46a0:
            if (0 < iVar7) {
              printk("%s(): ct sw token(%d) number = %d\n","token_tx_two_queues_init",uVar13);
            }
          }
          else if (uVar13 == 1) {
            *(int *)(pbVar2 + 0xbc) = *(int *)(iVar4 + 0xc) + -1;
            *(int *)(pbVar2 + 0xc4) = *(int *)(iVar4 + 0xc) - *(int *)(iVar4 + 0x14);
            *(int *)(pbVar2 + 0xc0) = *(int *)(iVar4 + 0xc) + 1;
            goto joined_r0x001d46a0;
          }
          iVar15 = *(int *)(pbVar2 + uVar13 * 0xa8 + 0x1c);
          iVar7 = iVar15 + 1;
          *(int *)(pbVar2 + uVar13 * 0xa8 + 0x20) = iVar7;
          pbVar12 = pbVar2 + uVar13 * 0xa8 + 0xc;
          pbVar12[0] = 0;
          pbVar12[1] = 0;
          pbVar12[2] = 0;
          pbVar12[3] = 0;
          pbVar12 = pbVar2 + uVar13 * 0xa8 + 8;
          pbVar12[0] = 0;
          pbVar12[1] = 0;
          pbVar12[2] = 0;
          pbVar12[3] = 0;
          *(short *)(pbVar2 + uVar13 * 0xa8 + 0x12) = (short)iVar15;
          (pbVar2 + uVar13 * 0xa8 + 0x10)[0] = 0;
          (pbVar2 + uVar13 * 0xa8 + 0x10)[1] = 0;
          os_alloc_mem(param_2,pbVar2 + uVar13 * 0xa8 + 0x24,iVar7 * 2);
          if (*(int *)(pbVar2 + uVar13 * 0xa8 + 0x24) != 0) {
            os_zero_mem(*(int *)(pbVar2 + uVar13 * 0xa8 + 0x24),
                        *(int *)(pbVar2 + uVar13 * 0xa8 + 0x20) << 1);
          }
          os_alloc_mem(param_2,pbVar2 + uVar13 * 0xa8 + 0x28,
                       *(int *)(pbVar2 + uVar13 * 0xa8 + 0x1c) << 5);
          if (*(int *)(pbVar2 + uVar13 * 0xa8 + 0x28) != 0) {
            os_zero_mem(*(int *)(pbVar2 + uVar13 * 0xa8 + 0x28),
                        *(int *)(pbVar2 + uVar13 * 0xa8 + 0x1c) << 5);
          }
          iVar7 = *(int *)(pbVar2 + uVar13 * 0xa8 + 0x24);
          uVar5 = 0;
          if (*(int *)(pbVar2 + uVar13 * 0xa8 + 0x1c) != 0) {
            uVar8 = 0;
            uVar10 = uVar8;
            do {
              if (iVar7 != 0) {
                if (uVar13 == 0) {
                  *(short *)(iVar7 + uVar8) = (short)uVar10;
                  iVar7 = *(int *)(pbVar2 + 0x24);
                }
                else {
                  *(short *)(iVar7 + uVar8) = (short)uVar10 + (short)*(undefined4 *)(iVar4 + 0x14);
                  iVar7 = *(int *)(pbVar2 + uVar13 * 0xa8 + 0x24);
                }
              }
              uVar5 = *(uint *)(pbVar2 + uVar13 * 0xa8 + 0x1c);
              uVar10 = uVar10 + 1;
              uVar8 = uVar8 + 2;
            } while (uVar10 < uVar5);
          }
          if (iVar7 != 0) {
            *(short *)(iVar7 + uVar5 * 2) = (short)*(undefined4 *)(pbVar2 + uVar13 * 0xa8 + 0x18);
          }
          uVar16 = *(undefined4 *)(pbVar2 + uVar13 * 0xa8 + 0x1c);
          pbVar12 = pbVar2 + uVar13 * 0xa8 + 0x40;
          pbVar12[0] = 0;
          pbVar12[1] = 0;
          pbVar12[2] = 0;
          pbVar12[3] = 0;
          pbVar12 = pbVar2 + uVar13 * 0xa8 + 0x44;
          pbVar12[0] = 0;
          pbVar12[1] = 0;
          pbVar12[2] = 0;
          pbVar12[3] = 0;
          *(undefined4 *)(pbVar2 + uVar13 * 0xa8 + 0x3c) = uVar16;
          pbVar12 = pbVar2 + uVar13 * 0xa8 + 0x48;
          pbVar12[0] = 0;
          pbVar12[1] = 0;
          pbVar12[2] = 0;
          pbVar12[3] = 0;
          pbVar14[5] = (byte)uVar13;
          *(undefined4 *)(pbVar2 + uVar13 * 0xa8 + 0x2c) = *(undefined4 *)(iVar4 + 0x10);
          *(int *)(pbVar2 + uVar13 * 0xa8 + 0x30) = *(int *)(pbVar2 + uVar13 * 0xa8 + 0x30) + 10;
          _clear_bit(0,pbVar2 + uVar13 * 0xa8 + 0x34);
          puVar9 = &DAT_002a08f4;
          pbVar12 = pbVar14;
          do {
            uVar1 = *puVar9;
            pbVar11 = pbVar12 + 8;
            pbVar12[0x50] = 0;
            pbVar12[0x51] = 0;
            pbVar12[0x52] = 0;
            pbVar12[0x53] = 0;
            *(undefined2 *)(pbVar12 + 0x4c) = uVar1;
            iVar7 = DebugLevel;
            puVar9 = puVar9 + 1;
            pbVar12 = pbVar11;
          } while (pbVar11 != pbVar2 + uVar13 * 0xa8 + 0x60);
          pbVar14[4] = 1;
          if (0 < iVar7) {
            iVar7 = (int)*(short *)(pbVar2 + uVar13 * 0xa8 + 0x12);
            printk("%s(): token que(%d) inited done!id_head/tail=%d/%d\n","token_tx_two_queues_init"
                   ,uVar13,(int)*(short *)(pbVar2 + uVar13 * 0xa8 + 0x10),iVar7);
            if (0 < DebugLevel) {
              printk("%s(): %p,%p\n","token_tx_two_queues_init",pbVar6,pbVar6,iVar7);
            }
          }
        }
        else if (-1 < DebugLevel) {
          printk("%s(): token que(%d) already inited!shall not happened!\n",
                 "token_tx_two_queues_init",uVar13);
          if (pbVar6 == (byte *)0x0) {
            if (-1 < DebugLevel) {
              printk("%s(): token que(%d) is NULL!\n","token_tx_two_queues_init",uVar13);
            }
          }
          else if (-1 < DebugLevel) {
            printk("\t%s(): token que(%d) id_head=%d, list.id_tail=%d\n","token_tx_two_queues_init",
                   uVar13,(int)*(short *)(pbVar2 + uVar13 * 0xa8 + 0x10),
                   (int)*(short *)(pbVar2 + uVar13 * 0xa8 + 0x12));
          }
        }
        uVar13 = uVar13 + 1 & 0xff;
      } while (uVar13 < *pbVar2);
    }
    if (*(char *)(iVar3 + 0x21) != '\0') {
      MtCmdCr4Set(param_2,0x20,1,0);
    }
    iVar3 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
    local_2c[0][0x158] = 0;
    local_2c[0][0x159] = 0;
    local_2c[0][0x15a] = 0;
    local_2c[0][0x15b] = 0;
    iVar3 = *(int *)(iVar3 + 0x1c);
    *(int *)(local_2c[0] + 0x15c) = iVar3;
    os_alloc_mem(param_2,local_2c[0] + 0x154,iVar3 << 5);
    uVar16 = 0;
    if (*(int *)(local_2c[0] + 0x154) != 0) {
      os_zero_mem(*(int *)(local_2c[0] + 0x154),*(int *)(local_2c[0] + 0x15c) << 5);
      return 0;
    }
  }
  return uVar16;
}

