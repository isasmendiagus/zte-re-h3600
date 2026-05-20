// module: mt7915.ko
// function: mt_op_get_rxv_dump_ring_attr @ 0x257ea0
// size: 80 bytes
//

undefined4 mt_op_get_rxv_dump_ring_attr(int param_1,undefined1 *param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    *param_2 = *(undefined1 *)(iVar1 + 0xa7c21a);
    param_2[2] = *(undefined1 *)(iVar1 + 0xa7c21e);
    param_2[1] = *(undefined1 *)(iVar1 + 0xa7c21c);
    param_2[3] = *(undefined1 *)(iVar1 + 0xa7c21d);
    return 0;
  }
  return 0x503;
}

