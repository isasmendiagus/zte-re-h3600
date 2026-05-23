// module: mt7915.ko
// function: set_fwlog_servermac @ 0x1d4e64
// size: 276 bytes
//

undefined4 set_fwlog_servermac(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char local_2c [24];
  
  local_2c[0] = '\0';
  local_2c[1] = '\0';
  local_2c[2] = '\0';
  local_2c[3] = '\0';
  local_2c[4] = '\0';
  local_2c[5] = '\0';
  local_2c[6] = '\0';
  local_2c[7] = '\0';
  local_2c[8] = '\0';
  local_2c[9] = '\0';
  local_2c[10] = '\0';
  local_2c[0xb] = '\0';
  local_2c[0xc] = '\0';
  local_2c[0xd] = '\0';
  local_2c[0xe] = '\0';
  local_2c[0xf] = '\0';
  local_2c[0x10] = '\0';
  local_2c[0x11] = '\0';
  local_2c[0x12] = '\0';
  local_2c[0x13] = '\0';
  strncpy(local_2c,param_2,0x13);
  sVar1 = strlen(param_2);
  if (sVar1 == 0x11) {
    iVar2 = strcmp(param_2,"00:00:00:00:00:00");
    if (iVar2 == 0) {
      if (0 < DebugLevel) {
        printk("%s : invalid mac setting\n","set_fwlog_servermac");
      }
    }
    else {
      param_1 = param_1 + 0xa7cc2c;
      pcVar3 = param_2;
      do {
        pcVar4 = pcVar3 + 3;
        AtoH(pcVar3,param_1,1);
        param_1 = param_1 + 1;
        pcVar3 = pcVar4;
      } while (pcVar4 != param_2 + 0x12);
      if (0 < DebugLevel) {
        printk("mac=[%s]\n",local_2c);
      }
    }
  }
  else if (0 < DebugLevel) {
    printk("%s : invalid length (%d)\n","set_fwlog_servermac",sVar1);
  }
  return 0;
}

