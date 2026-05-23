// module: mt7915.ko
// function: SetSrCfgProfile @ 0x16c7a4
// size: 72 bytes
//

int SetSrCfgProfile(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x1c,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 set srcfgsrprofile=3\nSR_PROFILE_QUERY_TXD_TIME           BIT(0)\nSR_PROFILE_SHOW_Q_LEN               BIT(1)\nSR_PROFILE_RPT_HANDLE_TIME          BIT(2)\nSR_PROFILE_GEN_TXC_TIME             BIT(3)\n"
           ,"SetSrCfgProfile");
  }
  return iVar1;
}

