// module: mt7915.ko
// function: Set_TxBfProfileDataWrite @ 0xe7e48
// size: 392 bytes
//

undefined4 Set_TxBfProfileDataWrite(int param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  byte *__s;
  undefined4 uVar3;
  ushort *puVar4;
  byte local_51;
  char local_50 [12];
  ushort local_44 [20];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(local_44,0x24);
  sVar2 = strlen(param_2);
  if (sVar2 == 0x3c) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s == (byte *)0x0) {
LAB_000e7fa0:
      if (*(code **)(iVar1 + 0x168) != (code *)0x0) {
        uVar3 = (**(code **)(iVar1 + 0x168))(param_1,local_44);
        return uVar3;
      }
    }
    else if ((((&_ctype)[*__s] & 0x44) != 0) && (((&_ctype)[__s[1]] & 0x44) != 0)) {
      puVar4 = local_44;
      do {
        sVar2 = strlen((char *)__s);
        if ((sVar2 & 1) == 0) {
          if ((sVar2 & 0xff) == 2) {
            AtoH(__s,&local_51,1);
            *puVar4 = (ushort)local_51;
          }
          else if (-1 < DebugLevel) {
            printk("%s:Error: Un-expected string len!!!!!\n","Set_TxBfProfileDataWrite");
          }
        }
        else {
          local_50[0] = '0';
          local_50[1] = '\0';
          strncat(local_50,(char *)__s,sVar2 & 0xff);
          AtoH(local_50,puVar4,2);
          *puVar4 = *puVar4 << 8 | *puVar4 >> 8;
        }
        puVar4 = puVar4 + 1;
        __s = (byte *)rstrtok(0,&_LC232);
        if (__s == (byte *)0x0) goto LAB_000e7fa0;
      } while ((((&_ctype)[*__s] & 0x44) != 0) && (((&_ctype)[__s[1]] & 0x44) != 0));
    }
  }
  return 0;
}

