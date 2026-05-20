// module: mt7915.ko
// function: Set_TxBfProfileSwTagWrite @ 0xe9060
// size: 368 bytes
//

undefined4 Set_TxBfProfileSwTagWrite(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c [2];
  
  if (param_2 == (char *)0x0) {
    return 1;
  }
  iVar1 = sscanf(param_2,"%u-%u-%u-%u-%u-%u",&local_30,&local_28,&local_2c,&local_24,&local_20,
                 local_1c);
  bVar3 = local_30 == 0;
  iVar2 = 0;
  if (!bVar3) {
    iVar2 = iVar1 + -1;
  }
  if (((((bVar3 || iVar1 == 1) || iVar2 < 0 != (!bVar3 && SBORROW4(iVar1,1))) || (2 < local_1c[0]))
      || (3 < local_28)) || ((3 < local_2c || (3 < local_20)))) {
    if (-1 < DebugLevel) {
      printk("%s: cmd params are invalid!!\n","Set_TxBfProfileSwTagWrite");
    }
  }
  else {
    if (0 < DebugLevel) {
      printk("%s: Lm=%d Nr=%d Nc=%d BW=%d CodeBook=%d Group=%d\n","Set_TxBfProfileSwTagWrite",
             local_30,local_28,local_2c,local_24,local_20,local_1c[0]);
    }
    iVar2 = TxBfPseudoTagUpdate(param_1,local_30 & 0xff,local_28 & 0xff,local_2c & 0xff,
                                local_24 & 0xff,local_20 & 0xff,local_1c[0] & 0xff);
    if (iVar2 != 0) {
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: set command failed.\n","Set_TxBfProfileSwTagWrite");
      return 0;
    }
  }
  return 0;
}

