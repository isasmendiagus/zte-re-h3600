// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_tag_matrix @ 0x24db90
// size: 252 bytes
//

undefined4 mt_agent_set_txbf_pfmu_tag_matrix(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint local_28 [6];
  
  uVar6 = 0;
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_28[4] = 0;
  local_28[5] = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 0x11) {
    do {
      pbVar3 = (byte *)agent_trtok(param_2,&_LC90);
      if (pbVar3 == (byte *)0x0) {
        uVar4 = mt_serv_set_txbf_pfmu_tag_matrix
                          (param_1,local_28[0] & 0xff,local_28[1] & 0xff,local_28[2] & 0xff,
                           local_28[3] & 0xff,local_28[4] & 0xff,local_28[5] & 0xff);
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
      iVar2 = _kstrtol(pbVar3,0x10,local_28 + uVar5);
      param_2 = (char *)0x0;
    } while (iVar2 == 0);
  }
  return 0x104;
}

