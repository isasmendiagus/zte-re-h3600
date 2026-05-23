// module: mt7915.ko
// function: mtf_txpower_boost_profile @ 0x1a192c
// size: 6496 bytes
//

void mtf_txpower_boost_profile(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  byte local_36 [2];
  char *local_34;
  char *local_30;
  char *local_2c;
  
  local_34 = (char *)0x0;
  local_36[0] = 0;
  local_36[1] = 0;
  iVar2 = RTMPGetKeyParameter("PowerUpRU26",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794db5) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU26] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU26] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e56) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU26] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (iVar2 < 0xc && local_34 != (char *)0x0);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794db5) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU26] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU52",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dc1) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU52] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU52] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e62) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU52] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dc1) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU52] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU106",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dcd) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU106] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU106] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e6e) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU106] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dcd) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU106] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU242",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dd9) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU242] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU242] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e7a) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU242] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dd9) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU242] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU484",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794de5) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU484] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU484] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e86) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU484] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794de5) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU484] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU996",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794df1) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU996] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e92) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794df1) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
  }
  iVar2 = RTMPGetKeyParameter("PowerUpRU996X2",param_2,0x20,param_3,1);
  if (iVar2 != 0) {
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      local_34 = (char *)rstrtok(param_2,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dfd) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996X2] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
    }
    else {
      local_34 = (char *)rstrtok(param_2,&_LC317);
      if ((local_34 == (char *)0x0) ||
         (local_30 = local_34, local_34 = (char *)rstrtok(0,&_LC317), local_34 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpRU996X2] Input parameter incorrect!!\n");
        }
      }
      else {
        local_2c = local_34;
        rstrtok(0,&_LC317);
      }
      local_34 = local_30;
      local_34 = (char *)rstrtok(local_30,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794e9e) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996X2] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
      }
      local_34 = local_2c;
      local_34 = (char *)rstrtok(local_2c,&_LC319);
      if (local_34 != (char *)0x0) {
        iVar2 = 0;
        do {
          pcVar3 = strsep(&local_34,":");
          if (pcVar3 != (char *)0x0) {
            uVar5 = 0;
            do {
              bVar1 = simple_strtol(pcVar3,0,10);
              local_36[uVar5] = bVar1;
              pcVar3 = strsep(&local_34,":");
              uVar4 = uVar5 ^ 1;
              uVar5 = 1;
              if (pcVar3 == (char *)0x0) {
                uVar4 = 0;
              }
            } while (uVar4 != 0);
          }
          if (local_36[0] < 0xc) {
            *(byte *)(param_1 + (uint)local_36[0] + 0x794dfd) = local_36[1];
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpRU996X2] Input parameter incorrect!!\n");
          }
          iVar2 = iVar2 + 1;
          local_34 = (char *)rstrtok(0,&_LC319);
        } while (local_34 != (char *)0x0 && iVar2 != 0xc);
        return;
      }
    }
  }
  return;
}

