// module: mt7915.ko
// function: PrintSrSd @ 0x16d9cc
// size: 264 bytes
//

void PrintSrSd(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  char *apcStack_38 [5];
  
  apcStack_38[0] = "1 - NO CONNECTED";
  apcStack_38[1] = "2 - NO CONGESTION";
  apcStack_38[2] = "3 - NO INTERFERENCE";
  apcStack_38[3] = "4 - ALL RULE PASS";
  if ((-1 < DebugLevel) && (printk("%s: Band%d\n","PrintSrSd",param_1), -1 < DebugLevel)) {
    uVar2 = *(uint *)(param_2 + (short)param_1 * 4);
    iVar1 = param_2 + (short)param_1 * 4;
    printk("-------------------------------------------------------------------\nHit Rule      = %s\nTimer Period  = %d(us)\n \t CH  Busytime       = %d\n \t SR  Period  Ratio  = %d.%1d%%\n \t Ttl Airtime Ratio  = %d.%1d%%\nTotal Airtime = %d(us) (OBSS+TX+RX)\n \t OBSS Airtime       = %d\n \t MyTx Airtime       = %d\n \t MyRx Airtime       = %d\n \t OBSS Airtime Ratio = %d.%1d%%\n"
           ,apcStack_38[*(byte *)(param_2 + param_1 + 0x40)],500000,*(undefined4 *)(iVar1 + 0x20),
           uVar2 / 10,uVar2 % 10,*(uint *)(iVar1 + 0x30) / 10,*(uint *)(iVar1 + 0x30) % 10,
           *(undefined4 *)(iVar1 + 0x28),*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x10),
           *(undefined4 *)(iVar1 + 0x18),*(uint *)(iVar1 + 0x38) / 10,*(uint *)(iVar1 + 0x38) % 10);
  }
  return;
}

