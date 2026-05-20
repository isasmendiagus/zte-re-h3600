// module: mt7915.ko
// function: set_ser @ 0xbc6e4
// size: 1384 bytes
//

undefined4 set_ser(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    uVar1 = os_str_toul(param_2,0,10,param_4,param_4);
    if (uVar1 == 0xcf) {
      CmdExtSER(param_1,2,0x7f,0);
      return 1;
    }
    if (uVar1 < 0xd0) {
      if (uVar1 == 0xca) {
        CmdExtSER(param_1,2,5,0);
        return 1;
      }
      if (uVar1 < 0xcb) {
        uVar2 = 1;
        if (uVar1 == 1) {
LAB_000bc860:
          CmdExtSER(param_1,uVar2,uVar2,0);
          return 1;
        }
        if (uVar1 == 0) {
          CmdExtSER(param_1,1,0,0);
          return 1;
        }
        if (uVar1 == 200) {
          CmdExtSER(param_1,2,1,0);
          return 1;
        }
        if (uVar1 == 0xc9) {
          CmdExtSER(param_1,2,3,0);
          return 1;
        }
      }
      else {
        if (uVar1 == 0xcc) {
          CmdExtSER(param_1,2,0x11,0);
          return 1;
        }
        if (uVar1 < 0xcc) {
          CmdExtSER(param_1,2,9,0);
          return 1;
        }
        if (uVar1 == 0xcd) {
          CmdExtSER(param_1,2,0x21,0);
          return 1;
        }
        if (uVar1 == 0xce) {
          CmdExtSER(param_1,2,0x41,0);
          return 1;
        }
      }
    }
    else {
      if (uVar1 == 0x130) {
        CmdExtSER(param_1,3,4,0);
        return 1;
      }
      if (uVar1 < 0x131) {
        if (uVar1 == 0x12d) {
          CmdExtSER(param_1,3,2,1);
          return 1;
        }
        if (uVar1 < 0x12e) {
          if (uVar1 == 300) {
            CmdExtSER(param_1,3,2,0);
            return 1;
          }
        }
        else {
          if (uVar1 == 0x12e) {
            uVar2 = 3;
            goto LAB_000bc860;
          }
          if (uVar1 == 0x12f) {
            CmdExtSER(param_1,3,3,1);
            return 1;
          }
        }
      }
      else {
        if (uVar1 == 0x133) {
          CmdExtSER(param_1,3,5,1);
          return 1;
        }
        if (uVar1 < 0x134) {
          if (uVar1 == 0x131) {
            CmdExtSER(param_1,3,4,1);
            return 1;
          }
          if (uVar1 == 0x132) {
            CmdExtSER(param_1,3,5,0);
            return 1;
          }
        }
        else {
          if (uVar1 == 0x134) {
            CmdExtSER(param_1,3,6,0);
            return 1;
          }
          if (uVar1 == 0x3e3) {
            CmdExtSER(param_1,3,1,0);
            return 1;
          }
        }
      }
    }
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("iwpriv rax set ser=[command ID]\n");
  if (DebugLevel < 1) {
LAB_000bca2c:
    if (0 < DebugLevel) {
      printk("%d : Level 2 BN0 recover\n",300);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Level 2 BN1 recover\n",0x12d);
      goto LAB_000bca6c;
    }
LAB_000bcaac:
    if (0 < DebugLevel) {
      printk("%d : Level 3 BN0 tx abort\n",0x130);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Level 3 BN1 tx abort\n",0x131);
      goto LAB_000bcaec;
    }
LAB_000bcb2c:
    if (0 < DebugLevel) {
      printk("%d : Level 3 BF recover\n",0x134);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : HW ERROR Tracking only, no recover\n",200);
      goto LAB_000bcb6c;
    }
LAB_000bcbac:
    if (DebugLevel < 1) goto LAB_000bcc2c;
    printk("%d : Set L3 rx abort only\n",0xcb);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%d : Set L3 tx abort only\n",0xcc);
  }
  else {
    printk("[command ID]\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%d : Disable SER\n",0);
    if (0 < DebugLevel) {
      printk("%d : Enable SER\n",1);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Level 1 recover\n",0x3e3);
      goto LAB_000bca2c;
    }
LAB_000bca6c:
    if (0 < DebugLevel) {
      printk("%d : Level 3 BN0 rx abort\n",0x12e);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Level 3 BN1 rx abort\n",0x12f);
      goto LAB_000bcaac;
    }
LAB_000bcaec:
    if (0 < DebugLevel) {
      printk("%d : Level 3 BN0 tx disable\n",0x132);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Level 3 BN1 tx disable\n",0x133);
      goto LAB_000bcb2c;
    }
LAB_000bcb6c:
    if (0 < DebugLevel) {
      printk("%d : Set L1 recover only\n",0xc9);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("%d : Set L2 recover only\n",0xca);
      goto LAB_000bcbac;
    }
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%d : Set L3 tx disable only\n",0xcd);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%d : Set L3 BF recover only\n",0xce);
LAB_000bcc2c:
  if (0 < DebugLevel) {
    printk("%d : Set All recover enable\n",0xcf);
  }
  return 1;
}

