#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import serial #talks to Arduino over USB
import csv 
import time #for the time.sleep

PORT = "COM4" #this depends on which port the Arduino is connected to. 
BAUD = 9600 #speed of communication must match

ser = serial.Serial(PORT, BAUD, timeout=40) #this function opens the connection. timeout=3 means readline() waits max 3 sec for data before giving up, so the program doesnt freeze
time.sleep(2) #most Arduinos reset when a serial connection opens, this gives it 2 seconds to restart
ser.reset_input_buffer() #throws away leftover data that is caused by partial transmission. 

with open("light.csv", "w", newline="") as light_file, open("time.csv", "w", newline="") as time_file: #this automatically closes whent the block ends
         
        light_writer = csv.writer(light_file) #turn python lists into csv rows
        time_writer = csv.writer(time_file)
        light_writer.writerow(["value", "over_threshold"]) #writes the header row 
        time_writer.writerow(["value"]) #writes the header row

        while True:
            raw = ser.readline() #reads bytes from the arduino up to newline character from println
            line = raw.decode("utf-8", errors="ignore").strip() #converts bytes to text while ignoring errors (Corrupted bytes). strip() removes trailing newline characters/spaces
            if not line: 
                break #stops loop

            parts = line.split(",") #splits a character into an array based on the commas between
            category = parts[0] #first item in the array is the category name eg "time"

            if category == "light" and len(parts) == 3: #this is for light because it has 3 parts
                light_writer.writerow([parts[1], parts[2]])  #writes the value and threshold(0,1) as a row
            elif category == "time" and len(parts) == 2: #this is for time because it has 2 parts
                time_writer.writerow([parts[1]]) #writes the value as a row
            
ser.close()


# In[ ]:




