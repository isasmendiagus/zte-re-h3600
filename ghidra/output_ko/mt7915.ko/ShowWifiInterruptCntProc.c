// module: mt7915.ko
// function: ShowWifiInterruptCntProc @ 0xea43c
// size: 180 bytes
//

undefined4 ShowWifiInterruptCntProc(undefined4 param_1)

{
  int iVar1;
  undefined4 local_3c;
  char local_38 [4];
  char acStack_34 [4];
  char acStack_30 [4];
  char acStack_2c [4];
  char local_28 [4];
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  iVar1 = 0;
  local_38[0] = 'W';
  local_38[1] = 'i';
  local_38[2] = 'f';
  local_38[3] = 'i';
  acStack_34[0] = ' ';
  acStack_34[1] = 'A';
  acStack_34[2] = 'b';
  acStack_34[3] = 'n';
  acStack_30[0] = 'o';
  acStack_30[1] = 'r';
  acStack_30[2] = 'm';
  acStack_30[3] = 'a';
  acStack_2c[0] = 'l';
  acStack_2c[1] = ' ';
  acStack_2c[2] = 'c';
  acStack_2c[3] = 'o';
  local_28[0] = 'u';
  local_28[1] = 'n';
  local_28[2] = 't';
  local_28[3] = 'e';
  uStack_24 = 0x72;
  uStack_20 = 0;
  uStack_1c = 0;
  os_zero_mem(&local_3c,4);
  while( true ) {
    MtCmdGetWifiInterruptCnt(param_1,iVar1,1,0xf,&local_3c);
    if (0 < DebugLevel) {
      printk("Band %u:%s = %u\n",iVar1,local_38,local_3c);
    }
    if (iVar1 == 1) break;
    iVar1 = 1;
  }
  return 1;
}

