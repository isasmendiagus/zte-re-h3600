// module: mt7915.ko
// function: raSelectTxRateTable @ 0x1d9150
// size: 48 bytes
//

void raSelectTxRateTable(void)

{
  undefined4 *in_r3;
  
  *in_r3 = 0;
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:TX rate table is Null!\n","raSelectTxRateTable");
  return;
}

