// module: mt7915.ko
// function: chip_set_txbf_angle @ 0x17c148
// size: 1148 bytes
//

undefined4
chip_set_txbf_angle(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hdev_privdata();
  switch(param_3) {
  case 0:
    *(ushort *)(iVar1 + 0xa78734) =
         *(ushort *)(iVar1 + 0xa78734) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa78735) = *(byte *)(iVar1 + 0xa78735) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78736) =
         *(ushort *)(iVar1 + 0xa78736) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa78737) = *(byte *)(iVar1 + 0xa78737) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78738) =
         *(ushort *)(iVar1 + 0xa78738) & 0xfe00 | (ushort)param_4[4] & 0x1ff;
    *(byte *)(iVar1 + 0xa78739) = *(byte *)(iVar1 + 0xa78739) & 1 | (byte)((param_4[5] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7873a) =
         *(ushort *)(iVar1 + 0xa7873a) & 0xfe00 | (ushort)param_4[6] & 0x1ff;
    *(byte *)(iVar1 + 0xa7873b) = *(byte *)(iVar1 + 0xa7873b) & 1 | (byte)((param_4[7] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7873c) =
         *(ushort *)(iVar1 + 0xa7873c) & 0xfe00 | (ushort)param_4[8] & 0x1ff;
    *(byte *)(iVar1 + 0xa7873d) = *(byte *)(iVar1 + 0xa7873d) & 1 | (byte)((param_4[9] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7873e) =
         *(ushort *)(iVar1 + 0xa7873e) & 0xfe00 | (ushort)param_4[10] & 0x1ff;
    *(byte *)(iVar1 + 0xa7873f) =
         *(byte *)(iVar1 + 0xa7873f) & 1 | (byte)((param_4[0xb] & 0x7f) << 1);
    *(ushort *)(iVar1 + 0xa78740) =
         *(ushort *)(iVar1 + 0xa78740) & 0xfe00 | (ushort)param_4[0xc] & 0x1ff;
    *(byte *)(iVar1 + 0xa78741) =
         *(byte *)(iVar1 + 0xa78741) & 1 | (byte)((param_4[0xd] & 0x7f) << 1);
    return 1;
  case 1:
    *(ushort *)(iVar1 + 0xa78742) =
         *(ushort *)(iVar1 + 0xa78742) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa78743) = *(byte *)(iVar1 + 0xa78743) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78744) =
         *(ushort *)(iVar1 + 0xa78744) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa78745) = *(byte *)(iVar1 + 0xa78745) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78746) =
         *(ushort *)(iVar1 + 0xa78746) & 0xfe00 | (ushort)param_4[4] & 0x1ff;
    *(byte *)(iVar1 + 0xa78747) = *(byte *)(iVar1 + 0xa78747) & 1 | (byte)((param_4[5] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78748) =
         *(ushort *)(iVar1 + 0xa78748) & 0xfe00 | (ushort)param_4[6] & 0x1ff;
    *(byte *)(iVar1 + 0xa78749) = *(byte *)(iVar1 + 0xa78749) & 1 | (byte)((param_4[7] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7874a) =
         *(ushort *)(iVar1 + 0xa7874a) & 0xfe00 | (ushort)param_4[8] & 0x1ff;
    *(byte *)(iVar1 + 0xa7874b) = *(byte *)(iVar1 + 0xa7874b) & 1 | (byte)((param_4[9] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7874c) =
         *(ushort *)(iVar1 + 0xa7874c) & 0xfe00 | (ushort)param_4[10] & 0x1ff;
    *(byte *)(iVar1 + 0xa7874d) =
         *(byte *)(iVar1 + 0xa7874d) & 1 | (byte)((param_4[0xb] & 0x7f) << 1);
    return 1;
  case 2:
    *(ushort *)(iVar1 + 0xa7874e) =
         *(ushort *)(iVar1 + 0xa7874e) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa7874f) = *(byte *)(iVar1 + 0xa7874f) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78750) =
         *(ushort *)(iVar1 + 0xa78750) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa78751) = *(byte *)(iVar1 + 0xa78751) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78752) =
         *(ushort *)(iVar1 + 0xa78752) & 0xfe00 | (ushort)param_4[4] & 0x1ff;
    *(byte *)(iVar1 + 0xa78753) = *(byte *)(iVar1 + 0xa78753) & 1 | (byte)((param_4[5] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78754) =
         *(ushort *)(iVar1 + 0xa78754) & 0xfe00 | (ushort)param_4[6] & 0x1ff;
    *(byte *)(iVar1 + 0xa78755) = *(byte *)(iVar1 + 0xa78755) & 1 | (byte)((param_4[7] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78756) =
         *(ushort *)(iVar1 + 0xa78756) & 0xfe00 | (ushort)param_4[8] & 0x1ff;
    *(byte *)(iVar1 + 0xa78757) = *(byte *)(iVar1 + 0xa78757) & 1 | (byte)((param_4[9] & 0x7f) << 1)
    ;
    return 1;
  case 3:
    *(ushort *)(iVar1 + 0xa78758) =
         *(ushort *)(iVar1 + 0xa78758) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa78759) = *(byte *)(iVar1 + 0xa78759) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7875a) =
         *(ushort *)(iVar1 + 0xa7875a) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa7875b) = *(byte *)(iVar1 + 0xa7875b) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7875c) =
         *(ushort *)(iVar1 + 0xa7875c) & 0xfe00 | (ushort)param_4[4] & 0x1ff;
    *(byte *)(iVar1 + 0xa7875d) = *(byte *)(iVar1 + 0xa7875d) & 1 | (byte)((param_4[5] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa7875e) =
         *(ushort *)(iVar1 + 0xa7875e) & 0xfe00 | (ushort)param_4[6] & 0x1ff;
    *(byte *)(iVar1 + 0xa7875f) = *(byte *)(iVar1 + 0xa7875f) & 1 | (byte)((param_4[7] & 0x7f) << 1)
    ;
    return 1;
  case 4:
    *(ushort *)(iVar1 + 0xa78760) =
         *(ushort *)(iVar1 + 0xa78760) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa78761) = *(byte *)(iVar1 + 0xa78761) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78762) =
         *(ushort *)(iVar1 + 0xa78762) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa78763) = *(byte *)(iVar1 + 0xa78763) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78764) =
         *(ushort *)(iVar1 + 0xa78764) & 0xfe00 | (ushort)param_4[4] & 0x1ff;
    *(byte *)(iVar1 + 0xa78765) = *(byte *)(iVar1 + 0xa78765) & 1 | (byte)((param_4[5] & 0x7f) << 1)
    ;
    break;
  case 5:
    *(ushort *)(iVar1 + 0xa78766) =
         *(ushort *)(iVar1 + 0xa78766) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa78767) = *(byte *)(iVar1 + 0xa78767) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    *(ushort *)(iVar1 + 0xa78768) =
         *(ushort *)(iVar1 + 0xa78768) & 0xfe00 | (ushort)param_4[2] & 0x1ff;
    *(byte *)(iVar1 + 0xa78769) = *(byte *)(iVar1 + 0xa78769) & 1 | (byte)((param_4[3] & 0x7f) << 1)
    ;
    return 1;
  case 6:
  case 7:
    *(ushort *)(iVar1 + 0xa7876a) =
         *(ushort *)(iVar1 + 0xa7876a) & 0xfe00 | (ushort)*param_4 & 0x1ff;
    *(byte *)(iVar1 + 0xa7876b) = *(byte *)(iVar1 + 0xa7876b) & 1 | (byte)((param_4[1] & 0x7f) << 1)
    ;
    return 1;
  }
  return 1;
}

