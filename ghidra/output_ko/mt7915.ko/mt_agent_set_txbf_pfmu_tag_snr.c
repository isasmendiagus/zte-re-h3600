// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_tag_snr @ 0x24dc8c
// size: 240 bytes
//

undefined4 mt_agent_set_txbf_pfmu_tag_snr(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_40 [8];
  undefined4 local_38 [9];
  
  sVar1 = strlen(param_2);
  if (sVar1 == 0xb || sVar1 == 0x17) {
    uVar6 = 0;
    pbVar3 = (byte *)agent_trtok(param_2,&_LC90);
    while (pbVar3 != (byte *)0x0) {
      uVar5 = uVar6 & 0xff;
      uVar6 = uVar6 + 1;
      if ((((9 < *pbVar3 - 0x30) && (5 < (*pbVar3 & 0xffffffdf) - 0x41)) ||
          ((9 < pbVar3[1] - 0x30 && (5 < (pbVar3[1] & 0xffffffdf) - 0x41)))) ||
         (iVar4 = _kstrtol(pbVar3,0x10,local_38 + uVar5), iVar4 != 0)) goto LAB_0024dcb8;
      local_40[uVar5] = (char)local_38[uVar5];
      pbVar3 = (byte *)agent_trtok(0,&_LC90);
    }
    uVar2 = mt_serv_set_txbf_pfmu_tag_snr(param_1,local_40);
  }
  else {
LAB_0024dcb8:
    uVar2 = 0x104;
  }
  return uVar2;
}

