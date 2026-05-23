// module: mt7915.ko
// function: hqa_mu_set_group @ 0x92b08
// size: 2380 bytes
//

undefined4 hqa_mu_set_group(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  ushort uVar21;
  char *pcVar22;
  int iVar23;
  undefined4 uVar24;
  uint uVar25;
  char *local_64 [2];
  ushort local_5a;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  byte local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined1 local_41;
  
  local_64[0] = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_set_group");
      goto LAB_00093084;
    }
LAB_00092f68:
    uVar24 = 0;
  }
  else {
    pcVar22 = strsep(local_64,":");
    if (pcVar22 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_00092f68;
      printk("%s: GroupIndex is NULL\n","hqa_mu_set_group");
LAB_00093084:
      if (DebugLevel < 1) goto LAB_00092f68;
      uVar24 = 0;
    }
    else {
      uVar21 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: NumOfUser is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar1 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: Bandwidth is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar2 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User0Ldpc is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar3 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User1Ldpc is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar4 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User2Ldpc is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar5 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User3Ldpc is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      bVar6 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User0Nss is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar7 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User1Nss is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar8 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User2Nss is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar9 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User3Nss is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar10 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: GroupId is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar11 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User0InitMCS is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar12 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User1InitMCS is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar13 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User2InitMCS is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar14 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User3InitMCS is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar15 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User0MuPfId is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar16 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User1MuPfId is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar17 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User2MuPfId is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar18 = simple_strtol(pcVar22,0,10);
      pcVar22 = strsep(local_64,":");
      if (pcVar22 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: User3MuPfId is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar19 = simple_strtol(pcVar22,0,10);
      if (local_64[0] == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092f68;
        printk("%s: SGI is NULL\n","hqa_mu_set_group");
        goto LAB_00093084;
      }
      uVar20 = simple_strtol(local_64[0],0,10);
      os_zero_mem(&local_5a,0x32);
      local_5a = uVar21;
      local_58 = uVar1;
      local_57 = uVar3;
      local_56 = uVar4;
      local_55 = uVar5;
      local_54 = bVar6;
      local_53 = uVar20;
      local_52 = uVar2;
      local_51 = uVar7;
      local_50 = uVar8;
      local_4f = uVar9;
      local_4e = uVar10;
      local_4d = uVar11;
      local_48 = uVar16;
      local_47 = uVar17;
      local_46 = uVar18;
      local_45 = uVar19;
      local_44 = uVar12;
      local_43 = uVar13;
      local_42 = uVar14;
      local_41 = uVar15;
      if (0 < DebugLevel) {
        uVar25 = (uint)bVar6;
        printk("%s: Gindex:%u Num_User:%u BW:%u LDPC[0~3]:%u %u %u %u\n","hqa_mu_set_group",uVar21,
               uVar1,uVar2,uVar3,uVar4,uVar5,uVar25);
        if ((0 < DebugLevel) &&
           (printk("%s: Nss[0~3]:%u %u %u %u GID:%u SGI:%u\n","hqa_mu_set_group",local_51,local_50,
                   local_4f,local_4e,local_4d,local_53,uVar25), 0 < DebugLevel)) {
          printk("%s: InitMCS[0~3]:%u %u %u %u PFID[0~3]:%u %u %u %u\n","hqa_mu_set_group",local_44,
                 local_43,local_42,local_41,local_48,local_47,local_46,local_45);
        }
      }
      iVar23 = hqa_wifi_test_mu_group_set(param_1,&local_5a);
      if (iVar23 != 0) goto LAB_00093084;
      if (DebugLevel < 1) {
        return 1;
      }
      uVar24 = 1;
    }
    printk("%s: CMD %s\n","hqa_mu_set_group");
  }
  return uVar24;
}

