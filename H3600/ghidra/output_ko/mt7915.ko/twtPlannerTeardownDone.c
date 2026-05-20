// module: mt7915.ko
// function: twtPlannerTeardownDone @ 0x168f54
// size: 548 bytes
//

undefined4 twtPlannerTeardownDone(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 local_54;
  int local_50;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: wdev=NULL, please check\n","twtPlannerTeardownDone");
    uVar3 = 1;
  }
  else {
    iVar1 = (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
    if (&DAT_0036db58 + param_1 + iVar1 == (undefined *)0x0) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: apcli_entry=NULL, please check\n","twtPlannerTeardownDone");
      uVar3 = 1;
    }
    else {
      iVar4 = *(int *)(&DAT_0057ffc4 + param_1 + iVar1);
      if (iVar4 == 0) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk("%s: pEntry=NULL, please check\n","twtPlannerTeardownDone");
        uVar3 = 1;
      }
      else {
        iVar5 = *(int *)(param_2 + 0xabc);
        if ((iVar5 != 0) && (uVar2 = FUN_00166e8c(), uVar2 < 0x10)) {
          __memzero(&DAT_00581100 + param_1 + iVar1 + uVar2 * 0x20,0x20);
          local_50 = (uint)*(byte *)(param_2 + 0x999) << 0x18;
          local_54 = (uint)*(byte *)(iVar5 + 4) << 0x10;
          local_54 = CONCAT31(local_54._1_3_,(char)uVar2);
          local_54 = CONCAT13((char)param_3,(undefined3)local_54);
          local_54._0_2_ = CONCAT11(2,(char)uVar2);
          local_50 = CONCAT22(local_50._2_2_,*(undefined2 *)(iVar4 + 0xe0));
          mt_asic_twt_agrt_update(param_2,local_54,local_50,0,0,0x2000000,0,0,0,0,0,0);
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s del twt agrt to FW,wcid=%d,flow_id=%d,tbl_idx=%d\n","twtPlannerDelAgrtTbl",
                 *(undefined2 *)(iVar4 + 0xe0),param_3,uVar2);
        }
        if (DebugLevel < 3) {
          uVar3 = 0;
        }
        else {
          printk("%s: wcid(%d), flow_id(%d)\n","twtPlannerTeardownDone",
                 *(undefined2 *)(iVar4 + 0xe0),param_3);
          uVar3 = 0;
        }
      }
    }
  }
  return uVar3;
}

