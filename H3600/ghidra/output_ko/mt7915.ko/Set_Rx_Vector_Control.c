// module: mt7915.ko
// function: Set_Rx_Vector_Control @ 0xec63c
// size: 340 bytes
//

undefined4 Set_Rx_Vector_Control(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  bool bVar4;
  bool bVar5;
  
  uVar2 = HcGetAmountOfBand();
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  uVar3 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  if ((0 < DebugLevel) &&
     (printk("%s: BandIdx = %d\n","Set_Rx_Vector_Control",uVar3,DebugLevel,param_4), 2 < DebugLevel)
     ) {
    printk("%s----------------->\n","Set_Rx_Vector_Control");
  }
  if (param_2 == 0) {
    bVar5 = true;
    bVar4 = false;
  }
  else {
    cVar1 = os_str_tol(param_2,0,10);
    bVar5 = cVar1 != '\0';
    bVar4 = !bVar5;
  }
  if ((uVar2 != 0) && (*(bool *)(param_1 + 0x29f0c1) = bVar4, 1 < uVar2)) {
    *(bool *)((int)param_1 + 0xa7c305) = bVar4;
  }
  *(bool *)((int)param_1 + 0xa7c349) = bVar4;
  AsicSetMacTxRx(param_1,4,bVar5);
  AsicSetRxvFilter(param_1,bVar5,uVar3);
  if (bVar5 == false) {
    param_1[0x29f08a] = 0;
  }
  else {
    param_1[0x29f08a] = 1;
  }
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","Set_Rx_Vector_Control");
    return 1;
  }
  return 1;
}

