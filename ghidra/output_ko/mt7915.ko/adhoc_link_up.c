// module: mt7915.ko
// function: adhoc_link_up @ 0x68718
// size: 176 bytes
//

undefined4 adhoc_link_up(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  UpdateBeaconHandler(iVar2,param_1,1,param_4,param_4);
  if (((*(byte *)(param_1 + 0x1a) < 0xf) || (*(char *)(iVar2 + 0x795074) != '\x01')) ||
     (iVar1 = RadarChannelCheck(iVar2), iVar1 == 0)) {
    AsicEnableIbssSync(iVar2,*(undefined2 *)(&DAT_00794c50 + iVar2),0,2);
  }
  iVar2 = wifi_sys_linkup(param_1,param_2);
  if ((iVar2 != 1) && (-1 < DebugLevel)) {
    printk("%s(): linkup fail!\n","adhoc_link_up");
  }
  return 1;
}

