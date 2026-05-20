// module: mt7915.ko
// function: Set_Probe_Rsp_Times_Proc @ 0xd867c
// size: 156 bytes
//

undefined4 Set_Probe_Rsp_Times_Proc(int param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = os_str_tol(param_2,0,10);
  if (bVar1 - 1 < 10) {
    *(byte *)(iVar2 + 0xf9) = bVar1;
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Set_PROBE_RSP_TIMES_Proc! ProbeRspTimes = %d\n");
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("Set_PROBE_RSP_TIMES_Proc! INVALID, ProbeRspTimes(%d) should be <1~10>\n");
  return 0;
}

