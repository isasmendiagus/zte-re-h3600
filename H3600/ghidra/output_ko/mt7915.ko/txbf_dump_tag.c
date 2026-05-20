// module: mt7915.ko
// function: txbf_dump_tag @ 0x17e38c
// size: 508 bytes
//

void txbf_dump_tag(int param_1,int param_2,ushort *param_3)

{
  int iVar1;
  
  *(ushort *)(param_1 + 0xa786fc) = (ushort)(((uint)*param_3 << 0x16) >> 0x16);
  *(byte *)(param_1 + 0xa786fe) = (byte)(((uint)*(byte *)((int)param_3 + 1) << 0x1d) >> 0x1f);
  *(byte *)(param_1 + 0xa786ff) = (byte)(((uint)*(byte *)((int)param_3 + 1) << 0x1b) >> 0x1e);
  *(byte *)(param_1 + 0xa78700) = (byte)(((uint)*(byte *)((int)param_3 + 1) << 0x19) >> 0x1e);
  *(byte *)(param_1 + 0xa78701) = *(byte *)((int)param_3 + 1) >> 7;
  *(byte *)(param_1 + 0xa78702) = (byte)(((uint)(byte)param_3[1] << 0x1d) >> 0x1d);
  *(byte *)(param_1 + 0xa78703) = (byte)(((uint)(byte)param_3[1] << 0x1a) >> 0x1d);
  *(byte *)(param_1 + 0xa78704) = (byte)param_3[1] >> 6;
  *(byte *)(param_1 + 0xa78705) = (byte)(((uint)*(byte *)((int)param_3 + 3) << 0x1e) >> 0x1e);
  *(byte *)(param_1 + 0xa78706) = (byte)(((uint)*(byte *)((int)param_3 + 3) << 0x1b) >> 0x1f);
  *(byte *)(param_1 + 0xa78707) = *(byte *)((int)param_3 + 3) >> 5;
  *(byte *)(param_1 + 0xa78710) = (byte)(((uint)(byte)param_3[2] << 0x1a) >> 0x1a);
  *(ushort *)(param_1 + 0xa78708) = param_3[2] >> 6;
  *(byte *)(param_1 + 0xa78711) = (byte)(((uint)(byte)param_3[3] << 0x1a) >> 0x1a);
  *(ushort *)(param_1 + 0xa7870a) = param_3[3] >> 6;
  *(byte *)(param_1 + 0xa78712) = (byte)(((uint)(byte)param_3[4] << 0x1a) >> 0x1a);
  *(ushort *)(param_1 + 0xa7870c) = param_3[4] >> 6;
  *(byte *)(param_1 + 0xa78713) = (byte)(((uint)(byte)param_3[5] << 0x1a) >> 0x1a);
  *(ushort *)(param_1 + 0xa7870e) = param_3[5] >> 6;
  *(byte *)(param_1 + 0xa78715) = (byte)(((uint)(byte)param_3[6] << 0x19) >> 0x19);
  *(byte *)(param_1 + 0xa78716) = (byte)(((uint)*(byte *)((int)param_3 + 0xd) << 0x19) >> 0x19);
  *(byte *)(param_1 + 0xa78717) = (byte)(((uint)(byte)param_3[7] << 0x1f) >> 0x1f);
  *(char *)(param_1 + 0xa78718) = (char)param_3[8];
  *(undefined1 *)(param_1 + 0xa78719) = *(undefined1 *)((int)param_3 + 0x11);
  *(char *)(param_1 + 0xa7871a) = (char)param_3[9];
  *(undefined1 *)(param_1 + 0xa7871b) = *(undefined1 *)((int)param_3 + 0x13);
  *(char *)(param_1 + 0xa7871c) = (char)param_3[10];
  *(undefined1 *)(param_1 + 0xa7871d) = *(undefined1 *)((int)param_3 + 0x15);
  *(char *)(param_1 + 0xa7871e) = (char)param_3[0xb];
  *(undefined1 *)(param_1 + 0xa7871f) = *(undefined1 *)((int)param_3 + 0x17);
  *(uint *)(param_1 + 0xa78720) = *(uint *)(param_3 + 0xe) & 0xffffff;
  *(byte *)(param_1 + 0xa78724) = (byte)(((uint)*(byte *)((int)param_3 + 0x1f) << 0x1b) >> 0x1b);
  *(byte *)(param_1 + 0xa78725) = (byte)(((uint)*(byte *)((int)param_3 + 0x21) << 0x1d) >> 0x1d);
  iVar1 = DebugLevel;
  *(char *)(param_1 + 0xa78726) = (char)param_3[0x11];
  *(byte *)(param_1 + 0xa78727) = (byte)(((uint)(byte)param_3[0x13] << 0x1e) >> 0x1e);
  *(byte *)(param_1 + 0xa78729) = (byte)(((uint)(byte)param_3[0x13] << 0x1b) >> 0x1d);
  *(byte *)(param_1 + 0xa78728) = (byte)param_3[0x13] >> 5;
  *(undefined1 *)(param_1 + 0xa7872a) = *(undefined1 *)((int)param_3 + 0x27);
  if (iVar1 < 3) {
    return;
  }
  FUN_0017e170(param_3);
  if (param_2 != 1) {
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  FUN_0017e2e0(param_3 + 0xe);
  return;
}

