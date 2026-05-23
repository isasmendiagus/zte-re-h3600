// module: mt7915.ko
// function: mt_op_get_rxv_dump_action @ 0x257e3c
// size: 100 bytes
//

undefined4 mt_op_get_rxv_dump_action(int param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  if (param_2 != 1) {
    if (param_2 != 3) {
      chip_rxv_dump_buf_alloc(iVar1,param_3);
      chip_rxv_dump_start(iVar1);
      return 0;
    }
    chip_rxv_dump_buf_clear();
    return 0;
  }
  chip_rxv_dump_stop();
  return 0;
}

