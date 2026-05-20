// module: mt7915.ko
// function: mt_serv_set_ibf_profile_update @ 0x2530e8
// size: 992 bytes
//

undefined4 mt_serv_set_ibf_profile_update(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint unaff_r11;
  uint uVar5;
  byte local_86;
  byte local_85;
  byte local_84;
  byte local_83;
  byte local_82;
  byte local_81;
  byte local_80;
  byte local_7f;
  undefined1 auStack_7e [3];
  undefined1 auStack_7b [3];
  char acStack_78 [45];
  char acStack_4b [7];
  char acStack_44 [32];
  
  uVar1 = (uint)*(byte *)(param_1 + 0x133);
  uVar4 = 0x1128;
  printk("%s : band[%d]\'s TxAntennaSel = 0x%x\n","mt_serv_set_ibf_profile_update",uVar1,
         param_1[uVar1 * 0x346 + 0x44a]);
  uVar2 = *(byte *)(param_1 + uVar1 * 0x346 + 0x44a) - 3;
  if (uVar2 < 0xd) {
    uVar5 = (uint)(byte)"mt_serv_set_ibf_profile_update"
                        [*(byte *)(param_1 + uVar1 * 0x346 + 0x44a) + 0x1d];
  }
  else {
    uVar5 = 3;
    uVar4 = 2;
    unaff_r11 = uVar5;
  }
  iVar3 = param_1[0x7c4];
  if (uVar2 < 0xd) {
    uVar4 = uVar5 - 1;
    unaff_r11 = uVar5;
  }
  if (uVar2 < 0xd) {
    uVar4 = uVar4 & 0xff;
  }
  if (*(code **)(iVar3 + 0x1a4) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1a4))(*param_1,param_2);
    iVar3 = param_1[0x7c4];
    if (*(int *)(iVar3 + 0x1a4) != 0) {
      (**(code **)(iVar3 + 0x1a8))(*param_1,0);
      iVar3 = param_1[0x7c4];
    }
  }
  if (*(code **)(iVar3 + 0x1ac) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1ac))(*param_1,0);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1b0) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1b0))(*param_1,0);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1b4) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1b4))(*param_1,&local_86,&local_82);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1bc) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1bc))(*param_1,&local_86,&local_82);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1c0) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1c0))(*param_1,uVar5,param_3,0,0,0,0);
  }
  sys_ad_zero_mem(auStack_7e,4);
  iVar3 = param_1[0x7c4];
  if (*(code **)(iVar3 + 0x1c4) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1c4))(*param_1,auStack_7e);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1c8) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1c8))(*param_1,0);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1cc) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1cc))(*param_1,0);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1d0) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1d0))(*param_1,0);
  }
  sys_ad_zero_mem(auStack_7e,6);
  net_ad_set_txbf_profile_tag_mcs_thrd(*param_1,auStack_7e,auStack_7b);
  iVar3 = param_1[0x7c4];
  if (*(code **)(iVar3 + 0x1d4) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1d4))(*param_1,0xff);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1d8) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1d8))(*param_1,0);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1dc) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1dc))(*param_1,uVar5);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1e0) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1e0))(*param_1,param_3);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x1a0) != (code *)0x0) {
    (**(code **)(iVar3 + 0x1a0))(*param_1,1);
    iVar3 = param_1[0x7c4];
  }
  if (*(code **)(iVar3 + 0x19c) != (code *)0x0) {
    (**(code **)(iVar3 + 0x19c))(*param_1,param_2);
  }
  if (uVar4 < 3) {
    uVar4 = (uint)(byte)(&UNK_002a4db0)[uVar4];
  }
  else {
    uVar4 = 0x18;
  }
  snprintf(acStack_78,0x50,"%.2x:00:%.2x:00:00:00:%.2x:00:02:%.2x:%.2x:00:00:00:00:",1,param_2,uVar4
           ,param_3,unaff_r11);
  snprintf(acStack_4b,0x23,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",(uint)local_86,(uint)local_82,
           (uint)local_85,(uint)local_81,(uint)local_84,(uint)local_80,(uint)local_83,(uint)local_7f
          );
  net_ad_set_sta_rec_bf_update(*param_1,acStack_78);
  snprintf(acStack_78,0x50,"%d",1);
  net_ad_set_sta_rec_bf_read(*param_1,acStack_78);
  snprintf(acStack_78,0x50,"mac:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x-type:sta-wtbl:1-ownmac:0-mode:",
           (uint)*(byte *)((int)param_1 + uVar1 * 0xd18 + 0x531),
           (uint)*(byte *)((int)param_1 + uVar1 * 0xd18 + 0x532),
           (uint)*(byte *)((int)param_1 + uVar1 * 0xd18 + 0x533),
           (uint)*(byte *)(param_1 + uVar1 * 0x346 + 0x14d),
           (uint)*(byte *)((int)param_1 + uVar1 * 0xd18 + 0x535),
           (uint)*(byte *)((int)param_1 + uVar1 * 0xd18 + 0x536));
  snprintf(acStack_44,0x1c,"aanac-bw:20-nss:%d-pfmuId:%d\n",param_3 + 1,param_2);
  mt_op_set_manual_assoc(*param_1,acStack_78);
  return 0;
}

