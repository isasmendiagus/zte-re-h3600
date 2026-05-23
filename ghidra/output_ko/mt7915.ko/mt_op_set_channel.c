// module: mt7915.ko
// function: mt_op_set_channel @ 0x257948
// size: 176 bytes
//

undefined4 mt_op_set_channel(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    iVar1 = net_ad_update_wdev(param_2,param_1,param_3);
    if (iVar1 == 0) {
      printk("%s: band_idx: %d, bw: %d, ch:%d","mt_op_set_channel",param_2,
             *(undefined1 *)(param_3 + 0xc56),*(undefined1 *)(param_3 + 0xc50));
      printk("ctrl_ch: %d, cntl_ch2: %d, pri_sel: %d\n",*(undefined1 *)(param_3 + 0xc52),
             *(undefined1 *)(param_3 + 0xc63),*(undefined1 *)(param_3 + 0xc53));
      uVar2 = 0;
    }
    else {
      printk("%s: set channel fail, ","mt_op_set_channel");
      printk("control channel: %d|%d\n",*(undefined1 *)(param_3 + 0xc52),
             *(undefined1 *)(param_3 + 0xc50));
      uVar2 = 0x605;
    }
  }
  return uVar2;
}

