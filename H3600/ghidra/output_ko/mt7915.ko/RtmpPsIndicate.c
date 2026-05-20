// module: mt7915.ko
// function: RtmpPsIndicate @ 0x1dd690
// size: 228 bytes
//

undefined4 RtmpPsIndicate(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar1 + 0x154) == '\x02') && (uVar2 = HcGetMaxStaNum(param_1), param_3 < uVar2)) {
    iVar1 = param_3 * 0x14c0 + param_1;
    if (param_4 == 1 && *(char *)(iVar1 + 0xa2818) == '\0') {
      *(undefined4 *)(iVar1 + 0xa280c) = jiffies;
    }
    else if (param_4 == 0 && *(char *)(iVar1 + 0xa2818) == '\x01') {
      *(undefined4 *)(iVar1 + 0xa280c) = 0;
    }
    iVar1 = param_3 * 0x14c0 + param_1;
    *(undefined4 *)(iVar1 + 0xa2808) = 0;
    *(char *)(iVar1 + 0xa2818) = (char)param_4;
    *(char *)(param_1 + param_3 * 0x620 + 0x2f763) = (char)param_4;
    return 0;
  }
  return 0;
}

