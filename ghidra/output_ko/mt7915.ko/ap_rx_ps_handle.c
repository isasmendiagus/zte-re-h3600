// module: mt7915.ko
// function: ap_rx_ps_handle @ 0x1d6ec
// size: 204 bytes
//

undefined4 ap_rx_ps_handle(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  
  uVar1 = *(ushort *)(param_3 + 0x4e);
  pcVar7 = *(char **)(param_3 + 0x1c);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar6 = (uint)uVar1 * 0x14c0 + param_1;
  iVar3 = RtmpPsIndicate(param_1,*(undefined4 *)(param_3 + 0x2c),*(undefined2 *)(iVar6 + 0xa1e00),
                         ((uint)(byte)pcVar7[1] << 0x1b) >> 0x1f,param_4);
  if (*(char *)(iVar2 + 0x154) != '\x02') {
    uVar5 = ((uint)(byte)pcVar7[1] << 0x1b) >> 0x1f;
    if (iVar3 != 1) {
      uVar5 = 0;
    }
    if (((uVar5 != 0) && ((*(uint *)(iVar6 + 0xa1dd4) & 0x800) != 0)) && (*pcVar7 < '\0')) {
      if ((*(uint *)(param_3 + 0x44) & 0x40000) == 0) {
        bVar4 = *(byte *)(*(int *)(param_3 + 0x3c) + 0x18);
      }
      else {
        bVar4 = *(byte *)(*(int *)(param_3 + 0x3c) + 0x20);
      }
      UAPSD_TriggerFrameHandle(param_1,(uint)uVar1 * 0x14c0 + param_1 + 0xa1d20,bVar4 & 7);
    }
  }
  return 1;
}

