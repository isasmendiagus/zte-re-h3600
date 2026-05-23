// module: mt7915.ko
// function: MakeBeacon @ 0xb5720
// size: 340 bytes
//

uint MakeBeacon(int param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort local_2e;
  uint local_2c [2];
  
  local_2c[0] = 0;
  local_2e = 0;
  pbVar3 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *pbVar3;
  bVar2 = pbVar3[2];
  _raw_spin_lock_bh(param_2 + 0x984);
  iVar7 = *(int *)(*(int *)(param_2 + 0x954) + 0xcc);
  iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar4 != 2) {
    bVar2 = bVar1;
  }
  iVar4 = iVar7 + (uint)bVar2;
  uVar5 = ComposeBcnPktHead(param_1,param_2,iVar4);
  local_2c[0] = uVar5 & 0xff;
  *(short *)(param_2 + 0x980) = (short)local_2c[0];
  if (param_3 == 1) {
    uVar5 = local_2c[0];
  }
  if (*(int *)(param_2 + 0x14) == 1) {
    iVar6 = *(int *)(param_2 + 4);
    *(undefined1 *)(param_2 + 0x95a) = 0x22;
    *(char *)(iVar4 + 0x22) = (char)*(undefined2 *)(iVar6 + 0x408c);
    *(char *)(iVar4 + 0x23) = (char)((ushort)*(undefined2 *)(iVar6 + 0x408c) >> 8);
    iVar6 = BcnTimUpdate(param_1,param_2,iVar4 + (uint)*(ushort *)(param_2 + 0x980));
    local_2c[0] = iVar6 + uVar5;
  }
  ComposeBcnPktTail(param_1,param_2,local_2c,iVar4);
  uVar5 = local_2c[0];
  if (0xe < *(byte *)(param_2 + 0x1a)) {
    local_2e = local_2e & 0x1fc0 | 0x2000;
  }
  asic_write_tmac_info_beacon(param_1,param_2,iVar7,&local_2e,local_2c[0]);
  _raw_spin_unlock_bh(param_2 + 0x984);
  return uVar5 & 0xffff;
}

