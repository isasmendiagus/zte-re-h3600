// module: mt7915.ko
// function: chip_write_txbf_pfmu_tag @ 0x17e588
// size: 636 bytes
//

undefined4 chip_write_txbf_pfmu_tag(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_60;
  byte bStack_5f;
  byte local_5e;
  byte local_5d;
  ushort local_5c;
  ushort local_5a;
  ushort local_58;
  ushort local_56;
  byte local_54;
  byte local_53;
  byte local_52;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined3 local_44;
  byte bStack_41;
  byte local_3f;
  undefined1 local_3e;
  byte local_3a;
  undefined1 local_39;
  
  iVar2 = hc_get_hdev_privdata();
  os_zero_mem(&local_60,0x1c);
  os_zero_mem(&local_44,0x1c);
  uVar1 = *(ushort *)(iVar2 + 0xa786fc) & 0x3ff;
  local_5c = (ushort)(*(byte *)(iVar2 + 0xa78710) & 0x3f);
  local_5a = (ushort)(*(byte *)(iVar2 + 0xa78711) & 0x3f);
  local_58 = (ushort)(*(byte *)(iVar2 + 0xa78712) & 0x3f);
  local_5d = local_5d & 0xc | *(byte *)(iVar2 + 0xa78705) & 3 |
             (*(byte *)(iVar2 + 0xa78706) & 1) << 4 | *(char *)(iVar2 + 0xa78707) << 5;
  local_5e = *(byte *)(iVar2 + 0xa78702) & 7 | (*(byte *)(iVar2 + 0xa78703) & 7) << 3 |
             *(char *)(iVar2 + 0xa78704) << 6;
  local_5c = local_5c | *(short *)(iVar2 + 0xa78708) << 6;
  _local_60 = CONCAT11((byte)(uVar1 >> 8) | (*(byte *)(iVar2 + 0xa786fe) & 1) << 2 |
                       (*(byte *)(iVar2 + 0xa786ff) & 3) << 3 |
                       (*(byte *)(iVar2 + 0xa78700) & 3) << 5 | *(char *)(iVar2 + 0xa78701) << 7,
                       (char)uVar1);
  local_5a = local_5a | *(short *)(iVar2 + 0xa7870a) << 6;
  local_50 = *(undefined1 *)(iVar2 + 0xa78718);
  local_58 = local_58 | *(short *)(iVar2 + 0xa7870c) << 6;
  local_56 = (ushort)(*(byte *)(iVar2 + 0xa78713) & 0x3f);
  local_4f = *(undefined1 *)(iVar2 + 0xa78719);
  local_4e = *(undefined1 *)(iVar2 + 0xa7871a);
  local_56 = local_56 | *(short *)(iVar2 + 0xa7870e) << 6;
  local_4d = *(undefined1 *)(iVar2 + 0xa7871b);
  local_54 = local_54 & 0x80 | *(byte *)(iVar2 + 0xa78715) & 0x7f;
  local_4c = *(undefined1 *)(iVar2 + 0xa7871c);
  local_53 = local_53 & 0x80 | *(byte *)(iVar2 + 0xa78716) & 0x7f;
  local_4b = *(undefined1 *)(iVar2 + 0xa7871d);
  local_4a = *(undefined1 *)(iVar2 + 0xa7871e);
  local_49 = *(undefined1 *)(iVar2 + 0xa7871f);
  local_52 = local_52 & 0xfe | *(byte *)(iVar2 + 0xa78717) & 1;
  local_3e = *(undefined1 *)(iVar2 + 0xa78726);
  local_39 = *(undefined1 *)(iVar2 + 0xa7872a);
  local_3a = *(byte *)(iVar2 + 0xa78727) & 3 | (*(byte *)(iVar2 + 0xa78729) & 7) << 2 |
             *(char *)(iVar2 + 0xa78728) << 5;
  local_3f = local_3f & 0xf8 | *(byte *)(iVar2 + 0xa78725) & 7;
  _local_44 = CONCAT13(bStack_41 & 0xe0 | *(byte *)(iVar2 + 0xa78724) & 0x1f,
                       (int3)*(undefined4 *)(iVar2 + 0xa78720));
  iVar2 = CmdETxBfPfmuProfileTagWrite(iVar2,&local_60,&local_44,0x1c,0x1c,param_2);
  if (iVar2 == 0) {
    if ((2 < DebugLevel) && (FUN_0017e170(&local_60), 2 < DebugLevel)) {
      FUN_0017e2e0(&local_44);
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

