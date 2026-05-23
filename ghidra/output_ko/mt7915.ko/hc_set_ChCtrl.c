// module: mt7915.ko
// function: hc_set_ChCtrl @ 0xaa6e8
// size: 48 bytes
//

undefined4 hc_set_ChCtrl(int param_1,int param_2,int param_3,int param_4)

{
  os_move_mem((void *)(param_1 + param_3 * 0x14),
              "get_channel_by_reference" + param_2 + param_4 * 0x14 + 0xc,0x14);
  return 0;
}

