// module: mt7915.ko
// function: indicate_amsdu_pkt @ 0xc928c
// size: 256 bytes
//

void indicate_amsdu_pkt(int param_1,int param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  short sVar4;
  undefined4 uVar5;
  
  iVar2 = FUN_000c53fc();
  if (iVar2 == 0) {
    if (1 < DebugLevel) {
      printk("%s:drop packet by PN mismatch!\n","indicate_amsdu_pkt");
    }
    *(int *)(param_1 + 0x9dce4) = *(int *)(param_1 + 0x9dce4) + 1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
    return;
  }
  uVar5 = *(undefined4 *)(param_2 + 0x38);
  uVar3 = get_netdev_from_bssid(param_1,param_3);
  RtmpOsPktInit(uVar5,uVar3,*(undefined4 *)(param_2 + 0x3c),*(undefined2 *)(param_2 + 0x40));
  *(char *)(*(int *)(param_2 + 0x38) + 0x2d) = (char)param_3;
  bVar1 = *(byte *)(*(int *)(param_2 + 0x18) + 6);
  if ((((bVar1 & 0x40) == 0) || ((*(byte *)(*(int *)(param_2 + 0x18) + 7) & 3) == 0)) ||
     ((bVar1 & 0x80) != 0)) {
    iVar2 = *(int *)(param_2 + 0x3c);
    sVar4 = *(short *)(param_2 + 0x40);
  }
  else {
    sVar4 = *(short *)(param_2 + 0x40) + -2;
    iVar2 = *(int *)(param_2 + 0x3c) + 2;
    *(int *)(param_2 + 0x3c) = iVar2;
    *(short *)(param_2 + 0x40) = sVar4;
  }
  deaggregate_amsdu_announce
            (param_1,*(undefined4 *)(param_2 + 0x38),iVar2,sVar4,*(undefined1 *)(param_2 + 0x4b));
  return;
}

