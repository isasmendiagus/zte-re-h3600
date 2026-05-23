// module: mt7915.ko
// function: txbf_clear_oui @ 0x84f68
// size: 64 bytes
//

void txbf_clear_oui(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (2 < DebugLevel) {
    printk("%s()\n","txbf_clear_oui",param_3,DebugLevel,param_4);
  }
  g_u4TxBfOui = 0;
  return;
}

