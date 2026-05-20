// module: mt7915.ko
// function: Set_TxBfProfileTag_McsThrd @ 0xe7968
// size: 276 bytes
//

undefined4 Set_TxBfProfileTag_McsThrd(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  byte *pbVar2;
  undefined2 *puVar3;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  local_16 = 0;
  local_14 = 0;
  local_12 = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 0x11) {
    pbVar2 = (byte *)rstrtok(param_2,&_LC232);
    if (pbVar2 == (byte *)0x0) {
LAB_000e7a34:
      local_1c = (undefined1)local_16;
      local_19 = local_16._1_1_;
      local_1b = (undefined1)local_14;
      local_18 = local_14._1_1_;
      local_1a = (undefined1)local_12;
      local_17 = local_12._1_1_;
      TxBfProfileTag_McsThd(0,&local_1c,&local_19);
      return 1;
    }
    if ((((&_ctype)[*pbVar2] & 0x44) != 0) && (((&_ctype)[pbVar2[1]] & 0x44) != 0)) {
      puVar3 = &local_16;
      do {
        AtoH(pbVar2,puVar3);
        pbVar2 = (byte *)rstrtok(0,&_LC232);
        if (pbVar2 == (byte *)0x0) goto LAB_000e7a34;
      } while ((((&_ctype)[*pbVar2] & 0x44) != 0) &&
              (puVar3 = (undefined2 *)((int)puVar3 + 1), ((&_ctype)[pbVar2[1]] & 0x44) != 0));
    }
  }
  return 0;
}

