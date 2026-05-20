// module: mt7915.ko
// function: mt7915_rxv_content_len @ 0x178ae8
// size: 152 bytes
//

undefined4 mt7915_rxv_content_len(int param_1,uint param_2,short param_3,ushort *param_4)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_4 == (ushort *)0x0) {
    return 1;
  }
  *param_4 = 0;
  if ((param_2 & 1) != 0) {
    *param_4 = (ushort)*(byte *)(iVar1 + 0x215);
  }
  if ((param_2 & 8) != 0) {
    *param_4 = (ushort)*(byte *)(iVar1 + 0x216) + *param_4;
  }
  if ((param_2 & 2) != 0) {
    *param_4 = (ushort)*(byte *)(iVar1 + 0x217) * param_3 + *param_4;
  }
  if ((param_2 & 4) == 0) {
    return 0;
  }
  *param_4 = (ushort)*(byte *)(iVar1 + 0x218) * param_3 + *param_4;
  return 0;
}

