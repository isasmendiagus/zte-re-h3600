// module: mt7915.ko
// function: ap_rx_peer_response_allowed @ 0x4b2ec
// size: 224 bytes
//

undefined1 ap_rx_peer_response_allowed(int param_1,undefined4 param_2,int param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined1 uStack_23;
  char local_22;
  byte local_1d;
  
  uVar2 = *(ushort *)(param_4 + 0x920);
  bVar1 = *(byte *)(param_4 + 0x91f);
  uVar3 = HcGetMaxStaNum();
  if (uVar2 < uVar3) {
    iVar4 = MacTableLookup(param_1,param_3);
    if (iVar4 == 0) {
      return 0;
    }
    if (*(int *)(iVar4 + 8) == 0) {
      return 0;
    }
    bVar1 = *(byte *)(*(int *)(iVar4 + 8) + 0x1a);
  }
  if ((*(byte *)(param_3 + 0x30) != bVar1) && (*(char *)(param_1 + 0x795941) == '\0')) {
    return 0;
  }
  hc_radio_query_by_channel(param_1,bVar1,&uStack_23);
  if (((bVar1 < 0xf) && (local_22 == '\x01')) && (*(char *)(param_1 + 0x795941) == '\0')) {
    if ((local_1d + 2 != (uint)*(byte *)(param_3 + 0x30)) &&
       ((uint)*(byte *)(param_3 + 0x30) != local_1d - 2)) {
      return 0;
    }
  }
  return 1;
}

