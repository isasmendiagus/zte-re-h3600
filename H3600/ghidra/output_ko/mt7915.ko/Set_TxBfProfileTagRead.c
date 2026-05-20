// module: mt7915.ko
// function: Set_TxBfProfileTagRead @ 0xe7c34
// size: 220 bytes
//

undefined4 Set_TxBfProfileTagRead(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  byte *pbVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined2 local_1a;
  
  local_1a = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 5) {
    pbVar2 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar2 == (byte *)0x0) {
LAB_000e7cfc:
      uVar3 = TxBfProfileTagRead(param_1,(undefined1)local_1a,local_1a._1_1_);
      return uVar3;
    }
    if ((((&_ctype)[*pbVar2] & 0x44) != 0) && (((&_ctype)[pbVar2[1]] & 0x44) != 0)) {
      puVar4 = &local_1a;
      do {
        AtoH(pbVar2,puVar4);
        pbVar2 = (byte *)rstrtok(0,&_LC232);
        if (pbVar2 == (byte *)0x0) goto LAB_000e7cfc;
      } while ((((&_ctype)[*pbVar2] & 0x44) != 0) &&
              (puVar4 = (undefined2 *)((int)puVar4 + 1), ((&_ctype)[pbVar2[1]] & 0x44) != 0));
    }
  }
  return 0;
}

