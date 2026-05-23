// module: mt7915.ko
// function: hc_get_hdev_ctrl @ 0xaa678
// size: 12 bytes
//

undefined4 hc_get_hdev_ctrl(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0xabc) + 0x24);
}

