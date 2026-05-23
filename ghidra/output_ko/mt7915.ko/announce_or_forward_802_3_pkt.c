// module: mt7915.ko
// function: announce_or_forward_802_3_pkt @ 0xc8b44
// size: 524 bytes
//

void announce_or_forward_802_3_pkt(int param_1,int param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  ushort uVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  
  if (param_3 == 0) {
    iVar8 = 0;
  }
  else {
    iVar7 = *(int *)(param_2 + 0xcc);
    iVar8 = *(int *)(param_3 + 0x904);
    if (CONCAT11(*(undefined1 *)(iVar7 + 0xc),*(undefined1 *)(iVar7 + 0xd)) == -0x7f00) {
      bVar1 = *(byte *)(iVar7 + 0xe);
      uVar4 = CONCAT11(bVar1,*(undefined1 *)(iVar7 + 0xf));
      iVar7 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
      uVar2 = *(ushort *)(param_3 + 0x8fa);
      if (uVar2 != 0 && ((uVar4 & 0xfff) != 0 && (uVar4 & 0xfff) != uVar2)) {
        sVar3 = *(short *)(param_3 + 0x900);
        bVar5 = (byte)(uVar2 >> 8);
        if (sVar3 == 3) {
          if (*(char *)(iVar7 + 0x228) == '\x01') {
            *(byte *)(*(int *)(param_2 + 0xcc) + 0xe) = bVar1 & 0xf0 | bVar5;
            *(char *)(*(int *)(param_2 + 0xcc) + 0xf) = (char)uVar2;
          }
        }
        else if (sVar3 == 4) {
          if (*(char *)(iVar7 + 0x228) == '\x01') {
            *(byte *)(*(int *)(param_2 + 0xcc) + 0xe) =
                 bVar1 & 0x10 | bVar5 | (byte)(((*(ushort *)(param_3 + 0x8fc) & 7) << 0xd) >> 8);
            *(char *)(*(int *)(param_2 + 0xcc) + 0xf) = (char)uVar2;
          }
        }
        else if (sVar3 == 1) {
          RTMPFreeNdisPacket(param_1,param_2,uVar2,param_4);
          return;
        }
      }
    }
    else if ((((*(short *)(param_3 + 0x8fa) != 0) && (*(ushort *)(param_3 + 0x900) - 3 < 2)) &&
             (iVar7 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
             *(char *)(iVar7 + 0x228) == '\x01')) &&
            (param_2 = RtmpOsVLANInsertTag(param_2,*(ushort *)(param_3 + 0x8fa) |
                                                   *(short *)(param_3 + 0x8fc) << 0xd), param_2 == 0
            )) {
      return;
    }
  }
  if ((*(code **)(iVar8 + 0x7c) != (code *)0x0) &&
     (cVar6 = (**(code **)(iVar8 + 0x7c))(param_1,param_3,param_2), cVar6 == '\x01')) {
    announce_802_3_packet(param_1,param_2,param_4,param_4);
    return;
  }
  if (3 < DebugLevel) {
    printk("%s(): No need to send to OS!\n","announce_or_forward_802_3_pkt");
  }
  *(int *)(param_1 + 0x9dce0) = *(int *)(param_1 + 0x9dce0) + 1;
  RTMPFreeNdisPacket(param_1,param_2,param_1 + 0x9d000,param_4);
  return;
}

