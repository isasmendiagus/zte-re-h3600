// module: mt7915.ko
// function: mt_agent_set_txbf_profile_tag_read @ 0x24d7fc
// size: 208 bytes
//

undefined4 mt_agent_set_txbf_profile_tag_read(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint local_18 [2];
  
  uVar6 = 0;
  local_18[0] = 0;
  local_18[1] = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 5) {
    do {
      pbVar3 = (byte *)agent_trtok(param_2,&_LC90);
      if (pbVar3 == (byte *)0x0) {
        uVar4 = mt_serv_set_txbf_profile_tag_read(param_1,local_18[0] & 0xff,local_18[1] & 0xff);
        return uVar4;
      }
      uVar5 = uVar6 & 0xff;
      uVar6 = uVar6 + 1;
      if ((9 < *pbVar3 - 0x30) && (5 < (*pbVar3 & 0xffffffdf) - 0x41)) {
        return 0x104;
      }
      if ((9 < pbVar3[1] - 0x30) && (5 < (pbVar3[1] & 0xffffffdf) - 0x41)) {
        return 0x104;
      }
      iVar2 = _kstrtol(pbVar3,0x10,local_18 + uVar5);
      param_2 = (char *)0x0;
    } while (iVar2 == 0);
  }
  return 0x104;
}

