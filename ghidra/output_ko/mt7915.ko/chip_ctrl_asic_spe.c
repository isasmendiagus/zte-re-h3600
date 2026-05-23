// module: mt7915.ko
// function: chip_ctrl_asic_spe @ 0x189834
// size: 420 bytes
//

undefined4 chip_ctrl_asic_spe(int param_1,int param_2,int param_3,uint param_4)

{
  uint local_1c [2];
  
  param_2 = param_2 * 0x10000;
  local_1c[0] = 0;
  if (param_3 == 10) {
    param_2 = param_2 + -0x7df1be20;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2,local_1c);
    local_1c[0] = param_4 & 0x1f | local_1c[0] & 0xffffffe0;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    if (0 < DebugLevel) {
      printk("%s: Ste3.1:[SPE index][%x][0x%04x]\n","chip_ctrl_asic_spe",param_2,local_1c[0] & 0x1f)
      ;
    }
  }
  else if ((param_3 == 0xb) && ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0')) {
    param_2 = param_2 + -0x7df1df28;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2,local_1c);
    local_1c[0] = (param_4 & 0x1f) << 0x10 | local_1c[0] & 0xffe0ffff;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    if (0 < DebugLevel) {
      printk("%s: [SPE index][%x][0x%04x]\n","chip_ctrl_asic_spe",param_2,
             (local_1c[0] << 0xb) >> 0x1b);
    }
  }
  else {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1be20,local_1c);
    local_1c[0] = local_1c[0] & 0xffffffe0;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1be20);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1df28,local_1c);
    local_1c[0] = local_1c[0] & 0xffe0ffff;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),param_2 + -0x7df1df28);
  }
  return 0;
}

