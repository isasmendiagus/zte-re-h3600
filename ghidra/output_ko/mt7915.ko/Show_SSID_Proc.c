// module: mt7915.ko
// function: Show_SSID_Proc @ 0xd56ac
// size: 224 bytes
//

undefined4 Show_SSID_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  undefined1 auStack_39 [37];
  
  iVar1 = *param_1;
  __memzero(auStack_39,0x21);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar1 = *(int *)(iVar1 + 0x3c) * 0x5834;
    memcpy(auStack_39,
           (char *)((int)param_1 +
                   (int)(
                        "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                        + iVar1 + 0x34)),(uint)*(byte *)((int)param_1 + iVar1 + 0x2bb2d1));
  }
  else if (*(char *)((int)param_1 + 0x286285) == '\0') {
    iVar1 = *(int *)(iVar1 + 0x3c);
    memcpy(auStack_39,(void *)((int)param_1 + iVar1 * 0x2137b0 + 0x57ff5e),
           (uint)*(byte *)((int)param_1 + iVar1 * 0x2137b0 + 0x57ff7e));
  }
  snprintf(param_2,param_3,"\t%s",auStack_39);
  return 0;
}

