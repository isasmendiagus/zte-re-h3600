// module: mt7915.ko
// function: getIPMacTbInfo @ 0x7adb4
// size: 436 bytes
//

void getIPMacTbInfo(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  piVar5 = *(int **)(param_1 + 8);
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if ((piVar5 == (int *)0x0) || ((char)*piVar5 == '\0')) {
    if (2 < DebugLevel) {
      printk("%s():IPMacTable not init yet!\n","getIPMacTbInfo");
    }
    return;
  }
  param_2[0] = '\n';
  param_2[1] = '\0';
  sprintf(param_2 + 1,"%-18s%-20s\n",&_LC18,&_LC19);
  piVar6 = piVar5 + 0x40;
  do {
    piVar5 = piVar5 + 1;
    for (puVar3 = (uint *)*piVar5; puVar3 != (uint *)0x0; puVar3 = (uint *)puVar3[4]) {
      sVar1 = strlen(param_2);
      iVar2 = RtmpOsCmdDisplayLenCheck(sVar1,0x1e);
      if (iVar2 == 0) break;
      __memzero(&local_2c,0x14);
      uVar4 = *puVar3;
      snprintf((char *)&local_2c,0x14,"%d.",uVar4 & 0xff);
      snprintf((char *)&local_2c,0x14,"%s%d.",&local_2c,(uVar4 << 0x10) >> 0x18);
      snprintf((char *)&local_2c,0x14,"%s%d.",&local_2c,(uVar4 << 8) >> 0x18);
      snprintf((char *)&local_2c,0x14,"%s%d",&local_2c,uVar4 >> 0x18);
      sVar1 = strlen(param_2);
      sprintf(param_2 + sVar1,"%-18s%02x:%02x:%02x:%02x:%02x:%02x\n",&local_2c,(uint)(byte)puVar3[1]
              ,(uint)*(byte *)((int)puVar3 + 5),(uint)*(byte *)((int)puVar3 + 6),
              (uint)*(byte *)((int)puVar3 + 7),(uint)(byte)puVar3[2],
              (uint)*(byte *)((int)puVar3 + 9));
    }
    if (piVar5 == piVar6) {
      return;
    }
  } while( true );
}

