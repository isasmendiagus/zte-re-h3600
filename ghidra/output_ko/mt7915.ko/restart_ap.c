// module: mt7915.ko
// function: restart_ap @ 0x35e8c
// size: 144 bytes
//

void restart_ap(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  UpdateBeaconHandler(*(undefined4 *)(param_1 + 8),param_1,6);
  wifi_sys_linkdown(param_1);
  wifi_sys_close(param_1);
  wifi_sys_open(param_1);
  wifi_sys_linkup(param_1,0);
  if ((*(int *)(param_1 + 0x2c) == 1) && (*(int *)(param_1 + 0x174) == 1)) {
    *(ushort *)(iVar1 + 0x408c) = *(ushort *)(iVar1 + 0x408c) & 0xffef;
  }
  else {
    *(ushort *)(iVar1 + 0x408c) = *(ushort *)(iVar1 + 0x408c) | 0x10;
  }
  UpdateBeaconHandler(*(undefined4 *)(param_1 + 8),param_1,2,param_4);
  return;
}

