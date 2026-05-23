// module: mt7915.ko
// function: set_token_setting @ 0xc3e6c
// size: 160 bytes
//

undefined4 set_token_setting(undefined4 param_1,char *param_2)

{
  int iVar1;
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (((((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
       (iVar1 = sscanf(param_2,"%d-%d-%d-%d",local_18,&local_14,&uStack_10,&uStack_c), iVar1 != 3))
      || (iVar1 = token_tx_setting(param_1,local_18[0],local_14,uStack_10,uStack_c), iVar1 != 0)) &&
     (0 < DebugLevel)) {
    printk("invalid input, should be [qidx]-[option]-[sub_option]-[value]\n");
  }
  return 1;
}

