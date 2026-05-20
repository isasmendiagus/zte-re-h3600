// module: mt7915.ko
// function: ht_support_bw_by_channel_boundary @ 0x13774c
// size: 360 bytes
//

uint ht_support_bw_by_channel_boundary(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar7 = *(int *)(param_2 + 8);
  if (iVar7 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = wlan_operate_get_ht_bw(iVar7);
    iVar2 = wlan_operate_get_ext_cha(iVar7);
    if (param_3 != 0) {
      if (3 < DebugLevel) {
        printk("%s(), Channel = %d, supported_bw = %d, extcha = %d, PeerSupChlLen = %d\n",
               "ht_support_bw_by_channel_boundary",*(undefined1 *)(iVar7 + 0x1a),uVar1,iVar2,
               *(undefined1 *)(param_3 + 0x51));
      }
      if ((*(byte *)(iVar7 + 0x1a) < 0xf) && (uVar3 = (uint)*(byte *)(param_3 + 0x51), 1 < uVar3)) {
        uVar8 = 0xe;
        uVar4 = 1;
        uVar5 = 0;
        do {
          uVar6 = (uint)*(byte *)(param_3 + uVar5 + 0x52);
          if ((uVar6 < 0xf) &&
             (uVar8 = (uVar6 - 1) + (uint)*(byte *)(param_3 + uVar5 + 0x53) & 0xff, uVar4 = uVar6,
             3 < DebugLevel)) {
            printk("  peer_sup_chl_min_2g = %d, peer_sup_chl_max_2g = %d\n",uVar6,uVar8);
            uVar3 = (uint)*(byte *)(param_3 + 0x51);
          }
          uVar5 = uVar5 + 2 & 0xff;
        } while (uVar5 < uVar3);
        if (uVar1 == 1 && iVar2 != 0) {
          if (iVar2 == 1) {
            uVar1 = (uint)(*(byte *)(iVar7 + 0x1a) + 4 <= uVar8);
          }
          else if (iVar2 == 3) {
            uVar1 = (uint)((int)uVar4 <= (int)(*(byte *)(iVar7 + 0x1a) - 4));
          }
          else {
            uVar1 = 1;
          }
        }
      }
    }
  }
  return uVar1;
}

