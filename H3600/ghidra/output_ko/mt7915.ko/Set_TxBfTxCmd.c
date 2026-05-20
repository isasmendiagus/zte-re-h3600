// module: mt7915.ko
// function: Set_TxBfTxCmd @ 0xe8e1c
// size: 200 bytes
//

undefined4 Set_TxBfTxCmd(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char local_20 [9];
  char local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  uVar5 = 0;
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  iVar3 = rstrtok(param_2,&_LC232);
  if (iVar3 == 0) {
    os_zero_mem(local_20 + 8,8);
    local_17 = '\0';
  }
  else {
    do {
      uVar2 = os_str_toul(iVar3,0,0x10);
      uVar4 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      *(undefined2 *)(local_20 + uVar4 * 2) = uVar2;
      iVar3 = rstrtok(0,&_LC232);
    } while (iVar3 != 0);
    cVar1 = local_20[0];
    os_zero_mem(local_20 + 8,8);
    local_17 = cVar1;
    if (cVar1 == '\x01') {
      local_16 = SUB41(local_20._0_4_,2);
      local_15 = (undefined1)local_20._4_4_;
    }
  }
  TxBfTxCmd(param_1,local_20 + 8);
  return 1;
}

