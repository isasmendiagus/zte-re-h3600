// module: mt7915.ko
// function: D_MsgHandle @ 0x9d038
// size: 696 bytes
//

void D_MsgHandle(undefined4 param_1,undefined4 *param_2,undefined1 *param_3)

{
  int iVar1;
  int local_5c;
  undefined1 local_58 [5];
  undefined1 local_53;
  undefined1 local_52;
  
  local_5c = 0;
  if (3 < DebugLevel) {
    printk("%s: action code (%d)\n","D_MsgHandle",*param_3);
  }
  if (param_2 != (undefined4 *)0x0) {
    switch(*param_3) {
    case 2:
      local_5c = (**(code **)(param_2[0x406] + 0x14))(param_2,param_3 + 0xc);
      if (local_5c == 0) {
        (**(code **)(param_2[0x406] + 0xc))(param_2,param_3,&local_5c);
      }
      else {
        *(undefined4 *)(local_5c + 4) = *(undefined4 *)(param_3 + 0x38);
        *(undefined1 *)(local_5c + 0xe) = param_3[7];
        *(undefined1 *)(local_5c + 0xf) = param_3[8];
      }
      break;
    case 3:
      (**(code **)(param_2[0x406] + 0x10))(param_2,param_3 + 0xc,0xff);
      break;
    case 4:
      *param_3 = 5;
      param_3[4] = *(undefined1 *)((int)param_2 + 0x106e);
      iVar1 = MacTableLookup(param_1,param_3 + 0xc);
      if (iVar1 == 0) {
        param_3[1] = 0;
        (**(code **)(param_2[0x406] + 0x10))(param_2,param_3 + 0xc,0xff);
      }
      else {
        param_3[1] = 8;
      }
      RtmpOSWrielessEventSend(*param_2,1,0x950,0,param_3,0x40);
      break;
    default:
      if (1 < DebugLevel) {
        printk("%s: unknown action code. (%d)\n","D_MsgHandle");
      }
      break;
    case 6:
      if (((&DAT_0036b920)[param_2[0x407]] != '\0') && (*(char *)(param_2 + 1) == '\x01')) {
        if (*(char *)((int)param_2 + 0x106e) == '\x02') {
          local_53 = *(undefined1 *)(param_2 + 0x408);
          local_58[0] = 7;
        }
        else {
          if (*(char *)((int)param_2 + 0x106e) != '\x01') {
            return;
          }
          local_52 = *(undefined1 *)((int)param_2 + 0x1021);
          local_58[0] = 8;
        }
        RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_58,0x40);
      }
      break;
    case 0xb:
      BndStrg_Enable(param_2,param_3[3]);
      break;
    case 0x13:
      if (((0 < DebugLevel) && (printk("=================================\n"), 0 < DebugLevel)) &&
         (printk(" D_MsgHandle 5G traffic alarm  ..\n"), 0 < DebugLevel)) {
        printk("=================================\n");
      }
      break;
    case 0x1b:
      *(char *)((int)param_2 + 0x108d) = (char)*(undefined4 *)(param_3 + 0x2c);
      break;
    case 0x1d:
      BndStrg_Del_MacTab_byMacAddr(param_1,param_2,param_3 + 0xc);
      break;
    case 0x22:
      iVar1 = (**(code **)(param_2[0x406] + 0x14))(param_2,param_3 + 0xc);
      if (iVar1 != 0) {
        *(undefined1 *)(iVar1 + 0xe) = param_3[7];
        *(undefined1 *)(iVar1 + 0xf) = param_3[8];
      }
    }
  }
  return;
}

