// module: mt7915.ko
// function: wmode_valid_and_correct @ 0xb8158
// size: 304 bytes
//

undefined4 wmode_valid_and_correct(int param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = *param_2;
  if (uVar3 == 0) {
    uVar3 = 0xff;
    *param_2 = 0xff;
    uVar2 = *(uint *)(iVar1 + 0x2c);
    if ((uVar2 & 2) != 0) {
      if ((uVar2 & 1) == 0) {
        uVar3 = 0xb1;
        *param_2 = 0xb1;
        goto LAB_000b81a0;
      }
LAB_000b81e8:
      if (((uVar2 & 4) == 0) || ((*(uint *)(param_1 + 0xa39f8c) & 1) != 0)) {
        uVar3 = uVar3 & 0xffe7;
        *param_2 = uVar3;
        goto LAB_000b81a0;
      }
LAB_000b8224:
      if (((uVar3 & 0x20) == 0) || ((*(uint *)(iVar1 + 0x2c) & 8) != 0)) {
        if (((uVar3 & 0x1c0) == 0) || ((*(uint *)(iVar1 + 0x2c) & 0x10) != 0)) {
          uVar3 = *param_2;
        }
        else {
          uVar3 = uVar3 & 0xff3f;
          *param_2 = uVar3;
        }
      }
      else {
        uVar3 = uVar3 & 0xffdf;
        *param_2 = uVar3;
      }
      goto LAB_000b81a0;
    }
  }
  else if (((uVar3 & 0xb1) == 0) || ((*(uint *)(iVar1 + 0x2c) & 2) != 0)) {
    if (((uVar3 & 0x4e) != 0) && ((*(uint *)(iVar1 + 0x2c) & 1) == 0)) {
      uVar3 = uVar3 & 0xffb1;
      *param_2 = uVar3;
      goto LAB_000b81a0;
    }
    if ((uVar3 & 0x18) != 0) {
      uVar2 = *(uint *)(iVar1 + 0x2c);
      goto LAB_000b81e8;
    }
    goto LAB_000b8224;
  }
  uVar3 = uVar3 & 0xff4e;
  *param_2 = uVar3;
LAB_000b81a0:
  if (uVar3 == 0) {
    *param_2 = 0xff;
  }
  return 1;
}

