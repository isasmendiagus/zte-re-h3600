// module: mt7915.ko
// function: HQA_ResetTxRxCounter @ 0x275e28
// size: 352 bytes
//

undefined4 HQA_ResetTxRxCounter(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_ResetTxRxCounter");
  }
  AsicGetRxStat(param_1,9);
  AsicGetRxStat(param_1,10);
  MtCmdSetPhyCounter(param_1,0,0);
  MtCmdSetPhyCounter(param_1,1,0);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    MtCmdSetPhyCounter(param_1,0,1);
    MtCmdSetPhyCounter(param_1,1,1);
  }
  MT_ATEUpdateRxStatistic(param_1,2);
  *(undefined4 *)(param_1 + 0xa3ad80) = 0;
  cVar2 = '\0';
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar1 = net_ad_wrap_service(param_1);
    *(undefined4 *)(iVar1 + 0x1e34) = 0;
    cVar2 = *(char *)(param_1 + 0x79504d);
  }
  puVar3 = (undefined4 *)(param_1 + 0xa7c010);
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != (undefined4 *)(param_1 + 0xa7c050));
  if (cVar2 != '\0') {
    puVar3 = (undefined4 *)(param_1 + 0xa7c178);
    do {
      puVar3 = puVar3 + 1;
      *puVar3 = 0;
    } while (puVar3 != (undefined4 *)(param_1 + 0xa7c1b8));
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

