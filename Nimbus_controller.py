import hid
import time
import serial

nimbus_vendor_id = 0x0111
nimbus_product_id = 0x1420

hid_device = hid.device()

arduino_port = '/dev/cu.usbserial-210'
baud_rate = 115200

button_map = {
    0: "DPAD_UP",
    1: "DPAD_RIGHT",
    2: "DPAD_DOWN",
    3: "DPAD_LEFT",
    4: "A",
    5: "B",
    6: "X",
    7: "Y",
    8: "L1",
    9: "R1",
    10: "L2",
    11: "R2",
    12: "JOYSTICK",
    13: "JOYSTICK_LEFT",
    14: "JOYSTICK_LEFT",
    15: "JOYSTICK_RIGHT",
    16: "JOYSTICK_RIGHT"
}

# Initialize the last known state storage for each button press
button_pressed = 0
last_button_pressed = -1  # Initialize with a value that won't match any button
last_press_time = 0
debounce_time = 0.2  # 200 milliseconds


arduino = serial.Serial(arduino_port, baud_rate, timeout=1)
isJoystickConnected = True;

while True:
    try:
        hid_device.open(nimbus_vendor_id, nimbus_product_id)
        
        isJoystickConnected = True;
        arduino.write(f"T\n".encode())

        print("Joystick connected!")
        print("T")

        while True:
            # Read the current state
            current_state = hid_device.read(64)

            # Skip all lines of data that are empty
            all_zeros = True
            for i in range(len(current_state)):
                if current_state[i] != 0:
                    button_pressed = i
                    all_zeros = False
                    break

            if all_zeros:
                continue

            current_time = time.time()

            # Debounce button presses
            if button_pressed == last_button_pressed and (current_time - last_press_time) < debounce_time:
                continue
            else:
                last_button_pressed = button_pressed
                last_press_time = current_time

            print(button_map[button_pressed])

            if( button_pressed <= 7 ):
                # Send to Arduino on Serial, don't encode back buttons and joysticks
                if "DPAD" in button_map[button_pressed]:
                    #simply send L, R, U, D to Arduino
                    arduino.write(f"{button_map[button_pressed][5]}\n".encode())
                else:
                    arduino.write(f"{button_map[button_pressed]}\n".encode())

    except Exception as e:
        hid_device.close()
        
        if isJoystickConnected:
            isJoystickConnected = False;
            
        arduino.write(f"F\n".encode())
        
        print("F")
        print("Joystick not connected. Retrying in 10s...")
        
        time.sleep(10)
