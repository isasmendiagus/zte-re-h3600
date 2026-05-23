// module: mt7915.ko
// function: PeerAuthSanity @ 0x112124
// size: 272 bytes
//

undefined4
PeerAuthSanity(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4,short *param_5,
              ushort *param_6,void *param_7,void *param_8)

{
  uint uVar1;
  
  *param_4 = *(undefined4 *)(param_2 + 10);
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 0xe);
  memmove(param_5,(void *)(param_2 + 0x18),2);
  memmove(param_6,(void *)(param_2 + 0x1a),2);
  memmove(param_7,(void *)(param_2 + 0x1c),2);
  if (*param_5 == 0) {
    if (*param_6 - 1 < 2) {
      return 1;
    }
  }
  else {
    if (*param_5 != 1) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("PeerAuthSanity fail - wrong algorithm\n");
      return 0;
    }
    uVar1 = (uint)*param_6;
    if (uVar1 == 1 || uVar1 == 4) {
      return 1;
    }
    if (uVar1 - 2 < 2) {
      memmove(param_8,(void *)(param_2 + 0x20),0x80);
      return 1;
    }
  }
  if (DebugLevel < 3) {
    return 0;
  }
  printk("PeerAuthSanity fail - wrong Seg#\n");
  return 0;
}

