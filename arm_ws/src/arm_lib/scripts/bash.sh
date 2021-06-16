#!/bin/bash
sleep 3 
python ik.py
rostopic pub  /catchrelease arm_gazebo/  catch
rostopic pub  /catchrelease arm_gazebo/   release 

rostopic pub /arm/pos_cmd arm_lib/Angles "{'chassis_arm1':30.0, 'arm1_arm2':40.0, 'arm2_arm3':30.0, 'arm3_arm4':30.0}"

