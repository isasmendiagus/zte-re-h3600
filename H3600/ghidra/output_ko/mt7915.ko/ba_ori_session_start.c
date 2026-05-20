// module: mt7915.ko
// function: ba_ori_session_start @ 0xa879c
// size: 348 bytes
//

void ba_ori_session_start(int param_1,int *param_2,uint param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = (uint)*(ushort *)(param_2 + 2);
  iVar4 = uVar5 * 0x14c0 + param_1;
  iVar2 = wlan_config_get_ba_enable(*(undefined4 *)(iVar4 + 0xa1d28));
  if (((int)(uint)*(ushort *)(iVar4 + 0xa29e0) >> (param_3 & 0xff) & 1U) != 0) {
    return;
  }
  if (iVar2 == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("HT_AutoBA = 0, disable BA\n");
    return;
  }
  if (param_2 == (int *)0x0) {
    return;
  }
  if (*param_2 == 0x400) {
    return;
  }
  uVar1 = *(ushort *)(param_2 + 2);
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar3 <= uVar1) {
    return;
  }
  if (*(byte *)(iVar4 + 0xa1ddf) < 0x40) {
    return;
  }
  if (*(char *)((int)param_2 + 0xc2) != '\x01') {
    return;
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) != 0) {
    return;
  }
  if (((((*(uint *)(iVar4 + 0xa1dd4) & 0x100000) == 0) && ((*(uint *)(iVar4 + 0xa1d20) & 0xc) == 0))
      && ((iVar2 = uVar5 * 0x14c0 + param_1, (*(uint *)(iVar2 + 0xa1e9c) & 1) == 0 ||
          ((*(uint *)(iVar2 + 0xa1fe4) & 1) == 0)))) &&
     ((*(uint *)(uVar5 * 0x14c0 + param_1 + 0xa1fe4) & 0x1e0) == 0)) {
    return;
  }
  ba_ori_session_setup(param_1,*(undefined2 *)(uVar5 * 0x14c0 + param_1 + 0xa1e00),param_3,0);
  return;
}

