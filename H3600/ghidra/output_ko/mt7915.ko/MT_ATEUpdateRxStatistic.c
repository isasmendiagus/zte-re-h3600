// module: mt7915.ko
// function: MT_ATEUpdateRxStatistic @ 0x2816cc
// size: 1240 bytes
//

void MT_ATEUpdateRxStatistic(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint *puVar8;
  short sVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  uint *puVar13;
  uint *puVar14;
  uint local_2c [2];
  
  if (param_2 == 0) {
    local_2c[0] = param_2;
    iVar4 = net_ad_wrap_service();
    iVar5 = net_ad_wrap_service(param_1);
    bVar1 = *(byte *)(param_3 + 9);
    uVar2 = *(undefined1 *)((uint)*(byte *)(iVar5 + 0x4cc) * 0xd18 + iVar4 + 0x1130);
    if ((bVar1 & 0x70) == 0) {
      if (3 < DebugLevel) {
        printk("\t%s: MODE_CCK RX\n","MT_ATEUpdateRxStatistic");
      }
      sVar9 = (short)(((uint)*(byte *)(param_3 + 0x19) << 2 | (uint)(*(byte *)(param_3 + 0x18) >> 6)
                      | (*(byte *)(param_3 + 0x1a) & 1) << 10) * 0x7d >> 8);
    }
    else {
      bVar3 = *(byte *)(param_3 + 10);
      if (3 < DebugLevel) {
        printk("\t%s: MODE_OFDM RX\n","MT_ATEUpdateRxStatistic");
      }
      uVar10 = (uint)*(byte *)(param_3 + 0x19) << 2 | (uint)(*(byte *)(param_3 + 0x18) >> 6);
      uVar7 = (uint)*(byte *)(param_3 + 0x1a) << 10;
      uVar11 = (uint)(short)(ushort)(((uVar10 | uVar7) << 0x14) >> 0x14);
      if (0x7ff < uVar11) {
        uVar11 = (uVar10 | uVar7 & 0xfff) - 0x1000;
      }
      sVar9 = (short)((1 << ((bVar3 & 1) << 1 | bVar1 >> 7) + 1 & 0xfU) * 10000 * uVar11 * 2 >> 0x10
                     );
    }
    *(int *)(param_1 + 0xa3b70c) = (int)sVar9;
    *(uint *)(param_1 + 0xa3b7d4) = (uint)*(byte *)(param_3 + 0x14);
    *(uint *)(param_1 + 0xa3b7d8) = (uint)*(byte *)(param_3 + 0x15);
    *(uint *)(param_1 + 0xa3b7dc) = (uint)*(byte *)(param_3 + 0x16);
    *(uint *)(param_1 + 0xa3b7e0) = (uint)*(byte *)(param_3 + 0x17);
    AsicFeLossGet(param_1,uVar2,local_2c);
    puVar13 = (uint *)(param_1 + 0xa3b7e4);
    puVar8 = (uint *)(param_1 + 0xa3b7f4);
    *(uint *)(param_1 + 0xa3b784) = ((*(byte *)(param_3 + 0x14) >> 1) - 0x6e) + (local_2c[0] & 0xff)
    ;
    iVar4 = 0;
    *(uint *)(param_1 + 0xa3b788) =
         ((*(byte *)(param_3 + 0x15) >> 1) - 0x6e) + (local_2c[0] >> 8 & 0xff);
    *(uint *)(param_1 + 0xa3b78c) =
         ((*(byte *)(param_3 + 0x16) >> 1) - 0x6e) + (local_2c[0] >> 0x10 & 0xff);
    *(uint *)(param_1 + 0xa3b790) =
         ((*(byte *)(param_3 + 0x17) >> 1) - 0x6e) + (local_2c[0] >> 0x18);
    uVar10 = (uint)*(byte *)(param_3 + 0x12);
    *(uint *)(param_1 + 0xa3b7e4) = uVar10;
    uVar7 = (uint)*(byte *)(param_3 + 0x13);
    *(uint *)(param_1 + 0xa3b7f4) = uVar7;
    *(uint *)(param_1 + 0xa3b7e8) = (uint)*(byte *)(param_3 + 0x12);
    *(uint *)(param_1 + 0xa3b7f8) = (uint)*(byte *)(param_3 + 0x13);
    *(uint *)(param_1 + 0xa3b7ec) = (uint)*(byte *)(param_3 + 0x12);
    *(uint *)(param_1 + 0xa3b7fc) = (uint)*(byte *)(param_3 + 0x13);
    *(uint *)(param_1 + 0xa3b7f0) = (uint)*(byte *)(param_3 + 0x12);
    *(uint *)(param_1 + 0xa3b800) = (uint)*(byte *)(param_3 + 0x13);
    *(uint *)(param_1 + 0xa3b794) = (((uint)*(byte *)(param_3 + 0x1b) << 0x19) >> 0x1a) - 0x10;
    puVar12 = puVar8;
    puVar14 = puVar13;
    while( true ) {
      iVar4 = iVar4 + 1;
      if (0x7f < uVar10) {
        *puVar13 = uVar10 - 0x100;
      }
      if (0x7f < uVar7) {
        *puVar8 = uVar7 - 0x100;
      }
      iVar5 = DebugLevel;
      puVar13 = puVar13 + 1;
      puVar8 = puVar8 + 1;
      if (iVar4 == 4) break;
      puVar14 = puVar14 + 1;
      uVar10 = *puVar14;
      puVar12 = puVar12 + 1;
      uVar7 = *puVar12;
    }
    if (((*(byte *)(param_3 + 0xf) & 0x40) != 0) &&
       ((((*(byte *)(param_3 + 0xf) & 7) << 3 | *(byte *)(param_3 + 0xe) >> 5) + 0x3f & 0x3f) < 0x3e
       )) {
      *(int *)(param_1 + 0xa3b804) = *(int *)(param_1 + 0xa3b804) + 1;
      *(int *)(param_1 + 0xa789d8) = *(int *)(param_1 + 0xa789d8) + 1;
      if (3 < iVar5) {
        printk("%s: GroupId:%d get MU packet #:%d\n","MT_ATEUpdateRxStatistic",
               (*(byte *)(param_3 + 0xf) & 7) << 3 | *(byte *)(param_3 + 0xe) >> 5);
      }
    }
    *(uint *)(param_1 + 0xa3b808) = *(byte *)(param_3 + 8) & 0x7f;
    *(uint *)(param_1 + 0xa3b80c) = *(uint *)(param_3 + 0x28) & 0xffffff;
    *(uint *)(param_1 + 0xa3b810) = (uint)*(byte *)(param_3 + 0x12);
    uVar7 = *(uint *)(param_1 + 0xa39ffc);
    if ((uVar7 & 2) != 0) {
      MT_ATEInsertLog(param_1,param_3,2,0x24);
      uVar7 = *(uint *)(param_1 + 0xa39ffc);
    }
    if ((uVar7 & 0x20) == 0) {
      if (3 < DebugLevel) {
        printk("%s: EN_LOG:%x\n","MT_ATEUpdateRxStatistic");
      }
    }
    else {
      bVar1 = *(byte *)(param_3 + 0xf);
      if (0 < DebugLevel) {
        uVar7 = ((uint)*(byte *)(param_3 + 9) << 0x19) >> 0x1d;
        uVar6 = get_phymode_str(uVar7);
        printk("\t\tPhyMode=%d(%s)\n",uVar7,uVar6);
        if (0 < DebugLevel) {
          printk("\t\tMCS=%d\n",*(byte *)(param_3 + 8) & 0x7f);
          if (DebugLevel < 1) {
            return;
          }
          printk("\t\tBW=%d\n",(*(byte *)(param_3 + 10) & 1) << 1 | *(byte *)(param_3 + 9) >> 7);
          if (DebugLevel < 1) {
            return;
          }
          printk("\t\tSGI=%d\n",((uint)*(byte *)(param_3 + 10) << 0x1c) >> 0x1f);
          if (DebugLevel < 1) {
            return;
          }
          printk("\t\tSTBC=%d\n",(*(byte *)(param_3 + 9) & 1) << 1 | *(byte *)(param_3 + 8) >> 7);
        }
        if ((0 < DebugLevel) &&
           (printk("\t\tLDPC=%d\n",((uint)*(byte *)(param_3 + 9) << 0x1e) >> 0x1f), 0 < DebugLevel))
        {
          printk("\t\tNsts=%d\n",((uint)bVar1 << 0x1a) >> 0x1d);
        }
      }
    }
  }
  else if (param_2 == 2) {
    __memzero(param_1 + 0xa3b70c,0x148);
    *(undefined1 *)(param_1 + 0xa3b774) = 0xff;
    *(undefined1 *)(param_1 + 0xa3b775) = 0xff;
    *(undefined1 *)(param_1 + 0xa3b776) = 0xff;
    *(undefined1 *)(param_1 + 0xa3b777) = 0xff;
  }
  else if (param_2 == 3) {
    *(undefined4 *)(param_1 + 0xa3b758) = *(undefined4 *)(param_3 + 0x60);
  }
  return;
}

