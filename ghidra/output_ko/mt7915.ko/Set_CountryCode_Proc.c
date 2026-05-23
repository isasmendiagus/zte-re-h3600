// module: mt7915.ko
// function: Set_CountryCode_Proc @ 0x33d84
// size: 164 bytes
//

undefined4 Set_CountryCode_Proc(int param_1,char *param_2)

{
  size_t sVar1;
  
  sVar1 = strlen(param_2);
  if (sVar1 == 2) {
    memmove((void *)(param_1 + 0x794c31),param_2,2);
    *(undefined1 *)(param_1 + 0x794c30) = 1;
  }
  else {
    __memzero(param_1 + 0x794c31,4);
    *(undefined1 *)(param_1 + 0x794c30) = 0;
  }
  if (2 < DebugLevel) {
    printk("Set_CountryCode_Proc::(bCountryFlag=%d, CountryCode=%s)\n",
           *(undefined1 *)(param_1 + 0x794c30),param_1 + 0x794c31);
  }
  return 1;
}

