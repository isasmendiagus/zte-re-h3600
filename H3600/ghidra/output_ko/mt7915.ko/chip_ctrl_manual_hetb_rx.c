// module: mt7915.ko
// function: chip_ctrl_manual_hetb_rx @ 0x18c338
// size: 2388 bytes
//

undefined4
chip_ctrl_manual_hetb_rx
          (int param_1,int param_2,int param_3,byte param_4,byte param_5,byte param_6,uint param_7,
          uint param_8,int param_9,char *param_10)

{
  int iVar1;
  ushort uVar2;
  uint *puVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  
  piVar5 = (int *)0x5df270;
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
    piVar5 = &_LANCHOR1;
  }
  if (param_3 == 0) {
    param_2 = param_2 * 0x10000;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
    local_38 = local_38 & 0xfffffff0;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[1],0);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[2],0);
    if (((0 < DebugLevel) &&
        (printk("%s: [Stop]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38),
        0 < DebugLevel)) &&
       (printk("%s:       0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[1],0),
       0 < DebugLevel)) {
      printk("%s:       0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[2],0);
    }
  }
  else {
    uVar8 = 0;
    uVar9 = 0;
    puVar3 = (uint *)(param_10 + 0xc);
    uVar4 = 0;
    local_38 = 0;
    do {
      if ((char)puVar3[-3] == '\0') {
LAB_0018c400:
        uVar6 = 0;
        uVar7 = 0;
      }
      else {
        uVar6 = *puVar3 >> 1;
        if (uVar6 < 0x45) {
          if (uVar6 < 0x25) goto LAB_0018c400;
          if (uVar6 < 0x35) {
            uVar6 = 1 << (uVar4 & 0xff);
            uVar7 = 1 << (uVar4 - 0x20 & 0xff) | 1U >> (0x20 - uVar4 & 0xff);
          }
          else {
            if (uVar6 < 0x3d) {
              uVar6 = 2;
            }
            else if (uVar6 < 0x41) {
              uVar6 = 3;
            }
            else if (uVar6 < 0x43) {
              uVar6 = 4;
            }
            else if (uVar6 == 0x43) {
              uVar6 = 5;
            }
            else {
              uVar6 = 6;
            }
            uVar7 = uVar6 << (uVar4 - 0x20 & 0xff) | uVar6 >> (0x20 - uVar4 & 0xff);
            uVar6 = uVar6 << (uVar4 & 0xff);
          }
        }
        else {
          uVar6 = 7 << (uVar4 & 0xff);
          uVar7 = 7 << (uVar4 - 0x20 & 0xff) | 7U >> (0x20 - uVar4 & 0xff);
        }
      }
      uVar4 = uVar4 + 3;
      uVar8 = uVar8 | uVar6;
      uVar9 = uVar9 | uVar7;
      puVar3 = puVar3 + 0x1b;
    } while (uVar4 != 0x30);
    param_2 = param_2 * 0x10000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1a92c,
                   uVar9 & 0xffff | 0x80000000);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1a930,uVar8);
    if (0 < DebugLevel) {
      printk("%s: [MAC]0x%x=0x%llx\n","chip_ctrl_manual_hetb_rx",param_2 + -0x7df1a930);
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
    local_38 = local_38 | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [Start]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38);
    }
    local_38 = local_38 | 2;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s:        0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38);
    }
    local_38 = param_7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[2],param_7);
    if (0 < DebugLevel) {
      printk("%s: [CSD_H]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[2],local_38);
    }
    local_38 = param_8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[1],param_8);
    if (0 < DebugLevel) {
      printk("%s: [CSD_L]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[1],local_38);
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
    local_38 = local_38 | 8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [Assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38);
    }
    local_38 = local_38 & 0xfffffff3;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [De-assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,
             local_38);
    }
    os_zero_mem(&local_30,8);
    uVar4 = *(uint *)(param_9 + 0x28);
    if (uVar4 < *(uint *)(param_9 + 0x18)) {
      uVar4 = *(uint *)(param_9 + 0x18);
    }
    uVar2 = (ushort)local_30;
    local_30 = CONCAT13(local_30._3_1_ & 0xf7 | (*(byte *)(param_9 + 0x5c) & 1) << 3,
                        (undefined3)local_30);
    uVar4 = local_30 >> 0x10 & 0xfc7f | ((byte)(&DAT_0029c3f0)[uVar4] & 7) << 7;
    local_30._0_3_ =
         CONCAT12((byte)uVar4 & 0xc3 | (param_5 & 3) << 4 | (param_4 & 3) << 2,
                  uVar2 & 0xf | (ushort)((*(uint *)(param_9 + 0x68) & 0xfff) << 4));
    local_30 = CONCAT13((byte)(uVar4 >> 8) & 0xfb | (param_6 & 1) << 2,(undefined3)local_30);
    local_2c = local_2c & 0x803fffff;
    local_38 = local_30;
    local_2c = CONCAT31((int3)(local_2c >> 8),
                        (byte)local_2c & 0xe3 |
                        (byte)((*(uint *)(param_9 + 0x30) & 3 | (*(byte *)(param_9 + 100) & 1) << 2)
                              << 2)) | 0x7fc00000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[2],local_30);
    if (0 < DebugLevel) {
      printk("%s: [CMM_H]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[2],local_38);
    }
    local_38 = local_2c;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[1],local_2c);
    if (0 < DebugLevel) {
      printk("%s: [CMM_L]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + piVar5[1],local_38);
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
    local_38 = local_38 | 8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [Assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38);
    }
    local_38 = local_38 & 0xfffffff3;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [De-assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,
             local_38);
    }
    iVar10 = 1;
    do {
      os_zero_mem(&local_34,4);
      if (*param_10 == '\0') {
        local_34 = 0xffffffff;
      }
      else {
        uVar4 = *(uint *)(param_10 + 0x18);
        if (*(uint *)(param_10 + 0x28) <= uVar4) {
          local_34._1_1_ = local_34._1_1_ & 0xf1;
        }
        if (uVar4 < *(uint *)(param_10 + 0x28)) {
          local_34._1_1_ = local_34._1_1_ & 0xf1 | (byte)(((byte)param_10[0x1c] & 7) << 1);
        }
        local_34._0_2_ = CONCAT11(local_34._1_1_,(char)iVar10 + -1);
        iVar1 = (*(uint *)(param_10 + 0xc) & 0xff) << 0xc;
        local_34._0_2_ = (ushort)local_34 & 0xfff | (ushort)iVar1;
        local_34._2_1_ = (byte)((uint)iVar1 >> 0x10);
        iVar1 = (*(uint *)(param_10 + 0x10) & 0xf) << 5;
        local_34 = CONCAT22((ushort)(byte)(local_34._2_1_ |
                                          (byte)((*(uint *)(param_10 + 0x14) & 1) << 4)) |
                            (ushort)iVar1,(ushort)local_34);
        local_34 = CONCAT13((byte)((uint)iVar1 >> 8) |
                            (byte)(((*(uint *)(param_10 + 0x10) << 0x1a) >> 0x1f) << 1) |
                            (byte)(((byte)param_10[0x1c] & 7 | (uVar4 - 1) * 8 & 0x3f) << 2),
                            (undefined3)local_34);
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[2],local_34);
      if (0 < DebugLevel) {
        printk("%s: [USR%d]0x%x=[0x%x]\n","chip_ctrl_manual_hetb_rx",iVar10 + -1,param_2 + piVar5[2]
               ,local_34);
      }
      os_zero_mem(&local_34,4);
      if (param_10[0x6c] == '\0') {
        local_34 = 0xffffffff;
      }
      else {
        if (*(uint *)(param_10 + 0x84) < *(uint *)(param_10 + 0x94)) {
          local_34._1_1_ = local_34._1_1_ & 0xf1 | (byte)(((byte)param_10[0x88] & 7) << 1);
        }
        else {
          local_34._1_1_ = local_34._1_1_ & 0xf1;
        }
        iVar1 = (*(uint *)(param_10 + 0x78) & 0xff) << 0xc;
        local_34._0_2_ = CONCAT11(local_34._1_1_,(char)iVar10) & 0xfff | (ushort)iVar1;
        local_34._2_1_ = (byte)((uint)iVar1 >> 0x10);
        iVar1 = (*(uint *)(param_10 + 0x7c) & 0xf) << 5;
        local_34 = CONCAT22((ushort)(byte)(local_34._2_1_ |
                                          (byte)((*(uint *)(param_10 + 0x80) & 1) << 4)) |
                            (ushort)iVar1,(ushort)local_34);
        local_34 = CONCAT13((byte)((uint)iVar1 >> 8) |
                            (byte)(((*(uint *)(param_10 + 0x7c) << 0x1a) >> 0x1f) << 1) |
                            (byte)(((byte)param_10[0x88] & 7 |
                                   (*(uint *)(param_10 + 0x84) - 1) * 8 & 0x3f) << 2),
                            (undefined3)local_34);
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + piVar5[1],local_34);
      if (0 < DebugLevel) {
        printk("%s: [USR%d]0x%x=[0x%x]\n","chip_ctrl_manual_hetb_rx",iVar10,param_2 + piVar5[1],
               local_34);
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
      local_38 = local_38 | 8;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
      if (0 < DebugLevel) {
        printk("%s: [Assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38
              );
      }
      local_38 = local_38 & 0xfffffff3;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
      if (0 < DebugLevel) {
        printk("%s: [De-assert Write]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,
               local_38);
      }
      iVar10 = iVar10 + 2;
      param_10 = param_10 + 0xd8;
    } while (iVar10 != 0x11);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5,&local_38);
    local_38 = local_38 | 4;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + *piVar5);
    if (0 < DebugLevel) {
      printk("%s: [Submit]0x%x=0x%x\n","chip_ctrl_manual_hetb_rx",param_2 + *piVar5,local_38);
    }
  }
  return 0;
}

