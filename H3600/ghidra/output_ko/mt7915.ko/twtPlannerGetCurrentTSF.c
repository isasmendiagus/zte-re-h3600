// module: mt7915.ko
// function: twtPlannerGetCurrentTSF @ 0x16a2d8
// size: 500 bytes
//

undefined4 twtPlannerGetCurrentTSF(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint local_30;
  int local_2c;
  
  local_30 = 0;
  local_2c = 0;
  if (param_2 != 0) {
    bVar1 = *(byte *)(param_2 + 0xe);
    if ((&DAT_0036db58 + param_1 + (uint)bVar1 * 0x2137b0 != (undefined *)0x0) &&
       ((twt_get_current_tsf(param_2,&local_30), iVar5 = local_2c, uVar2 = local_30, local_30 != 0
        || (local_2c != 0)))) {
      if (2 < DebugLevel) {
        printk("%s: u8CurTsf=%llu, Reason=%d\n","twtPlannerGetCurrentTSF",local_30,local_2c,*param_3
              );
      }
      iVar4 = *(int *)(&DAT_0057ffc4 + param_1 + (uint)bVar1 * 0x2137b0);
      if (iVar4 != 0) {
        if (*param_3 == 1) {
          param_3[6] = uVar2 + 1000000;
          param_3[7] = iVar5 + (uint)(0xfff0bdbf < uVar2);
          twtPlannerAddAgrtTbl(param_1,param_2,iVar4,param_3 + 2,*(undefined1 *)((int)param_3 + 5));
          return 0;
        }
        if (*param_3 != 2) {
          if (-1 < DebugLevel) {
            printk("Unknown reason to get TSF %u\n");
            return 0;
          }
          return 0;
        }
        piVar3 = (int *)FUN_001675e4(&DAT_0036db58 + param_1 + (uint)bVar1 * 0x2137b0,
                                     *(undefined1 *)((int)param_3 + 5));
        if (piVar3 != (int *)0x0) {
          param_3[6] = (int)(&DAT_004c4b40 + uVar2);
          param_3[7] = iVar5 + (uint)(0xffb3b4bf < uVar2);
          iVar5 = param_3[3];
          iVar6 = param_3[4];
          iVar4 = param_3[5];
          *piVar3 = param_3[2];
          piVar3[1] = iVar5;
          piVar3[2] = iVar6;
          piVar3[3] = iVar4;
          iVar5 = param_3[6];
          piVar3[5] = param_3[7];
          piVar3[4] = iVar5;
          twtReqFsmSendEvent(param_1,param_2,*(undefined1 *)((int)param_3 + 5),0);
          return 0;
        }
      }
    }
  }
  return 1;
}

