// module: mt7915.ko
// function: MtCmdBgndScan @ 0x1b9cd4
// size: 564 bytes
//

undefined4 MtCmdBgndScan(undefined4 param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 local_b0;
  undefined1 local_a8;
  char cStack_a7;
  undefined1 uStack_a5;
  undefined1 local_a4;
  undefined1 local_a3;
  undefined1 local_74;
  char local_73;
  undefined1 local_72;
  undefined1 local_71;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  undefined1 uStack_61;
  undefined1 local_60 [60];
  
  uVar3 = param_2 >> 0x10 & 0xff;
  cStack_a7 = (char)(param_2 >> 8);
  local_a8 = (undefined1)param_2;
  uVar4 = param_3 >> 0x10 & 0xff;
  uStack_a5 = (undefined1)(param_2 >> 0x18);
  local_a4 = (undefined1)param_3;
  local_a3 = (undefined1)(param_3 >> 8);
  if (cStack_a7 == '\0') {
    if (DebugLevel < 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("%s: central channel = 0 is invalid\n","MtCmdBgndScan");
      uVar1 = 0xffffffff;
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("%s: control_ch = %d, central_chl = %d, BW = %d,TXStream = %d, RXPath = %d, BandIdx = %d, Reason(%d)\n"
             ,"MtCmdBgndScan",param_2 & 0xff,cStack_a7,uVar3,uStack_a5,param_3 & 0xff,uVar4,local_a3
            );
    }
    iVar2 = AndesAllocCmdMsg(param_1,0x4c);
    if (iVar2 == 0) {
      uVar1 = 3;
    }
    else {
      AndesInitCmdMsg(iVar2,0x4eed0000,0x8000f,0,0,EventExtCmdResult);
      os_zero_mem(&local_74,0x4c);
      local_b0 = (undefined1)(param_3 >> 0x10);
      local_74 = local_a8;
      local_73 = cStack_a7;
      uVar3 = uVar3 - 1 & 0xff;
      local_6e = local_b0;
      local_71 = uStack_a5;
      local_70 = local_a4;
      if (uVar3 < 6) {
        local_72 = (&DAT_0029ecd0)[uVar3];
      }
      else {
        local_72 = 0;
      }
      local_6f = local_a3;
      if (2 < DebugLevel) {
        printk("%s: control_ch = %d, central_chl = %d, BW = %d,TXStream = %d, RXStream = %d, BandIdx=%d, Reason(%d)\n"
               ,"MtCmdBgndScan",param_2 & 0xff,cStack_a7,local_72,uStack_a5,param_3 & 0xff,uVar4,
               local_a3);
      }
      puVar5 = &uStack_61;
      do {
        puVar5 = puVar5 + 1;
        *puVar5 = 0x3f;
      } while (puVar5 != local_60 + 0x30);
      AndesAppendCmdMsg(iVar2,&local_74,0x4c);
      uVar1 = chip_cmd_tx(param_1,iVar2);
    }
    if (3 < DebugLevel) {
      printk("%s:(ret = %d)\n","MtCmdBgndScan",uVar1);
    }
  }
  return uVar1;
}

