// module: mt7915.ko
// function: show_tpinfo_host @ 0xe2244
// size: 620 bytes
//

void show_tpinfo_host(int param_1,undefined4 param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  
  switch(param_2) {
  case 0:
    if (((0 < DebugLevel) && (printk("\t0: help\n"), 0 < DebugLevel)) &&
       ((printk("\t1: tx free notify host info\n"), 0 < DebugLevel &&
        (printk("\t2: wfdma info\n"), 0 < DebugLevel)))) {
      printk("\t3: counter info\n");
      return;
    }
    break;
  case 1:
    pbVar1 = (byte *)hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
    if (param_3 == 2) {
      iVar3 = 3;
    }
    else {
      iVar3 = 1;
    }
    if (*pbVar1 != 0) {
      uVar4 = 0;
      do {
        if (iVar3 <= DebugLevel) {
          printk("\tTX Token Que Index = %d\n",uVar4);
        }
        if (DebugLevel < 1) {
LAB_000e22fc:
          if (iVar3 <= DebugLevel) {
            printk("\tTX Token Total Deq Number = %d\n",
                   *(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x44));
            if (iVar3 <= DebugLevel) {
              printk("\tTX Token Total Back Number = %d\n",
                     *(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x48));
            }
          }
        }
        else {
          printk("\tTX Token Full Count = %d\n",*(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x38));
          if (DebugLevel < iVar3) goto LAB_000e22fc;
          printk("\tTX FreeToken Number = %d\n",*(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x3c));
          if (((iVar3 <= DebugLevel) &&
              (printk("\tTX FreeToken LowMark = %d\n",*(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x2c))
              , iVar3 <= DebugLevel)) &&
             (printk("\tTX FreeToken HighMark = %d\n",*(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x30))
             , iVar3 <= DebugLevel)) {
            printk("\tTX Token Total Enq Number = %d\n",
                   *(undefined4 *)(pbVar1 + uVar4 * 0xa8 + 0x40));
            goto LAB_000e22fc;
          }
        }
        pbVar2 = pbVar1 + uVar4 * 0xa8;
        do {
          if (iVar3 <= DebugLevel) {
            printk("\tTX Free Notify deep_boundary(%d) = %d\n",*(undefined2 *)(pbVar2 + 0x4c),
                   *(undefined4 *)(pbVar2 + 0x50));
          }
          pbVar2 = pbVar2 + 8;
        } while (pbVar2 != pbVar1 + uVar4 * 0xa8 + 0x60);
        uVar4 = uVar4 + 1 & 0xff;
        if (*pbVar1 <= uVar4) {
          return;
        }
      } while( true );
    }
    break;
  case 2:
    FUN_000d64d4(param_1,param_3);
    return;
  case 3:
    FUN_000d65e8(param_1,param_3);
    return;
  }
  return;
}

