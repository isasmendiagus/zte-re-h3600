// module: mt7915.ko
// function: PeerDeauthSanity @ 0x1120c4
// size: 96 bytes
//

undefined4
PeerDeauthSanity(undefined4 param_1,int param_2,undefined4 param_3,undefined4 *param_4,
                undefined4 *param_5,undefined4 *param_6,void *param_7)

{
  *param_4 = *(undefined4 *)(param_2 + 4);
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 8);
  *param_5 = *(undefined4 *)(param_2 + 10);
  *(undefined2 *)(param_5 + 1) = *(undefined2 *)(param_2 + 0xe);
  *param_6 = *(undefined4 *)(param_2 + 0x10);
  *(undefined2 *)(param_6 + 1) = *(undefined2 *)(param_2 + 0x14);
  memmove(param_7,(void *)(param_2 + 0x18),2);
  return 1;
}

