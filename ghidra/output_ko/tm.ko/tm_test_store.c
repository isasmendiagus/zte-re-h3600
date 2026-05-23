// module: tm.ko
// function: tm_test_store @ 0x773d4
// size: 2500 bytes
//

undefined4 tm_test_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  undefined4 extraout_r1_10;
  undefined4 extraout_r1_11;
  undefined4 extraout_r1_12;
  undefined4 extraout_r1_13;
  undefined4 extraout_r1_14;
  undefined4 extraout_r1_15;
  undefined4 extraout_r1_16;
  undefined4 extraout_r1_17;
  undefined4 extraout_r1_18;
  undefined4 extraout_r1_19;
  undefined4 extraout_r1_20;
  undefined4 extraout_r1_21;
  undefined4 extraout_r1_22;
  undefined4 extraout_r1_23;
  undefined4 extraout_r1_24;
  undefined4 extraout_r1_25;
  undefined4 extraout_r1_26;
  undefined4 extraout_r1_27;
  undefined4 extraout_r1_28;
  undefined4 extraout_r1_29;
  undefined4 extraout_r1_30;
  undefined4 extraout_r1_31;
  undefined4 extraout_r1_32;
  undefined4 extraout_r1_33;
  undefined4 extraout_r1_34;
  undefined4 extraout_r1_35;
  undefined4 extraout_r1_36;
  undefined4 extraout_r1_37;
  undefined4 extraout_r1_38;
  undefined4 extraout_r1_39;
  undefined4 extraout_r1_40;
  char *__s1;
  uint uVar4;
  uint uVar5;
  uint local_ac;
  uint local_a8;
  uint local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  int local_8c;
  uint local_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  __s1 = (char *)*param_2;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_a0 = 0;
  local_9c = 0;
  iVar3 = capable(0xc);
  if (iVar3 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    sscanf(param_3,"%d %d %d %d %d",&local_ac,&local_a8,&local_a4,&local_a0,&local_9c);
    disableIRQinterrupts();
    iVar3 = strcmp(__s1,"sprbsrxbist");
    if (iVar3 == 0) {
      printk("[tmtst]sprbsrxbist input:prbsMode =0x%x,RxbistEnable=0x%x\n",local_ac,local_a8);
    }
    else {
      iVar3 = strcmp(__s1,"gportstatistics1");
      if (iVar3 == 0) {
        iVar3 = zte_api_sw_port_get_port_statistics1(local_ac & 0xff,&local_90);
        if (iVar3 == 0) {
          printk("inbytes = %lld\n",0,local_90,local_8c);
          printk("inpkts = %lld\n",extraout_r1_17,local_88,uStack_84);
          printk("inunicast = %lld\n",extraout_r1_18,local_80,uStack_7c);
          printk("inmulticast = %lld\n",extraout_r1_19,local_78,uStack_74);
          printk("inbroadcast = %lld\n",extraout_r1_20,local_70,uStack_6c);
          printk("inerror = %lld\n",extraout_r1_21,local_68,uStack_64);
          printk("indiscard = %lld\n",extraout_r1_22,local_60,uStack_5c);
          printk("outbytes = %lld\n",extraout_r1_23,local_58,uStack_54);
          printk("outpkts = %lld\n",extraout_r1_24,local_50,uStack_4c);
          printk("outunicast = %lld\n",extraout_r1_25,local_48,uStack_44);
          printk("outmulticast = %lld\n",extraout_r1_26,local_40,uStack_3c);
          printk("outbroadcast = %lld\n",extraout_r1_27,local_38,uStack_34);
          printk("outerror = %lld\n",extraout_r1_28,local_30,uStack_2c);
          printk("outdiscard = %lld\n",extraout_r1_29,local_28,uStack_24);
        }
        else {
          printk("[tmtst]g_port_statistics1 fail, error code %d!\n");
        }
      }
      else {
        iVar3 = strcmp(__s1,"gportstatistics2");
        if (iVar3 == 0) {
          iVar3 = zte_api_sw_port_get_port_statistics2(local_ac & 0xff,&local_90);
          if (iVar3 == 0) {
            printk("inundersize = %lld\n",0,local_90,local_8c);
            printk("inoversize = %lld\n",extraout_r1,local_88,uStack_84);
            printk("infragments = %lld\n",extraout_r1_00,local_80,uStack_7c);
            printk("injabbers = %lld\n",extraout_r1_01,local_78,uStack_74);
            printk("outundersize = %lld\n",extraout_r1_02,local_70,uStack_6c);
            printk("outoversize = %lld\n",extraout_r1_03,local_68,uStack_64);
            printk("pppoefiltered = %lld\n",extraout_r1_04,local_60,uStack_5c);
            printk("statechange = %lld\n",extraout_r1_05,local_58,uStack_54);
            printk("outpause = %lld\n",extraout_r1_06,local_50,uStack_4c);
            printk("dropevents = %lld\n",extraout_r1_07,local_40,uStack_3c);
          }
          else {
            printk("[tmtst]g_port_statistics2 fail, error code %d!\n");
          }
        }
        else {
          iVar3 = strcmp(__s1,"gportstatistics3");
          if (iVar3 == 0) {
            iVar3 = zte_api_sw_port_get_port_statistics3(local_ac & 0xff,&local_90);
            if (iVar3 == 0) {
              printk("in64 = %lld\n",0,local_90,local_8c);
              printk("in65to127 = %lld\n",extraout_r1_30,local_88,uStack_84);
              printk("in128to255 = %lld\n",extraout_r1_31,local_80,uStack_7c);
              printk("in256to511 = %lld\n",extraout_r1_32,local_78,uStack_74);
              printk("in512to1023 = %lld\n",extraout_r1_33,local_70,uStack_6c);
              printk("in1024tomax = %lld\n",extraout_r1_34,local_68,uStack_64);
              printk("out64 = %lld\n",extraout_r1_35,local_60,uStack_5c);
              printk("out65to127 = %lld\n",extraout_r1_36,local_58,uStack_54);
              printk("out128to255 = %lld\n",extraout_r1_37,local_50,uStack_4c);
              printk("out256to511 = %lld\n",extraout_r1_38,local_48,uStack_44);
              printk("out512to1024 = %lld\n",extraout_r1_39,local_40,uStack_3c);
              printk("out1024tomax = %lld\n",extraout_r1_40,local_38,uStack_34);
            }
            else {
              printk("[tmtst]g_port_statistics3 fail, error code %d!\n");
            }
          }
          else {
            iVar3 = strcmp(__s1,"gportstatistics4");
            if (iVar3 == 0) {
              iVar3 = zte_api_sw_port_get_port_statistics4(local_ac & 0xff,&local_90);
              if (iVar3 == 0) {
                printk("outexcession = %lld\n",0,local_90,local_8c);
                printk("outlate = %lld\n",extraout_r1_08,local_88,uStack_84);
                printk("outsingle = %lld\n",extraout_r1_09,local_80,uStack_7c);
                printk("outmultiple = %lld\n",extraout_r1_10,local_78,uStack_74);
                printk("SQE = %lld\n",extraout_r1_11,local_70,uStack_6c);
                printk("outdeferred = %lld\n",extraout_r1_12,local_68,uStack_64);
                printk("outmacerror = %lld\n",extraout_r1_13,local_60,uStack_5c);
                printk("outcarrier = %lld\n",extraout_r1_14,local_58,uStack_54);
                printk("inalignment = %lld\n",extraout_r1_15,local_50,uStack_4c);
                printk("inmacerror = %lld\n",extraout_r1_16,local_48,uStack_44);
              }
              else {
                printk("[tmtst]g_port_statistics4 fail, error code %d!\n");
              }
            }
            else {
              iVar3 = strcmp(__s1,"sportingratelimit");
              if (iVar3 == 0) {
                __memzero(&local_98,0x18);
                local_98 = local_ac;
                local_94 = CONCAT31(local_94._1_3_,(undefined1)local_a8);
                local_90 = local_a4;
                local_8c = iVar3;
                iVar3 = tm_port_rate_limit_set(local_ac,local_a8 & 0xff,local_a4,0);
                if (iVar3 == 0) {
                  printk("[tmtst]tm_port_rate_limit_set input: port = %d ena = %d BandWidth = %llu kbps\n"
                         ,local_98,local_94 & 0xff);
                }
                else {
                  printk("[tmtst]tm_port_rate_limit_set fail, error code %d!\n");
                }
              }
              else {
                iVar3 = strcmp(__s1,"gportingratelimit");
                if (iVar3 == 0) {
                  local_98 = local_ac;
                  iVar3 = tm_port_rate_limit_get(local_ac,&local_94,&local_90);
                  if (iVar3 == 0) {
                    printk("[tmtst]tm_port_rate_limit_get input: port = %d\n output: ena = %d BandWidth = %llu kbps\n"
                           ,local_98,local_94 & 0xff);
                  }
                  else {
                    printk("[tmtst]tm_port_rate_limit_get fail, error code %d!\n");
                  }
                }
                else {
                  iVar3 = strcmp(__s1,"sportcastratelimit");
                  uVar1 = local_ac;
                  if (iVar3 == 0) {
                    uVar5 = local_a8 & 0xff;
                    iVar3 = tm_port_cast_rate_limit_set(local_ac,uVar5,local_a4,0,local_a0);
                    if (iVar3 == 0) {
                      printk("[tmtst]tm_port_cast_rate_limit_set input: port = %d ena = %d BandWidth = %d kbps,type = %d\n"
                             ,uVar1,uVar5);
                    }
                    else {
                      printk("[tmtst]tm_port_cast_rate_limit_set fail, error code %d!\n");
                    }
                  }
                  else {
                    iVar3 = strcmp(__s1,"gportcastratelimit");
                    if (iVar3 == 0) {
                      local_98 = local_ac;
                      local_88 = local_a8;
                      iVar3 = tm_port_cast_rate_limit_get(local_ac,&local_94,&local_90,local_a8);
                      if (iVar3 == 0) {
                        printk("[tmtst]tm_port_cast_rate_limit_get input: port = %d\n output: ena = %d BandWidth = %d kbps,type = %d\n"
                               ,local_98,local_94 & 0xff,local_88,local_90,local_8c,local_88);
                      }
                      else {
                        printk("[tmtst]tm_port_cast_rate_limit_get fail, error code %d!\n");
                      }
                    }
                    else {
                      iVar3 = strcmp(__s1,"sportegrssch");
                      uVar2 = local_a0;
                      uVar5 = local_a8;
                      uVar1 = local_ac;
                      if (iVar3 == 0) {
                        uVar4 = local_a4 & 0xff;
                        iVar3 = tm_port_egress_spdwrr_schedule_set(local_ac,local_a8,uVar4,local_a0)
                        ;
                        if (iVar3 == 0) {
                          printk("[tmtst]tm_port_egress_spdwrr_schedule_set input: port = %d, queue = %d, SchMod = %d, WrrWeight = %d\n"
                                 ,uVar1,uVar5,uVar4,uVar2);
                        }
                        else {
                          printk("[tmtst]tm_port_egress_spdwrr_schedule_set fail, error code %d!\n")
                          ;
                        }
                      }
                      else {
                        iVar3 = strcmp(__s1,"gportegrssch");
                        if (iVar3 == 0) {
                          local_98 = local_ac;
                          local_94 = local_a8;
                          iVar3 = tm_port_egress_spdwrr_schedule_get
                                            (local_ac,local_a8,&local_90,&local_8c);
                          if (iVar3 == 0) {
                            printk("[tmtst]tm_port_egress_spdwrr_schedule_get input: port = %d, queu = %d\n"
                                   ,local_98,local_94);
                            printk("[tmtst]tm_port_egress_spdwrr_schedule_get output: SchMod = %d, WrrWeight = %d\n"
                                   ,local_90 & 0xff,local_8c);
                          }
                          else {
                            printk(
                                  "[tmtst]tm_port_egress_spdwrr_schedule_get fail, error code %d!\n"
                                  );
                          }
                        }
                        else {
                          iVar3 = strcmp(__s1,"sportegrstfsharp");
                          uVar5 = local_a4;
                          uVar1 = local_ac;
                          if (iVar3 == 0) {
                            uVar4 = local_a8 & 0xff;
                            iVar3 = tm_port_egress_traffic_sharp_set(local_ac,uVar4,local_a4);
                            if (iVar3 == 0) {
                              printk("[tmtst]tm_port_egress_traffic_sharp_set input: port = %d, shp_ena = %d, BandWidth = %d\n"
                                     ,uVar1,uVar4,uVar5);
                            }
                            else {
                              printk(
                                    "[tmtst]tm_port_egress_traffic_sharp_set fail, error code %d!\n"
                                    );
                            }
                          }
                          else {
                            iVar3 = strcmp(__s1,"gportegrstfsharp");
                            if (iVar3 == 0) {
                              local_98 = local_ac;
                              iVar3 = tm_port_egress_traffic_sharp_get(local_ac,&local_94,&local_90)
                              ;
                              if (iVar3 == 0) {
                                printk("[tmtst]tm_port_egress_traffic_sharp_get input: port = %d\n output: shp_ena = %d, BandWidth = %d\n"
                                       ,local_98,local_94 & 0xff,local_90);
                              }
                              else {
                                printk(
                                      "[tmtst]tm_port_egress_traffic_sharp_get fail, error code %d!\n"
                                      );
                              }
                            }
                            else {
                              iVar3 = strcmp(__s1,"spqshprate");
                              uVar4 = local_a4;
                              uVar5 = local_a8;
                              uVar1 = local_ac;
                              if (iVar3 == 0) {
                                iVar3 = tm_tcont_que_sharp_set(local_ac,local_a8,local_a4);
                                if (iVar3 == 0) {
                                  printk("[tmtst]tm_tcont_que_sharp_set input: tcont = %d, queue = %d, shp_bw = %d kbps\n"
                                         ,uVar1,uVar5,uVar4);
                                  return param_4;
                                }
                              }
                              else {
                                iVar3 = strcmp(__s1,"stcontshprate");
                                uVar5 = local_a8;
                                uVar1 = local_ac;
                                if (iVar3 != 0) {
                                  iVar3 = strcmp(__s1,"spqweight");
                                  uVar4 = local_a4;
                                  uVar5 = local_a8;
                                  uVar1 = local_ac;
                                  if (iVar3 == 0) {
                                    iVar3 = tm_tcont_que_sch_weight_set(local_ac,local_a8,local_a4);
                                    if (iVar3 != 0) {
                                      printk(
                                            "[tmtst]tm_tcont_que_sch_weight_set fail, error code %d!\n"
                                            );
                                      return param_4;
                                    }
                                    printk("[tmtst]tm_tcont_que_sch_weight_set input: tcont = %d, queue = %d, que_weight = %d\n"
                                           ,uVar1,uVar5,uVar4);
                                    return param_4;
                                  }
                                  iVar3 = strcmp(__s1,"spqdwrr");
                                  uVar5 = local_a8;
                                  uVar1 = local_ac;
                                  if (iVar3 != 0) {
                                    return param_4;
                                  }
                                  uVar4 = local_a4 & 0xff;
                                  iVar3 = tm_tcont_que_sch_sp_dwwr_mod_set(local_ac,local_a8,uVar4);
                                  if (iVar3 != 0) {
                                    printk(
                                          "[tmtst]tm_tcont_que_sch_sp_dwwr_mod_set fail, error code %d!\n"
                                          );
                                    return param_4;
                                  }
                                  printk("[tmtst]tm_tcont_que_sch_sp_dwwr_mod_set input: tcont = %d, queue = %d, sch_mode = %d\n"
                                         ,uVar1,uVar5,uVar4);
                                  return param_4;
                                }
                                iVar3 = tm_tcont_sharp_set(local_ac,local_a8);
                                if (iVar3 == 0) {
                                  printk("[tmtst]tm_tcont_que_sharp_set input: tcont = %d, shp_bw = %d kbps\n"
                                         ,uVar1,uVar5);
                                  return param_4;
                                }
                              }
                              printk("[tmtst]tm_tcont_que_sharp_set fail, error code %d!\n");
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return param_4;
}

