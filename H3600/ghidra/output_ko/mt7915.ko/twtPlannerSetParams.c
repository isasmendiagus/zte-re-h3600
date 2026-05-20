// module: mt7915.ko
// function: twtPlannerSetParams @ 0x16a4d0
// size: 360 bytes
//

void twtPlannerSetParams(undefined4 param_1,int param_2,uint param_3,undefined4 param_4,
                        undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                        undefined4 param_9,undefined4 param_10)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 uVar7;
  undefined4 *local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  uVar6 = *(undefined4 *)(param_2 + 8);
  local_4c = (undefined4 *)0x0;
  local_40 = param_5;
  uStack_3c = param_6;
  local_48._1_1_ = (char)(param_3 >> 8);
  cVar3 = local_48._1_1_;
  local_48._0_1_ = (undefined1)param_3;
  uVar2 = (undefined1)local_48;
  local_38 = param_7;
  uStack_34 = param_8;
  local_30 = param_9;
  uStack_2c = param_10;
  bVar1 = local_48._1_1_ == '\x01';
  uStack_44 = param_4;
  if (local_48._1_1_ == '\x01' || local_48._1_1_ == '\x04') {
    local_48 = param_3;
    os_alloc_mem(uVar6,&local_4c,0x20);
    if (local_4c == (undefined4 *)0x0) {
      return;
    }
    uVar7 = local_48._2_1_;
    if (bVar1) {
      uVar5 = 1;
    }
    else {
      uVar5 = 2;
    }
    *local_4c = uVar5;
    local_4c[2] = local_40;
    local_4c[3] = uStack_3c;
    local_4c[4] = local_38;
    local_4c[5] = uStack_34;
    local_4c[6] = local_30;
    local_4c[7] = uStack_2c;
    *(undefined1 *)(local_4c + 1) = uVar2;
    *(undefined1 *)((int)local_4c + 5) = local_48._2_1_;
    twtPlannerGetCurrentTSF(uVar6,param_2,local_4c,0x20);
    uVar4 = local_48;
    if (local_4c != (undefined4 *)0x0) {
      os_free_mem();
      uVar4 = local_48;
    }
  }
  else {
    local_48._2_1_ = (undefined1)(param_3 >> 0x10);
    uVar4 = param_3;
    uVar7 = local_48._2_1_;
  }
  local_48 = uVar4;
  if (cVar3 == '\x05') {
    uVar4 = FUN_00166e8c(uVar6,param_2,uVar7);
    if (uVar4 < 0x10) {
      twtReqFsmSendEvent(uVar6,param_2,uVar7,1);
      return;
    }
    if (-1 < DebugLevel) {
      printk("BSS %u TWT flow %u doesn\'t exist\n\n",param_3 & 0xff,uVar7);
    }
  }
  return;
}

