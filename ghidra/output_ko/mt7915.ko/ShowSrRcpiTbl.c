// module: mt7915.ko
// function: ShowSrRcpiTbl @ 0x16c96c
// size: 72 bytes
//

int ShowSrRcpiTbl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x24,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srrcpitbl=0\n","ShowSrRcpiTbl");
  }
  return iVar1;
}

