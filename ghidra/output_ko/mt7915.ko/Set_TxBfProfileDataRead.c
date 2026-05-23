// module: mt7915.ko
// function: Set_TxBfProfileDataRead @ 0xe7d60
// size: 232 bytes
//

undefined4 Set_TxBfProfileDataRead(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  byte *pbVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_1c;
  
  local_1c = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 0xb) {
    pbVar2 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar2 == (byte *)0x0) {
LAB_000e7e28:
      uVar3 = TxBfProfileDataRead(param_1,local_1c & 0xff,local_1c._1_1_,local_1c._3_1_);
      return uVar3;
    }
    if ((((&_ctype)[*pbVar2] & 0x44) != 0) && (((&_ctype)[pbVar2[1]] & 0x44) != 0)) {
      puVar4 = &local_1c;
      do {
        AtoH(pbVar2,puVar4);
        pbVar2 = (byte *)rstrtok(0,&_LC232);
        if (pbVar2 == (byte *)0x0) goto LAB_000e7e28;
      } while ((((&_ctype)[*pbVar2] & 0x44) != 0) &&
              (puVar4 = (undefined4 *)((int)puVar4 + 1), ((&_ctype)[pbVar2[1]] & 0x44) != 0));
    }
  }
  return 0;
}

