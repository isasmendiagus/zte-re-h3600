// module: mt7915.ko
// function: he_mode_adjust @ 0x205690
// size: 332 bytes
//

void he_mode_adjust(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  byte bVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  byte local_28 [8];
  
  pbVar10 = local_28;
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_28[4] = 0;
  local_28[5] = 0;
  local_28[6] = 0;
  local_28[7] = 0;
  uVar4 = wlan_config_get_he_tx_nss();
  if ((*(ushort *)(param_1 + 0x18) & 0x1c0) != 0) {
    iVar9 = *(int *)(param_2 + 0x24);
    uVar7 = *(uint *)(param_2 + 100) & 0xffffffe7;
    *(uint *)(param_2 + 100) = uVar7;
    uVar2 = *(ushort *)(param_1 + 0x18);
    if ((uVar2 & 0x40) != 0) {
      *(uint *)(param_2 + 100) = uVar7 | 8;
      uVar2 = *(ushort *)(param_1 + 0x18);
    }
    if ((uVar2 & 0x80) != 0) {
      *(uint *)(param_2 + 100) = *(uint *)(param_2 + 100) | 0x10;
    }
    *(byte *)(param_2 + 0xbf) =
         *(byte *)(param_2 + 0xbf) & 0x1d | 0xa0 | (*(int *)(param_2 + 0x80) != 0) << 1;
    bVar3 = wlan_config_get_he_tx_stbc(param_1);
    pcVar5 = (char *)(param_2 + 0x38);
    uVar8 = 0;
    *(byte *)(param_2 + 0xbe) = *(byte *)(param_2 + 0xbe) | 0x40;
    *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0xfb | (bVar3 & iVar9 != 0) << 2;
    uVar7 = 2;
    do {
      pcVar5 = pcVar5 + 1;
      cVar1 = *pcVar5;
      uVar6 = uVar8 & 0xff;
      if (cVar1 == '\0') {
        *pbVar10 = 7;
      }
      else if (cVar1 == '\x01') {
        *pbVar10 = 9;
      }
      else {
        if (cVar1 != '\x02') break;
        *pbVar10 = 0xb;
      }
      uVar8 = uVar8 + 1;
      pbVar10 = pbVar10 + 1;
      uVar7 = uVar6;
    } while (uVar8 != 8);
    if (uVar4 <= uVar7) {
      uVar7 = uVar4;
    }
    *(byte *)(param_2 + 0xbe) =
         *(byte *)(param_2 + 0xbe) & 0xc0 | local_28[uVar7 & 0xff] & 0xf | (byte)((uVar7 & 3) << 4);
  }
  return;
}

