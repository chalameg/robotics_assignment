#!/usr/bin/env python

## Simple transformation demo that published transformed vector by rotation and translation
## to the 'chatter' topic
import numpy as np
import rospy

from std_msgs.msg import String

from vector_transformation.msg import input_msg
from vector_transformation.msg import output_msg

in_mess = input_msg()
out_mess = output_msg()

in_mess.point.x = 0
in_mess.point.y = 2
in_mess.point.z = 3

in_mess.distance = 2
in_mess.theta = 40
in_mess.beta = 30
in_mess.gamma = 30

def rotatez(v, degree):
    rad = np.radians(degree)
    m = np.array([
        [np.cos(rad), -np.sin(rad), 0],
        [np.sin(rad), np.cos(rad), 0],
        [0,         0,            1]
    ])
    return np.dot(m, v)

def rotatey(v, degree):
    rad = np.radians(degree)
    m = np.array([
        [np.cos(rad),0, np.sin(rad)],
        [0,         1,            0],
        [-np.sin(rad),0, np.cos(rad)],
    ])
    return np.dot(m, v)

def rotatex(v, degree):
    rad = np.radians(degree)
    m = np.array([
        [1,         0,          0],
        [0, np.cos(rad), -np.sin(rad)],
        [0, np.sin(rad), np.cos(rad)],
        
    ])
    return np.dot(m, v)

def translateByD(v, distance):
    return np.multiply(v, distance)

rotatedx = rotatex([in_mess.point.x,in_mess.point.y,in_mess.point.z], in_mess.theta) 
rotatedy = rotatey(rotatedx, in_mess.beta) 
rotatedz = rotatez(rotatedy, in_mess.gamma) 

translated = translateByD(rotatedz, in_mess.distance)

out_mess.output_vector.x = translated[0]
out_mess.output_vector.y = translated[1]
out_mess.output_vector.z = translated[2]

transformed_vector = out_mess.output_vector 

def transformer():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('transformer', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        output_vector = "Transformed vector = %s" %  transformed_vector
        rospy.loginfo(output_vector)
        pub.publish(output_vector)
        rate.sleep()

if __name__ == '__main__':
    try:
        transformer()
    except rospy.ROSInterruptException:
        pass
