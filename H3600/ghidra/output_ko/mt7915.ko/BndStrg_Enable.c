// module: mt7915.ko
// function: BndStrg_Enable @ 0x9cebc
// size: 376 bytes
//

undefined4 BndStrg_Enable(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined1 local_50 [3];
  undefined1 local_4d;
  
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 4;
  }
  else {
    if (*(char *)(param_1 + 1) != '\0') {
      if (*(byte *)((int)param_1 + 5) == param_2) {
        if (0 < DebugLevel) {
          pcVar2 = "disabled";
          if (*(byte *)((int)param_1 + 5) != 0) {
            pcVar2 = "enabled";
          }
          printk(&_LC52,"BndStrg_Enable",pcVar2);
          return 0;
        }
      }
      else {
        if (param_2 == 0) {
          *(undefined1 *)((int)param_1 + 5) = 0;
          BndStrg_SetInfFlags(param_1[0x407],param_1,0);
          local_4d = *(undefined1 *)((int)param_1 + 5);
          local_50[0] = 0xb;
          RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
        }
        else {
          *(undefined1 *)((int)param_1 + 5) = 1;
          BndStrg_SetInfFlags(param_1[0x407],param_1,1);
          local_4d = *(undefined1 *)((int)param_1 + 5);
          local_50[0] = 0xb;
          RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
        }
        if (0 < DebugLevel) {
          printk(&_LC53,"BndStrg_Enable");
        }
      }
      return 0;
    }
    uVar1 = 5;
  }
  return uVar1;
}

