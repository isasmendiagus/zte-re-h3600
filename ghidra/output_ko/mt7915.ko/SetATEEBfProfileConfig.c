// module: mt7915.ko
// function: SetATEEBfProfileConfig @ 0x2677f0
// size: 1228 bytes
//

undefined4 SetATEEBfProfileConfig(int param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  int iVar4;
  byte *__s;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  int local_98;
  undefined4 local_94;
  byte local_8b [3];
  uint local_88 [4];
  char local_78 [8];
  char *pcStack_70;
  undefined4 uStack_6c;
  undefined2 local_68;
  
  iVar1 = net_ad_wrap_service();
  uVar6 = (uint)*(byte *)(iVar1 + 0x4cc);
  local_8b[0] = 0;
  local_8b[1] = 0;
  local_8b[2] = 0;
  local_88[0] = 0;
  local_88[1] = 0;
  local_88[2] = 0;
  local_88[3] = 0;
  iVar1 = net_ad_wrap_service(param_1);
  iVar1 = *(int *)(uVar6 * 0xd18 + iVar1 + 0x504);
  if ((param_2 == (char *)0x0) || (sVar2 = strlen(param_2), sVar2 != 8)) {
LAB_00267854:
    uVar3 = 0;
  }
  else {
    iVar4 = net_ad_wrap_service(param_1);
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      pbVar7 = local_8b;
      do {
        sVar2 = strlen((char *)__s);
        if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_00267854;
        AtoH(__s,pbVar7);
        __s = (byte *)rstrtok(0,&_LC2);
        pbVar7 = pbVar7 + 1;
      } while (__s != (byte *)0x0);
    }
    uVar8 = (uint)local_8b[0];
    iVar5 = net_ad_wrap_service(param_1);
    switch(*(undefined1 *)(uVar6 * 0xd18 + iVar5 + 0x1128)) {
    case 3:
      local_94 = 1;
      local_98 = 0;
      break;
    default:
      local_94 = 3;
      local_98 = 2;
      break;
    case 7:
      local_94 = 2;
      local_98 = 1;
      break;
    case 0xc:
      if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
        local_94 = 1;
        local_98 = 0;
      }
      else {
        local_94 = 3;
        local_98 = 2;
      }
    }
    uVar9 = (uint)local_8b[2];
    iVar5 = iVar4 + uVar6 * 0xd18;
    snprintf(local_78,0x50,"%d",uVar8);
    Set_TxBfProfileTag_PfmuIdx(param_1,local_78);
    iVar4 = iVar4 + uVar6 * 0xd18;
    Set_TxBfProfileTag_BfType(param_1,&_LC332);
    Set_TxBfProfileTag_DBW(param_1,&_LC326);
    Set_TxBfProfileTag_SuMu(param_1,&_LC326);
    mt_WrapIBfCalGetEBfMemAlloc(param_1,local_88,local_88 + 2);
    snprintf(local_78,0x18,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",local_88[2] & 0xff,
             local_88[0] & 0xff,local_88[2] >> 8 & 0xff,local_88[0] >> 8 & 0xff,
             local_88[2] >> 0x10 & 0xff,local_88[0] >> 0x10 & 0xff,local_88[2] >> 0x18,
             local_88[0] >> 0x18);
    Set_TxBfProfileTag_Mem(param_1,local_78);
    snprintf(local_78,0x12,"%.2x:%.2x:00:01:00:00",local_94,uVar9);
    Set_TxBfProfileTag_Matrix(param_1,local_78);
    builtin_strncpy(local_78,"00:00:00",8);
    pcStack_70 = "(%d), timeout(%dms)\n";
    Set_TxBfProfileTag_SNR(param_1,&_LC329);
    Set_TxBfProfileTag_SmartAnt(param_1,&_LC326);
    Set_TxBfProfileTag_SeIdx(param_1,&_LC326);
    Set_TxBfProfileTag_RmsdThrd(param_1,&_LC326);
    builtin_strncpy(local_78,"00:00:00",8);
    pcStack_70 = (char *)0x3a30303a;
    uStack_6c = 0x303a3030;
    local_68 = 0x30;
    Set_TxBfProfileTag_McsThrd(param_1,local_78);
    Set_TxBfProfileTag_InValid(param_1,&_LC332);
    snprintf(local_78,0x50,"%d",uVar8);
    Set_TxBfProfileTagWrite(param_1,local_78);
    snprintf(local_78,0x50,"01:%.2x:00:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",(int)*(char *)(iVar1 + 0xd),
             (uint)*(byte *)(iVar4 + 0x531),(uint)*(byte *)(iVar5 + 0x532),
             (uint)*(byte *)(iVar5 + 0x533),(uint)*(byte *)(iVar5 + 0x534),
             (uint)*(byte *)(iVar5 + 0x535),(uint)*(byte *)(iVar5 + 0x536));
    ate_set_cmm_starec(param_1,local_78);
    if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
      uVar3 = 4;
    }
    else {
      uVar3 = 1;
    }
    snprintf(local_78,0x50,
             "%.2x:00:%.2x:00:01:00:%.2x:00:02:%.2x:%.2x:00:00:00:00:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x"
             ,uVar3,uVar8,(uint)(byte)(&UNK_002a58e4)[local_98],uVar9,local_94,local_88[0] & 0xff,
             local_88[2] & 0xff,local_88[0] >> 8 & 0xff,local_88[2] >> 8 & 0xff,
             local_88[0] >> 0x10 & 0xff,local_88[2] >> 0x10 & 0xff,local_88[0] >> 0x18,
             local_88[2] >> 0x18);
    Set_StaRecBfUpdate(param_1,local_78);
    snprintf(local_78,0x50,"%d",uVar3);
    Set_StaRecBfRead(param_1,local_78);
    snprintf(local_78,0x50,
             "mac:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x-type:sta-wtbl:1-ownmac:0-mode:aanac-bw:20-nss:%d-pfmuId:%d\n"
             ,(uint)*(byte *)(iVar4 + 0x531),(uint)*(byte *)(iVar5 + 0x532),
             (uint)*(byte *)(iVar5 + 0x533),(uint)*(byte *)(iVar5 + 0x534),
             (uint)*(byte *)(iVar5 + 0x535),(uint)*(byte *)(iVar5 + 0x536),uVar9 + 1,uVar8);
    ate_set_manual_assoc(param_1,local_78);
    uVar3 = 1;
  }
  return uVar3;
}

