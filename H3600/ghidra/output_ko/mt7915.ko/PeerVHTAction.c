// module: mt7915.ko
// function: PeerVHTAction @ 0xa1b5c
// size: 344 bytes
//

void PeerVHTAction(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_34 [4];
  undefined4 local_30;
  
  uVar3 = *(ushort *)(param_2 + 0x920);
  cVar1 = *(char *)(param_2 + 0x19);
  uVar4 = HcGetMaxStaNum();
  if (uVar3 < uVar4) {
    if (cVar1 == '\0') {
      if (0 < DebugLevel) {
        printk("ACTION - VHT Compressed Beamforming action---->\n");
      }
      hex_dump("VHT Compressed BF",param_2,*(undefined4 *)(param_2 + 0x908));
      return;
    }
    if (cVar1 == '\x02') {
      uVar4 = (uint)*(ushort *)(param_2 + 0x920);
      if (2 < DebugLevel) {
        printk("ACTION - Operating Mode Notification action---->\n");
      }
      hex_dump("OperatingModeNotify",param_2,*(undefined4 *)(param_2 + 0x908));
      if (2 < DebugLevel) {
        bVar2 = *(byte *)(param_2 + 0x1a);
        printk("\t RxNssType=%d, RxNss=%d, ChBW=%d\n",bVar2 >> 7,((uint)bVar2 << 0x19) >> 0x1d,
               bVar2 & 3);
      }
      if ((*(byte *)(param_2 + 0x1a) & 0x80) == 0) {
        iVar5 = uVar4 * 0x14c0;
        *(undefined1 *)(param_1 + iVar5 + 0xa2a40) = 1;
        *(undefined1 *)(param_1 + iVar5 + 0xa2a41) = *(undefined1 *)(param_2 + 0x1a);
      }
      __memzero(auStack_34,0x1c);
      local_30 = 1;
      RAParamUpdate(param_1,uVar4 * 0x14c0 + param_1 + 0xa1d20,auStack_34);
    }
  }
  return;
}

