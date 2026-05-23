// module: mt7915.ko
// function: mtf_txpower_boost_info @ 0x1a14b0
// size: 788 bytes
//

undefined4 mtf_txpower_boost_info(undefined4 param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("CCK\n (M0)-(M1)-(M2)-(M3)\n");
    return 1;
  case 1:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("OFDM\n");
    goto joined_r0x001a1594;
  case 2:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("HT20\n");
joined_r0x001a1594:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("(M0)-(M1)-(M2)-(M3)-(M4)-(M5)-(M6)-(M7)\n");
    return 1;
  case 3:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("HT40\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("(M0)-(M1)-(M2)-(M3)-(M4)-(M5)-(M6)-(M7)-(M8)\n");
    return 1;
  case 4:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("VHT20\n");
    if (DebugLevel < 1) {
      return 1;
    }
    goto LAB_001a17e4;
  case 5:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("VHT40\n");
    break;
  case 6:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("VHT80\n");
    break;
  case 7:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("VHT160\n");
    break;
  case 8:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU26\n");
    break;
  case 9:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU52\n");
    break;
  case 10:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU106\n");
    break;
  case 0xb:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU242\n");
    break;
  case 0xc:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU484\n");
    break;
  case 0xd:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU996\n");
    break;
  case 0xe:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("RU996X2\n");
    break;
  default:
    return 0;
  }
  if (DebugLevel < 1) {
    return 1;
  }
LAB_001a17e4:
  printk("(M0)-(M1)-(M2)-(M3)-(M4)-(M5)-(M6)-(M7)-(M8)-(M9)-(M10)-(M11)\n");
  return 1;
}

