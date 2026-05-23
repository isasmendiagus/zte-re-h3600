// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_tag_mem @ 0x24da64
// size: 300 bytes
//

undefined4 mt_agent_set_txbf_pfmu_tag_mem(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined4 local_38 [8];
  
  uVar6 = 0;
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  sVar1 = strlen(param_2);
  if (sVar1 == 0x17) {
    do {
      pbVar3 = (byte *)agent_trtok(param_2,&_LC90);
      if (pbVar3 == (byte *)0x0) {
        local_40 = (undefined1)local_38[0];
        local_3c = (undefined1)local_38[1];
        local_3f = (undefined1)local_38[2];
        local_3b = (undefined1)local_38[3];
        local_3e = (undefined1)local_38[4];
        local_3a = (undefined1)local_38[5];
        local_3d = (undefined1)local_38[6];
        local_39 = (undefined1)local_38[7];
        uVar4 = mt_serv_set_txbf_pfmu_tag_mem(param_1,&local_3c,&local_40);
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
      iVar2 = _kstrtol(pbVar3,0x10,local_38 + uVar5);
      param_2 = (char *)0x0;
    } while (iVar2 == 0);
  }
  return 0x104;
}

