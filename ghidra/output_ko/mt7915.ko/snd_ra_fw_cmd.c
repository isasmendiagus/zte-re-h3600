// module: mt7915.ko
// function: snd_ra_fw_cmd @ 0x1dd34c
// size: 240 bytes
//

void snd_ra_fw_cmd(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_3c [4];
  int local_38;
  undefined1 local_2d;
  undefined1 local_2a;
  undefined1 local_28;
  
  iVar2 = param_2 + 0x285d58;
  hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
  down_interruptible(iVar2);
  if ((*(int *)(param_3 * 0x14c0 + param_2 + 0xa1d20) != 0) && (*(char *)(iVar1 + 0x150) == '\x01'))
  {
    __memzero(auStack_3c,0x1c);
    if (param_1 == 8) {
      local_2a = *param_4;
    }
    else if (param_1 == 0xb) {
      local_2d = *param_4;
    }
    else {
      if (param_1 != 7) goto LAB_001dd3b8;
      local_28 = *param_4;
    }
    local_38 = param_1;
    RAParamUpdate(param_2,param_3 * 0x14c0 + param_2 + 0xa1d20,auStack_3c);
    up(iVar2);
    return;
  }
LAB_001dd3b8:
  up(iVar2);
  return;
}

