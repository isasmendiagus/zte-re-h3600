// module: mt7915.ko
// function: CmdHeRaMuMetricInfo @ 0x1b3974
// size: 504 bytes
//

undefined4 CmdHeRaMuMetricInfo(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar3 = 0;
  uVar4 = 0;
  uVar5 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x1c);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    *param_2 = 0x22;
    if (2 < DebugLevel) {
      uVar2 = (uint)(byte)param_2[5];
      printk("%s: u1ReadClr=0x%02X, u1Band=0x%02X, u1NUser=0x%02X, u1DBW=0x%02X,\n",
             "CmdHeRaMuMetricInfo",param_2[2],param_2[3],param_2[4],uVar2,uVar3,uVar4,uVar5);
      if (2 < DebugLevel) {
        printk("u1NTxer=0x%02X, u1PFD=0x%02X, u1RuSize=0x%02X, u1RuIdx=0x%02X\n",param_2[6],
               param_2[7],param_2[8],param_2[9],uVar2,uVar3,uVar4,uVar5);
        if (2 < DebugLevel) {
          printk("u1SpeIdx=0x%02X, u1SpeedUp=0x%02X, u1LDPC=0x%02X, u1PollingTime=0x%02X\n",
                 param_2[10],param_2[0xb],param_2[0xc],param_2[0xd],uVar2,uVar3,uVar4,uVar5);
          if (2 < DebugLevel) {
            printk("%s: u1NStsUser0=0x%02X, u1NStsUser1=0x%02X, u1NStsUser2=0x%02X, u1NStsUser3=0x%02X,\n"
                   ,"CmdHeRaMuMetricInfo",param_2[0x10],param_2[0x11],param_2[0x12],param_2[0x13],
                   uVar3,uVar4,uVar5);
            if (2 < DebugLevel) {
              printk("%s: u2PfidUser0=0x%04X, u2PfidUser1=0x%04X, u2PfidUser2=0x%04X, u2PfidUser3=0x%04X,\n"
                     ,"CmdHeRaMuMetricInfo",*(undefined2 *)(param_2 + 0x14),
                     *(undefined2 *)(param_2 + 0x16),*(undefined2 *)(param_2 + 0x18),
                     *(undefined2 *)(param_2 + 0x1a));
            }
          }
        }
      }
    }
    AndesInitCmdMsg(iVar1,CONCAT13(0x1e,CONCAT12(0xed,(short)uVar3)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar4 >> 8),8)),500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0x1c);
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdHeRaMuMetricInfo",uVar3);
  }
  return uVar3;
}

