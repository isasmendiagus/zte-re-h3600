// module: mt7915.ko
// function: Set_TxBfProfilePnWrite @ 0xe879c
// size: 784 bytes
//

undefined4 Set_TxBfProfilePnWrite(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  char cVar4;
  size_t sVar5;
  byte *__s;
  undefined4 uVar6;
  ushort *puVar7;
  uint uVar8;
  byte local_5d;
  char local_5c [12];
  ushort local_50;
  ushort uStack_4e;
  undefined4 local_4c;
  uint3 local_48;
  undefined1 uStack_45;
  uint3 local_44;
  byte bStack_41;
  byte local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  sVar5 = strlen(param_2);
  if (sVar5 == 0x37) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s == (byte *)0x0) {
LAB_000e88f8:
      cVar4 = local_3c._2_1_;
      uVar8 = local_3c & 0xff;
      if (local_3c._2_1_ != '\x03') {
        os_zero_mem(&local_50,0x14);
        local_4c._0_2_ = (ushort)((char)(local_34 >> 8) >> 3 & 1);
        iVar1 = (local_38 >> 0x10 & 0x7ff) << 0xb;
        local_50 = (ushort)local_38 & 0x7ff | (ushort)iVar1;
        local_48._0_2_ = (ushort)((byte)((int)local_30 >> 0x1a) & 3);
        iVar2 = (local_30 & 0x7ff) << 0xc;
        local_4c._0_2_ = (ushort)local_4c | (local_34._2_2_ & 0x7ff) << 1 | (ushort)iVar2;
        local_44._0_2_ = (ushort)((char)((uint)local_28 >> 8) >> 1 & 7);
        uVar3 = (ushort)local_44 | (local_28._2_2_ & 0x7ff) << 3;
        _local_50 = CONCAT22((ushort)((uint)iVar1 >> 0x10) | (ushort)((local_34 & 0x3ff) << 6),
                             local_50);
        _local_48 = CONCAT13((char)local_28,
                             (uint3)(ushort)((ushort)local_48 | ((ushort)local_2c & 0x7ff) << 2) |
                             (uint3)local_2c._2_2_ << 0xd);
        local_4c = CONCAT22((ushort)((uint)iVar2 >> 0x10) | local_30._2_2_ << 7,(ushort)local_4c);
        iVar1 = (local_24 & 0x7ff) << 0xe;
        local_40 = local_40 & 0xf0 | (byte)(local_24 >> 0x18) & 0xf;
        _local_44 = CONCAT13((byte)((uint)iVar1 >> 0x18) | (byte)((local_24 >> 0x10 & 0x7f) << 1),
                             (uint3)uVar3 | (uint3)iVar1);
        uVar6 = TxBfProfilePnWrite(param_1,uVar8,cVar4,&local_50);
        return uVar6;
      }
      os_zero_mem(&local_50,8);
      iVar1 = (local_38 >> 0x10 & 0x7ff) << 0xb;
      local_50 = (ushort)local_38 & 0x7ff | (ushort)iVar1;
      local_4c = CONCAT31(local_4c._1_3_,(char)(local_34 >> 8) >> 3) & 0xffffff01;
      _local_50 = CONCAT22((ushort)((uint)iVar1 >> 0x10) | (ushort)((local_34 & 0x3ff) << 6),
                           local_50);
      local_4c = CONCAT22(local_4c._2_2_,(ushort)local_4c & 0xf001 | (local_34._2_2_ & 0x7ff) << 1);
      uVar6 = TxBfProfilePnWrite(param_1,uVar8,3,&local_50);
      return uVar6;
    }
    if ((((&_ctype)[*__s] & 0x44) != 0) && (((&_ctype)[__s[1]] & 0x44) != 0)) {
      puVar7 = (ushort *)&local_3c;
      do {
        sVar5 = strlen((char *)__s);
        if ((sVar5 & 1) == 0) {
          if ((sVar5 & 0xff) == 2) {
            AtoH(__s,&local_5d,1);
            *puVar7 = (ushort)local_5d;
          }
          else if (-1 < DebugLevel) {
            printk("%s:Error: Un-expected string len!!!!!\n","Set_TxBfProfilePnWrite");
          }
        }
        else {
          local_5c[0] = '0';
          local_5c[1] = '\0';
          strncat(local_5c,(char *)__s,sVar5 & 0xff);
          AtoH(local_5c,puVar7,2);
          *puVar7 = *puVar7 >> 8 | *puVar7 << 8;
        }
        puVar7 = puVar7 + 1;
        __s = (byte *)rstrtok(0,&_LC232);
        if (__s == (byte *)0x0) goto LAB_000e88f8;
      } while ((((&_ctype)[*__s] & 0x44) != 0) && (((&_ctype)[__s[1]] & 0x44) != 0));
    }
  }
  return 0;
}

