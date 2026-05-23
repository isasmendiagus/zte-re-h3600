// module: mt7915.ko
// function: mtf_show_mac_info @ 0x19ee30
// size: 48 bytes
//

void mtf_show_mac_info(int param_1)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("MAC[Ver:Rev/ID=0x%08x : 0x%08x]\n",*(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8)
         ,*(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc));
  return;
}

