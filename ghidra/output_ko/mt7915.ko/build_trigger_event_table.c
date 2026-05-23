// module: mt7915.ko
// function: build_trigger_event_table @ 0x144cf8
// size: 264 bytes
//

undefined4 build_trigger_event_table(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  undefined1 local_27;
  undefined1 auStack_26 [18];
  
  uVar1 = HcGetBandByWdev(*(undefined4 *)(param_2 + 0x92c));
  pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  if (((*(char *)(param_1 + 0x79564e) == '\x01') &&
      (uVar3 = (uint)*(byte *)(param_3 + 0x30), uVar3 - 1 < 0xe)) && (pbVar2[0x49c] != 0)) {
    if (*pbVar2 == uVar3) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0;
      pbVar5 = pbVar2;
      do {
        uVar4 = uVar4 + 1;
        if (uVar4 == pbVar2[0x49c]) {
          return 1;
        }
        pbVar5 = pbVar5 + 0x14;
      } while (*pbVar5 != uVar3);
    }
    if (pbVar2[uVar4 * 0x14 + 1] == 1) {
      PeerBeaconAndProbeRspSanity2
                (param_1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_26,&local_27);
      TriEventTableSetEntry
                (param_1,param_1 + 0x7956b8,param_3 + 6,param_3 + 0xdc,*(uint *)(param_3 + 0xa8) & 1
                 ,local_27,*(undefined1 *)(param_3 + 0x30));
    }
  }
  return 1;
}

