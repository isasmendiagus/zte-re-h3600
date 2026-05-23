// module: mt7915.ko
// function: HcShowBandInfo @ 0xa9328
// size: 432 bytes
//

void HcShowBandInfo(undefined4 param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined *local_f8;
  int local_f4;
  uint local_f0;
  undefined4 local_ec;
  undefined1 local_e8 [4];
  uint local_e4;
  
  local_f8 = (undefined *)0x0;
  local_f4 = 0;
  local_f0 = 0;
  local_ec = 0;
  os_zero_mem(local_e8,200);
  AsicGetDbdcCtrl(param_1,local_e8);
  if (0 < DebugLevel) {
    printk("\tDbdcEnable: %d\n",local_e8[0]);
  }
  if (local_e4 != 0) {
    puVar1 = local_e8;
    uVar2 = 0;
    uVar3 = local_e4;
    do {
      switch(puVar1[8]) {
      case 0:
        local_f8 = &DAT_004d4d57;
        break;
      case 1:
        local_f8 = (undefined *)0x544d474d;
        local_f4 = (uint)local_f4._1_3_ << 8;
        break;
      case 2:
        local_f8 = &DAT_00535342;
        break;
      case 3:
        local_f8 = (undefined *)0x5353424d;
        local_f4 = (uint)local_f4._1_3_ << 8;
LAB_000a9460:
        if (0 < DebugLevel) {
          printk("\t(%s,0-%d): Band %d\n",&local_f8,(byte)puVar1[9] + 1,puVar1[10]);
          uVar3 = local_e4;
        }
        goto LAB_000a93e0;
      case 4:
        local_f8 = (undefined *)0x45504552;
        local_f4._0_1_ = 'A';
        local_f4._1_1_ = 'T';
        local_f4._2_1_ = 'E';
        local_f4._3_1_ = 'R';
        local_f0 = local_f0 & 0xffffff00;
        break;
      case 5:
        local_f8 = (undefined *)CONCAT13(local_f8._3_1_,0x554d);
        break;
      case 6:
        local_f8 = (undefined *)CONCAT13(local_f8._3_1_,0x4642);
        break;
      case 7:
        local_f8 = &DAT_00415450;
        break;
      default:
        if (puVar1[8] == '\x03') goto LAB_000a9460;
      }
      if (0 < DebugLevel) {
        printk("\t(%s,%d): Band %d\n",&local_f8,puVar1[9],puVar1[10]);
        uVar3 = local_e4;
      }
LAB_000a93e0:
      uVar2 = uVar2 + 1;
      puVar1 = puVar1 + 3;
    } while (uVar2 < uVar3);
  }
  return;
}

