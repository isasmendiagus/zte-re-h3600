// module: mt7915.ko
// function: net_ad_read_bulk_mac_bbp_reg @ 0x25d688
// size: 132 bytes
//

undefined4 net_ad_read_bulk_mac_bbp_reg(int param_1,undefined4 param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined1 auStack_24 [8];
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    uVar3 = 0x606;
  }
  else {
    uVar1 = *(ushort *)(param_3 + 1);
    iVar7 = *param_3;
    if (uVar1 != 0) {
      uVar6 = 0;
      iVar5 = iVar7;
      do {
        uVar6 = uVar6 + 1;
        mac_io_read32(*(undefined4 *)(iVar2 + 0xa797a0),iVar5,auStack_24);
        iVar4 = iVar5 - iVar7;
        iVar5 = iVar5 + 4;
        sys_ad_move_mem((void *)(param_3[2] + iVar4),auStack_24,4);
      } while (uVar1 != uVar6);
    }
    uVar3 = 0;
  }
  return uVar3;
}

