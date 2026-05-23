// module: mt7915.ko
// function: RTMPGetLastTxRate @ 0xdc910
// size: 140 bytes
//

uint RTMPGetLastTxRate(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_4c [49];
  byte local_1b;
  byte local_19;
  char local_18;
  byte local_17;
  char local_16;
  byte local_15;
  byte local_14;
  
  MtCmdGetTxStatistic(param_1,4,0,*(undefined2 *)(param_2 + 0xe0),auStack_4c);
  uVar3 = local_1b & 7;
  uVar2 = (uint)(local_18 != '\0');
  uVar4 = uVar3;
  if (3 < uVar3) {
    uVar4 = (uint)local_14;
  }
  if (3 < uVar3) {
    uVar4 = uVar4 - 1;
  }
  uVar1 = uVar2 << 9;
  if (uVar3 < 4) {
    uVar4 = (uint)local_15;
  }
  else {
    uVar4 = uVar4 & 3;
    uVar2 = (uint)local_15;
  }
  if (3 < uVar3) {
    uVar4 = uVar2 + uVar4 * 0x10;
  }
  return uVar3 << 0xd | (local_17 & 3) << 7 | (uint)(local_16 != '\0') << 6 | uVar1 |
         (local_19 & 1) << 10 | uVar4 & 0x3f;
}

