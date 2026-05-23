// module: mt7915.ko
// function: chip_get_tx_mibinfo @ 0x189730
// size: 244 bytes
//

uint chip_get_tx_mibinfo(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  uint local_c [2];
  
  param_2 = param_2 * 0x10000;
  local_c[0] = 0;
  if (10 < param_3) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df12f40,local_c);
    return local_c[0];
  }
  switch(param_4) {
  case 0:
    uVar1 = 0xd0a0;
    break;
  case 1:
    uVar1 = 0xd0a0;
    goto LAB_0018979c;
  case 2:
    uVar1 = 0xd0a4;
    break;
  case 3:
    uVar1 = 0xd0a4;
LAB_0018979c:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + (uVar1 | 0x820e0000),local_c);
    return local_c[0] >> 0x10;
  default:
    if (-1 < DebugLevel) {
      printk("Unknown DBW:%d\n",param_4);
      return local_c[0];
    }
    return 0;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + (uVar1 | 0x820e0000),local_c);
  return local_c[0] & 0xffff;
}

