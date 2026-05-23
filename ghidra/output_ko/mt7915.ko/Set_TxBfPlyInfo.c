// module: mt7915.ko
// function: Set_TxBfPlyInfo @ 0xe8d24
// size: 248 bytes
//

undefined4 Set_TxBfPlyInfo(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 uStack_28;
  undefined1 local_27;
  undefined2 local_26;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined1 local_20;
  
  uVar5 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar3 = rstrtok(param_2,&_LC232);
  if (iVar3 == 0) {
    os_zero_mem(&uStack_28,0x10);
    local_27 = 0;
  }
  else {
    do {
      uVar2 = os_str_toul(iVar3,0,0x10);
      uVar4 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      *(undefined2 *)((int)&local_30 + uVar4 * 2) = uVar2;
      iVar3 = rstrtok(0,&_LC232);
    } while (iVar3 != 0);
    uVar1 = (undefined1)local_30;
    uVar5 = local_30 & 0xff;
    os_zero_mem(&uStack_28,0x10);
    local_27 = uVar1;
    uVar1 = (undefined1)((uint)local_2c >> 0x10);
    if (uVar5 == 1) {
      local_24 = (undefined1)(local_30 >> 0x10);
      local_23 = (char)local_2c;
      local_22 = uVar1;
    }
    else if (uVar5 == 2) {
      local_26 = local_30._2_2_;
      local_21 = (char)local_2c;
      local_20 = uVar1;
    }
  }
  TxBfPlyInfo(param_1,&uStack_28);
  return 1;
}

