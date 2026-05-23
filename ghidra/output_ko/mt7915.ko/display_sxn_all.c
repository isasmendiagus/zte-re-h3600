// module: mt7915.ko
// function: display_sxn_all @ 0x979f8
// size: 112 bytes
//

void display_sxn_all(uint *param_1)

{
  uint uVar1;
  
  uVar1 = (*param_1 << 10) >> 0x12;
  *param_1 = *param_1 & 0xffc0003f | uVar1 << 6;
  if (uVar1 == 0) {
    return;
  }
  uVar1 = 0;
  do {
    if (0 < DebugLevel) {
      printk("DW%02d: 0x%08X\n",uVar1,param_1[uVar1 + 1]);
    }
    uVar1 = uVar1 + 1 & 0xffff;
  } while (uVar1 < (*param_1 << 10) >> 0x10);
  return;
}

