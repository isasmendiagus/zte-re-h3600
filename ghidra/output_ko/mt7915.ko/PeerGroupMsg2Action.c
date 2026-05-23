// module: mt7915.ko
// function: PeerGroupMsg2Action @ 0x1214a8
// size: 416 bytes
//

void PeerGroupMsg2Action(int param_1,int param_2,undefined4 *param_3,int param_4)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_21 [5];
  
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerGroupMsg2Action");
  }
  if ((*(byte *)(param_4 + 1) & 3) == 3) {
    iVar7 = 0x1e;
    iVar6 = 0x26;
  }
  else {
    iVar7 = 0x18;
    iVar6 = 0x20;
  }
  if ((*(char *)(param_3 + 0xe6) == '\n') &&
     (iVar7 = WpaMessageSanity(param_1,param_4 + iVar6,(*(int *)(param_4 + 0x908) + -8) - iVar7,6,
                               param_3,param_2,(int)param_3 + 0x1ce), iVar7 != 0)) {
    RTMPCancelTimer(param_3 + 0xe9,auStack_21);
    *(undefined1 *)((int)param_3 + 0x399) = 1;
    uVar1 = *(ushort *)(param_2 + 0xe0);
    uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar1 < uVar2) &&
       (((*(ushort *)(param_2 + 0xe0) < 0x120 &&
         (iVar7 = (uint)*(ushort *)(param_2 + 0xe0) * 0x620, param_1 + iVar7 != -0x2f6a0)) &&
        (*(char *)(param_1 + iVar7 + 0x2f762) == '\x01')))) {
      MWDSAPPeerEnable(param_1,param_2);
    }
    if (0 < DebugLevel) {
      uVar3 = GetAuthModeStr(*param_3);
      uVar4 = GetEncryModeStr(param_3[0x52]);
      uVar5 = GetEncryModeStr(param_3[0x8a]);
      printk("AP SETKEYS DONE - AKMMap=%s, PairwiseCipher=%s, GroupCipher=%s from %02x:%02x:%02x:%02x:%02x:%02x\n\n"
             ,uVar3,uVar4,uVar5,*(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
             *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
             *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
    }
  }
  return;
}

