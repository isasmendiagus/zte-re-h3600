// module: mt7915.ko
// function: TxBfProfileDataPrint @ 0x881a8
// size: 324 bytes
//

void TxBfProfileDataPrint(int param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte bStack_37;
  byte local_2f;
  
  iVar1 = DebugLevel;
  uVar5 = param_3[3];
  uVar2 = *param_3;
  uVar3 = param_3[1];
  uVar4 = param_3[2];
  *(uint *)(param_1 + 0xa786e0) = uVar2;
  *(uint *)(param_1 + 0xa786e4) = uVar3;
  *(uint *)(param_1 + 0xa786e8) = uVar4;
  *(uint *)(param_1 + 0xa786ec) = uVar5;
  *(uint *)(param_1 + 0xa786f0) = param_3[4];
  if (0 < iVar1) {
    local_2f = (byte)(uVar5 >> 8);
    bStack_37 = (byte)(uVar3 >> 8);
    printk("============================= TxBf profile Data - Subcarrier Idx = %d ========================================\nPsi41 = 0x%x, Phi31 = 0x%x, Psi31 = 0x%x, Phi21 = 0x%x, Psi21 = 0x%x, Phi11 = 0x%x\nPsi43 = 0x%x, Phi33 = 0x%x, Psi42 = 0x%x, Phi32 = 0x%x, Psi32 = 0x%x, Phi22 = 0x%x\nSNR00 = 0x%x, SNR01 = 0x%x, SNR02 = 0x%x, SNR03 = 0x%x\n==============================================================================================================\n"
           ,param_2,bStack_37 >> 1,uVar3 & 0x1ff,uVar2 >> 0x19,uVar2 >> 0x10 & 0x1ff,
           uVar2 >> 9 & 0x7f,uVar2 & 0x1ff,uVar4 >> 0x19,uVar4 >> 0x10 & 0x1ff,uVar4 >> 9 & 0x7f,
           uVar4 & 0x1ff,uVar3 >> 0x19,uVar3 >> 0x10 & 0x1ff,uVar5 & 0xf,uVar5 >> 4 & 0xf,
           local_2f & 0xf,local_2f >> 4);
  }
  return;
}

