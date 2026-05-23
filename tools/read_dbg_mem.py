#!/usr/bin/env python3
"""After kernel ran TX tests, DTR-reset H3600 + drop to U-Boot prompt
+ read scratch DDR at 0x47000000 to extract TX debug counters."""
import serial, time
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)
# Recover any glitched UART
ser.dtr = False; ser.rts = False; time.sleep(0.3)
ser.dtr = True; ser.rts = True; time.sleep(0.3)
ser.dtr = False; ser.rts = False; time.sleep(0.3)
ser.reset_input_buffer()
print('DTR pulse reset')
ser.dtr = True; time.sleep(2); ser.dtr = False
buf = b''
sent = 0
end = time.time() + 25
while time.time() < end:
    d = ser.read(2000)
    if d: buf += d
    text = buf.decode('latin-1', errors='replace')
    if sent == 0 and 'Press 1' in text:
        ser.write(b'1\r'); ser.flush(); time.sleep(0.5)
        sent = 1
    elif sent == 1 and 'password' in text:
        ser.write(b'Boot4128s!\r'); ser.flush(); time.sleep(1)
        sent = 2
    elif sent == 2 and text.rstrip().endswith('=>'):
        ser.write(b'md.l 0x47000000 16\r'); ser.flush(); time.sleep(2)
        sent = 3
        break
b2 = ser.read(4000)
buf += b2
print(buf.decode('latin-1', errors='replace')[-2000:])
ser.close()
