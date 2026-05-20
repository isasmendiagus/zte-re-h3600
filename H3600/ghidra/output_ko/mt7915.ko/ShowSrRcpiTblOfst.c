// module: mt7915.ko
// function: ShowSrRcpiTblOfst @ 0x16c9b8
// size: 72 bytes
//

int ShowSrRcpiTblOfst(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = SrCmdShow(param_1,param_2,0x25,1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s: iwpriv ra0 show srrcpitblofst=0\n","ShowSrRcpiTblOfst");
  }
  return iVar1;
}

