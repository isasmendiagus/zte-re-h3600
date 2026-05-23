// module: mt7915.ko
// function: Show_STA_RAInfo_Proc @ 0xd55dc
// size: 208 bytes
//

undefined4 Show_STA_RAInfo_Proc(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  
  param_2[0] = '\n';
  param_2[1] = '\0';
  sprintf(param_2 + 1,"ITxBfEn: %d\n",((uint)*(byte *)(param_1 + 0x794ccd) << 0x1d) >> 0x1f,
          param_1 + 0x794000,param_4);
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"ITxBfTimeout: %ld\n",*(undefined4 *)(param_1 + 0x795994));
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"ETxBfTimeout: %ld\n",*(undefined4 *)(param_1 + 0x795998));
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"CommonCfg.ETxBfEnCond: %ld\n",*(undefined4 *)(param_1 + 0x79599c));
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"ETxBfNoncompress: %d\n",(uint)*(byte *)(param_1 + 0x7959a4));
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"ETxBfIncapable: %d\n",(uint)*(byte *)(param_1 + 0x7959a5));
  return 0;
}

