// module: mt7915.ko
// function: Set_HostReportTxLatency @ 0xe6514
// size: 60 bytes
//

bool Set_HostReportTxLatency(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = os_str_tol(param_2,0,10);
  iVar2 = CmdExtCmdCfgUpdate(param_1,1,0,uVar1);
  return iVar2 == 1;
}

