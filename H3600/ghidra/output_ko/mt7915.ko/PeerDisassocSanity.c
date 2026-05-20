// module: mt7915.ko
// function: PeerDisassocSanity @ 0x11234c
// size: 48 bytes
//

undefined4
PeerDisassocSanity(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4,
                  void *param_5)

{
  *param_4 = *(undefined4 *)(param_2 + 10);
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 0xe);
  memmove(param_5,(void *)(param_2 + 0x18),2);
  return 1;
}

