// module: mt7915.ko
// function: DfsSelectChannel @ 0x2354dc
// size: 1148 bytes
//

void DfsSelectChannel(int param_1,byte *param_2,int param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  bool bVar7;
  
  pbVar6 = param_2 + 0x2b4;
  iVar5 = 0;
  do {
    if (2 < DebugLevel) {
      printk("[%s]: RadarDetected[%d]=%d, pDfsParam->DfsChBand[%d]=%d\n","DfsSelectChannel",iVar5,
             *pbVar6,iVar5,pbVar6[-3]);
    }
    bVar7 = iVar5 != 1;
    iVar5 = 1;
    pbVar6 = pbVar6 + 1;
  } while (bVar7);
  if (param_2[param_3 + 4] == 3) {
    if (((param_2[0x2b4] != 0) && (param_2[0x2b1] != 0)) ||
       ((param_2[0x2b5] != 0 && (param_2[0x2b2] != 0)))) {
      uVar1 = WrapDfsRandomSelectChannel(param_1,0,0,0);
      *param_2 = (byte)uVar1;
      if (2 < DebugLevel) {
        printk("[%s]: BW_160, Single band, selected is %d\n","DfsSelectChannel",uVar1);
        uVar3 = (uint)param_2[param_3];
        goto LAB_002355dc;
      }
    }
  }
  else {
    if (param_2[param_3 + 4] == 6) {
      uVar3 = (uint)*param_2;
      uVar4 = (uint)param_2[1];
      if (uVar3 < uVar4) {
        if ((param_2[0x2b4] != 0) && (param_2[0x2b1] != 0)) {
          uVar3 = WrapDfsRandomSelectChannel(param_1,0,uVar4,param_3);
          *param_2 = (byte)uVar3;
        }
        if ((param_2[0x2b5] == 0) || (param_2[0x2b2] == 0)) {
          uVar4 = (uint)param_2[1];
        }
        else {
          uVar4 = WrapDfsRandomSelectChannel(param_1,0,uVar3,param_3);
          uVar3 = (uint)*param_2;
          param_2[1] = (byte)uVar4;
        }
      }
      if (2 < DebugLevel) {
        printk("[%s]: 80+80MHz band, selected is %d, %d\n","DfsSelectChannel");
        uVar3 = (uint)*param_2;
        uVar4 = (uint)param_2[1];
      }
      if (param_2[3] == 0) {
        param_2[2] = (byte)uVar3;
        uVar2 = uVar3;
        if (uVar3 <= uVar4) goto LAB_002355c0;
LAB_002355a0:
        param_2[1] = (byte)uVar3;
        *param_2 = (byte)uVar4;
        uVar3 = uVar4;
      }
      else {
        param_2[2] = (byte)uVar4;
        uVar2 = uVar4;
        if (uVar4 < uVar3) goto LAB_002355a0;
      }
      if (uVar2 != uVar3) {
        param_2[3] = 1;
        return;
      }
LAB_002355c0:
      param_2[3] = 0;
      return;
    }
    if ((param_2[param_3 + 0x2b4] != 0) && (param_2[param_3 + 0x2b1] != 0)) {
      if ((param_2[0x2ca] == 1) && (*(int *)(param_1 + 0xa79184) == 2)) {
        uVar3 = WrapDfsRandomSelectChannel(param_1,0,0,param_3);
        if (2 < DebugLevel) {
          printk("[%s]: tempCh selected is %d\n","DfsSelectChannel",uVar3);
        }
        iVar5 = RadarChannelCheck(param_1,uVar3);
        if (iVar5 == 0) {
          *(undefined4 *)(param_1 + 0x79540c) = 0;
          *(undefined1 *)(param_1 + 0x7953fb) = 0;
          mtRddControl(param_1,0,2,0,0);
          param_2[param_3] = (byte)uVar3;
          if (DebugLevel < 1) goto LAB_002355dc;
          printk("RDD[%d] detect. InBand channel is switched to another non-DFS channel randomly\n",
                 param_3);
          uVar3 = (uint)param_2[param_3];
        }
        else {
          pbVar6 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),param_3);
          if (*(int *)(param_1 + 0x79540c) == 3) {
            if (0 < DebugLevel) {
              printk("[%s]: out-band CAC is not ended, ch_stat %d\n","DfsSelectChannel");
            }
            *(undefined4 *)(param_1 + 0x79540c) = 2;
            uVar3 = (uint)param_2[0x2cb];
            param_2[param_3] = param_2[0x2cb];
          }
          else if (*(int *)(param_1 + 0x79540c) == 4) {
            if (0 < DebugLevel) {
              printk("[%s]: out-band CAC is ended, ch_stat %d\n","DfsSelectChannel");
            }
            param_2[param_3] = *pbVar6;
            iVar5 = DebugLevel;
            *(undefined4 *)(param_1 + 0x79540c) = 5;
            if ((iVar5 < 1) ||
               (printk("RDD[%d] detect. OutBand channel %d will be set to InBand\n",param_3,
                       param_2[0x2cb]), DebugLevel < 3)) goto LAB_002355d8;
            printk("[%s]: ch_stat %d\n","DfsSelectChannel",*(undefined4 *)(param_1 + 0x79540c));
            uVar3 = (uint)param_2[param_3];
          }
          else if (param_2[0x2d4] == 0) {
            param_2[param_3] = param_2[0x2cb];
            if (DebugLevel < 3) goto LAB_002355d8;
            printk("%s, RDD[%d] detect. zw DFS is not enabled\n","DfsSelectChannel",param_3);
            uVar3 = (uint)param_2[param_3];
          }
          else {
            uVar3 = (uint)param_2[param_3];
          }
        }
      }
      else {
        uVar3 = WrapDfsRandomSelectChannel(param_1,0,param_2[1 - param_3],param_3);
        param_2[param_3] = (byte)uVar3;
      }
      if (DebugLevel < 3) goto LAB_002355dc;
      printk("[%s]: band index: %d, selected is %d\n","DfsSelectChannel",param_3);
    }
  }
LAB_002355d8:
  uVar3 = (uint)param_2[param_3];
LAB_002355dc:
  param_2[2] = (byte)uVar3;
  param_2[3] = (byte)param_3;
  return;
}

