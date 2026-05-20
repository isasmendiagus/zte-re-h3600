// module: mt7915.ko
// function: WscRxMsgTypeFromUpnp @ 0x3cb54
// size: 212 bytes
//

undefined1 WscRxMsgTypeFromUpnp(undefined4 param_1,ushort *param_2,uint param_3)

{
  bool bVar1;
  uint uVar2;
  
  if (*param_2 == 0x4a10) {
    do {
      if (param_3 < 5) {
        return 0xff;
      }
      uVar2 = (param_2[1] & 0xff) << 8 | (uint)(param_2[1] >> 8);
      if ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x1022) {
        return (char)param_2[2];
      }
      param_2 = (ushort *)((int)param_2 + uVar2 + 4);
      bVar1 = (int)(uVar2 + 4) <= (int)param_3;
      param_3 = param_3 + (0xfffc - uVar2) & 0xffff;
    } while (bVar1);
    if (2 < DebugLevel) {
      printk("unexpected WSC IE Length(%u)\n",uVar2);
    }
  }
  return 0xff;
}

