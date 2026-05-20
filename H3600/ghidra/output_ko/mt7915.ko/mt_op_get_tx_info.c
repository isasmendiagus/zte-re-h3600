// module: mt7915.ko
// function: mt_op_get_tx_info @ 0x2580ac
// size: 160 bytes
//

undefined4 mt_op_get_tx_info(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined4 uVar5;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar5 = 0x503;
  }
  else {
    iVar2 = hc_get_chip_dbg(*(undefined4 *)(iVar1 + 0xa797a0));
    if (iVar2 == 0) {
      uVar5 = 0x500;
    }
    else {
      bVar4 = *(byte *)(param_2 + 0xc57);
      if (4 < bVar4) {
        bVar4 = 3;
      }
      iVar3 = (**(code **)(iVar2 + 0xa4))(iVar1,0,*(undefined1 *)(param_2 + 0xc55),bVar4,param_4);
      *(int *)(param_2 + 0xc3c) = *(int *)(param_2 + 0xc3c) + iVar3;
      bVar4 = *(byte *)(param_3 + 0xc57);
      if (4 < bVar4) {
        bVar4 = 3;
      }
      iVar1 = (**(code **)(iVar2 + 0xa4))(iVar1,1,*(undefined1 *)(param_3 + 0xc55),bVar4);
      uVar5 = 0;
      *(int *)(param_3 + 0xc3c) = *(int *)(param_3 + 0xc3c) + iVar1;
    }
  }
  return uVar5;
}

