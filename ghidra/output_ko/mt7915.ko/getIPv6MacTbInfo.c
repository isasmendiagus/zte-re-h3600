// module: mt7915.ko
// function: getIPv6MacTbInfo @ 0x7cc50
// size: 468 bytes
//

void getIPv6MacTbInfo(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  ushort *puVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  pcVar4 = *(char **)(param_1 + 0xc);
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if ((pcVar4 == (char *)0x0) || (*pcVar4 == '\0')) {
    if (2 < DebugLevel) {
      printk("%s():IPv6MacTable not init yet!\n","getIPv6MacTbInfo");
    }
    return;
  }
  param_2[0] = '\n';
  param_2[1] = '\0';
  sprintf(param_2 + 1,"%-40s%-20s\n",&_LC15,&_LC16);
  pcVar5 = pcVar4 + 0x100;
  do {
    pcVar4 = pcVar4 + 4;
    for (puVar3 = *(ushort **)pcVar4; puVar3 != (ushort *)0x0; puVar3 = *(ushort **)(puVar3 + 0xe))
    {
      sVar1 = strlen(param_2);
      iVar2 = RtmpOsCmdDisplayLenCheck(sVar1,0x1e);
      if (iVar2 == 0) break;
      __memzero(&local_50,0x28);
      sprintf((char *)&local_50,"%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
              (*puVar3 & 0xff) << 8 | (uint)(*puVar3 >> 8),
              (puVar3[1] & 0xff) << 8 | (uint)(puVar3[1] >> 8),
              (puVar3[2] & 0xff) << 8 | (uint)(puVar3[2] >> 8),
              (puVar3[3] & 0xff) << 8 | (uint)(puVar3[3] >> 8),
              (puVar3[4] & 0xff) << 8 | (uint)(puVar3[4] >> 8),
              (puVar3[5] & 0xff) << 8 | (uint)(puVar3[5] >> 8),
              (puVar3[6] & 0xff) << 8 | (uint)(puVar3[6] >> 8),
              (puVar3[7] & 0xff) << 8 | (uint)(puVar3[7] >> 8));
      sVar1 = strlen(param_2);
      sprintf(param_2 + sVar1,"%-40s%02x:%02x:%02x:%02x:%02x:%02x\n",&local_50,(uint)(byte)puVar3[8]
              ,(uint)*(byte *)((int)puVar3 + 0x11),(uint)(byte)puVar3[9],
              (uint)*(byte *)((int)puVar3 + 0x13),(uint)(byte)puVar3[10],
              (uint)*(byte *)((int)puVar3 + 0x15));
    }
    if (pcVar4 == pcVar5) {
      return;
    }
  } while( true );
}

