// module: mt7915.ko
// function: mt7915_get_default_bin_image_file @ 0x176d6c
// size: 160 bytes
//

undefined4
mt7915_get_default_bin_image_file
          (undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  undefined4 uVar2;
  size_t sVar3;
  undefined4 extraout_r2;
  
  pcVar1 = (char *)get_dev_eeprom_binary();
  if (*pcVar1 == '\0') {
    sVar3 = strlen(param_2);
    uVar2._0_1_ = 'm';
    uVar2._1_1_ = 'w';
    uVar2._2_1_ = 'a';
    uVar2._3_1_ = 'r';
    builtin_strncpy(param_2 + sVar3,"/lib/firmware/e2p",0x12);
  }
  else {
    uVar2 = get_dev_eeprom_binary(param_1);
    sprintf(param_2,"/lib/firmware/%s",uVar2);
    uVar2 = extraout_r2;
  }
  if (0 < DebugLevel) {
    printk("Use default BIN from:%s.\n",param_2,uVar2,DebugLevel,param_4);
  }
  return 0;
}

