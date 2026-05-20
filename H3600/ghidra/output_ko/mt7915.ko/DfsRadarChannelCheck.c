// module: mt7915.ko
// function: DfsRadarChannelCheck @ 0x231cac
// size: 276 bytes
//

uint DfsRadarChannelCheck(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_2 + 0x1a);
  if (uVar2 < 0xf) {
    return 0;
  }
  if (*(char *)(param_1 + 0x7953ef) == '\0') {
    return 0;
  }
  if (*(int *)(param_2 + 0x14) == 2) {
    if (0 < DebugLevel) {
      printk("[%s] wdev_type=sta, skip dfs.\n","DfsRadarChannelCheck",param_3,DebugLevel,param_4);
      return 0;
    }
    return 0;
  }
  if (param_4 == 6) {
    iVar1 = RadarChannelCheck(param_1,uVar2);
    if (iVar1 == 0) {
      iVar1 = RadarChannelCheck(param_1,param_3 - 2U & 0xff);
      uVar2 = (uint)(iVar1 != 0);
      goto LAB_00231d10;
    }
  }
  else if ((param_4 != 3) || (0xc < uVar2 - 0x24)) {
    uVar2 = RadarChannelCheck(param_1,uVar2);
LAB_00231d10:
    if (uVar2 != 1) {
      if (*(char *)(param_1 + 0x7953fa) == '\0') {
        return uVar2;
      }
      goto LAB_00231d28;
    }
  }
  uVar2 = 1;
LAB_00231d28:
  DfsGetSysParameters(param_1,param_2,param_3,param_4);
  return uVar2;
}

