// module: mt7915.ko
// function: chip_show_tmac_info @ 0x18aa64
// size: 1268 bytes
//

undefined4 chip_show_tmac_info(int param_1)

{
  int iVar1;
  undefined4 local_1c;
  
  iVar1 = *(int *)(param_1 + 0x4328);
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4000,&local_1c);
  if (DebugLevel < 1) goto LAB_0018aaa4;
  printk("TX Stream = %d\n",((local_1c << 0xe) >> 0x1e) + 1);
  if (DebugLevel < 1) {
LAB_0018ac84:
    if (DebugLevel < 1) goto LAB_0018aaa4;
    printk("TXOP Burst Stop = %d\n",(local_1c << 5) >> 0x1f);
    if (DebugLevel < 1) goto LAB_0018aaa4;
    printk("RDG Mode = %d\n",(local_1c << 4) >> 0x1f);
  }
  else {
    printk("TX RIFS Enable = %d\n",(local_1c << 9) >> 0x1f);
    if (DebugLevel < 1) goto LAB_0018aaa4;
    printk("RX RIFS Mode = %d\n",(local_1c << 8) >> 0x1f);
    if (0 < DebugLevel) {
      printk("TXOP TBTT Control = %d\n",(local_1c << 7) >> 0x1f);
      if (DebugLevel < 1) goto LAB_0018aaa4;
      printk("TXOP TBTT Stop Control = %d\n",(local_1c << 6) >> 0x1f);
      goto LAB_0018ac84;
    }
  }
  if (0 < DebugLevel) {
    printk("RDG Responser Enable = %d\n",(local_1c << 2) >> 0x1f);
    if (0 < DebugLevel) {
      printk("Smoothing = %d\n",local_1c >> 0x1f);
    }
  }
LAB_0018aaa4:
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4004,&local_1c);
  if (0 < DebugLevel) {
    printk("AP Power Save RXPE Off Time(unit 2us) = %d\n",(local_1c << 0x17) >> 0x18);
    if (0 < DebugLevel) {
      printk("AP Power Save RXPE On Time(unit 2us) = %d\n",(local_1c & 0x3f) << 10);
      if (0 < DebugLevel) {
        printk("AP Power Save Halt Time (unit 32us) = %d\n",(local_1c << 6) >> 0x16);
        if (0 < DebugLevel) {
          printk("AP Power Enable = %d\n",(local_1c << 3) >> 0x1f);
        }
      }
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4014,&local_1c);
  if (0 < DebugLevel) {
    printk("AC0 TXOP = 0x%x (unit: 32us)\n",local_1c & 0xffff);
    if (0 < DebugLevel) {
      printk("AC1 TXOP = 0x%x (unit: 32us)\n",local_1c._2_2_);
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4010,&local_1c);
  if (0 < DebugLevel) {
    printk("AC2 TXOP = 0x%x (unit: 32us)\n",local_1c & 0xffff);
    if (0 < DebugLevel) {
      printk("AC3 TXOP = 0x%x (unit: 32us)\n",local_1c._2_2_);
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f401c,&local_1c);
  if (0 < DebugLevel) {
    printk("AC10 TXOP = 0x%x (unit: 32us)\n",local_1c & 0xffff);
    if (0 < DebugLevel) {
      printk("AC11 TXOP = 0x%x (unit: 32us)\n",local_1c._2_2_);
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4018,&local_1c);
  if (0 < DebugLevel) {
    printk("AC12 TXOP = 0x%x (unit: 32us)\n",local_1c & 0xffff);
    if (0 < DebugLevel) {
      printk("AC13 TXOP = 0x%x (unit: 32us)\n",local_1c._2_2_);
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f40a4,&local_1c);
  if (0 < DebugLevel) {
    printk("EIFS Time, Band0 (unit: 1us) = %d\n",local_1c & 0x1ff);
    if (0 < DebugLevel) {
      printk("RIFS Time, Band0 (unit: 1us) = %d\n",(local_1c << 0x11) >> 0x1b);
      if (0 < DebugLevel) {
        printk("SIFS Time, Band0 (unit: 1us) = %d\n",(local_1c << 9) >> 0x19);
        if (0 < DebugLevel) {
          printk("SLOT Time, Band0 (unit: 1us) = %d\n",(local_1c << 1) >> 0x19);
        }
      }
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4074,&local_1c);
  if (0 < DebugLevel) {
    printk("EIFS Time, Band1 (unit: 1us) = %d\n",local_1c & 0x1ff);
    if (0 < DebugLevel) {
      printk("RIFS Time, Band1 (unit: 1us) = %d\n",(local_1c << 0x11) >> 0x1b);
      if (0 < DebugLevel) {
        printk("SIFS Time, Band1 (unit: 1us) = %d\n",(local_1c << 9) >> 0x19);
        if (0 < DebugLevel) {
          printk("SLOT Time, Band1 (unit: 1us) = %d\n",(local_1c << 1) >> 0x19);
        }
      }
    }
  }
  mac_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0x820f4098,&local_1c);
  if (0 < DebugLevel) {
    printk("Aggregation Timeout (unit: 50ns) = 0x%x\n",local_1c._2_1_);
  }
  return 0;
}

