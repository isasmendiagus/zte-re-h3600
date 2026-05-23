// module: tm.ko
// function: greg_info_store @ 0x6e7e4
// size: 676 bytes
//

undefined4 greg_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  char *__s1;
  uint uVar3;
  uint local_28;
  uint local_24;
  uint local_20;
  undefined1 local_1c [8];
  
  __s1 = (char *)*param_2;
  local_28 = 0;
  local_24 = 0;
  iVar2 = capable(0xc);
  if (iVar2 == 0) {
    param_4 = 0xffffffff;
  }
  else {
    sscanf(param_3,"%d %d",&local_28,&local_24);
    iVar2 = strcmp(__s1,"phyLdoTest");
    if (iVar2 == 0) {
      if (0xff < local_28) {
        printk("ldo value>0xff,and will be set 0x1f\n");
        local_28 = 0x1f;
      }
      gephy_ldo_test(local_28);
    }
    else {
      iVar2 = strcmp(__s1,"phyGuardEn");
      if (iVar2 == 0) {
        if (local_28 < 2) {
          if (1 < local_24) {
            printk("print_level > 1,and will be set 1\n");
            local_28 = 1;
          }
        }
        else {
          printk("enable value > 1,and will be set 1\n");
          local_28 = 1;
        }
        g_phy_avoid_button = (undefined1)local_28;
        g_phy_dbg_lvl = (undefined1)local_24;
      }
    }
    disableIRQinterrupts();
    iVar2 = strcmp(__s1,"sportstatus");
    uVar1 = local_28;
    if (iVar2 == 0) {
      uVar3 = local_24 & 0xff;
      iVar2 = tm_port_status_set(local_28,uVar3);
      if (iVar2 == 0) {
        printk("tm_port_status_set input:p_port = %d,p_state = %d\n",uVar1,uVar3);
      }
      else {
        printk("tm_port_status_set fail, error code %d!\n");
      }
    }
    else {
      iVar2 = strcmp(__s1,"gportstatus");
      if (iVar2 == 0) {
        local_20 = local_28;
        iVar2 = tm_port_status_get(local_28,local_1c);
        if (iVar2 == 0) {
          printk("tm_port_status_get input:p_port = %d output:p_state = %d\n",local_20,local_1c[0]);
        }
        else {
          printk("tm_port_status_get fail, error code %d!\n");
        }
      }
      else {
        iVar2 = strcmp(__s1,"sport802xauth");
        uVar1 = local_28;
        if (iVar2 == 0) {
          uVar3 = local_24 & 0xff;
          iVar2 = tm_port_802x_authen_set(local_28,uVar3);
          if (iVar2 == 0) {
            printk("tm_port_802x_authen_set input:p_port = %d,p_state = %d\n",uVar1,uVar3);
          }
          else {
            printk("tm_port_802x_authen_set fail, error code %d!\n");
          }
        }
        else {
          iVar2 = strcmp(__s1,"gport802xauth");
          if (iVar2 == 0) {
            local_20 = local_28;
            iVar2 = tm_port_802x_authen_get(local_28,local_1c);
            if (iVar2 == 0) {
              printk("tm_port_802x_authen_get input:p_port = %d output:p_state = %d\n",local_20,
                     local_1c[0]);
            }
            else {
              printk("tm_port_802x_authen_get fail, error code %d!\n");
            }
          }
        }
      }
    }
  }
  return param_4;
}

