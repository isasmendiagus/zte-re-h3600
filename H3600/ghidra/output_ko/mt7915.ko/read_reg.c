// module: mt7915.ko
// function: read_reg @ 0x1c92b0
// size: 184 bytes
//

undefined4 read_reg(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    if (0 < DebugLevel) {
      printk("%s(): Not support for HIF_MT yet!\n","read_reg");
    }
  }
  else if (param_2 == 0x40) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_3 + 0x10000,param_4);
  }
  else if (param_2 == 0x41) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_3,param_4);
  }
  else if (0 < DebugLevel) {
    printk("illegal base = %x\n",param_2);
  }
  return 0;
}

