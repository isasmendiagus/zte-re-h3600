// module: mt7915.ko
// function: mt_wtbltlv_debug @ 0x198d94
// size: 1828 bytes
//

void mt_wtbltlv_debug(undefined4 param_1,undefined4 param_2,int param_3,int param_4,
                     undefined1 *param_5)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 local_26;
  undefined2 local_22;
  
  uVar1 = (undefined1)param_4;
  if (param_3 == 0) {
    *param_5 = 0;
    param_5[1] = 0;
    param_5[3] = 0;
    param_5[2] = 0x14;
    if (param_4 == 0) {
      local_26 = 0;
      local_22 = 0;
      os_move_mem(param_5 + 4,&local_26,6);
      param_5[10] = 0;
      param_5[0xb] = 0;
      param_5[0xc] = 0;
      param_5[0xd] = 0;
      param_5[0xe] = 0;
      param_5[0xf] = 0;
      param_5[0x10] = 0;
      param_5[0x11] = 0;
      param_5[0x12] = 0;
      CmdExtWtblUpdate(param_1,param_2,2,param_5,0x14);
      return;
    }
    if (param_4 == 1) {
      local_26 = 0xffffffff;
      local_22 = 0xffff;
      os_move_mem(param_5 + 4,&local_26,6);
      param_5[0xb] = 1;
      param_5[0xc] = 1;
      param_5[0xd] = 1;
      param_5[0xe] = 1;
      param_5[0xf] = 1;
      param_5[0x11] = 0;
      param_5[0x12] = 1;
      param_5[10] = 0xe;
      param_5[0x10] = 0x20;
      CmdExtWtblUpdate(param_1,param_2,2,param_5,0x14);
      return;
    }
    if (param_4 == 2) {
      CmdExtWtblUpdate(param_1,param_2,3,param_5,0x14);
      return;
    }
    goto LAB_00198de0;
  }
  if (param_3 == 1) {
    uVar2 = 0xc;
    *param_5 = 1;
    param_5[1] = 0;
    param_5[3] = 0;
    param_5[2] = 0xc;
    if ((param_4 == 0) || (param_4 == 1)) {
LAB_00198e2c:
      param_5[4] = uVar1;
      param_5[5] = uVar1;
      param_5[6] = uVar1;
      param_5[7] = uVar1;
      CmdExtWtblUpdate(param_1,param_2,2,param_5,uVar2);
      return;
    }
  }
  else if (param_3 == 2) {
    uVar2 = 8;
    *param_5 = 2;
    param_5[1] = 0;
    param_5[3] = 0;
    param_5[2] = 8;
    if ((param_4 == 0) || (param_4 == 1)) {
      param_5[4] = uVar1;
      param_5[5] = uVar1;
      param_5[6] = uVar1;
      param_5[7] = uVar1;
      CmdExtWtblUpdate();
      return;
    }
  }
  else {
    if (param_3 == 3) {
      uVar2 = 8;
      *param_5 = 3;
      param_5[1] = 0;
      param_5[3] = 0;
      param_5[2] = 8;
      if ((param_4 == 0) || (param_4 == 1)) goto LAB_00198e2c;
      if (param_4 == 2) {
        CmdExtWtblUpdate();
        return;
      }
      goto LAB_00198de0;
    }
    if (param_3 != 4) {
      if (param_3 == 5) {
        *param_5 = 5;
        param_5[1] = 0;
        param_5[3] = 0;
        param_5[2] = 8;
        if ((param_4 == 0) || (param_4 == 1)) {
          param_5[4] = uVar1;
          CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
          return;
        }
        if (param_4 == 2) {
          CmdExtWtblUpdate(param_1,param_2,3,param_5,8);
          return;
        }
      }
      else {
        if (param_3 == 6) {
          *param_5 = 6;
          param_5[1] = 0;
          param_5[3] = 0;
          param_5[2] = 8;
          if ((param_4 == 0) || (param_4 == 1)) {
            param_5[4] = uVar1;
            param_5[5] = uVar1;
            param_5[6] = uVar1;
            CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
            return;
          }
        }
        else if (param_3 == 9) {
          *param_5 = 9;
          param_5[1] = 0;
          param_5[3] = 0;
          param_5[2] = 8;
          if (param_4 == 0) goto LAB_0019903c;
          if (param_4 == 1) {
            param_5[4] = 1;
            param_5[5] = 1;
LAB_00199138:
            CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
            return;
          }
        }
        else {
          if (param_3 != 10) {
            if (param_3 == 0xb) {
              *param_5 = 0xb;
              param_5[1] = 0;
              param_5[3] = 0;
              param_5[2] = 8;
              if (param_4 == 0) {
                return;
              }
              if (param_4 == 1) {
                param_5[4] = 0x3e;
                CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
                return;
              }
              if (param_4 == 2) {
                return;
              }
            }
            else if (param_3 == 0xc) {
              *param_5 = 0xc;
              param_5[2] = 0xc;
              param_5[1] = 0;
              param_5[3] = 0;
              if ((param_4 == 0) || (param_4 == 1)) {
                param_5[4] = uVar1;
                param_5[5] = uVar1;
                param_5[6] = uVar1;
                param_5[7] = uVar1;
                param_5[8] = uVar1;
                CmdExtWtblUpdate(param_1,param_2,2,param_5,0xc);
                return;
              }
              if (param_4 == 2) {
                uVar2 = 0xc;
LAB_00199268:
                CmdExtWtblUpdate(param_1,param_2,3,param_5,uVar2);
                return;
              }
            }
            else if (param_3 == 0xd) {
              *param_5 = 0xd;
              param_5[1] = 0;
              param_5[3] = 0;
              param_5[2] = 8;
              if ((param_4 == 0) || (param_4 == 1)) {
                param_5[4] = uVar1;
                CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
                return;
              }
              if (param_4 == 2) {
                uVar2 = 8;
                goto LAB_00199268;
              }
            }
            else {
              if (param_3 != 0xe) {
                if (param_3 != 0xf) {
                  return;
                }
                *param_5 = 0xf;
                param_5[1] = 0;
                param_5[3] = 0;
                param_5[2] = 0xc;
                if (param_4 == 0) {
                  return;
                }
                if (param_4 == 1) {
                  os_fill_mem(param_5 + 4,6,0xf);
                  CmdExtWtblUpdate(param_1,param_2,2,param_5,0xc);
                  return;
                }
                if (param_4 != 2) {
                  return;
                }
                CmdExtWtblUpdate(param_1,param_2,3,param_5,0xc);
                hex_dump("WTBL_PN",param_5 + 4,6);
                return;
              }
              *param_5 = 0xe;
              param_5[1] = 0;
              param_5[3] = 0;
              param_5[2] = 0x10;
              if (param_4 == 0) {
                param_5[5] = 0;
                param_5[9] = 0;
                param_5[0xd] = 0;
                param_5[4] = 1;
                param_5[8] = 0xff;
                param_5[10] = 0xff;
                param_5[0xb] = 0xff;
                param_5[0xc] = 0x78;
                param_5[0xe] = 0x34;
                param_5[0xf] = 0x12;
                CmdExtWtblUpdate(param_1,param_2,2,param_5,0x10);
                return;
              }
              if (param_4 == 1) {
                param_5[4] = 1;
                param_5[5] = 0;
                param_5[9] = 0;
                param_5[8] = 0xff;
                param_5[10] = 0xff;
                param_5[0xb] = 0xff;
                param_5[0xd] = 0x56;
                param_5[0xc] = 0x78;
                param_5[0xe] = 0x34;
                param_5[0xf] = 0x12;
                CmdExtWtblUpdate(param_1,param_2,2,param_5,0x10);
                return;
              }
              if (param_4 == 2) {
                param_5[4] = 1;
                CmdExtWtblUpdate(param_1,param_2,3,param_5,0x10);
                if (DebugLevel < 1) {
                  return;
                }
                printk("%s::rWtblRawDataRw.u4DwValue(%x)\n","mt_wtbltlv_debug",
                       *(undefined4 *)(param_5 + 0xc));
                return;
              }
            }
            goto LAB_00198de0;
          }
          *param_5 = 10;
          param_5[1] = 0;
          param_5[3] = 0;
          param_5[2] = 8;
          if ((param_4 == 0) || (param_4 == 1)) {
            param_5[4] = uVar1;
            goto LAB_00199138;
          }
        }
        if (param_4 == 2) {
          CmdExtWtblUpdate(param_1,param_2,3,param_5,8);
          return;
        }
      }
      goto LAB_00198de0;
    }
    uVar2 = 8;
    *param_5 = 4;
    param_5[1] = 0;
    param_5[3] = 0;
    param_5[2] = 8;
    if ((param_4 == 0) || (param_4 == 1)) {
LAB_0019903c:
      param_5[4] = uVar1;
      param_5[5] = uVar1;
      CmdExtWtblUpdate(param_1,param_2,2,param_5,8);
      return;
    }
  }
  if (param_4 == 2) {
    CmdExtWtblUpdate(param_1,param_2,3,param_5,uVar2);
    return;
  }
LAB_00198de0:
  if (0 < DebugLevel) {
    printk("%s::Cmd Error\n","mt_wtbltlv_debug");
  }
  return;
}

