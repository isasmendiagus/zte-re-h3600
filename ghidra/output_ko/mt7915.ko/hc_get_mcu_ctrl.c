// module: mt7915.ko
// function: hc_get_mcu_ctrl @ 0xaac24
// size: 12 bytes
//

undefined4 hc_get_mcu_ctrl(int param_1)

{
  return *(undefined4 *)(param_1 + 0x4320);
}

