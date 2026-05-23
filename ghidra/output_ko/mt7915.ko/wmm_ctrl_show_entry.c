// module: mt7915.ko
// function: wmm_ctrl_show_entry @ 0xad7d8
// size: 312 bytes
//

void wmm_ctrl_show_entry(byte *param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = (uint)*param_1;
  if (uVar1 == 0) {
    return;
  }
  iVar3 = 0;
  iVar4 = 0;
  do {
    puVar2 = (undefined1 *)(*(int *)(param_1 + 4) + iVar3);
    if ((puVar2[4] != '\0') && (0 < DebugLevel)) {
      printk("\tEdcaIdx: %d,BandIdx: %d, RfCnt: %d, TXMODE: %d\n",puVar2[3],*puVar2,puVar2[1],
             puVar2[2]);
      if (0 < DebugLevel) {
        printk("\tAifs: %d/%d/%d/%d\n",puVar2[0xb],puVar2[0xc],puVar2[0xd],puVar2[0xe]);
        if (0 < DebugLevel) {
          printk("\tTxop: %d/%d/%d/%d\n",*(undefined2 *)(puVar2 + 0x18),
                 *(undefined2 *)(puVar2 + 0x1a),*(undefined2 *)(puVar2 + 0x1c),
                 *(undefined2 *)(puVar2 + 0x1e));
          if (0 < DebugLevel) {
            printk("\tCwmin: %d/%d/%d/%d\n",puVar2[0xf],puVar2[0x10],puVar2[0x11],puVar2[0x12]);
            if (0 < DebugLevel) {
              printk("\tCwmax: %d/%d/%d/%d\n",puVar2[0x13],puVar2[0x14],puVar2[0x15],puVar2[0x16]);
            }
          }
        }
      }
      uVar1 = (uint)*param_1;
    }
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + 0x28;
  } while (iVar4 < (int)uVar1);
  return;
}

