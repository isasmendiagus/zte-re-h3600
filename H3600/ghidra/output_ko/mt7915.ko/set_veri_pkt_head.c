// module: mt7915.ko
// function: set_veri_pkt_head @ 0x1d6080
// size: 2268 bytes
//

undefined4 set_veri_pkt_head(undefined4 param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  size_t sVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  bool bVar7;
  int local_74;
  uint local_70;
  char local_6a [16];
  ushort local_5a;
  char local_58 [16];
  ushort local_48;
  char local_46 [16];
  ushort local_36;
  int local_34;
  uint local_30;
  undefined1 auStack_2c [6];
  undefined1 auStack_26 [6];
  undefined1 auStack_20 [8];
  
  local_74 = 0;
  local_70 = 0;
  local_6a[0] = '\0';
  local_6a[1] = '\0';
  local_6a[2] = '\0';
  local_6a[3] = '\0';
  local_6a[4] = '\0';
  local_6a[5] = '\0';
  local_6a[6] = '\0';
  local_6a[7] = '\0';
  local_6a[8] = '\0';
  local_6a[9] = '\0';
  local_6a[10] = '\0';
  local_6a[0xb] = '\0';
  local_6a[0xc] = '\0';
  local_6a[0xd] = '\0';
  local_6a[0xe] = '\0';
  local_6a[0xf] = '\0';
  local_5a = 0;
  local_58[0] = '\0';
  local_58[1] = '\0';
  local_58[2] = '\0';
  local_58[3] = '\0';
  local_58[4] = '\0';
  local_58[5] = '\0';
  local_58[6] = '\0';
  local_58[7] = '\0';
  local_58[8] = '\0';
  local_58[9] = '\0';
  local_58[10] = '\0';
  local_58[0xb] = '\0';
  local_58[0xc] = '\0';
  local_58[0xd] = '\0';
  local_58[0xe] = '\0';
  local_58[0xf] = '\0';
  local_48 = 0;
  local_46[0] = '\0';
  local_46[1] = '\0';
  local_46[2] = '\0';
  local_46[3] = '\0';
  local_46[4] = '\0';
  local_46[5] = '\0';
  local_46[6] = '\0';
  local_46[7] = '\0';
  local_46[8] = '\0';
  local_46[9] = '\0';
  local_46[10] = '\0';
  local_46[0xb] = '\0';
  local_46[0xc] = '\0';
  local_46[0xd] = '\0';
  local_46[0xe] = '\0';
  local_46[0xf] = '\0';
  local_36 = 0;
  __memzero(&local_34,0x1c);
  if (param_2 == (char *)0x0) {
    return 1;
  }
  uVar3 = sscanf(param_2,"%d-%d-%17s-%17s-%17s",&local_74,&local_70,local_6a,local_58,local_46);
  uVar2 = local_70;
  iVar1 = local_74;
  local_5a = local_5a & 0xff;
  local_48 = local_48 & 0xff;
  local_36 = local_36 & 0xff;
  if (local_74 < 4) {
    sVar4 = strlen(local_6a);
    if ((sVar4 == 0x11) || (local_6a[0] == '\0')) {
      sVar4 = strlen(local_58);
      if ((sVar4 == 0x11) || (local_58[0] == '\0')) {
        sVar4 = strlen(local_46);
        if ((sVar4 == 0x11) || (local_46[0] == '\0')) {
          if (iVar1 == 1) {
            bVar7 = 7 < uVar2;
            if (uVar2 != 8) {
              bVar7 = uVar2 != 10;
            }
            if (!bVar7 || (uVar2 == 8 || uVar2 == 0xb)) {
              if (uVar3 < 5) goto LAB_001d641c;
              if (-1 < DebugLevel) {
                printk("the head of ctrl_type pkt need TA/RA only.\n",sVar4);
                goto LAB_001d62d0;
              }
            }
            else if (-1 < DebugLevel) {
              printk("ctrl type only support BAR/RTS/Ps-Poll pkt_subtype:%d\n",uVar2);
              goto LAB_001d62d0;
            }
          }
          else if (iVar1 == 0) {
            if (uVar3 == 5) {
LAB_001d641c:
              local_30 = uVar2;
              local_34 = iVar1;
              if (-1 < DebugLevel) {
                printk("%s(): pkt_type:%d, pkt_subtype:0x%x, addr1_str:%17s, addr2_str:%17s, addr3_str:%17s\n"
                       ,"set_veri_pkt_head",iVar1,uVar2,local_6a,local_58,local_46);
                local_30 = local_70;
                local_34 = local_74;
              }
              pbVar5 = (byte *)rstrtok(local_6a,&_LC32);
              if (pbVar5 != (byte *)0x0) {
                puVar6 = auStack_2c;
                do {
                  sVar4 = strlen((char *)pbVar5);
                  if (((sVar4 != 2) || (((&_ctype)[*pbVar5] & 0x44) == 0)) ||
                     (((&_ctype)[pbVar5[1]] & 0x44) == 0)) goto LAB_001d62d0;
                  AtoH(pbVar5,puVar6);
                  pbVar5 = (byte *)rstrtok(0,&_LC32);
                  puVar6 = puVar6 + 1;
                } while (pbVar5 != (byte *)0x0);
              }
              pbVar5 = (byte *)rstrtok(local_58,&_LC32);
              if (pbVar5 != (byte *)0x0) {
                puVar6 = auStack_26;
                do {
                  sVar4 = strlen((char *)pbVar5);
                  if (((sVar4 != 2) || (((&_ctype)[*pbVar5] & 0x44) == 0)) ||
                     (((&_ctype)[pbVar5[1]] & 0x44) == 0)) goto LAB_001d62d0;
                  AtoH(pbVar5,puVar6);
                  pbVar5 = (byte *)rstrtok(0,&_LC32);
                  puVar6 = puVar6 + 1;
                } while (pbVar5 != (byte *)0x0);
              }
              pbVar5 = (byte *)rstrtok(local_46,&_LC32);
              if (pbVar5 != (byte *)0x0) {
                puVar6 = auStack_20;
                do {
                  sVar4 = strlen((char *)pbVar5);
                  if (((sVar4 != 2) || (((&_ctype)[*pbVar5] & 0x44) == 0)) ||
                     (((&_ctype)[pbVar5[1]] & 0x44) == 0)) goto LAB_001d62d0;
                  AtoH(pbVar5,puVar6);
                  pbVar5 = (byte *)rstrtok(0,&_LC32);
                  puVar6 = puVar6 + 1;
                } while (pbVar5 != (byte *)0x0);
              }
              prepare_veri_pkt_head(param_1,&local_34);
              return 1;
            }
            if (-1 < DebugLevel) {
              printk("mgmt format error: input_argument:%d, addr1_str:%s, addr2_str:%s, addr3_str:%s\n"
                     ,uVar3,local_6a,local_58,local_46);
              goto LAB_001d62d0;
            }
          }
          else if (iVar1 == 2) {
            if ((uVar2 & 0xfffffff3) == 0) {
              if (uVar3 == 5) goto LAB_001d641c;
              if (-1 < DebugLevel) {
                printk("802.11 data format error: addr1_str:%s, addr2_str:%s, addr3_str:%s\n",
                       local_6a,local_58,local_46);
                goto LAB_001d62d0;
              }
            }
            else if (-1 < DebugLevel) {
              printk("verify 802.11 Data support DATA/NULL DATA/QoS DATA/QoS Null only\n",sVar4);
              goto LAB_001d62d0;
            }
          }
          else {
            if (iVar1 != 3 || uVar3 < 5) goto LAB_001d641c;
            if (-1 < DebugLevel) {
              printk("dot3 data format error: addr1_str:%s, addr2_str:%s\n",local_6a,local_58);
              goto LAB_001d62d0;
            }
          }
        }
        else if (-1 < DebugLevel) {
          printk("len addr3_str is incorrect:%d\n",sVar4);
          goto LAB_001d62d0;
        }
      }
      else if (-1 < DebugLevel) {
        printk("len addr2_str is incorrect:%d\n",sVar4);
        goto LAB_001d62d0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("len addr1_str is incorrect:%d\n",sVar4);
      goto LAB_001d62d0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("pkt_type error:%d\n",local_74);
LAB_001d62d0:
    if (0 < DebugLevel) {
      printk("Step 1:\n");
      if (DebugLevel < 1) {
LAB_001d634c:
        if (DebugLevel < 1) {
LAB_001d63bc:
          if (0 < DebugLevel) {
            printk("\t\t- addr3 is a must for 802.11 data and mgmt packet\n");
          }
        }
        else {
          printk(
                "\tType: 2: DATA, acceptable subtype: 0:data, 4:null data, 8: QoS data, 12: QoS Null\n"
                );
          if (0 < DebugLevel) {
            printk("\tType: 3: 802.3 format pacekt\n");
LAB_001d6384:
            if ((0 < DebugLevel) &&
               (printk("\t\t- addr1 & addr2 is for a1 and a3 of 802.11 data and mgmt pkt\n"),
               0 < DebugLevel)) {
              printk("\t\t- also could be da & sa of 802.3 packet, ra & ta of CTRL pkt\n");
              goto LAB_001d63bc;
            }
          }
        }
      }
      else {
        printk("iwpriv ra0 set veri_pkt_head=\'type\'-\'subtype\'-\'addr1\'-\'addr2\'-\'addr3\'\n");
        if (0 < DebugLevel) {
          printk("\nDescription:\n");
          if (DebugLevel < 1) goto LAB_001d6384;
          printk(
                "\tType: 0: MGMT, acceptable subtype: any subtype EXCEPT beacon of 802.11 mgmt pkt\n"
                );
          if (0 < DebugLevel) {
            printk("\tType: 1: CTRL, acceptable subtype: 8:BAR, PS-Poll:10, RTS:11\n");
            goto LAB_001d634c;
          }
        }
      }
    }
  }
  FUN_001d54e4();
  if (DebugLevel < 1) {
    return 0;
  }
  printk("(Optional) Step 3: you can just type to enable some of them.\n");
  if (DebugLevel < 1) {
LAB_001d6780:
    if (0 < DebugLevel) {
      printk("\t\t- NA: 1:enable NO ACK packet in this packet\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t- TM: 1:enable timing measurement in this packet\n");
      goto LAB_001d67b8;
    }
LAB_001d67f0:
    if (0 < DebugLevel) {
      printk("\t\t- txs2h: 1:enable TXS2HOST in this packet. need to assign PacketID\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk(
            "\t\t- PM: 1:enable PM mode is controlled by SW. need to assign PM status in wifi hdr\n\n"
            );
      goto LAB_001d6828;
    }
LAB_001d6860:
    if (0 < DebugLevel) {
      printk(
            "\tfor example, iwpriv ra0 set veri_pkt_ctrl_en=sn:100, to set seq to 100 while you enabled seq\n"
            );
      if (DebugLevel < 1) {
        return 0;
      }
      printk(
            "\tiwpriv ra0 set veri_pkt_ctrl_assign=du:\'x\'-sn:\'x\'-pm:\'x\'-pid:\'x\'-life:\'x\'\n"
            );
      goto LAB_001d6898;
    }
LAB_001d68d0:
    if (DebugLevel < 1) goto LAB_001d6940;
    printk("\t\t- PM: the PM in wifi_hdr, it follows the WIFI spec\n");
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\t\t- PID: the PID assigned for TXS, it cannot exceed 255\n\n");
  }
  else {
    printk(
          "for example, iwpriv ra0 set veri_pkt_ctrl_en=du:1-na:1, to just control duration and no_ack.\n\n"
          );
    if (DebugLevel < 1) {
      return 0;
    }
    printk("\tiwpriv ra0 set veri_pkt_ctrl_en=du:\'x\'-na:\'x\'-tm:\'x\'");
    if (0 < DebugLevel) {
      printk("-sn:\'x\'-txs2m:\'x\'-txs2h:\'x\'-pm:\'x\'-life:\'x\'\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t- DU: 1:enable the duration is controlled by SW. need to assign dur in wifi hdr\n"
            );
      goto LAB_001d6780;
    }
LAB_001d67b8:
    if (0 < DebugLevel) {
      printk("\t\t- SN: 1:enable the seq is controlled by SW. need to assign seq in wifi hdr\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t- txs2m: 1:enable TXS2MCU in this packet. need to assign PacketID\n");
      goto LAB_001d67f0;
    }
LAB_001d6828:
    if (0 < DebugLevel) {
      printk("\t\t- life: 1:enable pkt lifetime is filled by SW. need to assign lifetime\n\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk(
            "(Optional) Step 4: you can only assign the value that you already want to controlled\n"
            );
      goto LAB_001d6860;
    }
LAB_001d6898:
    if (0 < DebugLevel) {
      printk("\t\t- DU: the duration in wifi_hdr\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t- SN: the SEQ in wifi_hdr, it cannot exceed 4095\n");
      goto LAB_001d68d0;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("\t\t- life: the lifetime assigned, it cannot exceed 255\n\n");
  if (DebugLevel < 1) {
    return 0;
  }
  printk("Step 5:\n");
LAB_001d6940:
  if (0 < DebugLevel) {
    printk("\tiwpriv ra0 set send_veri_pkt=1\n");
  }
  return 0;
}

