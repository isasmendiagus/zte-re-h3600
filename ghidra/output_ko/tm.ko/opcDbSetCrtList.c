// module: tm.ko
// function: opcDbSetCrtList @ 0x557a0
// size: 88 bytes
//

undefined4 opcDbSetCrtList(int param_1)

{
  if (param_1 == 0) {
    s_tmFlowInfoListHead = s_tmFlowInfoListHead_u;
  }
  else {
    if (param_1 != 1) {
      printk("direction is invalid\n");
      return 0xfffffff4;
    }
    s_tmFlowInfoListHead = s_tmFlowInfoListHead_d;
  }
  g_direction = param_1;
  return 0;
}

