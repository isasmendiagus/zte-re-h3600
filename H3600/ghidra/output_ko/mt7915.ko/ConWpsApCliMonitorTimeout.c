// module: mt7915.ko
// function: ConWpsApCliMonitorTimeout @ 0x1e5a3c
// size: 260 bytes
//

void ConWpsApCliMonitorTimeout(undefined4 param_1,int param_2)

{
  char *pcVar1;
  byte local_11;
  
  local_11 = 0;
  if (0 < DebugLevel) {
    printk("%s: Interface %s\n","ConWpsApCliMonitorTimeout",*(undefined4 *)(param_2 + 4));
  }
  if (*(int *)(&DAT_0036da4c + param_2) == 1) {
    _WscStop(param_2,1,&DAT_005825ec + param_2,0);
  }
  else if (*(int *)(&DAT_0036da4c + param_2) == 2) {
    _WscStop(param_2,1,&DAT_0036ee3c + param_2,0);
  }
  local_11 = 0;
  do {
    RTEnqueueInternalCmd(param_2,7,&local_11,1);
    local_11 = local_11 + 1;
  } while (local_11 < 2);
  (&DAT_00580e8d)[param_2] = 1;
  pcVar1 = s_OTH__d__d_N_A__0037170c + param_2 + 0x14;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  *(undefined4 *)(&DAT_00584ed0 + param_2) = 0;
  (&DAT_0036da50)[param_2] = 0;
  return;
}

