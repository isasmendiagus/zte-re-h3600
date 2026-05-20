// module: mt7915.ko
// function: disable_tx_burst @ 0xc7b88
// size: 164 bytes
//

void disable_tx_burst(int param_1,int param_2,undefined4 param_3,undefined4 param_4,
                     undefined2 param_5)

{
  int iVar1;
  
  if ((param_2 != 0) && (iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0)), iVar1 == 2))
  {
    if (2 < DebugLevel) {
      printk("%s, prio=%d, level=0x%x, <caller: %pS>\n","disable_tx_burst",param_4,param_5);
    }
    HW_SET_TX_BURST(param_1,param_2,param_3,param_4,param_5,0);
    return;
  }
  return;
}

