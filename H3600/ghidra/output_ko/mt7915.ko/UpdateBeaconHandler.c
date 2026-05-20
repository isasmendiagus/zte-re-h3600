// module: mt7915.ko
// function: UpdateBeaconHandler @ 0xb4fc0
// size: 540 bytes
//

void UpdateBeaconHandler(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    pcVar4 = "UpdateBeaconHandler";
    uVar2 = 0xddd8;
LAB_000b5140:
    printk(uVar2 | 0x2c0000,pcVar4);
    return;
  }
  if (DebugLevel < 3) {
    iVar5 = *(int *)(param_2 + 0x14);
    if ((iVar5 - 0x10U & 0xffffffef) != 0 && (iVar5 != 4 && iVar5 != 1)) {
      return;
    }
  }
  else {
    uVar1 = *(undefined1 *)(param_2 + 0xc);
    uVar3 = RtmpOsGetNetDevName(*(undefined4 *)(param_1 + 4));
    printk("%s, wdev(%d) devname:%s, reason = %d (caller:%pS)\n","UpdateBeaconHandler",uVar1,uVar3,
           param_3);
    iVar5 = *(int *)(param_2 + 0x14);
    if ((iVar5 - 0x10U & 0xffffffef) != 0 && (iVar5 != 4 && iVar5 != 1)) {
      if (DebugLevel < 3) {
        return;
      }
      printk("%s, wdev(%d) beacon needless (type:%d, caller:%pS)\n","UpdateBeaconHandler",
             *(undefined1 *)(param_2 + 0xc));
      return;
    }
  }
  if (*(uint *)(param_2 + 0x990) < 3) {
    if (0 < DebugLevel) {
      printk("%s, wdev(%d) bss not ready (state:%d, caller:%pS)!!\n","UpdateBeaconHandler",
             *(undefined1 *)(param_2 + 0xc));
    }
    return;
  }
  if ((*(int *)(param_2 + 0x3fe4) == 0) || (*(char *)(*(int *)(param_2 + 0x3fe4) + 4) != '\x01')) {
    if (param_3 == 0) {
      if (0 < DebugLevel) {
        printk("BCN_UPDATE_INIT, OmacIdx = %x\n",*(undefined1 *)(param_2 + 0x29));
      }
      iVar5 = bcn_buf_init(param_1,param_2);
      if (iVar5 != 0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("bcn_buf_init fail!!\n");
        return;
      }
      *(undefined1 *)(param_2 + 0x950) = 1;
      *(undefined4 *)(param_1 + 0x829214) = 0;
    }
  }
  else if (param_3 != 8) {
    if (DebugLevel < 0) {
      return;
    }
    pcVar4 = (char *)(uint)*(byte *)(param_2 + 0xc);
    uVar2 = 0xde98;
    goto LAB_000b5140;
  }
  HW_BEACON_UPDATE(param_1,param_2,param_3 & 0xff);
  ZTE_wlan_default_setting(param_1,param_2);
  return;
}

