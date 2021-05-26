;; Auto-generated. Do not edit!


(when (boundp 'arm_lib::Angles)
  (if (not (find-package "ARM_LIB"))
    (make-package "ARM_LIB"))
  (shadow 'Angles (find-package "ARM_LIB")))
(unless (find-package "ARM_LIB::ANGLES")
  (make-package "ARM_LIB::ANGLES"))

(in-package "ROS")
;;//! \htmlinclude Angles.msg.html


(defclass arm_lib::Angles
  :super ros::object
  :slots (_chassis_arm1 _arm1_arm2 _arm2_arm3 _arm3_arm4 ))

(defmethod arm_lib::Angles
  (:init
   (&key
    ((:chassis_arm1 __chassis_arm1) 0.0)
    ((:arm1_arm2 __arm1_arm2) 0.0)
    ((:arm2_arm3 __arm2_arm3) 0.0)
    ((:arm3_arm4 __arm3_arm4) 0.0)
    )
   (send-super :init)
   (setq _chassis_arm1 (float __chassis_arm1))
   (setq _arm1_arm2 (float __arm1_arm2))
   (setq _arm2_arm3 (float __arm2_arm3))
   (setq _arm3_arm4 (float __arm3_arm4))
   self)
  (:chassis_arm1
   (&optional __chassis_arm1)
   (if __chassis_arm1 (setq _chassis_arm1 __chassis_arm1)) _chassis_arm1)
  (:arm1_arm2
   (&optional __arm1_arm2)
   (if __arm1_arm2 (setq _arm1_arm2 __arm1_arm2)) _arm1_arm2)
  (:arm2_arm3
   (&optional __arm2_arm3)
   (if __arm2_arm3 (setq _arm2_arm3 __arm2_arm3)) _arm2_arm3)
  (:arm3_arm4
   (&optional __arm3_arm4)
   (if __arm3_arm4 (setq _arm3_arm4 __arm3_arm4)) _arm3_arm4)
  (:serialization-length
   ()
   (+
    ;; float32 _chassis_arm1
    4
    ;; float32 _arm1_arm2
    4
    ;; float32 _arm2_arm3
    4
    ;; float32 _arm3_arm4
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _chassis_arm1
       (sys::poke _chassis_arm1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _arm1_arm2
       (sys::poke _arm1_arm2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _arm2_arm3
       (sys::poke _arm2_arm3 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _arm3_arm4
       (sys::poke _arm3_arm4 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _chassis_arm1
     (setq _chassis_arm1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _arm1_arm2
     (setq _arm1_arm2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _arm2_arm3
     (setq _arm2_arm3 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _arm3_arm4
     (setq _arm3_arm4 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get arm_lib::Angles :md5sum-) "5fe5f0b7cf47a023278ced6a6706ef7a")
(setf (get arm_lib::Angles :datatype-) "arm_lib/Angles")
(setf (get arm_lib::Angles :definition-)
      "float32 chassis_arm1
float32 arm1_arm2
float32 arm2_arm3
float32 arm3_arm4

# float32 arm4_x
# float32 arm4_y
# float32 arm4_z

")



(provide :arm_lib/Angles "5fe5f0b7cf47a023278ced6a6706ef7a")


