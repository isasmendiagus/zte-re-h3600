// module: mt7915.ko
// function: PeerBeaconAndProbeRspSanity2 @ 0x110c5c
// size: 288 bytes
//

undefined4
PeerBeaconAndProbeRspSanity2
          (undefined4 param_1,int param_2,uint param_3,undefined4 param_4,char *param_5)

{
  byte *pbVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  
  uVar6 = 0;
  *param_5 = '\0';
  pcVar4 = (char *)(param_2 + 0x24);
  RTMPZeroMemory(param_4,0xe);
  uVar3 = (uint)*(byte *)(param_2 + 0x25);
  if (uVar3 + 0x26 <= param_3) {
    iVar5 = 0x24;
    do {
      cVar2 = *pcVar4;
      if (cVar2 == '<') {
        if (2 < DebugLevel) {
          printk("PeerBeaconAndProbeRspSanity - IE_EXT_CHANNEL_SWITCH_ANNOUNCEMENT\n");
        }
      }
      else if (cVar2 == 'J') {
        if (uVar3 == 0xe) {
          uVar6 = 1;
          RTMPMoveMemory(param_4,pcVar4 + 2);
        }
        else if (2 < DebugLevel) {
          printk("PeerBeaconAndProbeRspSanity - wrong IE_OVERLAPBSS_SCAN_PARM (len=%d)\n",uVar3);
        }
      }
      else if (cVar2 == ';') {
        if (uVar3 == 0) {
          if (2 < DebugLevel) {
            printk("PeerBeaconAndProbeRspSanity - wrong IE_SUPP_REG_CLASS (len=%d)\n",0);
          }
        }
        else {
          *param_5 = pcVar4[2];
        }
      }
      pbVar1 = (byte *)(pcVar4 + 1);
      pcVar4 = pcVar4 + *pbVar1 + 2;
      iVar5 = iVar5 + *pbVar1 + 2;
      uVar3 = (uint)(byte)pcVar4[1];
    } while (uVar3 + 2 + iVar5 <= param_3);
  }
  return uVar6;
}

