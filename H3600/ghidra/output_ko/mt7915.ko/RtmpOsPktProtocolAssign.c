// module: mt7915.ko
// function: RtmpOsPktProtocolAssign @ 0x244cc0
// size: 24 bytes
//

void RtmpOsPktProtocolAssign(int param_1)

{
  undefined2 uVar1;
  
  uVar1 = eth_type_trans(param_1,*(undefined4 *)(param_1 + 0x18));
  *(undefined2 *)(param_1 + 0xa4) = uVar1;
  return;
}

