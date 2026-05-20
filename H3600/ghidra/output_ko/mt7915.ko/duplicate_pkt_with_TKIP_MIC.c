// module: mt7915.ko
// function: duplicate_pkt_with_TKIP_MIC @ 0x24374c
// size: 180 bytes
//

int duplicate_pkt_with_TKIP_MIC
              (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((*(int *)(param_2 + 0x68) == 0) && (7 < *(int *)(param_2 + 0xc4) - *(int *)(param_2 + 0xc0)))
  {
    return param_2;
  }
  iVar2 = skb_copy_expand(param_2,*(int *)(param_2 + 0xcc) - *(int *)(param_2 + 200),8,0x20,param_4)
  ;
  __dev_kfree_skb_any(param_2,1);
  uVar1 = g_stWlanRadioStat._8_4_;
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  if (iVar2 != 0) {
    g_stWlanRadioStat._8_4_ = uVar1;
    return iVar2;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("Extend Tx.MIC for packet failed!, dropping packet!\n");
  return 0;
}

