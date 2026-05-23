// module: mt7915.ko
// function: prepare_veri_pkt_ctrl_en @ 0x1d5ed4
// size: 28 bytes
//

undefined4 prepare_veri_pkt_ctrl_en(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0xa7cc58) = param_2 | *(uint *)(param_1 + 0xa7cc58);
  return 1;
}

