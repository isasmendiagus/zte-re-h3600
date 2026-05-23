// module: mt7915.ko
// function: ZTE_WLAN_Temperature_Protection_Show @ 0x15fb64
// size: 140 bytes
//

undefined4 ZTE_WLAN_Temperature_Protection_Show(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &_LANCHOR0;
  while( true ) {
    printk("\ndbdc ucBandidx:%d config: Enable=%d, High=%d, Low=%d, step=%d, timer=%d, recover=%d, Min=%d\n"
           ,iVar2,*puVar1,puVar1[1],puVar1[2],puVar1[3],puVar1[4],puVar1[5],puVar1[6]);
    printk("HighCnt=%d, LowCnt=%d Percent=%d\n",puVar1[8],puVar1[9],puVar1[7]);
    if (iVar2 == 1) break;
    iVar2 = 1;
    puVar1 = puVar1 + 10;
  }
  return 1;
}

