// module: mt7915.ko
// function: HQA_FFT @ 0x26ccf0
// size: 112 bytes
//

void HQA_FFT(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: %d\n","HQA_FFT",uVar1);
  }
                    /* WARNING: Could not recover jumptable at 0x0026cd44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar2 + 0xdc))(param_1,uVar1);
  return;
}

