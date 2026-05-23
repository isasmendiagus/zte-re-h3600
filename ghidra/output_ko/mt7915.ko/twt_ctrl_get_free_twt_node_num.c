// module: mt7915.ko
// function: twt_ctrl_get_free_twt_node_num @ 0x16ab50
// size: 24 bytes
//

void twt_ctrl_get_free_twt_node_num(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  *param_2 = *(undefined1 *)(param_1 + 0x2c39);
  *param_3 = *(undefined1 *)(param_1 + 0x2c3a);
  return;
}

