// module: mt7915.ko
// function: ZeroWait_DFS_set_NOP_to_Channel_List @ 0x237938
// size: 436 bytes
//

void ZeroWait_DFS_set_NOP_to_Channel_List(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  if (DebugLevel < 1) {
    if (2 < param_3) {
      return;
    }
  }
  else {
    printk("[%s] Channel: %d, Bw: %d, NOP: %d\n","ZeroWait_DFS_set_NOP_to_Channel_List",param_2,
           param_3,param_4);
    if (2 < param_3) {
      if (DebugLevel < 1) {
        return;
      }
      printk("[%s] Not a valid BW for ZeroWait\n","ZeroWait_DFS_set_NOP_to_Channel_List");
      return;
    }
  }
  iVar1 = RadarChannelCheck(param_1,param_2);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("[%s] Ch %d is not a DFS channel. InValid\n","ZeroWait_DFS_set_NOP_to_Channel_List",
             param_2);
      return;
    }
  }
  else {
    iVar1 = 0;
    while( true ) {
      pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar1);
      if (pbVar2[0x49c] == 0) break;
      uVar4 = 0;
      pbVar6 = pbVar2 + ((byte)(pbVar2[0x49c] - 1) + 1) * 0x14;
      pbVar3 = pbVar2;
      do {
        pbVar5 = pbVar3 + 0x14;
        if (*pbVar3 == param_2) {
          uVar4 = (uint)pbVar3[8] & 1 << (param_3 & 0xff) & 0xffU;
        }
        pbVar3 = pbVar5;
      } while (pbVar5 != pbVar6);
      if (uVar4 == 0) break;
      do {
        while (*pbVar2 != param_2) {
          pbVar2 = pbVar2 + 0x14;
          if (pbVar2 == pbVar6) goto LAB_00237a40;
        }
        pbVar2[9] = (byte)param_3;
        pbVar3 = pbVar2 + 0x14;
        if (param_3 - 1 < 2) {
          *(short *)(pbVar2 + 10) = (short)param_4;
        }
        else {
          *(short *)(pbVar2 + 0xc) = (short)param_4;
        }
        pbVar2[7] = pbVar2[7] + 1;
        pbVar2 = pbVar3;
      } while (pbVar3 != pbVar6);
LAB_00237a40:
      if (iVar1 == 1) {
        return;
      }
      iVar1 = 1;
    }
    if (0 < DebugLevel) {
      printk("[%s] Ch%d doesn\'t support BW %d\n","ZeroWait_DFS_set_NOP_to_Channel_List",param_2,
             param_3);
      return;
    }
  }
  return;
}

