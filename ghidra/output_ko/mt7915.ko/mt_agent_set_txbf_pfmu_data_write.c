// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_data_write @ 0x24e06c
// size: 252 bytes
//

undefined4 mt_agent_set_txbf_pfmu_data_write(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined2 local_84 [18];
  undefined4 local_60 [19];
  
  sys_ad_zero_mem(local_60,0x24);
  sVar1 = strlen(param_2);
  if (sVar1 == 0x3c) {
    pbVar3 = (byte *)agent_trtok(param_2,&_LC90);
    if (pbVar3 != (byte *)0x0) {
      iVar5 = 0;
      puVar6 = local_60;
      do {
        if ((((9 < *pbVar3 - 0x30) && (5 < (*pbVar3 & 0xffffffdf) - 0x41)) ||
            ((9 < pbVar3[1] - 0x30 && (5 < (pbVar3[1] & 0xffffffdf) - 0x41)))) ||
           ((iVar5 == 0x24 || (iVar4 = _kstrtol(pbVar3,0x10,puVar6), iVar4 != 0))))
        goto LAB_0024e098;
        *(short *)((int)local_84 + iVar5) = (short)*(undefined4 *)((int)local_60 + iVar5 * 2);
        pbVar3 = (byte *)agent_trtok(0,&_LC90);
        iVar5 = iVar5 + 4;
        puVar6 = puVar6 + 2;
      } while (pbVar3 != (byte *)0x0);
    }
    uVar2 = mt_serv_set_txbf_pfmu_data_write(param_1,local_84);
  }
  else {
LAB_0024e098:
    uVar2 = 0x104;
  }
  return uVar2;
}

