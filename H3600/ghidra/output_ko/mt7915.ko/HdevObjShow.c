// module: mt7915.ko
// function: HdevObjShow @ 0xae1dc
// size: 296 bytes
//

void HdevObjShow(undefined1 *param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if ((((0 < DebugLevel) &&
       (printk("band_id\t: %d\n",**(undefined1 **)(*(int *)(param_1 + 8) + 4)), 0 < DebugLevel)) &&
      (printk("obj_id\t: %d\n",*param_1), 0 < DebugLevel)) &&
     (((printk("omac_id\t: %d\n",param_1[4]), 0 < DebugLevel &&
       (printk("wmmcap\t: %d\n",param_1[6]), 0 < DebugLevel)) &&
      (printk("wmm_idx\t: %d\n",param_1[5]), 0 < DebugLevel)))) {
    pcVar1 = "TXCMD";
    if (param_1[0x1e] == '\0') {
      pcVar1 = "TXD";
    }
    printk("tx_mode\t: %s\n",pcVar1);
  }
  puVar3 = (undefined4 *)(param_1 + 0xc);
  puVar2 = (undefined4 *)*puVar3;
  if (puVar3 == puVar2) {
    return;
  }
  do {
    if (0 < DebugLevel) {
      printk("\trept_id: %d, omac_id:%x\n",*(undefined1 *)(puVar2 + -1),
             *(undefined1 *)((int)puVar2 + -3));
    }
    puVar2 = (undefined4 *)*puVar2;
  } while (puVar3 != puVar2);
  return;
}

