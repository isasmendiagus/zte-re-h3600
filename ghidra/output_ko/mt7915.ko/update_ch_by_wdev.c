// module: mt7915.ko
// function: update_ch_by_wdev @ 0xd8c2c
// size: 112 bytes
//

void update_ch_by_wdev(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int *)(param_2 + 0x14) == 1) {
    if (*(byte *)(param_2 + 0x1a) < 0xf) {
      MacTableResetWdev();
    }
    else {
      MacTableResetNonMapWdev();
    }
    if ((*(ushort *)(param_2 + 0x18) & 0xb1) != 0) {
      WrapDfsRadarDetectStop(param_1);
      DfsZeroHandOffRecovery(param_1,param_2);
    }
  }
  wlan_operate_init(param_2);
  UpdateBeaconHandler(param_1,param_2,2,param_4);
  return;
}

