// module: mt7915.ko
// function: ZTE_set_CountryCode_Proc @ 0x33e28
// size: 184 bytes
//

undefined4 ZTE_set_CountryCode_Proc(int param_1,char *param_2)

{
  size_t sVar1;
  
  sVar1 = strlen(param_2);
  if (sVar1 == 2) {
    memmove((void *)(param_1 + 0x794c36),param_2,2);
    *(undefined1 *)(param_1 + 0x794c35) = 1;
    *(undefined1 *)(param_1 + 0x794c38) = 0x20;
    *(undefined1 *)(param_1 + 0x794c39) = 0;
  }
  else {
    __memzero(param_1 + 0x794c36,4);
    *(undefined1 *)(param_1 + 0x794c35) = 0;
  }
  if (0 < DebugLevel) {
    printk("%s::(bCountryFlag=%d, CountryCode=%s)\n","ZTE_set_CountryCode_Proc",
           *(undefined1 *)(param_1 + 0x794c35),param_1 + 0x794c36);
  }
  return 1;
}

