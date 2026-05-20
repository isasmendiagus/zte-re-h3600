// module: mt7915.ko
// function: RtmpVlanPktCopy @ 0xc5abc
// size: 80 bytes
//

int RtmpVlanPktCopy(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = *param_2;
  iVar2 = skb_copy(param_3,0x20);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x18) = uVar3;
    uVar1 = *(undefined1 *)(param_2 + 3);
    *(undefined2 *)(iVar2 + 0x42) = 0x120;
    *(undefined1 *)(iVar2 + 0x2d) = uVar1;
    RTMPFreeNdisPacket(param_1,param_3);
  }
  return iVar2;
}

