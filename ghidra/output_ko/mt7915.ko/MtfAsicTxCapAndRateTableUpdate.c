// module: mt7915.ko
// function: MtfAsicTxCapAndRateTableUpdate @ 0x195668
// size: 628 bytes
//

void MtfAsicTxCapAndRateTableUpdate(int param_1,uint param_2,int param_3,uint *param_4,char param_5)

{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined1 auStack_e0 [188];
  int local_24;
  
  iVar4 = FUN_00195078();
  if (iVar4 == 1) {
    __memzero(auStack_e0,0xc0);
    iVar4 = asic_get_wtbl_entry234(param_1,param_2,auStack_e0);
    if (iVar4 == 0) {
      if (-1 < DebugLevel) {
        printk("%s():Cannot found WTBL2/3/4 for WCID(%d)\n","MtfAsicTxCapAndRateTableUpdate",param_2
              );
      }
    }
    else {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_24 + 0xc,&local_e8);
      bVar5 = (byte)((uint)local_e8 >> 0x10);
      if (param_5 == '\0') {
        bVar5 = bVar5 & 0xe0;
      }
      else {
        bVar5 = bVar5 & 0xe0 | 0x18;
      }
      local_e8._0_3_ = CONCAT12(bVar5,(undefined2)local_e8);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),local_24 + 0xc,local_e8);
      bVar3 = hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_24 + 0x14,&local_e4);
      bVar1 = *(byte *)(param_3 + 5);
      bVar5 = bVar1 & 1;
      if ((bVar1 & 1) == 0) {
        local_e4._1_1_ = local_e4._1_1_ & 0xbf | bVar5 << 6;
      }
      else {
        local_e4._1_1_ = local_e4._1_1_ | 0x40;
        bVar5 = local_e4._1_1_;
      }
      local_e4 = CONCAT22(local_e4._2_2_,CONCAT11(local_e4._1_1_,(undefined1)local_e4));
      bVar8 = (bVar1 & 2) != 0;
      if (bVar8) {
        local_e4 = CONCAT22(local_e4._2_2_,CONCAT11(local_e4._1_1_,(undefined1)local_e4)) | 0x8000;
      }
      else {
        bVar5 = local_e4._1_1_ & 0x7f;
      }
      if (!bVar8) {
        local_e4._0_2_ = CONCAT11(bVar5,(undefined1)local_e4);
      }
      uVar6 = *(byte *)(param_3 + 4) - 1 & 0xff;
      if (uVar6 < 4) {
        uVar7 = (int)&_LANCHOR0 + uVar6;
      }
      else {
        bVar3 = 0;
        uVar7 = uVar6;
      }
      if (uVar6 < 4) {
        bVar3 = *(byte *)(uVar7 + 0x174) & 3;
      }
      bVar5 = (bVar3 & 3) << 4;
      uVar2 = local_e4._2_2_;
      if (*(char *)(param_3 + 3) == '\0') {
        bVar5 = local_e4._1_1_ & 0xc0 | bVar5;
      }
      else {
        bVar5 = local_e4._1_1_ & 0xcf | bVar5 | 0xf;
      }
      local_e4 = CONCAT31((int3)(CONCAT13(local_e4._3_1_,
                                          (int3)CONCAT22(uVar2,CONCAT11(bVar5,(char)local_e4))) >> 8
                                ),(char)local_e4) & 0x1fffffe0 | 0xe0;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x29020,local_e4);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x29024,
                     param_4[2] << 0x18 | param_4[1] << 0xc | *param_4);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x29028,
                     param_4[2] >> 8 | param_4[3] << 4 | param_4[4] << 0x10 | param_4[5] << 0x1c);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x2902c,
                     param_4[5] >> 4 | param_4[6] << 8 | param_4[7] << 0x14);
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f9830,param_2 | 0x6000);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s(): WaitIdle failed\n","MtfAsicTxCapAndRateTableUpdate");
  }
  return;
}

