// module: mt7915.ko
// function: TxBfProfilePnPrint @ 0x86de4
// size: 388 bytes
//

void TxBfProfilePnPrint(undefined4 param_1,ushort *param_2)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  
  switch(param_1) {
  case 0:
    if (DebugLevel < 1) {
      return;
    }
    uVar2 = (uint)(byte)param_2[4];
    uVar3 = (uint)param_2[3];
    pcVar1 = 
    "============================= TxBf profile PN Info 20M ========================================\n1STS_TX0 = 0x%x, 1STS_TX1 = 0x%x, 1STS_TX2 = 0x%x, 1STS_TX3 = 0x%x\n2STS_TX0 = 0x%x, 2STS_TX1 = 0x%x, 2STS_TX2 = 0x%x, 2STS_TX3 = 0x%x\n3STS_TX0 = 0x%x, 3STS_TX1 = 0x%x, 3STS_TX2 = 0x%x, 3STS_TX3 = 0x%x\n===============================================================================================\n"
    ;
    break;
  case 1:
    if (DebugLevel < 1) {
      return;
    }
    uVar2 = (uint)(byte)param_2[4];
    uVar3 = (uint)param_2[3];
    pcVar1 = 
    "============================= TxBf profile PN Info 40M ========================================\n1STS_TX0 = 0x%x, 1STS_TX1 = 0x%x, 1STS_TX2 = 0x%x, 1STS_TX3 = 0x%x\n2STS_TX0 = 0x%x, 2STS_TX1 = 0x%x, 2STS_TX2 = 0x%x, 2STS_TX3 = 0x%x\n3STS_TX0 = 0x%x, 3STS_TX1 = 0x%x, 3STS_TX2 = 0x%x, 3STS_TX3 = 0x%x\n===============================================================================================\n"
    ;
    break;
  case 2:
    if (DebugLevel < 1) {
      return;
    }
    uVar2 = (uint)(byte)param_2[4];
    uVar3 = (uint)param_2[3];
    pcVar1 = 
    "============================= TxBf profile PN Info 80M ========================================\n1STS_TX0 = 0x%x, 1STS_TX1 = 0x%x, 1STS_TX2 = 0x%x, 1STS_TX3 = 0x%x\n2STS_TX0 = 0x%x, 2STS_TX1 = 0x%x, 2STS_TX2 = 0x%x, 2STS_TX3 = 0x%x\n3STS_TX0 = 0x%x, 3STS_TX1 = 0x%x, 3STS_TX2 = 0x%x, 3STS_TX3 = 0x%x\n===============================================================================================\n"
    ;
    break;
  case 3:
    if (0 < DebugLevel) {
      printk("============================= TxBf profile PN Info 80M ========================================\n1STS_TX0 = 0x%x, 1STS_TX1 = 0x%x\n2STS_TX0 = 0x%x, 2STS_TX1 = 0x%x\n===============================================================================================\n"
             ,*param_2 & 0x7ff,(uint)(*(int *)param_2 << 10) >> 0x15,
             param_2[1] >> 6 | ((byte)param_2[2] & 1) << 0xb,((uint)param_2[2] << 0x14) >> 0x15);
    }
  default:
    goto switchD_00086df0_default;
  }
  printk(pcVar1,*param_2 & 0x7ff,(uint)(*(int *)param_2 << 10) >> 0x15,
         param_2[1] >> 6 | ((byte)param_2[2] & 1) << 0xb,((uint)param_2[2] << 0x14) >> 0x15,
         (uint)(*(int *)(param_2 + 2) << 9) >> 0x15,uVar3 >> 7 | (uVar2 & 3) << 0xb,
         ((uint)param_2[4] << 0x13) >> 0x15,(uint)(*(int *)(param_2 + 4) << 8) >> 0x15,
         *(undefined1 *)((int)param_2 + 0xb),((uint)param_2[6] << 0x12) >> 0x15,
         (uint)(*(int *)(param_2 + 6) << 7) >> 0x15,
         (uint)(*(byte *)((int)param_2 + 0xf) >> 1) | ((byte)param_2[8] & 0xf) << 0xb);
switchD_00086df0_default:
  return;
}

