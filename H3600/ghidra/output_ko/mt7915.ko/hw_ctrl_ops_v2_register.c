// module: mt7915.ko
// function: hw_ctrl_ops_v2_register @ 0xb0a18
// size: 92 bytes
//

void hw_ctrl_ops_v2_register(undefined4 *param_1)

{
  *param_1 = hw_ctrl_flow_v2_open;
  param_1[1] = hw_ctrl_flow_v2_close;
  param_1[2] = hw_ctrl_flow_v2_link_up;
  param_1[3] = hw_ctrl_flow_v2_link_down;
  param_1[4] = hw_ctrl_flow_v2_connt_act;
  param_1[5] = hw_ctrl_flow_v2_disconnt_act;
  param_1[6] = hw_ctrl_flow_v2_peer_update;
  return;
}

