// module: mt7915.ko
// function: MtCmdCfgOnOff @ 0x1b6ac4
// size: 292 bytes
//

void MtCmdCfgOnOff(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  byte bVar2;
  byte local_64 [4];
  undefined4 local_60;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
    bVar2 = 0;
    if (*(int *)(param_1 + 0xa77bb4) == 1) {
      bVar2 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
    }
  }
  else {
    bVar2 = 1;
  }
  os_zero_mem(local_64,0x4c);
  if (2 < DebugLevel) {
    printk("%s, Type:%d Enable:%d Band:%d\n","MtCmdCfgOnOff",param_2,param_3,param_4);
  }
  switch(param_2) {
  case 0:
    local_64[1] = 5;
    break;
  case 1:
    local_64[1] = 6;
    break;
  case 2:
    local_64[1] = 7;
    break;
  case 3:
    local_64[1] = 8;
    break;
  case 4:
    local_64[1] = 0x14;
    break;
  case 5:
    local_64[1] = 0x15;
    uVar1 = param_3;
    goto LAB_001b6b70;
  case 6:
    local_64[1] = 0x18;
    break;
  case 7:
    local_64[1] = 0x19;
    break;
  default:
    uVar1 = param_3;
    if (param_2 == 5) goto LAB_001b6b70;
  }
  local_60._0_2_ = CONCAT11((char)param_4,(char)param_3);
  uVar1 = local_60;
LAB_001b6b70:
  local_60 = uVar1;
  local_64[0] = bVar2;
  MtCmdATETest(param_1,local_64);
  return;
}

