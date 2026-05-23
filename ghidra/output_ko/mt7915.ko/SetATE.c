// module: mt7915.ko
// function: SetATE @ 0x26958c
// size: 80 bytes
//

void SetATE(int param_1,undefined4 param_2)

{
  if (0 < DebugLevel) {
    printk("%s: Arg = %s\n","SetATE",param_2);
  }
  mt_agent_cli_act(param_2,param_1 + 0xa77bb4);
  return;
}

