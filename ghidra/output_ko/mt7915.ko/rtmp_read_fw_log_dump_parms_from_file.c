// module: mt7915.ko
// function: rtmp_read_fw_log_dump_parms_from_file @ 0x1d4c48
// size: 368 bytes
//

void rtmp_read_fw_log_dump_parms_from_file(int param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 local_1c [2];
  
  iVar1 = RTMPGetKeyParameter("fwlogserverip",param_2,0x80,param_3,1);
  if ((((iVar1 != 0) && (*param_2 != '\0')) &&
      (iVar3 = rtinet_aton(param_2,local_1c), iVar1 = DebugLevel, iVar3 != 0)) &&
     (*(undefined4 *)(param_1 + 0xa7cc28) = local_1c[0], 2 < iVar1)) {
    printk("fw_log_server_ip=%s(%x)\n",param_2);
  }
  iVar1 = RTMPGetKeyParameter("fwlogservermac",param_2,0x19,param_3,1);
  if (iVar1 != 0) {
    sVar2 = strlen(param_2);
    if (sVar2 == 0x11) {
      iVar1 = strcmp(param_2,"00:00:00:00:00:00");
      if (iVar1 == 0) {
        if (-1 < DebugLevel) {
          printk("%s : invalid mac setting\n","rtmp_read_fw_log_dump_parms_from_file");
        }
      }
      else {
        param_1 = param_1 + 0xa7cc2c;
        pcVar4 = param_2;
        do {
          pcVar5 = pcVar4 + 3;
          AtoH(pcVar4,param_1,1);
          param_1 = param_1 + 1;
          pcVar4 = pcVar5;
        } while (pcVar5 != param_2 + 0x12);
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s : invalid length (%d)\n","rtmp_read_fw_log_dump_parms_from_file",sVar2);
    }
  }
  return;
}

