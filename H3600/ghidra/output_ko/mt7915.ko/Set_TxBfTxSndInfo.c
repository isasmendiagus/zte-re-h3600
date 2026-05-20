// module: mt7915.ko
// function: Set_TxBfTxSndInfo @ 0xe8bcc
// size: 316 bytes
//

undefined4 Set_TxBfTxSndInfo(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 uStack_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined2 local_22;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 uVar2;
  undefined1 uVar3;
  
  uVar7 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar5 = rstrtok(param_2,&_LC232);
  if (iVar5 == 0) {
    os_zero_mem(&uStack_28,0x10);
    local_27 = 0;
switchD_000e8c54_caseD_0:
    local_26 = (undefined1)(local_30 >> 0x10);
  }
  else {
    do {
      uVar4 = os_str_toul(iVar5,0,0x10);
      uVar6 = uVar7 & 0xff;
      uVar7 = uVar7 + 1;
      *(undefined2 *)((int)&local_30 + uVar6 * 2) = uVar4;
      iVar5 = rstrtok(0,&_LC232);
    } while (iVar5 != 0);
    uVar3 = (undefined1)local_30;
    uVar7 = local_30 & 0xff;
    os_zero_mem(&uStack_28,0x10);
    local_27 = uVar3;
    uVar1 = (undefined1)(local_30 >> 0x10);
    uVar2 = (undefined1)local_2c;
    uVar3 = (undefined1)((uint)local_2c >> 0x10);
    switch(uVar7) {
    case 0:
      goto switchD_000e8c54_caseD_0;
    case 1:
      local_25 = uVar1;
      local_24 = uVar2;
      local_23 = uVar3;
      break;
    case 2:
      local_22 = local_30._2_2_;
      local_20 = uVar2;
      break;
    case 3:
      local_22 = local_30._2_2_;
      local_1f = uVar2;
      break;
    case 4:
      local_1e = uVar1;
      break;
    case 5:
      local_1d = uVar1;
      local_1c = uVar2;
      local_1b = uVar3;
      break;
    case 6:
      local_1a = uVar1;
    }
  }
  TxBfTxSndInfo(param_1,&uStack_28);
  return 1;
}

