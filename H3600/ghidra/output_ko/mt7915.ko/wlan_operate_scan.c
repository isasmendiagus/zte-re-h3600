// module: mt7915.ko
// function: wlan_operate_scan @ 0x107740
// size: 128 bytes
//

void wlan_operate_scan(int param_1,undefined1 param_2)

{
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  
  os_zero_mem(&local_1b,0xb);
  if ((*(ushort *)(param_1 + 0x18) & 0x100) == 0) {
    local_1b = (*(ushort *)(param_1 + 0x18) & 0xb1) != 0;
  }
  else {
    local_1b = 2;
  }
  local_18 = 0;
  local_17 = 0;
  local_1a = 0;
  local_14 = 0;
  local_19 = 0;
  local_16 = param_2;
  local_15 = param_2;
  hc_radio_res_request(param_1);
  return;
}

