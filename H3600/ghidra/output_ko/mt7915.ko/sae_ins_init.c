// module: mt7915.ko
// function: sae_ins_init @ 0x208dc8
// size: 320 bytes
//

void sae_ins_init(undefined4 param_1,int param_2,int *param_3,int *param_4,undefined4 *param_5,
                 int *param_6,int param_7,int param_8,undefined1 param_9)

{
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_ins_init");
  }
  __memzero(param_3,0x188);
  param_3[0x58] = *param_4;
  *(short *)(param_3 + 0x59) = (short)param_4[1];
  *(undefined4 *)((int)param_3 + 0x166) = *param_5;
  *(undefined2 *)((int)param_3 + 0x16a) = *(undefined2 *)(param_5 + 1);
  param_3[0x5b] = *param_6;
  *(short *)(param_3 + 0x5c) = (short)param_6[1];
  RTMPInitTimer(param_1,param_3 + 0x4b,rtmp_timer_sae_auth_retransmit,param_3,0);
  if (3 < DebugLevel) {
    printk("%s: timer valid = %d\n","sae_ins_init",(char)param_3[0x52]);
  }
  param_3[0x60] = param_2;
  *(undefined1 *)(param_3 + 0x23) = param_9;
  param_3[0x5d] = param_7;
  param_3[0x5e] = param_8;
  if ((param_2 != 0) && (*param_3 - 1U < 2)) {
    *(int *)(param_2 + 0x1b904) = *(int *)(param_2 + 0x1b904) + -1;
  }
  *param_3 = 0;
  *(undefined1 *)((int)param_3 + 0x2e) = 0;
  *(undefined2 *)(param_3 + 1) = 0;
  *(undefined2 *)((int)param_3 + 6) = 0;
  *(undefined1 *)((int)param_3 + 0x2f) = 0;
  param_3[0x5f] = 0;
  *(undefined1 *)((int)param_3 + 0x129) = 0;
  return;
}

