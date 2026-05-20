// module: tm.ko
// function: tm_convert_value_to_name @ 0x66e40
// size: 2036 bytes
//

void tm_convert_value_to_name(int param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  
  if (param_1 == 0) {
    switch(param_2) {
    case 0:
      pcVar9 = "ZTE_SW_ACL_FIELD_UNIPORT";
      goto LAB_00067150;
    case 1:
      pcVar9 = "ZTE_SW_ACL_FIELD_PONPORT";
      goto LAB_00067150;
    case 2:
      pcVar9 = "ZTE_SW_ACL_FIELD_DMAC";
      goto LAB_00067114;
    case 3:
      pcVar9 = "ZTE_SW_ACL_FIELD_SMAC";
LAB_00067114:
      uVar4 = *(undefined4 *)(pcVar9 + 4);
      uVar6 = *(undefined4 *)(pcVar9 + 8);
      uVar5 = *(undefined4 *)(pcVar9 + 0xc);
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      uVar2 = *(undefined2 *)(pcVar9 + 0x14);
      uVar3 = *(undefined4 *)(pcVar9 + 0x10);
      *(undefined4 *)(param_3 + 4) = uVar4;
      *(undefined4 *)(param_3 + 8) = uVar6;
      *(undefined4 *)(param_3 + 0xc) = uVar5;
      *(undefined4 *)(param_3 + 0x10) = uVar3;
      *(undefined2 *)(param_3 + 0x14) = uVar2;
      return;
    case 4:
      pcVar9 = "ZTE_SW_ACL_FIELD_TAG_LEVEL";
      goto LAB_00066fb4;
    case 5:
      pcVar9 = "ZTE_SW_ACL_FIELD_OUTERTPID";
      goto LAB_00066fb4;
    case 6:
    case 8:
      pcVar9 = "ZTE_SW_ACL_FIELD_OUTERTAG";
      break;
    case 7:
      pcVar9 = "ZTE_SW_ACL_FIELD_INNERTPID";
      goto LAB_00066fb4;
    case 9:
      pcVar9 = "ZTE_SW_ACL_FIELD_ETHERTYPE";
LAB_00066fb4:
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar6 = *(undefined4 *)(pcVar9 + 8);
      uVar5 = *(undefined4 *)(pcVar9 + 0xc);
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      uVar3 = *(undefined4 *)(pcVar9 + 0x10);
      uVar4 = *(undefined4 *)(pcVar9 + 0x14);
      *(undefined4 *)(param_3 + 8) = uVar6;
      *(undefined4 *)(param_3 + 0xc) = uVar5;
      uVar2 = *(undefined2 *)(pcVar9 + 0x18);
      cVar1 = pcVar9[0x1a];
      *(undefined4 *)(param_3 + 0x10) = uVar3;
      *(undefined4 *)(param_3 + 0x14) = uVar4;
      *(undefined2 *)(param_3 + 0x18) = uVar2;
      param_3[0x1a] = cVar1;
      return;
    case 10:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV4_VERSION";
      goto LAB_00066ffc;
    case 0xb:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV4_TOS";
      break;
    case 0xc:
      builtin_strncpy(param_3,"ZTE_SW_ACL_FIELD_IPV4_PROTOCOL",0x1f);
      return;
    case 0xd:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV4_DIP";
      break;
    case 0xe:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV4_SIP";
      break;
    case 0xf:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_NEXTHEADER";
      do {
        pcVar8 = param_3 + 0x10;
        uVar3 = *(undefined4 *)(pcVar9 + 4);
        uVar4 = *(undefined4 *)(pcVar9 + 8);
        uVar6 = *(undefined4 *)(pcVar9 + 0xc);
        pcVar7 = pcVar9 + 0x10;
        bVar10 = pcVar9 != "_IPV6_NEXTHEADER";
        *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
        *(undefined4 *)(param_3 + 4) = uVar3;
        *(undefined4 *)(param_3 + 8) = uVar4;
        *(undefined4 *)(param_3 + 0xc) = uVar6;
        pcVar9 = pcVar7;
        param_3 = pcVar8;
      } while (bVar10);
      goto LAB_00067060;
    case 0x10:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_TRAFFIC_CLASS";
      do {
        pcVar7 = param_3;
        uVar3 = *(undefined4 *)(pcVar9 + 4);
        uVar4 = *(undefined4 *)(pcVar9 + 8);
        uVar6 = *(undefined4 *)(pcVar9 + 0xc);
        bVar10 = pcVar9 != "_IPV6_TRAFFIC_CLASS";
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
        *(undefined4 *)(pcVar7 + 4) = uVar3;
        *(undefined4 *)(pcVar7 + 8) = uVar4;
        *(undefined4 *)(pcVar7 + 0xc) = uVar6;
        pcVar9 = pcVar9 + 0x10;
        param_3 = pcVar7 + 0x10;
      } while (bVar10);
      builtin_strncpy(pcVar7 + 0x10,"ASS",4);
      return;
    case 0x11:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_FLOWLABEL";
      goto LAB_000671c0;
    case 0x12:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_DIPV6";
      goto LAB_00067190;
    case 0x13:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_SIPV6";
      goto LAB_00067190;
    case 0x14:
      pcVar9 = "ZTE_SW_ACL_FIELD_L4_DPORT";
      break;
    case 0x15:
      pcVar9 = "ZTE_SW_ACL_FIELD_L4_SPORT";
      break;
    case 0x16:
      pcVar9 = "ZTE_SW_ACL_FIELD_IPV6_SECONDHEADER";
      do {
        pcVar8 = param_3 + 0x10;
        uVar3 = *(undefined4 *)(pcVar9 + 4);
        uVar4 = *(undefined4 *)(pcVar9 + 8);
        uVar6 = *(undefined4 *)(pcVar9 + 0xc);
        pcVar7 = pcVar9 + 0x10;
        bVar10 = pcVar9 != "_IPV6_SECONDHEADER";
        *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
        *(undefined4 *)(param_3 + 4) = uVar3;
        *(undefined4 *)(param_3 + 8) = uVar4;
        *(undefined4 *)(param_3 + 0xc) = uVar6;
        pcVar9 = pcVar7;
        param_3 = pcVar8;
      } while (bVar10);
      goto LAB_00067260;
    default:
      goto switchD_00066e54_caseD_17;
    case 0x18:
      if (g_tm_debug_level == 0) {
        return;
      }
      printk("Excess valid match field \n");
      return;
    }
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar6 = *(undefined4 *)(pcVar9 + 8);
    uVar5 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    uVar3 = *(undefined4 *)(pcVar9 + 0x10);
    uVar4 = *(undefined4 *)(pcVar9 + 0x14);
    *(undefined4 *)(param_3 + 0xc) = uVar5;
    *(undefined4 *)(param_3 + 8) = uVar6;
    uVar2 = *(undefined2 *)(pcVar9 + 0x18);
    *(undefined4 *)(param_3 + 0x10) = uVar3;
    *(undefined4 *)(param_3 + 0x14) = uVar4;
    *(undefined2 *)(param_3 + 0x18) = uVar2;
    return;
  }
  if (param_1 != 1) {
    if (g_tm_debug_level == 0) {
      return;
    }
    printk("Invalid match or act flag \n");
    return;
  }
  switch(param_2) {
  case 0:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_DMAC";
    goto LAB_000675a4;
  case 1:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_SMAC";
LAB_000675a4:
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar6 = *(undefined4 *)(pcVar9 + 8);
    uVar5 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    uVar3 = *(undefined4 *)(pcVar9 + 0x10);
    uVar4 = *(undefined4 *)(pcVar9 + 0x14);
    *(undefined4 *)(param_3 + 8) = uVar6;
    *(undefined4 *)(param_3 + 0xc) = uVar5;
    *(undefined4 *)(param_3 + 0x10) = uVar3;
    *(undefined4 *)(param_3 + 0x14) = uVar4;
    return;
  case 2:
    pcVar9 = "ZTE_SW_ACL_ACT_UNTAG_ADD_ONETAG";
    goto LAB_000671c0;
  case 3:
    pcVar9 = "ZTE_SW_ACL_ACT_UNTAG_ADD_TWOTAG";
    goto LAB_000671c0;
  case 4:
    pcVar9 = "ZTE_SW_ACL_ACT_ONETAG_ADD_ONETAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "NETAG_ADD_ONETAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 5:
    pcVar9 = "ZTE_SW_ACL_ACT_ONETAG_DEL_ONETAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "NETAG_DEL_ONETAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 6:
    pcVar9 = "ZTE_SW_ACL_ACT_ONETAG_MOD_ONETAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "NETAG_MOD_ONETAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 7:
    pcVar9 = "ZTE_SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG";
    do {
      pcVar7 = param_3;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "NETAG_ADD_ONETAG_MOD_ONETAG";
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      *(undefined4 *)(pcVar7 + 4) = uVar3;
      *(undefined4 *)(pcVar7 + 8) = uVar4;
      *(undefined4 *)(pcVar7 + 0xc) = uVar6;
      param_3 = pcVar7 + 0x10;
      pcVar9 = pcVar9 + 0x10;
    } while (bVar10);
    builtin_strncpy(pcVar7 + 0x10,"_MOD_ONETAG",0xc);
    return;
  case 8:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_ADD_ONETAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_ADD_ONETAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 9:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_DEL_ONETAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_DEL_ONETAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 10:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_MOD_INNERTAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_MOD_INNERTAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "AG";
    goto LAB_00067260;
  case 0xb:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_MOD_OUTERTAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_MOD_OUTERTAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "AG";
    goto LAB_00067260;
  case 0xc:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_DEL_TWOTAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_DEL_TWOTAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 0xd:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG";
    do {
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "AG_MOD_INNERTAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = param_3 + 0x10;
    } while (bVar10);
    return;
  case 0xe:
    pcVar9 = "ZTE_SW_ACL_ACT_TWOTAG_MOD_TWOTAG";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "WOTAG_MOD_TWOTAG";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 0xf:
    builtin_strncpy(param_3,"ZTE_SW_ACL_ACT_SET_ETHERTYPE",0x1d);
    return;
  case 0x10:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV4_VERSION";
LAB_000671c0:
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar4 = *(undefined4 *)(pcVar9 + 8);
    uVar6 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    *(undefined4 *)(param_3 + 8) = uVar4;
    *(undefined4 *)(param_3 + 0xc) = uVar6;
    uVar3 = *(undefined4 *)(pcVar9 + 0x14);
    uVar4 = *(undefined4 *)(pcVar9 + 0x18);
    uVar6 = *(undefined4 *)(pcVar9 + 0x1c);
    *(undefined4 *)(param_3 + 0x10) = *(undefined4 *)(pcVar9 + 0x10);
    *(undefined4 *)(param_3 + 0x14) = uVar3;
    *(undefined4 *)(param_3 + 0x18) = uVar4;
    *(undefined4 *)(param_3 + 0x1c) = uVar6;
    return;
  case 0x11:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV4_TOS";
    goto LAB_00067190;
  case 0x12:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV4_PROTOCOL";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "ET_IPV4_PROTOCOL";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "";
    break;
  case 0x13:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV4_DIP";
    goto LAB_00067190;
  case 0x14:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV4_SIP";
    goto LAB_00067190;
  case 0x15:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV6_NEXTHEADER";
    do {
      pcVar8 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "ET_IPV6_NEXTHEADER";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar8;
    } while (bVar10);
    pcVar7 = "ER";
LAB_00067260:
    cVar1 = pcVar7[2];
    *(undefined2 *)pcVar8 = *(undefined2 *)pcVar7;
    pcVar8[2] = cVar1;
    return;
  case 0x16:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV6_TRAFFIC_CLASS";
    do {
      pcVar7 = param_3;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "ET_IPV6_TRAFFIC_CLASS";
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      *(undefined4 *)(pcVar7 + 4) = uVar3;
      *(undefined4 *)(pcVar7 + 8) = uVar4;
      *(undefined4 *)(pcVar7 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar7 + 0x10;
    } while (bVar10);
    builtin_strncpy(pcVar7 + 0x10,"CLASS",6);
    return;
  case 0x17:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV6_FLOWLABEL";
    do {
      pcVar7 = param_3 + 0x10;
      uVar3 = *(undefined4 *)(pcVar9 + 4);
      uVar4 = *(undefined4 *)(pcVar9 + 8);
      uVar6 = *(undefined4 *)(pcVar9 + 0xc);
      bVar10 = pcVar9 != "ET_IPV6_FLOWLABEL";
      *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
      *(undefined4 *)(param_3 + 4) = uVar3;
      *(undefined4 *)(param_3 + 8) = uVar4;
      *(undefined4 *)(param_3 + 0xc) = uVar6;
      pcVar9 = pcVar9 + 0x10;
      param_3 = pcVar7;
    } while (bVar10);
    pcVar7[0] = 'L';
    pcVar7[1] = '\0';
    return;
  case 0x18:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV6_DIPV6";
    goto LAB_00066ffc;
  case 0x19:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_IPV6_SIPV6";
LAB_00066ffc:
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar4 = *(undefined4 *)(pcVar9 + 8);
    uVar5 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    *(undefined4 *)(param_3 + 8) = uVar4;
    uVar3 = *(undefined4 *)(pcVar9 + 0x10);
    uVar4 = *(undefined4 *)(pcVar9 + 0x14);
    uVar6 = *(undefined4 *)(pcVar9 + 0x18);
    *(undefined4 *)(param_3 + 0xc) = uVar5;
    uVar2 = *(undefined2 *)(pcVar9 + 0x1c);
    *(undefined4 *)(param_3 + 0x10) = uVar3;
    *(undefined4 *)(param_3 + 0x14) = uVar4;
    *(undefined2 *)(param_3 + 0x1c) = uVar2;
    *(undefined4 *)(param_3 + 0x18) = uVar6;
    return;
  case 0x1a:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_L4_DPORT";
    goto LAB_00067190;
  case 0x1b:
    pcVar9 = "ZTE_SW_ACL_ACT_SET_L4_SPORT";
LAB_00067190:
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar4 = *(undefined4 *)(pcVar9 + 8);
    uVar5 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    *(undefined4 *)(param_3 + 8) = uVar4;
    uVar3 = *(undefined4 *)(pcVar9 + 0x10);
    uVar4 = *(undefined4 *)(pcVar9 + 0x14);
    uVar6 = *(undefined4 *)(pcVar9 + 0x18);
    *(undefined4 *)(param_3 + 0xc) = uVar5;
    *(undefined4 *)(param_3 + 0x10) = uVar3;
    *(undefined4 *)(param_3 + 0x14) = uVar4;
    *(undefined4 *)(param_3 + 0x18) = uVar6;
    return;
  case 0x1c:
    pcVar9 = "ZTE_SW_ACL_ACT_MIRROR";
    goto LAB_00067114;
  case 0x1d:
    pcVar9 = "ZTE_SW_ACL_ACT_RATELIMIT";
    goto LAB_00067150;
  case 0x1e:
    pcVar9 = "Excess  valid act  field";
LAB_00067150:
    uVar3 = *(undefined4 *)(pcVar9 + 4);
    uVar6 = *(undefined4 *)(pcVar9 + 8);
    uVar5 = *(undefined4 *)(pcVar9 + 0xc);
    *(undefined4 *)param_3 = *(undefined4 *)pcVar9;
    *(undefined4 *)(param_3 + 4) = uVar3;
    uVar3 = *(undefined4 *)(pcVar9 + 0x10);
    uVar4 = *(undefined4 *)(pcVar9 + 0x14);
    *(undefined4 *)(param_3 + 0xc) = uVar5;
    *(undefined4 *)(param_3 + 8) = uVar6;
    cVar1 = pcVar9[0x18];
    *(undefined4 *)(param_3 + 0x10) = uVar3;
    *(undefined4 *)(param_3 + 0x14) = uVar4;
    param_3[0x18] = cVar1;
    return;
  default:
switchD_00066e54_caseD_17:
    return;
  }
LAB_00067060:
  *pcVar8 = *pcVar7;
  return;
}

