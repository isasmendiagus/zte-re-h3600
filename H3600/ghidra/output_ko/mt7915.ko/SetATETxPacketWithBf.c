// module: mt7915.ko
// function: SetATETxPacketWithBf @ 0x2695e0
// size: 768 bytes
//

undefined4 SetATETxPacketWithBf(int param_1,char *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  size_t sVar4;
  byte *__s;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 local_44;
  char local_40 [36];
  
  iVar3 = net_ad_wrap_service();
  iVar7 = *(int *)(param_1 + 0xa77bb8);
  local_44 = 0;
  local_40[0] = '\0';
  local_40[1] = '\0';
  local_40[2] = '\0';
  local_40[3] = '\0';
  local_40[4] = '\0';
  local_40[5] = '\0';
  local_40[6] = '\0';
  local_40[7] = '\0';
  local_40[8] = '\0';
  local_40[9] = '\0';
  local_40[10] = '\0';
  local_40[0xb] = '\0';
  local_40[0xc] = '\0';
  local_40[0xd] = '\0';
  local_40[0xe] = '\0';
  local_40[0xf] = '\0';
  local_40[0x10] = '\0';
  local_40[0x11] = '\0';
  local_40[0x12] = '\0';
  local_40[0x13] = '\0';
  local_40[0x14] = '\0';
  local_40[0x15] = '\0';
  local_40[0x16] = '\0';
  local_40[0x17] = '\0';
  local_40[0x18] = '\0';
  local_40[0x19] = '\0';
  local_40[0x1a] = '\0';
  local_40[0x1b] = '\0';
  local_40[0x1c] = '\0';
  local_40[0x1d] = '\0';
  local_40[0x1e] = '\0';
  local_40[0x1f] = '\0';
  bVar1 = *(byte *)(iVar3 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: control_band_idx = %d\n","SetATETxPacketWithBf",(uint)bVar1);
  }
  if ((param_2 == (char *)0x0) || (sVar4 = strlen(param_2), sVar4 != 8)) {
LAB_00269658:
    uVar5 = 0;
  }
  else {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar6 = &local_44;
      do {
        sVar4 = strlen((char *)__s);
        if (((sVar4 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_00269658;
        AtoH(__s,puVar6);
        __s = (byte *)rstrtok(0,&_LC2);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      } while (__s != (byte *)0x0);
    }
    iVar3 = (uint)bVar1 * 0xd18;
    uVar2 = local_44 >> 0x10;
    *(undefined1 *)(iVar7 + iVar3 + 0x510) = local_44._1_1_;
    if ((char)local_44 == '\0') {
      iVar7 = net_ad_wrap_service(param_1);
      if (*(char *)(iVar7 + iVar3 + 0x11ce) != '\0') {
        TxBfProfileTagRead(param_1,2,1);
        TxBfProfileTag_InValid(param_1 + 0xa786fc,1);
        TxBfProfileTagWrite(param_1,param_1 + 0xa786c4,param_1 + 0xa786d4,2);
        iVar7 = net_ad_wrap_service(param_1);
        *(undefined1 *)(iVar7 + iVar3 + 0x11ce) = 0;
        return 1;
      }
      SetATE(param_1,"RXSTOP");
      iVar7 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar7 + iVar3 + 0x11cd) = 0;
      iVar7 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar7 + iVar3 + 0x11cc) = 0;
    }
    else {
      SetATE(param_1,"RXSTOP");
      TxBfProfileTagRead(param_1,2,1);
      TxBfProfileTag_InValid(param_1 + 0xa786fc,0);
      TxBfProfileTagWrite(param_1,param_1 + 0xa786c4,param_1 + 0xa786d4,2);
      iVar7 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar7 + iVar3 + 0x11cd) = 1;
      iVar7 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar7 + iVar3 + 0x11cc) = 1;
      iVar7 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar7 + iVar3 + 0x11ce) = 1;
    }
    SetATE(param_1,"TXSTOP");
    snprintf(local_40,0x20,"%d",uVar2 & 0xff);
    SetATETxCount(param_1,local_40);
    SetATE(param_1,"TXCOMMIT");
    SetATE(param_1,"TXFRAME");
    uVar5 = 1;
  }
  return uVar5;
}

