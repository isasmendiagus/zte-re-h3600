// module: mt7915.ko
// function: txbf_set_oui @ 0x84f1c
// size: 72 bytes
//

void txbf_set_oui(uint param_1)

{
  g_u4TxBfOui = g_u4TxBfOui | 1 << (param_1 & 0xff);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s() u1BfOui:%u, g_u4TxBfOui: %u\n","txbf_set_oui",param_1);
  return;
}

