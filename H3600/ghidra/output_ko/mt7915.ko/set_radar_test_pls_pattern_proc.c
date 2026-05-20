// module: mt7915.ko
// function: set_radar_test_pls_pattern_proc @ 0x101b4c
// size: 296 bytes
//

undefined4 set_radar_test_pls_pattern_proc(undefined4 param_1,int param_2)

{
  char *__s;
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined1 local_194 [4];
  undefined1 auStack_190 [384];
  
  memset(local_194,0,0x184);
  if (param_2 == 0) {
    return 1;
  }
  __s = (char *)rstrtok(param_2,&_LC24);
  if (__s == (char *)0x0) {
    local_194[0] = 0;
    uVar3 = 0;
  }
  else {
    puVar2 = auStack_190;
    uVar3 = 0;
    do {
      iVar1 = sscanf(__s,"%u-%hu-%hi",puVar2,puVar2 + 4,puVar2 + 6);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 0xc;
      if (iVar1 != 3) {
        if (DebugLevel < 0) {
          return 1;
        }
        printk(
              "Format Error! Please enter in the following format\nStartTime0-PulseWidth0-PulsePower0;StartTime1-PulseWidth1-PulsePower1;...\n"
              );
        return 1;
      }
      __s = (char *)rstrtok(0,&_LC24);
    } while (uVar3 < 0x20 && __s != (char *)0x0);
    local_194[0] = (undefined1)uVar3;
  }
  if (0 < DebugLevel) {
    printk("%s:No of pulses = %d\n","set_radar_test_pls_pattern_proc",uVar3 & 0xff);
  }
  mt_cmd_set_test_radar_pattern(param_1,local_194);
  return 1;
}

