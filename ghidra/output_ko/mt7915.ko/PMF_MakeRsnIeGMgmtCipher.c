// module: mt7915.ko
// function: PMF_MakeRsnIeGMgmtCipher @ 0x21a058
// size: 280 bytes
//

undefined4 PMF_MakeRsnIeGMgmtCipher(int param_1,int param_2,byte *param_3,undefined4 param_4)

{
  byte bVar1;
  void *__dest;
  uint uVar2;
  
  if ((*(int *)(param_1 + (param_2 + 0x166) * 4) == 2) && (*(char *)(param_1 + 0x3e0) == '\x01')) {
    uVar2 = *(uint *)(param_1 + 999);
    __dest = (void *)(param_1 + param_2 * 0xff + 0x5a4 + (uint)*param_3);
    if ((uVar2 & 0x200) == 0) {
      if ((uVar2 & 0x400) == 0) {
        if ((uVar2 & 0x800) == 0) {
          if ((uVar2 & 0x1000) == 0) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("[PMF]%s: insert fail, IGTK cipher is wrong\n","PMF_MakeRsnIeGMgmtCipher",0,
                   DebugLevel,param_4);
            return 0;
          }
          memmove(__dest,&OUI_PMF_BIP_GMAC_256_CIPHER,4);
        }
        else {
          memmove(__dest,&OUI_PMF_BIP_GMAC_128_CIPHER,4);
        }
      }
      else {
        memmove(__dest,&OUI_PMF_BIP_CMAC_256_CIPHER,4);
      }
    }
    else {
      memmove(__dest,&OUI_PMF_BIP_CMAC_128_CIPHER,4);
    }
    bVar1 = *param_3;
    *param_3 = (byte)(bVar1 + 4);
    if (2 < DebugLevel) {
      printk("[PMF]%s: Insert BIP to the group management cipher of RSNIE\n",
             "PMF_MakeRsnIeGMgmtCipher",bVar1 + 4,DebugLevel,param_4);
      return 1;
    }
  }
  return 1;
}

