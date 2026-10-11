#!/usr/bin/env python
# coding: utf-8

# In[16]:


import serial #talks to Arduino over USB
import csv 
import time #for the time.sleep

PORT = "COM4" #this depends on which port the Arduino is connected to. 
BAUD = 9600 #speed of communication must match

ser = serial.Serial(PORT, BAUD, timeout=60) #this function opens the connection. timeout=3 means readline() waits max 3 sec for data before giving up, so the program doesnt freeze
time.sleep(2) #most Arduinos reset when a serial connection opens, this gives it 2 seconds to restart
#ser.reset_input_buffer() #throws away leftover data that is caused by partial transmission. 

with open("light.csv", "w", newline="") as light_file, \
     open("time.csv", "w", newline="") as time_file: #this automatically closes whent the block ends
         
        light_writer = csv.writer(light_file) #turn python lists into csv rows
        time_writer = csv.writer(time_file)
        light_writer.writerow(["value", "over_threshold"]) #writes the header row 
        time_writer.writerow(["value"]) #writes the header row

        while True:
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            print("received:", repr(line))      # debug: see raw data
            if line == "" or line == "done":    # stop on silence or "done"
                break

            parts = line.split(",")
            if parts[0] == "light" and len(parts) == 3:
                light_writer.writerow([parts[1], parts[2]])
            elif parts[0] == "time" and len(parts) == 2:
                time_writer.writerow([parts[1]])

ser.close()
print("Finished")


# In[ ]:




