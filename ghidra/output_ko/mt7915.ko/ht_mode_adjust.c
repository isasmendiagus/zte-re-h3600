// module: mt7915.ko
// function: ht_mode_adjust @ 0x1378b4
// size: 368 bytes
//

undefined4 ht_mode_adjust(int param_1,int param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  
  iVar7 = *(int *)(param_2 + 8);
  if (iVar7 == 0) {
    uVar6 = 0;
  }
  else {
    wlan_operate_get_addht(iVar7);
    pbVar3 = (byte *)wlan_operate_get_ht_cap(iVar7);
    iVar4 = HcGetBandByWdev(iVar7);
    if (((*param_3 & 0x10) == 0) || ((*pbVar3 & 0x10) == 0)) {
      *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | 0x40;
      *(undefined1 *)(param_1 + iVar4 + 0x285943) = 1;
    }
    else {
      *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | 0x60;
    }
    bVar1 = *param_3;
    uVar5 = wlan_operate_get_ht_bw(iVar7);
    uVar5 = uVar5 & ((uint)bVar1 << 0x1e) >> 0x1f;
    *(ushort *)(param_2 + 0xbe) = *(ushort *)(param_2 + 0xbe) & 0xfe7f | (ushort)(uVar5 << 7);
    if (uVar5 == 1) {
      *(byte *)(param_2 + 0xbf) =
           *(byte *)(param_2 + 0xbf) & 0xfd |
           (byte)((((uint)*pbVar3 << 0x19) >> 0x1f & (uint)(*param_3 >> 6)) << 1);
    }
    else {
      *(byte *)(param_2 + 0xbf) =
           *(byte *)(param_2 + 0xbf) & 0xfd |
           (byte)((((uint)*pbVar3 << 0x1a) >> 0x1f & (uint)(*param_3 >> 5)) << 1);
      *(undefined1 *)(param_1 + 0x285945) = 1;
    }
    bVar1 = *(byte *)(param_2 + 0xbf);
    bVar2 = param_3[1] & *pbVar3 >> 7;
    uVar5 = bVar1 & 0xfffffffb;
    *(byte *)(param_2 + 0xbf) = (byte)uVar5 | bVar2 << 2;
    if (DebugLevel < 4) {
      uVar6 = 1;
    }
    else {
      printk("%s(), MODE = %d, BW = %d, SGI = %d, STBC = %d\n","ht_mode_adjust",bVar1 >> 5,
             ((uint)*(ushort *)(param_2 + 0xbe) << 0x17) >> 0x1e,(uVar5 << 0x1e) >> 0x1f,bVar2);
      uVar6 = 1;
    }
  }
  return uVar6;
}

