// module: mt7915.ko
// function: set_mumimo_fixed_group_rate @ 0x179864
// size: 2212 bytes
//

undefined4 set_mumimo_fixed_group_rate(undefined4 param_1,char *param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  char *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  byte local_36;
  undefined1 uStack_35;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  byte local_2c;
  byte bStack_2b;
  byte local_2a;
  byte bStack_29;
  undefined2 local_28;
  undefined1 local_26;
  char cStack_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_36 = 0;
  uStack_35 = 0;
  local_34 = 0;
  local_32 = 0;
  local_30 = 0;
  local_2e = 0;
  local_2c = 0;
  bStack_2b = 0;
  local_2a = 0;
  bStack_29 = 0;
  local_28 = 0;
  local_26 = 0;
  cStack_25 = '\0';
  local_40 = 0x11;
  local_3c = 0xb;
  local_44 = param_2;
  pcVar6 = strsep(&local_44,"-");
  if (pcVar6 != (char *)0x0) {
    cVar2 = os_str_tol(pcVar6,0,10);
    local_36 = local_36 & 0xfc | cVar2 - 1U & 3;
    pcVar6 = strsep(&local_44,"-");
    if (pcVar6 != (char *)0x0) {
      uVar3 = os_str_tol(pcVar6,0,10);
      local_28 = CONCAT11(local_28._1_1_,uVar3);
      pcVar6 = strsep(&local_44,"-");
      if (pcVar6 != (char *)0x0) {
        local_26 = os_str_tol(pcVar6,0,10);
        pcVar6 = strsep(&local_44,"-");
        if (pcVar6 != (char *)0x0) {
          uVar3 = os_str_tol(pcVar6,0,10);
          local_28 = CONCAT11(uVar3,(undefined1)local_28);
          pcVar6 = strsep(&local_44,"-");
          if (pcVar6 != (char *)0x0) {
            cStack_25 = os_str_tol(pcVar6,0,10);
            bVar4 = local_36 & 3;
            if ((local_36 & 3) == 0) {
              pcVar6 = strsep(&local_44,"-");
              if (pcVar6 != (char *)0x0) {
                local_34 = os_str_tol(pcVar6,bVar4,10);
                pcVar6 = strsep(&local_44,"-");
                if (pcVar6 != (char *)0x0) {
                  bVar4 = os_str_tol(pcVar6,bVar4,10);
                  bVar1 = 0xb < bVar4;
                  local_36 = local_36 & 0xef | bVar1 << 4;
                  if (cStack_25 == '\x01') {
                    if (bVar1) {
                      bVar4 = bVar4 - 0xb;
                    }
                    local_2a = local_2a & 0xf0 | bVar4 & 0xf;
                  }
                  else {
                    if (bVar1) {
                      bVar4 = bVar4 - 0xb;
                    }
                    local_2c = local_2c & 0xf0 | bVar4 & 0xf;
                    if (cStack_25 == '\x02') {
                      pcVar6 = strsep(&local_44,"");
                      if (pcVar6 == (char *)0x0) goto LAB_00179d38;
                      bVar4 = os_str_tol(pcVar6,0,10);
                      local_36 = local_36 & 0xef | (0xb < bVar4) << 4;
                      if (0xb < bVar4) {
                        bVar4 = bVar4 - 0xb;
                      }
                      local_2a = local_2a & 0xf0 | bVar4 & 0xf;
                    }
                  }
                  goto LAB_001799a0;
                }
              }
            }
            else {
LAB_001799a0:
              if ((local_36 & 3) == 0) goto LAB_001799a8;
              pcVar6 = strsep(&local_44,"-");
              if (pcVar6 != (char *)0x0) {
                local_34 = os_str_tol(pcVar6,0,10);
                pcVar6 = strsep(&local_44,"-");
                if (pcVar6 != (char *)0x0) {
                  bVar4 = os_str_tol(pcVar6,0,10);
                  bVar1 = 0xb < bVar4;
                  local_36 = local_36 & 0xef | bVar1 << 4;
                  if (cStack_25 == '\x01') {
                    if (bVar1) {
                      bVar4 = bVar4 - 0xb;
                    }
                    local_2a = local_2a & 0xf0 | bVar4 & 0xf;
                  }
                  else {
                    if (bVar1) {
                      bVar4 = bVar4 - 0xb;
                    }
                    local_2c = local_2c & 0xf0 | bVar4 & 0xf;
                  }
                  pcVar6 = strsep(&local_44,"-");
                  if (cStack_25 == '\x02') {
                    if (pcVar6 == (char *)0x0) goto LAB_00179d38;
                    bVar4 = os_str_tol(pcVar6,0,10);
                    local_36 = local_36 & 0xef | (0xb < bVar4) << 4;
                    if (0xb < bVar4) {
                      bVar4 = bVar4 - 0xb;
                    }
                    local_2a = local_2a & 0xf0 | bVar4 & 0xf;
                    pcVar6 = strsep(&local_44,"-");
                  }
                  if (pcVar6 != (char *)0x0) {
                    local_32 = os_str_tol(pcVar6,0,10);
                    if (((local_36 & 3) == 1) && (cStack_25 != '\x02')) {
                      pcVar6 = strsep(&local_44,"");
                    }
                    else {
                      pcVar6 = strsep(&local_44,"-");
                    }
                    if (pcVar6 != (char *)0x0) {
                      uVar8 = os_str_tol(pcVar6,0,10);
                      uVar8 = uVar8 & 0xff;
                      bVar1 = 0xb < uVar8;
                      bVar4 = local_36 & 0xdf | bVar1 << 5;
                      if (cStack_25 == '\x01') {
joined_r0x00179fa0:
                        if (bVar1) {
                          uVar8 = uVar8 - 0xb;
                        }
                        local_2a = local_2a & 0xf | (byte)((uVar8 & 0xf) << 4);
                        local_36 = bVar4;
                      }
                      else {
                        if (bVar1) {
                          uVar8 = uVar8 - 0xb;
                        }
                        local_2c = local_2c & 0xf | (byte)((uVar8 & 0xf) << 4);
                        if ((local_36 & 3) == 1) {
                          local_36 = bVar4;
                          if (cStack_25 == '\x02') {
                            pcVar6 = strsep(&local_44,"");
                            goto LAB_00179f84;
                          }
                        }
                        else {
                          local_36 = bVar4;
                          if (cStack_25 == '\x02') {
                            pcVar6 = strsep(&local_44,"-");
LAB_00179f84:
                            if (cStack_25 == '\x02') {
                              if (pcVar6 != (char *)0x0) {
                                uVar8 = os_str_tol(pcVar6,0,10);
                                uVar8 = uVar8 & 0xff;
                                bVar1 = 0xb < uVar8;
                                bVar4 = local_36 & 0xdf | bVar1 << 5;
                                goto joined_r0x00179fa0;
                              }
                            }
                            else if (pcVar6 != (char *)0x0) goto LAB_00179b94;
                            goto LAB_00179d38;
                          }
                        }
                      }
LAB_00179b94:
                      bVar4 = local_36 & 3;
                      if (bVar4 < 2) {
LAB_00179c64:
                        if (bVar4 != 3) goto LAB_001799a8;
                        pcVar6 = strsep(&local_44,"-");
                        if (pcVar6 != (char *)0x0) {
                          local_2e = os_str_tol(pcVar6,0,10);
                          if (cStack_25 == '\x02') {
                            pcVar6 = "-";
                          }
                          else {
                            pcVar6 = "";
                          }
                          pcVar6 = strsep(&local_44,pcVar6);
                          if (pcVar6 != (char *)0x0) {
                            uVar8 = os_str_tol(pcVar6,0,10);
                            uVar8 = uVar8 & 0xff;
                            bVar1 = 0xb < uVar8;
                            local_36 = local_36 & 0x7f | bVar1 << 7;
                            if (cStack_25 == '\x01') {
joined_r0x0017a054:
                              if (bVar1) {
                                uVar8 = uVar8 - 0xb;
                              }
                              bStack_29 = bStack_29 & 0xf | (byte)((uVar8 & 0xf) << 4);
                            }
                            else {
                              if (bVar1) {
                                uVar8 = uVar8 - 0xb;
                              }
                              bStack_2b = bStack_2b & 0xf | (byte)((uVar8 & 0xf) << 4);
                              if (cStack_25 == '\x02') {
                                pcVar6 = strsep(&local_44,"");
                                if (cStack_25 == '\x02') {
                                  if (pcVar6 != (char *)0x0) {
                                    uVar8 = os_str_tol(pcVar6,0,10);
                                    uVar8 = uVar8 & 0xff;
                                    bVar1 = 0xb < uVar8;
                                    local_36 = local_36 & 0x7f | bVar1 << 7;
                                    goto joined_r0x0017a054;
                                  }
                                }
                                else if (pcVar6 != (char *)0x0) goto LAB_001799a8;
                                goto LAB_00179d38;
                              }
                            }
LAB_001799a8:
                            iVar7 = AndesAllocCmdMsg(param_1,0x1a);
                            if (iVar7 != 0) {
                              local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
                              local_20 = CONCAT31(local_20._1_3_,10);
                              uVar9 = 1;
                              AndesInitCmdMsg(iVar7,local_24,local_20,local_1c,local_18,local_14);
                              AndesAppendCmdMsg(iVar7,&local_40,4);
                              AndesAppendCmdMsg(iVar7,&local_3c,4);
                              AndesAppendCmdMsg(iVar7,&local_36,0x12);
                              AndesSendCmdMsg(param_1,iVar7);
                              goto LAB_00179d3c;
                            }
                          }
                        }
                      }
                      else {
                        pcVar6 = strsep(&local_44,"-");
                        if (pcVar6 != (char *)0x0) {
                          local_30 = os_str_tol(pcVar6,0,10);
                          if (((local_36 & 3) == 2) && (cStack_25 != '\x02')) {
                            pcVar6 = strsep(&local_44,"");
                          }
                          else {
                            pcVar6 = strsep(&local_44,"-");
                          }
                          if (pcVar6 != (char *)0x0) {
                            bVar5 = os_str_tol(pcVar6,0,10);
                            bVar1 = 0xb < bVar5;
                            bVar4 = local_36 & 0xbf | bVar1 << 6;
                            if (cStack_25 == '\x01') {
                              if (bVar1) {
                                bVar5 = bVar5 - 0xb;
                              }
                              bStack_29 = bStack_29 & 0xf0 | bVar5 & 0xf;
                              local_36 = bVar4;
                            }
                            else {
                              if (bVar1) {
                                bVar5 = bVar5 - 0xb;
                              }
                              bStack_2b = bStack_2b & 0xf0 | bVar5 & 0xf;
                              if ((local_36 & 3) == 2) {
                                local_36 = bVar4;
                                if (cStack_25 == '\x02') {
                                  pcVar6 = strsep(&local_44,"");
                                  goto LAB_00179edc;
                                }
                              }
                              else {
                                local_36 = bVar4;
                                if (cStack_25 == '\x02') {
                                  pcVar6 = strsep(&local_44,"-");
LAB_00179edc:
                                  if (cStack_25 == '\x02') {
                                    if (pcVar6 != (char *)0x0) {
                                      bVar4 = os_str_tol(pcVar6,0,10);
                                      bVar1 = 0xb < bVar4;
                                      if (bVar1) {
                                        bVar4 = bVar4 - 0xb;
                                      }
                                      bStack_29 = bStack_29 & 0xf0 | bVar4 & 0xf;
                                      bVar4 = local_36 & 3;
                                      local_36 = local_36 & 0xbf | bVar1 << 6;
                                      goto LAB_00179c64;
                                    }
                                  }
                                  else if (pcVar6 != (char *)0x0) goto LAB_00179c60;
                                  goto LAB_00179d38;
                                }
                              }
                            }
LAB_00179c60:
                            bVar4 = local_36 & 3;
                            goto LAB_00179c64;
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
LAB_00179d38:
  uVar9 = 0;
LAB_00179d3c:
  if (-1 < DebugLevel) {
    printk("%s:(Ret = %d_\n","set_mumimo_fixed_group_rate",uVar9);
  }
  return uVar9;
}

