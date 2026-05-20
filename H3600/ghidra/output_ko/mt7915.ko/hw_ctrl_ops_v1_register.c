// module: mt7915.ko
// function: hw_ctrl_ops_v1_register @ 0xb04d0
// size: 92 bytes
//

void hw_ctrl_ops_v1_register(undefined4 *param_1)

{
  *param_1 = hw_ctrl_flow_v1_open;
  param_1[1] = hw_ctrl_flow_v1_close;
  param_1[2] = hw_ctrl_flow_v1_link_up;
  param_1[3] = hw_ctrl_flow_v1_link_down;
  param_1[4] = hw_ctrl_flow_v1_connt_act;
  param_1[5] = hw_ctrl_flow_v1_disconnt_act;
  param_1[6] = hw_ctrl_flow_v1_peer_update;
  return;
}

