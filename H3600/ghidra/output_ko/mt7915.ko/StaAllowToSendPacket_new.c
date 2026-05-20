// module: mt7915.ko
// function: StaAllowToSendPacket_new @ 0x6836c
// size: 164 bytes
//

undefined4 StaAllowToSendPacket_new(int param_1,int param_2,int param_3,undefined2 *param_4)

{
  int iVar1;
  
  if ("hif_set_WPDMA"[param_1 + 0xc] == '\x01') {
    return 0;
  }
  if ((**(byte **)(param_3 + 0xcc) & 1) != 0) {
    *param_4 = *(undefined2 *)(param_2 + 0x10);
    return 1;
  }
  iVar1 = MacTableLookup2(param_1,*(byte **)(param_3 + 0xcc),param_2);
  if (iVar1 != 0) {
    if (param_2 != *(int *)(iVar1 + 8)) {
      printk(&_LC8,0x40);
      dump_stack();
    }
    if (*(int *)(iVar1 + 0xfc) == 2) {
      *param_4 = *(undefined2 *)(iVar1 + 0xe0);
      return 1;
    }
  }
  return 0;
}

