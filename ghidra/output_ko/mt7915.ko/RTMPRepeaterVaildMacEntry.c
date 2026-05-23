// module: mt7915.ko
// function: RTMPRepeaterVaildMacEntry @ 0x827e4
// size: 124 bytes
//

bool RTMPRepeaterVaildMacEntry(int param_1,byte *param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = __aeabi_uidiv(*(undefined1 *)(iVar2 + 0x14a),*(undefined1 *)(iVar2 + 0x1c4),
                        param_1 + param_3,iVar2,param_4);
  if (((byte)(&DAT_00367912)[param_1 + param_3] < bVar1) && ((*param_2 & 1) == 0)) {
    iVar2 = RepeaterInvaildMacLookup(param_1,param_2);
    return iVar2 == 0;
  }
  return false;
}

