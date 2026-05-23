// module: mt7915.ko
// function: sta_dev_rx_mgmt_frm @ 0x56564
// size: 748 bytes
//

undefined4 sta_dev_rx_mgmt_frm(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined *puVar4;
  byte *pbVar5;
  uint uVar6;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  byte local_2a;
  undefined1 local_29;
  
  pbVar5 = *(byte **)(param_2 + 0x1c);
  if (param_3 == (int *)0x0) {
    uVar6 = (uint)*(byte *)(param_1 + 0x794ab8);
    if (uVar6 == 0) {
      return 1;
    }
  }
  else {
    iVar1 = wdev_search_by_wcid(param_1,(short)param_3[0x38]);
    if (((((iVar1 != 0) && (iVar1 = GetStaCfgByWdev(param_1), iVar1 != 0)) &&
         ((*(uint *)(iVar1 + 0x212464) & 1) != 0)) &&
        ((iVar2 = RtmpPktPmBitCheck(param_1,iVar1), iVar2 == 1 && ((pbVar5[1] & 0x20) != 0)))) &&
       (*(char *)(param_1 + 0x794caa) == '\0')) {
      hif_ps_poll_enq(param_1,iVar1);
    }
    uVar6 = (uint)*(byte *)(param_1 + 0x794ab8);
    if (uVar6 == 0) goto LAB_0005661c;
  }
  pcVar3 = &DAT_0036e600 + param_1;
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    if (((*pcVar3 != '\0') && ((*pbVar5 & 0xf0) == 0x80)) &&
       ((iVar2 = memcmp(pcVar3 + 0x211980,(void *)(param_2 + 0x2c),6), iVar2 == 0 &&
        ("RadarStateCheck"[param_1 + 0xc] == '\0')))) {
      pcVar3[-0x1a0] = *(char *)(param_2 + 0x5c);
      pcVar3[-0x19f] = *(char *)(param_2 + 0x5d);
    }
    pcVar3 = pcVar3 + 0x2137b0;
  } while (iVar1 < (int)uVar6);
  if (param_3 == (int *)0x0) {
    puVar4 = &DAT_0036db58 + param_1;
    iVar1 = 0;
    do {
      iVar1 = iVar1 + 1;
      if (puVar4[0xaa8] != '\0') {
        local_2a = *(byte *)(param_2 + 0x5c);
        if (*(byte *)(param_2 + 0x5d) <= *(byte *)(param_2 + 0x5c)) {
          local_2a = *(byte *)(param_2 + 0x5d);
        }
        local_2e = *(undefined1 *)(param_2 + 0x58);
        local_2d = *(undefined1 *)(param_2 + 0x59);
        local_2c = *(undefined1 *)(param_2 + 0x5a);
        local_2b = *(undefined1 *)(param_2 + 0x5b);
        local_29 = (undefined1)*(undefined2 *)(param_2 + 0x80);
        MlmeEnqueueForRecv(param_1,*(undefined2 *)(param_2 + 0x4e),&local_2e,
                           *(undefined2 *)(param_2 + 0x40),pbVar5,0,puVar4,
                           *(byte *)(param_2 + 99) >> 5);
      }
      puVar4 = puVar4 + 0x2137b0;
    } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x794ab8));
    return 1;
  }
LAB_0005661c:
  if (((*pbVar5 & 0xf0) == 0xd0) && (*param_3 == 0x10001)) {
    RtmpPsIndicate(param_1,*(undefined4 *)(param_2 + 0x2c),*(undefined2 *)(param_2 + 0x4e),
                   ((uint)pbVar5[1] << 0x1b) >> 0x1f);
  }
  if (param_3[2] == 0) {
    printk(&_LC23,0xa07);
    dump_stack();
  }
  else {
    local_2e = *(undefined1 *)(param_2 + 0x58);
    local_2d = *(undefined1 *)(param_2 + 0x59);
    local_2c = *(undefined1 *)(param_2 + 0x5a);
    local_2a = *(byte *)(param_2 + 0x5c);
    if (*(byte *)(param_2 + 0x5d) <= *(byte *)(param_2 + 0x5c)) {
      local_2a = *(byte *)(param_2 + 0x5d);
    }
    local_2b = *(undefined1 *)(param_2 + 0x5b);
    local_29 = (undefined1)*(undefined2 *)(param_2 + 0x80);
    MlmeEnqueueForRecv(param_1,*(undefined2 *)(param_2 + 0x4e),&local_2e,
                       *(undefined2 *)(param_2 + 0x40),pbVar5,0,param_3[2],
                       *(byte *)(param_2 + 99) >> 5);
  }
  return 1;
}

