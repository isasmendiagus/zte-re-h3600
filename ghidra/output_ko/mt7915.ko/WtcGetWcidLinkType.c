// module: mt7915.ko
// function: WtcGetWcidLinkType @ 0xadc98
// size: 16 bytes
//

undefined1 WtcGetWcidLinkType(int param_1,int param_2)

{
  return *(undefined1 *)(param_1 + param_2 * 0x10 + 0x1a32);
}

