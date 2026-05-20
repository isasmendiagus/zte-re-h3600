// module: mt7915.ko
// function: mt_op_get_rxv_dump_rxv_content @ 0x257f30
// size: 64 bytes
//

undefined4
mt_op_get_rxv_dump_rxv_content(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    chip_rxv_dump_rxv_content_compose(iVar1,param_2,param_4,param_3);
    return 0;
  }
  return 0x503;
}

