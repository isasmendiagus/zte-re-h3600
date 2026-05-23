// module: mt7915.ko
// function: sta_legacy_tx @ 0x53ee0
// size: 216 bytes
//

int sta_legacy_tx(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_2 + 0x904);
  iVar1 = fill_tx_blk();
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x9db94) + 1;
    *(int *)(param_1 + 0x9db94) = iVar1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc),param_1 + 0x9d000,iVar1,param_4);
    return 1;
  }
  if (*(char *)(param_3 + 5) == '\x01') {
    uVar2 = *(uint *)(param_1 + 0xa39c08);
    *(uint *)(param_1 + 0xa39c08) = uVar2 + 1;
    *(uint *)(param_1 + 0xa39c0c) = *(int *)(param_1 + 0xa39c0c) + (uint)(0xfffffffe < uVar2);
  }
  if (*(byte *)(param_3 + 0x62) < *(byte *)(param_1 + 0x794cd3)) {
    *(byte *)(param_3 + 0x62) = *(byte *)(param_1 + 0x794cd3);
  }
  if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
    pcVar3 = *(code **)(iVar4 + 0x40);
  }
  else {
    pcVar3 = *(code **)(iVar4 + 0x44);
  }
  (*pcVar3)(param_1,param_2,param_3);
  iVar1 = asic_hw_tx(param_1,param_3);
  if (iVar1 == 0) {
    *(int *)(param_1 + 0xa78a18) = *(int *)(param_3 + 0x28) + *(int *)(param_1 + 0xa78a18);
    return 0;
  }
  return iVar1;
}

