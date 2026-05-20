// module: mt7915.ko
// function: twtPlannerAddAgrtTbl @ 0x169edc
// size: 424 bytes
//

undefined4
twtPlannerAddAgrtTbl(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  bool bVar4;
  undefined1 local_55;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  twtPlannerDbgPrintVal(param_1,param_4);
  if (param_2 != 0 && param_3 != 0) {
    iVar2 = twtPlannerDrvAgrtAdd(param_1,param_2,param_5,param_4,&local_55);
    if (iVar2 == 0) {
      if (*(int *)(param_2 + 0xabc) != 0) {
        local_48 = *(undefined4 *)(param_4 + 0x14);
        bVar3 = *(char *)(param_4 + 2) << 2;
        bVar4 = *(char *)(param_4 + 3) == '\0';
        bVar1 = bVar3 | *(byte *)(param_4 + 1);
        if (bVar4) {
          bVar3 = 2;
        }
        if (!bVar4) {
          bVar3 = 0;
        }
        local_44 = CONCAT13(2,CONCAT12(*(undefined1 *)(param_4 + 6),*(undefined2 *)(param_4 + 8)));
        local_40 = CONCAT31(local_40._1_3_,bVar1 | bVar3);
        local_54 = CONCAT13(param_5,CONCAT12(*(undefined1 *)(*(int *)(param_2 + 0xabc) + 4),
                                             (undefined2)local_54));
        local_4c = *(undefined4 *)(param_4 + 0x10);
        local_54 = CONCAT31(local_54._1_3_,local_55);
        local_50 = CONCAT13(*(undefined1 *)(param_2 + 0x999),
                            CONCAT12(*(undefined1 *)(param_4 + 5),*(undefined2 *)(param_3 + 0xe0)));
        mt_asic_twt_agrt_update
                  (param_2,local_54,local_50,local_4c,local_48,local_44,local_40,local_3c,local_38,
                   local_34,local_30,local_2c);
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s: set twt agrt to FW,wcid=%d,flow_id=%d,tbl_idx=%d\n","twtPlannerAddAgrtTbl",
               *(undefined2 *)(param_3 + 0xe0),param_5,local_55);
        return 0;
      }
    }
    else if (1 < DebugLevel) {
      printk("%s: Agreement table is full\n","twtPlannerAddAgrtTbl");
    }
  }
  return 1;
}

