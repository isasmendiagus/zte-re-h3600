// module: mt7915.ko
// function: phy_freq_get_cfg @ 0x106ff4
// size: 104 bytes
//

void phy_freq_get_cfg(int param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 0xb10);
  os_zero_mem(param_2,9);
  param_2[4] = *(undefined1 *)(param_1 + 0x1a);
  *param_2 = *puVar1;
  param_2[5] = puVar1[5];
  param_2[1] = puVar1[0x15];
  param_2[3] = puVar1[0x14];
  param_2[2] = puVar1[0x5c];
  param_2[6] = puVar1[1];
  param_2[7] = puVar1[2];
  param_2[8] = puVar1[4];
  return;
}

