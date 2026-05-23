// module: mt7915.ko
// function: DH_PublicKey_Generate @ 0x1faa88
// size: 456 bytes
//

void DH_PublicKey_Generate
               (undefined4 param_1,int param_2,int param_3,uint param_4,undefined4 param_5,
               int param_6,undefined4 param_7,uint *param_8)

{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("DH_PublicKey_Generate: G length is (%d)\n");
    }
  }
  else if (param_4 == 0) {
    if (-1 < DebugLevel) {
      printk("DH_PublicKey_Generate: P length is (%d)\n",0);
    }
  }
  else if (param_6 == 0) {
    if (-1 < DebugLevel) {
      printk("DH_PublicKey_Generate: private key length is (%d)\n",0);
    }
  }
  else if (*param_8 < param_4) {
    if (-1 < DebugLevel) {
      printk("DH_PublicKey_Generate: public key length(%d) must be large or equal than P length(%d)\n"
             ,*param_8,param_4);
    }
  }
  else if ((*(byte *)(param_3 + param_4 + -1) & 1) == 0) {
    if (-1 < DebugLevel) {
      printk("DH_PublicKey_Generate: P value must be odd\n");
    }
  }
  else {
    BigInteger_Init(&local_20);
    BigInteger_Init(&local_1c);
    BigInteger_Init(&local_18);
    BigInteger_Init(&local_14);
    BigInteger_Bin2BI(param_1,param_2,&local_20);
    BigInteger_Bin2BI(param_3,param_4,&local_1c);
    BigInteger_Bin2BI(param_5,param_6,&local_18);
    BigInteger_Montgomery_ExpMod(local_20,local_18,local_1c,&local_14);
    BigInteger_BI2Bin(local_14,param_7,param_8);
    BigInteger_Free(&local_20);
    BigInteger_Free(&local_1c);
    BigInteger_Free(&local_18);
    BigInteger_Free(&local_14);
  }
  return;
}

