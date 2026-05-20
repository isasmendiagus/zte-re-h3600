// module: mt7915.ko
// function: MTAPAutoSelectChannel @ 0x23e84
// size: 788 bytes
//

uint MTAPAutoSelectChannel(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ulonglong uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined1 auStack_70 [4];
  int local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
  uint local_5c;
  undefined8 local_58;
  uint local_50;
  int *local_4c;
  undefined1 auStack_48 [12];
  undefined4 local_3c [3];
  undefined4 ****local_30;
  undefined4 ****local_2c;
  
  local_6c = param_2;
  local_68 = param_3;
  iVar2 = HcGetBandByWdev(param_2);
  local_64 = iVar2;
  iVar3 = HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
  if (iVar2 == 0) {
    if (((*(ushort *)(local_6c + 0x18) & 0xb1) != 0) && (*(char *)(param_1 + 0x79504d) != '\0')) {
      printk("[%s] Incorrect Bandidx for 5G Phy mode\n","MTAPAutoSelectChannel");
    }
  }
  else if (((*(ushort *)(local_6c + 0x18) & 0x4e) != 0) && (*(char *)(param_1 + 0x79504d) != '\0'))
  {
    printk("[%s] Incorrect Bandidx for 2G Phy mode\n","MTAPAutoSelectChannel");
  }
  if (*(int *)(iVar3 + 0x10) == 1) {
    uVar6 = (uint)*(byte *)(iVar3 + 0xd);
    if (0 < DebugLevel) {
      printk("[MTAPAutoSelectChannel] ACS channel is selected, selected ch = %d\n",uVar6);
    }
  }
  else {
    local_4c = &DebugLevel;
    if (2 < DebugLevel) {
      printk("%s----------------->\n","MTAPAutoSelectChannel");
    }
    iVar2 = local_6c;
    APAutoChannelInit(param_1,local_6c);
    AutoChSelBuildChannelList(param_1,param_4,iVar2);
    if (2 < *local_4c) {
      printk("%s: IsABand = %d, ChannelListNum = %d\n","MTAPAutoSelectChannel",param_4,
             *(undefined1 *)(iVar3 + 0xe));
    }
    if (*(char *)(iVar3 + 0xe) != '\0') {
      local_60 = param_1 + 0x36b000;
      local_5c = (uint)auStack_70 & 0xffffe000;
      uVar6 = 0;
      local_50 = 0xcccccccd;
      do {
        iVar2 = iVar3 + uVar6 * 8;
        wlan_operate_scan(local_6c,*(undefined1 *)(iVar2 + 0x74));
        *(char *)(local_60 + 0x861) = (char)uVar6;
        *(undefined1 *)(local_60 + 0x860) = *(undefined1 *)(iVar2 + 0x74);
        AsicGetChBusyCnt(param_1,local_64,0,0);
        iVar2 = HcGetQloadCtrl(param_1);
        if (*(char *)(iVar2 + 0xc0) == '\x01') {
          uVar5 = 400;
        }
        else {
          uVar5 = 200;
        }
        if ((*(uint *)(local_5c + 4) & 0x1fff00) == 0) {
          local_58 = (ulonglong)local_50 * (ulonglong)uVar5;
          uVar1 = (ulonglong)local_58 >> 0x23;
          __init_waitqueue_head(auStack_48,"&_wait",&_LANCHOR1);
          iVar2 = 0;
          do {
            local_3c[0] = 0;
            local_30 = &local_30;
            local_2c = &local_30;
            for (iVar7 = 1; iVar4 = prepare_to_wait_event(auStack_48,local_3c,1),
                iVar7 != 0 && iVar4 == 0; iVar7 = schedule_timeout(iVar7)) {
            }
            iVar2 = iVar2 + 1;
            finish_wait(auStack_48,local_3c);
          } while (iVar2 < (int)(uint)uVar1);
        }
        else {
          RtmpusecDelay(uVar5 * 1000);
        }
        UpdateChannelInfo(param_1,uVar6,local_68,local_6c);
        uVar6 = uVar6 + 1 & 0xff;
      } while (uVar6 < *(byte *)(iVar3 + 0xe));
    }
    uVar6 = SelectBestChannel(param_1,local_68,local_6c);
    if (2 < *local_4c) {
      printk("%s<-----------------\n","MTAPAutoSelectChannel");
    }
  }
  return uVar6;
}

