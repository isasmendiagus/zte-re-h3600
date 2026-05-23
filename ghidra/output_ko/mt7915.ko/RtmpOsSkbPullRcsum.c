// module: mt7915.ko
// function: RtmpOsSkbPullRcsum @ 0x244dc8
// size: 132 bytes
//

void RtmpOsSkbPullRcsum(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  
  if (*(uint *)(param_1 + 100) < param_2) {
    return;
  }
  skb_pull();
  bVar2 = *(byte *)(param_1 + 0x75) & 6;
  if (bVar2 == 4) {
    uVar3 = *(uint *)(param_1 + 0x7c);
    uVar1 = csum_partial(*(undefined4 *)(param_1 + 0xcc),param_2,0,4,param_4);
    *(uint *)(param_1 + 0x7c) = (uint)CARRY4(~uVar1,uVar3) + ~uVar1 + uVar3;
    return;
  }
  if (bVar2 == 6) {
    if ((int)((uint)*(ushort *)(param_1 + 0x7c) +
             (*(int *)(param_1 + 200) - *(int *)(param_1 + 0xcc))) < 0) {
      *(byte *)(param_1 + 0x75) = *(byte *)(param_1 + 0x75) & 0xf9;
    }
    return;
  }
  return;
}

