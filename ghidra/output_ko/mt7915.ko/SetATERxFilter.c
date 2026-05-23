// module: mt7915.ko
// function: SetATERxFilter @ 0x2609b0
// size: 292 bytes
//

undefined4 SetATERxFilter(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [3];
  
  iVar2 = net_ad_wrap_service();
  uVar1 = *(undefined1 *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATERxFilter",param_2);
  }
  iVar4 = 0;
  local_2c[0] = 0;
  local_2c[1] = 0;
  local_2c[2] = 0;
  iVar2 = rstrtok(param_2,&_LC2);
  if (iVar2 == 0) {
    uVar3 = 0;
    uVar6 = 0;
    uVar7 = 0;
  }
  else {
    puVar5 = local_2c;
    do {
      uVar3 = simple_strtol(iVar2,0,0x10);
      iVar4 = iVar4 + 1;
      *puVar5 = uVar3;
      iVar2 = rstrtok(0,&_LC2);
      puVar5 = puVar5 + 1;
    } while (iVar4 != 3 && iVar2 != 0);
    uVar7 = (undefined1)local_2c[0];
    uVar6 = (undefined1)local_2c[1];
    uVar3 = local_2c[2];
  }
  os_zero_mem(&local_34,8);
  local_30._0_3_ = CONCAT12(uVar1,CONCAT11(uVar6,uVar7));
  local_34 = uVar3;
  MtATESetRxFilter(param_1,uVar3,local_30);
  if (0 < DebugLevel) {
    printk("%s: Promiscuous:%x, FrameReport:%x, filterMask:%x\n","SetATERxFilter",local_30 & 0xff,
           local_30._1_1_,local_34);
  }
  return 1;
}

