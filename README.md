# esp32_web_hex_keypad
ESP32 web-based Hexadecimal Keypad

## Introduction
I will be exhibiting my COSMAC homebrew computer at [Maker Faire Tokyo 2020](https://makezine.jp/event/makers-mft2020/m0029/) in October.
  (In japanese)

However, due to COVID-19 protection, I cannot touch the product directly.
So I decided to use ESP32 and a relay module to operate the COSMAC VIP OS remotely.
We dared to use relays because we wanted visitors to feel the sensation of touching the switch.

You can also see it on [my blog](https://kanpapa.com/cosmac/blog/2020/09/cosmac-vip-os-ESP32-remote-keypad.html). (In japanese)

<table class="table table-hover table-striped table-bordered">
  <tr align="center">
   <td><img src="https://github.com/kanpapa/esp32_web_hex_keypad/blob/master/pics/Screenshot_cosmac_vip_os_remote1.png"></td>
   <td><img src="https://github.com/kanpapa/esp32_web_hex_keypad/blob/master/pics/cosmac_vip_auto_vram1.jpg"></td>
  </tr>
  <tr align="center">
    <td>COSMAC VIP Web UI</td>
    <td>Photo of this system</td>
  </tr>
</table>

## Hardware
* Controller: ESP32DEV-C
* Relay Module: [Sainsmart 16-Channel 12V Relay Module](https://www.sainsmart.com/products/16-channel-12v-relay-module) 
* Schematic: [doc/esp32_remote_relay_rev01_sch.pdf](doc/esp32_remote_relay_rev01_sch.pdf)

## Software
ESP32 remote relay controller program for Arduino IDE  
  Kazuhiro Ouchi  @kanpapa  
  [src/esp32_remote_relay_controller/esp32_remote_relay_controller.ino](src/esp32_remote_relay_controller/esp32_remote_relay_controller.ino)
   

Original Source:  
  Rui Santos  
  Complete project details at https://randomnerdtutorials.com  
  How to Set an ESP32 Access Point (AP) for Web Server  
  https://randomnerdtutorials.com/esp32-access-point-ap-web-server/  

License:  
  Creative Commons Attribution-Non Commercial-Share Alike v3.0 license  
  https://creativecommons.org/licenses/by-nc-sa/3.0/  
