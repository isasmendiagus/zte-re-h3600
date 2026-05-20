// module: mt7915.ko
// function: Set_TxBfFbRptDbgInfo @ 0xe8adc
// size: 240 bytes
//

undefined4 Set_TxBfFbRptDbgInfo(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  char local_2b [4];
  char local_27;
  ushort local_26;
  byte local_23;
  byte local_22;
  undefined1 local_21;
  
  uVar4 = 0;
  local_2b[0] = '\0';
  local_2b[1] = 0;
  local_2b[2] = 0;
  iVar3 = rstrtok(param_2,&_LC232);
  if (iVar3 == 0) {
    os_zero_mem(local_2b + 3,0x10);
    local_27 = '\0';
  }
  else {
    do {
      cVar2 = simple_strtol(iVar3,0,10);
      uVar1 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      local_2b[uVar1] = cVar2;
      iVar3 = rstrtok(0,&_LC232);
      local_27 = local_2b[0];
    } while (iVar3 != 0);
    os_zero_mem(local_2b + 3,0x10);
    if (local_27 == '\x03') {
      local_22 = local_2b[1];
    }
    else if (local_27 == '\x04') {
      local_21 = local_2b[2];
      local_26 = (ushort)(byte)local_2b[1];
    }
    else if (local_27 == '\x02') {
      local_23 = local_2b[1];
    }
  }
  TxBfFbRptDbgInfo(param_1,local_2b + 3);
  return 1;
}

