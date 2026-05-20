// module: mt7915.ko
// function: HdevHwResourceExit @ 0xae5cc
// size: 96 bytes
//

void HdevHwResourceExit(int param_1)

{
  byte bVar1;
  byte bVar2;
  
  WtcExit();
  if (*(char *)(param_1 + 0x32d8) != '\0') {
    bVar1 = 0;
    do {
      bVar2 = bVar1 + 1;
      HdevExit(param_1,bVar1);
      bVar1 = bVar2;
    } while (bVar2 < *(byte *)(param_1 + 0x32d8));
  }
  wmm_ctrl_exit(param_1 + 0x1a08);
  twt_ctrl_exit(param_1);
  bss_color_table_deinit(param_1);
  return;
}

