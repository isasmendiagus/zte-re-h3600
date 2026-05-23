// module: mt7915.ko
// function: MtCmdGetWifiInterruptCntRsp @ 0x1ac6e4
// size: 100 bytes
//

void MtCmdGetWifiInterruptCntRsp(int param_1,short *param_2)

{
  short *psVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (*param_2 == 5) {
    if ((char)param_2[2] == '\0') {
      return;
    }
    psVar1 = param_2 + 2;
    iVar3 = 0;
    puVar2 = *(undefined4 **)(param_1 + 0xc);
    do {
      psVar1 = psVar1 + 2;
      iVar3 = iVar3 + 1;
      *puVar2 = *(undefined4 *)psVar1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < (int)(uint)*(byte *)(param_2 + 2));
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("%s:Get Wifi Interrupt Counter Error!\n","MtCmdGetWifiInterruptCntRsp");
  return;
}

