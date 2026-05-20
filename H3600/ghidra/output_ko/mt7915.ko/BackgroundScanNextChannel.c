// module: mt7915.ko
// function: BackgroundScanNextChannel @ 0x22e070
// size: 504 bytes
//

void BackgroundScanNextChannel(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  code *pcVar4;
  undefined1 local_34 [3];
  undefined1 local_31;
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = param_2 >> 4;
  os_zero_mem(local_34,0x14);
  if (2 < DebugLevel) {
    printk("%s Scan Channel=%d, band idx = %d ===============>\n","BackgroundScanNextChannel",
           *(undefined1 *)(param_1 + 0xa7905c),uVar1);
  }
  if (*(char *)(param_1 + 0xa7905c) == '\0') {
    if (*(code **)(iVar2 + 0x280) != (code *)0x0) {
      (**(code **)(iVar2 + 0x280))(param_1,8);
    }
    GenerateGroupChannelList(param_1);
    uVar3 = BgndSelectBestChannel(param_1,uVar1);
    iVar2 = DebugLevel;
    *(char *)(param_1 + 0xa795e5) = (char)uVar3;
    if (0 < iVar2) {
      printk("Best Channel=%d, IsSwitchChannel=%d Noisy=%d\n",uVar3,
             *(undefined1 *)(param_1 + 0xa79791),*(undefined4 *)(param_1 + 0xa7961c));
    }
    *(undefined4 *)(param_1 + 0xa79184) = 0;
    *(undefined1 *)(param_1 + 0xa79754) = 0;
    if ((*(byte *)(param_1 + uVar1 * 0x14 + 0xa795e8) != uVar3) &&
       (*(char *)(param_1 + 0xa79791) == '\x01')) {
      *(undefined1 *)(param_1 + 0xa79791) = 0;
      MlmeEnqueue(param_1,0x2b,3,0,0,0);
      RtmpOsMlmeUp(param_1 + 0x286298);
    }
    *(undefined1 *)(param_1 + 0xa79791) = 0;
    greenap_resume(param_1,1);
    return;
  }
  if ((param_2 & 0xf) == 1) {
    *(undefined4 *)(param_1 + 0xa79184) = 1;
    pcVar4 = *(code **)(iVar2 + 0x280);
  }
  else {
    *(undefined4 *)(param_1 + 0xa79184) = 1;
    pcVar4 = *(code **)(iVar2 + 0x280);
    if (*(char *)(param_1 + 0xa7922e) != *(char *)(param_1 + 0xa7905c)) {
      if (pcVar4 != (code *)0x0) {
        (*pcVar4)(param_1,7,0);
      }
      goto LAB_0022e190;
    }
  }
  if (pcVar4 != (code *)0x0) {
    (*pcVar4)(param_1,6,0);
  }
LAB_0022e190:
  local_34[0] = 1;
  local_31 = 0;
  mt_cmd_set_rdd_ipi_hist(param_1,local_34);
  RTMPSetTimer(param_1 + 0xa79190,*(undefined2 *)(param_1 + 0xa79230));
  return;
}

