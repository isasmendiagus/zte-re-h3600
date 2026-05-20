// module: mt7915.ko
// function: InsertChannelRepIE @ 0x13eb40
// size: 400 bytes
//

void InsertChannelRepIE(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,
                       char param_5,int param_6,undefined2 param_7)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  byte local_36 [2];
  int local_34;
  char local_30 [16];
  
  local_30[0] = '\0';
  local_30[1] = '\0';
  local_30[2] = '\0';
  local_30[3] = '\0';
  local_30[4] = '\0';
  local_30[5] = '\0';
  local_30[6] = '\0';
  local_30[7] = '\0';
  local_30[8] = '\0';
  local_30[9] = '\0';
  local_30[10] = '\0';
  local_30[0xb] = '\0';
  local_30[0xc] = '\0';
  local_30[0xd] = '\0';
  local_30[0xe] = '\0';
  local_30[0xf] = '\0';
  local_36[1] = 0x33;
  if (param_5 != '\0') {
    local_36[0] = 1;
    pcVar1 = (char *)get_channelset_by_reg_class(param_1,param_5,param_7);
    uVar2 = get_channel_set_num();
    iVar3 = get_channel_set_num(param_6);
    if (uVar2 != 0 && pcVar1 != (char *)0x0) {
      uVar5 = 0;
      uVar6 = uVar2;
      if (iVar3 != 0) {
        pcVar4 = pcVar1 + (uVar2 - 1 & 0xff) + 1;
        pcVar7 = (char *)(param_6 + -1);
        do {
          pcVar7 = pcVar7 + 1;
          if (*pcVar1 == *pcVar7) {
            local_30[uVar5] = *pcVar1;
            uVar5 = uVar5 + 1 & 0xff;
          }
        } while ((pcVar7 != (char *)(param_6 + (iVar3 - 1U & 0xff))) ||
                (pcVar1 = pcVar1 + 1, pcVar7 = (char *)(param_6 + -1), pcVar1 != pcVar4));
        pcVar1 = local_30;
        uVar6 = uVar5;
      }
      if (3 < DebugLevel) {
        printk("%s: Requlatory class (%d), NumberOfChannels=%d, channel_set_num=%d\n",
               "InsertChannelRepIE",param_5,uVar6,uVar2);
      }
      uVar2 = uVar6 + local_36[0] & 0xff;
      local_36[0] = (byte)(uVar6 + local_36[0]);
      if (1 < uVar2) {
        MakeOutgoingFrame(param_2,&local_34,1,local_36 + 1,1,local_36,1,&param_5,uVar2 - 1,pcVar1,
                          0xffffffff);
        *param_3 = *param_3 + local_34;
        return;
      }
    }
  }
  return;
}

