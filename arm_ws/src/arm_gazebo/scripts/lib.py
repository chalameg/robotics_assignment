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


# print(rotatex(60))
# print()

m1 = translatez(0.1)
m2 = rotatez(60).dot(translatez(0.05))
m3 = rotatex(30).dot(translatez(2.0))
m4 = rotatex(-90).dot(translatez(1.0))
m5 = rotatex(-30).dot(translatez(1.0))

m = m1
mats = [m2, m3, m4, m5]
for i in range(len(mats)):
    m = m.dot(mats[i])

# m = (((m1.dot(m2)).dot(m3)).dot(m4)).dot(m5)
#coordinate decsent

# print(m[1,3])

import tinyik as ik
arm = ik.Actuator([
        'z', [0.0, 0., 0.15], 
        'x', [0.0, 0., 2.0],
        'x', [0.0, 0., 1.],
        'x', [0.0, 0., 1.]
        ])

arm.ee = [1.0, 1.0, 1.0]

# ik.visualize(arm)
print(arm.ee.shape)

print(arm.angles)

# for i in range(len(arm.angles)):
#     print(np.degrees(arm.angles[i]))