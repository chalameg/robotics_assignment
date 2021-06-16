#!/usr/bin/env python
from __future__ import print_function
from arm_lib.srv import ik, ikResponse
import rospy

import numpy as np

import tinyik as tik

def handle_ik(req):
    arm = tik.Actuator([
        'z', [0.0, 0., 0.15], 
        'x', [0.0, 0., 2.0],
        'x', [0.0, 0., 1.],
        'x', [0.0, 0., 1.],
        "z", [0, 0, 0.15],
        "x", [0, 0, 0.15]
        ])

    arm.ee = req.actuator_pose

    return ikResponse(arm.angles)

def ik_server():
    rospy.init_node('ik_server')
    s = rospy.Service('ik', ik, handle_ik)
    print("Ready to do inverse kinematics.")
    rospy.spin()

if __name__ == "__main__":
    ik_server()