#!/usr/bin/env python
from __future__ import print_function
from arm_lib.srv import fk, fkResponse
import rospy

import numpy as np

def rotatex(degree):
    rad = np.radians(degree)
    m = np.array([
        [1,         0,          0,     0],
        [0, np.cos(rad), -np.sin(rad), 0],
        [0, np.sin(rad), np.cos(rad),  0],
        [0,          0,            0,  1],
        
    ])

    return m

def rotatez(degree):
    rad = np.radians(degree)
    m = np.array([
        [np.cos(rad), -np.sin(rad), 0, 0],
        [np.sin(rad), np.cos(rad), 0,  0],
        [0,         0,            1,  0],
        [0,         0,            0,  1]
    ])
    return m

def rotatey(degree):
    rad = np.radians(degree)
    m = np.array([
        [np.cos(rad),0, np.sin(rad), 0],
        [0,         1,            0, 0],
        [-np.sin(rad),0, np.cos(rad),0],
        [0,         0,            0, 1]
    ])
    return m

def translatez(distance):
    m = np.array([
        [1, 0, 0,        0],
        [0, 1, 0,        0],
        [0, 0, 1, distance],
        [0, 0, 0,        1]
    ])
    return m


def handle_fk(req):
    # print("Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b)))
    m1 = translatez(0.1)
    m2 = rotatez(req.joint_angles[0]).dot(translatez(req.link_lengths[0]))
    m3 = rotatex(req.joint_angles[1]).dot(translatez(req.link_lengths[1]))
    m4 = rotatex(req.joint_angles[2]).dot(translatez(req.link_lengths[2]))
    m5 = rotatex(req.joint_angles[3]).dot(translatez(req.link_lengths[3]))

    m = m1
    mats = [m2, m3, m4, m5]
    for i in range(len(mats)):
        m = m.dot(mats[i])
    
    actuator_pose = [m[0,3], m[1,3], m[2,3]]

    return fkResponse(actuator_pose)

def fk_server():
    rospy.init_node('fk_server')
    s = rospy.Service('fk', fk, handle_fk)
    print("Ready to do forward kinematics.")
    rospy.spin()

if __name__ == "__main__":
    fk_server()