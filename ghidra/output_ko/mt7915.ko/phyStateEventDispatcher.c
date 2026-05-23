// module: mt7915.ko
// function: phyStateEventDispatcher @ 0x1527e8
// size: 120 bytes
//

void phyStateEventDispatcher(int param_1,char *param_2)

{
  undefined1 *puVar1;
  
  if (*param_2 == '\x03') {
    puVar1 = *(undefined1 **)(param_1 + 0xc);
    *puVar1 = 3;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
    puVar1[3] = param_2[3];
    puVar1[4] = param_2[4];
    puVar1[5] = param_2[5];
    puVar1[6] = param_2[6];
    puVar1[7] = param_2[7];
    return;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: event:%d\n","phyStateEventDispatcher");
  return;
}

