// module: mt7915.ko
// function: MtfAsicGetTxTscByDriver @ 0x197008
// size: 300 bytes
//

void MtfAsicGetTxTscByDriver(int param_1,int param_2,undefined1 *param_3)

{
  undefined2 uVar1;
  int iVar2;
  uint local_dc;
  undefined1 auStack_d8 [188];
  int local_1c;
  
  uVar1 = *(undefined2 *)(param_2 + 0x9a0);
  local_dc = 0;
  __memzero(auStack_d8,0xc0);
  iVar2 = asic_get_wtbl_entry234(param_1,uVar1,auStack_d8);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Cannot found WTBL2/3/4 for WCID(%d)\n","MtfAsicGetTxTscByDriver",uVar1);
    }
  }
  else {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_1c + 0x24,&local_dc);
    *param_3 = (char)local_dc;
    param_3[1] = (char)(local_dc >> 8);
    param_3[2] = (char)(local_dc >> 0x10);
    param_3[3] = (char)(local_dc >> 0x18);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),local_1c + 0x28,&local_dc);
    iVar2 = DebugLevel;
    param_3[4] = (char)local_dc;
    param_3[5] = (char)(local_dc >> 8);
    if (2 < iVar2) {
      printk("%s(): WCID(%d) TxTsc 0x%02x-0x%02x-0x%02x-0x%02x-0x%02x-0x%02x\n",
             "MtfAsicGetTxTscByDriver",uVar1,*param_3,param_3[1],param_3[2],param_3[3],
             local_dc & 0xff,local_dc >> 8 & 0xff);
    }
  }
  return;
}

