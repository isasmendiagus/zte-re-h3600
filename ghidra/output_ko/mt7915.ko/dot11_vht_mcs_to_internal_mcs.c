// module: mt7915.ko
// function: dot11_vht_mcs_to_internal_mcs @ 0x202c38
// size: 484 bytes
//

undefined4
dot11_vht_mcs_to_internal_mcs(undefined4 param_1,undefined4 param_2,int param_3,ushort *param_4)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  
  uVar4 = ((uint)*param_4 << 0x17) >> 0x1e;
  if (uVar4 - 1 < 3) {
    uVar4 = (uint)(byte)"vht_mode_adjust"[uVar4 + 0xf];
  }
  else {
    uVar4 = 0;
  }
  bVar3 = *(byte *)(param_3 + 4);
  if ((bVar3 & 3) != 3) {
    iVar1 = wlan_operate_get_tx_stream(param_2);
    if (iVar1 != 0) {
      if ((byte)(&DAT_002a1560)[*(byte *)(param_3 + 4) & 3] < (byte)(&DAT_002a1550)[uVar4]) {
        *(byte *)param_4 =
             (byte)*param_4 & 0xc0 | (&DAT_002a1560)[*(byte *)(param_3 + 4) & 3] & 0x3f;
        bVar3 = *(byte *)(param_3 + 4);
        goto LAB_00202cc4;
      }
      *(byte *)param_4 = (byte)*param_4 & 0xc0 | (&DAT_002a1550)[uVar4] & 0x3f;
    }
    bVar3 = *(byte *)(param_3 + 4);
  }
LAB_00202cc4:
  if ((bVar3 & 0xc) != 0xc) {
    uVar2 = wlan_operate_get_tx_stream(param_2);
    if (1 < uVar2) {
      if ((byte)(&DAT_002a1560)[((uint)*(byte *)(param_3 + 4) << 0x1c) >> 0x1e] <
          (byte)(&DAT_002a1551)[uVar4]) {
        *(byte *)param_4 =
             (byte)*param_4 & 0xc0 |
             (&DAT_002a1560)[((uint)*(byte *)(param_3 + 4) << 0x1c) >> 0x1e] & 0x3f | 0x10;
        bVar3 = *(byte *)(param_3 + 4);
        goto LAB_00202d1c;
      }
      *(byte *)param_4 = (byte)*param_4 & 0xc0 | (&DAT_002a1551)[uVar4] & 0x3f | 0x10;
    }
    bVar3 = *(byte *)(param_3 + 4);
  }
LAB_00202d1c:
  if ((bVar3 & 0x30) != 0x30) {
    uVar2 = wlan_operate_get_tx_stream(param_2);
    if (2 < uVar2) {
      if ((byte)(&DAT_002a1560)[((uint)*(byte *)(param_3 + 4) << 0x1a) >> 0x1e] <
          (byte)(&DAT_002a1552)[uVar4]) {
        *(byte *)param_4 =
             (byte)*param_4 & 0xc0 |
             (&DAT_002a1560)[((uint)*(byte *)(param_3 + 4) << 0x1a) >> 0x1e] & 0x3f | 0x20;
        bVar3 = *(byte *)(param_3 + 4);
        goto LAB_00202d74;
      }
      *(byte *)param_4 = (byte)*param_4 & 0xc0 | (&DAT_002a1552)[uVar4] & 0x3f | 0x20;
    }
    bVar3 = *(byte *)(param_3 + 4);
  }
LAB_00202d74:
  if (((bVar3 & 0xc0) != 0xc0) && (uVar2 = wlan_operate_get_tx_stream(param_2), 3 < uVar2)) {
    if ((byte)(&DAT_002a1560)[*(byte *)(param_3 + 4) >> 6] < (byte)(&DAT_002a1553)[uVar4]) {
      *(byte *)param_4 =
           (byte)*param_4 & 0xc0 | (&DAT_002a1560)[*(byte *)(param_3 + 4) >> 6] & 0x3f | 0x30;
    }
    else {
      *(byte *)param_4 = (byte)*param_4 & 0xc0 | (&DAT_002a1553)[uVar4] & 0x3f | 0x30;
    }
  }
  return 1;
}

