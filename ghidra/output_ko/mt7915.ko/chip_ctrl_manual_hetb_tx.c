// module: mt7915.ko
// function: chip_ctrl_manual_hetb_tx @ 0x18cc90
// size: 1648 bytes
//

undefined4
chip_ctrl_manual_hetb_tx
          (int param_1,int param_2,int param_3,byte param_4,byte param_5,byte param_6,int param_7)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_34 = 0;
  if (param_3 == 0) {
    if (param_7 == 0) {
      if (0 < DebugLevel) {
        printk("%s[%d]: invalid input\n","chip_ctrl_manual_hetb_tx",0xf6f);
      }
    }
    else {
      os_zero_mem(&local_30,8);
      uVar2 = local_30;
      uVar5 = *(uint *)(param_7 + 0x18);
      uVar7 = *(uint *)(param_7 + 0x28);
      uVar10 = uVar7;
      if (uVar7 < uVar5) {
        uVar10 = uVar5;
      }
      bVar13 = uVar5 < uVar7;
      uVar4 = local_2c._2_2_;
      uVar1 = (ushort)local_30;
      bVar8 = local_30._3_1_ & 0xf7 | (*(byte *)(param_7 + 0x5c) & 1) << 3;
      local_30 = CONCAT13(bVar8,(undefined3)local_30);
      uVar3 = local_30;
      local_30._2_1_ = bVar8;
      if (bVar13) {
        local_30._2_1_ = SUB41(uVar2,2);
      }
      uVar1 = uVar1 & 0xf | (ushort)((*(uint *)(param_7 + 0x68) & 0xfff) << 4);
      bVar9 = local_30._2_1_;
      if (bVar13) {
        bVar9 = local_30._2_1_ | 0x40;
      }
      local_30._2_2_ = SUB42(uVar3,2);
      local_30 = CONCAT22(local_30._2_2_,uVar1);
      if (bVar13) {
        local_30._0_3_ = CONCAT12(bVar9,uVar1);
        local_30 = CONCAT13(bVar8,(undefined3)local_30);
      }
      local_2c = CONCAT31(local_2c._1_3_,
                          (byte)local_2c & 0xe3 |
                          (byte)((*(uint *)(param_7 + 0x30) & 3 |
                                 (*(byte *)(param_7 + 100) & 1) << 2) << 2));
      local_2c = CONCAT22(uVar4,(undefined2)local_2c) & 0x803fffff | 0x7fc00000;
      if (uVar10 == 1 && param_6 != 0) {
        uVar1 = local_30._2_2_ & 0xfc7f | 0x80;
      }
      else {
        uVar1 = local_30._2_2_ & 0xfc7f | ((byte)(&DAT_0029c3f0)[uVar10] & 7) << 7;
      }
      local_30._2_1_ = (byte)uVar1;
      local_30._3_1_ = (byte)(uVar1 >> 8);
      iVar11 = param_2 * 0x10000;
      local_30._0_3_ =
           CONCAT12(local_30._2_1_ & 0xc3 | (param_5 & 3) << 4 | (param_4 & 3) << 2,(ushort)local_30
                   );
      local_30 = CONCAT13(local_30._3_1_ & 0xfb | (param_6 & 1) << 2,(undefined3)local_30);
      local_34 = local_30;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc90,local_30);
      local_34 = local_2c;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc8c,local_2c);
      if (0 < DebugLevel) {
        printk("%s: Step1: [CMM][%x][0x%llx]\n","chip_ctrl_manual_hetb_tx",iVar11 + -0x7df1bc90,
               DebugLevel,local_30,local_2c);
      }
      uVar10 = (*(uint *)(param_7 + 0xc) & 0xff) << 0xc | 1 |
               (*(uint *)(param_7 + 0x14) & 1) << 0x14 | (*(uint *)(param_7 + 0x10) & 0xf) << 0x15 |
               (*(uint *)(param_7 + 0x1c) & 7 | (uVar10 - 1) * 8) << 0x1a;
      local_34 = uVar10;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc88,uVar10);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc84,0xef);
      if ((0 < DebugLevel) &&
         (printk("%s: Step1: [USR][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11 + -0x7df1bc88,
                 uVar10), 0 < DebugLevel)) {
        printk("%s:        [USR][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11 + -0x7df1bc84,0xef
              );
      }
      local_34 = 0xffffffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc80,0x7ffffff);
      iVar12 = iVar11 + -0x7df1bc78;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11 + -0x7df1bc7c,local_34 & 0x7ffffff);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,local_34 & 0x3ffff);
      if (((0 < DebugLevel) &&
          (printk("%s: Step2: [RSSI][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11 + -0x7df1bc80,
                  local_34 & 0x7ffffff), 0 < DebugLevel)) &&
         (printk("%s:        [RSSI][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11 + -0x7df1bc7c,
                 local_34 & 0x7ffffff), 0 < DebugLevel)) {
        printk("%s:        [RSSI][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar12,
               local_34 & 0x3ffff);
      }
      local_34 = 0xffffffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,0xffffffff);
      if (0 < DebugLevel) {
        printk("%s:        [BWD][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar12,
               local_34 & 0xff000000);
      }
      iVar12 = iVar11 + -0x7df1be20;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,&local_34);
      local_34 = local_34 & 0xffcfffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar12);
      if (0 < DebugLevel) {
        printk("%s: Step3: [CBW Mode][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar12,
               local_34 & 0x300000);
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,&local_34);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,local_34 & 0xfff7ffff);
      if (0 < DebugLevel) {
        printk("%s:        [CBW 160NC IND][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar12,
               local_34 & 0x80000);
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar12,&local_34);
      iVar6 = net_ad_wrap_service(param_1);
      local_34 = (*(byte *)(param_2 * 0xd18 + iVar6 + 0x1133) & 7) << 0x10 | local_34;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar12);
      if (0 < DebugLevel) {
        printk("%s:        [CBW PRIM20 CH][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar12,
               local_34 & 0x70000);
      }
      iVar11 = iVar11 + -0x7cf71bfc;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar11,&local_34);
      local_34 = local_34 & 0xffffcf00 | 0x217f;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11);
      if (0 < DebugLevel) {
        printk("%s: Step4: [TXPWR IND/SKU][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11,local_34
              );
      }
    }
  }
  else {
    iVar11 = param_2 * 0x10000 + -0x7df1bc84;
    if (param_3 == 1) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar11,&local_34);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11,local_34 | 0x80000000);
      if (0 < DebugLevel) {
        printk("%s: Step6: [TF_RESP_TEST_MODE][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11,
               local_34 | 0x80000000);
      }
    }
    else {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar11,&local_34);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar11,local_34 & 0x7fffff00);
      if (0 < DebugLevel) {
        printk("%s: [Proactive HETB TX turned off][%x][0x%04x]\n","chip_ctrl_manual_hetb_tx",iVar11,
               local_34 & 0x7fffff00);
      }
    }
  }
  return 0;
}

