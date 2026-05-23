// module: mt7915.ko
// function: log_time_end @ 0x147760
// size: 376 bytes
//

void log_time_end(undefined1 param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int local_30;
  int local_2c;
  
  if (*(char *)((int)param_4 + 0x11) == '\x01') {
    do_gettimeofday(&local_30);
    param_4[2] = (local_2c + (local_30 - *param_4) * 1000000) - param_4[1];
  }
  else if (*(char *)((int)param_4 + 0x11) == '\0') {
    param_4[2] = jiffies - param_4[2];
  }
  param_4[3] = param_2;
  iVar6 = param_4[3];
  uVar7 = _LANCHOR0 + 1;
  iVar4 = param_4[1];
  iVar5 = param_4[2];
  iVar1 = (uint)_LANCHOR0 * 0x14;
  *(undefined1 *)(param_4 + 4) = param_1;
  iVar2 = DebugLevel;
  *(int *)(&DAT_005f36ac + iVar1) = *param_4;
  *(int *)(&DAT_005f36b0 + iVar1) = iVar4;
  *(int *)(&DAT_005f36b4 + iVar1) = iVar5;
  *(int *)(&DAT_005f36b8 + iVar1) = iVar6;
  *(int *)(&DAT_005f36bc + iVar1) = param_4[4];
  _LANCHOR0 = (char)uVar7 + (char)((uVar7 & 0xff) / 0x28) * -0x28;
  if (param_3 <= iVar2) {
    if (*(char *)((int)param_4 + 0x11) == '\x01') {
      if (0 < iVar2) {
        printk("%s: %lu usec\n",param_2,param_4[2]);
      }
    }
    else if ((*(char *)((int)param_4 + 0x11) == '\0') && (0 < iVar2)) {
      printk("%s: %lu jiffies",param_2,param_4[2]);
      if (0 < DebugLevel) {
        uVar3 = jiffies_to_msecs(param_4[2]);
        printk(", %u msec\n",uVar3);
      }
    }
  }
  return;
}

