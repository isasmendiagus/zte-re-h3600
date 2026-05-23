// module: mt7915.ko
// function: phy_cfg_init @ 0x106380
// size: 40 bytes
//

void phy_cfg_init(int param_1)

{
  *(undefined1 *)(param_1 + 10) = 0;
  *(undefined1 *)(param_1 + 0x10) = 0xff;
  *(undefined1 *)(param_1 + 0xb) = 0;
  *(undefined1 *)(param_1 + 0xc) = 0;
  *(undefined1 *)(param_1 + 0xd) = 0;
  *(undefined1 *)(param_1 + 0xe) = 0;
  *(undefined1 *)(param_1 + 0xf) = 0;
  return;
}

