// module: mt7915.ko
// function: mt_ate_add_allocation @ 0x28c710
// size: 344 bytes
//

undefined4 mt_ate_add_allocation(int param_1,uint param_2,int param_3,uint param_4)

{
  uint uVar1;
  
  if (param_4 - 0x43 < 2) {
    param_4 = 0;
  }
  else if (param_4 < 0x41) {
    if (param_4 < 0x3d) {
      if (param_4 < 0x35) {
        if (param_4 < 0x25) {
          param_4 = (uint)((int)((ulonglong)param_4 * 0x38e38e39 >> 0x20) << 0x17) >> 0x18;
        }
        else {
          param_4 = (param_4 % 0x25) * 0x400000 >> 0x18;
        }
      }
      else {
        param_4 = (param_4 % 0x35) * 0x800000 >> 0x18;
      }
    }
    else {
      param_4 = param_4 % 0x3d;
    }
  }
  else {
    param_4 = (param_4 % 0x41) * 2;
  }
  uVar1 = param_4 + param_3 * 4 & 0xff;
  if (param_2 != 0x7f &&
      (*(byte *)(param_1 + uVar1) == 0xff && *(byte *)(param_1 + uVar1) != param_2)) {
    *(char *)(param_1 + uVar1) = (char)param_2;
    if (param_2 != 200) {
      if (param_2 == 0xd0) {
        param_1 = param_1 + uVar1;
        *(undefined1 *)(param_1 + 1) = 0x73;
        *(undefined1 *)(param_1 + 2) = 0x73;
        *(undefined1 *)(param_1 + 3) = 0x73;
      }
      return 0;
    }
    *(undefined1 *)(param_1 + uVar1 + 1) = 0x72;
  }
  return 0;
}

