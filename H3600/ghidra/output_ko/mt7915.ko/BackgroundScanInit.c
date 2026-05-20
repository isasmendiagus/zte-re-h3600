// module: mt7915.ko
// function: BackgroundScanInit @ 0x22dc60
// size: 460 bytes
//

void BackgroundScanInit(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s ===============>\n","BackgroundScanInit");
  }
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      pcVar2 = "%s: NULL pointer <==============\n";
      goto LAB_0022ddfc;
    }
  }
  else {
    wlan_config_get_vht_bw(param_2);
    if (*(char *)(param_1 + 0xa7979c) != '\x01') {
      os_zero_mem(param_1 + 0xa78ad0,0xcd0);
      *(undefined1 *)(param_1 + 0xa7979c) = 1;
    }
    *(undefined4 *)(param_1 + 0xa7962c) = 63000;
    if (*(char *)(param_1 + 0x795404) != '\0') {
      RTMPInitTimer(param_1,param_1 + 0xa791c4,rtmp_timer_dfs_zero_wait_ch_init_timeout,param_1,0);
    }
    *(undefined1 *)(param_1 + 0xa78ad2) = 1;
    BackgroundScanStateMachineInit(param_1,param_1 + 0xa79178,param_1 + 0xa79060);
    RTMPInitTimer(param_1,param_1 + 0xa79190,rtmp_timer_BackgroundScanTimeout,param_1,0);
    if (*(code **)(iVar1 + 0x284) != (code *)0x0) {
      (**(code **)(iVar1 + 0x284))(param_1);
    }
    iVar1 = DebugLevel;
    *(undefined2 *)(param_1 + 0xa79230) = 200;
    *(undefined4 *)(param_1 + 0xa79624) = 600000;
    *(undefined4 *)(param_1 + 0xa79798) = 80000;
    *(undefined4 *)(param_1 + 0xa79610) = 10;
    *(undefined1 *)(param_1 + 0xa79620) = 0x55;
    *(undefined1 *)(param_1 + 0xa7979d) = 2;
    *(undefined4 *)(param_1 + 0xa79618) = 0;
    *(undefined1 *)(param_1 + 0xa79630) = 0;
    *(undefined1 *)(param_1 + 0xa79753) = 0;
    if (2 < iVar1) {
      pcVar2 = "%s <===============\n";
LAB_0022ddfc:
      printk(pcVar2,"BackgroundScanInit");
      return;
    }
  }
  return;
}

