// module: mt7915.ko
// function: update_peer_he_muedca_ies @ 0x2053b0
// size: 188 bytes
//

undefined4 update_peer_he_muedca_ies(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  
  iVar1 = CompareMUEdcaParameters
                    ((undefined4 *)(param_2 + 0xc3),param_1,*(undefined4 *)(param_2 + 0xcb),
                     *(undefined1 *)(param_2 + 0xcf),*(undefined4 *)(param_2 + 0xc3),
                     *(undefined4 *)(param_2 + 199),*(undefined4 *)(param_2 + 0xcb),
                     *(undefined1 *)(param_2 + 0xcf));
  if (iVar1 == 0) {
    *(byte *)(param_1 + 0x1478) = *(byte *)(param_2 + 0xc3) & 0xf;
    pbVar3 = (byte *)(param_1 + 0x1479);
    iVar1 = param_2;
    do {
      iVar4 = iVar1 + 3;
      *pbVar3 = *(byte *)(iVar1 + 0xc5) & 0xf;
      pbVar3[1] = *(byte *)(iVar1 + 0xc5) >> 4;
      pbVar3[2] = *(byte *)(iVar1 + 0xc4) & 0xf;
      pbVar3[3] = (byte)(((uint)*(byte *)(iVar1 + 0xc4) << 0x1b) >> 0x1f);
      pbVar3[4] = *(byte *)(iVar1 + 0xc6);
      pbVar3 = pbVar3 + 8;
      iVar1 = iVar4;
    } while (iVar4 != param_2 + 0xc);
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

