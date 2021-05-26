; Auto-generated. Do not edit!


(cl:in-package arm_lib-msg)


;//! \htmlinclude Angles.msg.html

(cl:defclass <Angles> (roslisp-msg-protocol:ros-message)
  ((chassis_arm1
    :reader chassis_arm1
    :initarg :chassis_arm1
    :type cl:float
    :initform 0.0)
   (arm1_arm2
    :reader arm1_arm2
    :initarg :arm1_arm2
    :type cl:float
    :initform 0.0)
   (arm2_arm3
    :reader arm2_arm3
    :initarg :arm2_arm3
    :type cl:float
    :initform 0.0)
   (arm3_arm4
    :reader arm3_arm4
    :initarg :arm3_arm4
    :type cl:float
    :initform 0.0))
)

(cl:defclass Angles (<Angles>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Angles>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Angles)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name arm_lib-msg:<Angles> is deprecated: use arm_lib-msg:Angles instead.")))

(cl:ensure-generic-function 'chassis_arm1-val :lambda-list '(m))
(cl:defmethod chassis_arm1-val ((m <Angles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_lib-msg:chassis_arm1-val is deprecated.  Use arm_lib-msg:chassis_arm1 instead.")
  (chassis_arm1 m))

(cl:ensure-generic-function 'arm1_arm2-val :lambda-list '(m))
(cl:defmethod arm1_arm2-val ((m <Angles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_lib-msg:arm1_arm2-val is deprecated.  Use arm_lib-msg:arm1_arm2 instead.")
  (arm1_arm2 m))

(cl:ensure-generic-function 'arm2_arm3-val :lambda-list '(m))
(cl:defmethod arm2_arm3-val ((m <Angles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_lib-msg:arm2_arm3-val is deprecated.  Use arm_lib-msg:arm2_arm3 instead.")
  (arm2_arm3 m))

(cl:ensure-generic-function 'arm3_arm4-val :lambda-list '(m))
(cl:defmethod arm3_arm4-val ((m <Angles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader arm_lib-msg:arm3_arm4-val is deprecated.  Use arm_lib-msg:arm3_arm4 instead.")
  (arm3_arm4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Angles>) ostream)
  "Serializes a message object of type '<Angles>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'chassis_arm1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'arm1_arm2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'arm2_arm3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'arm3_arm4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Angles>) istream)
  "Deserializes a message object of type '<Angles>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'chassis_arm1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'arm1_arm2) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'arm2_arm3) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'arm3_arm4) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Angles>)))
  "Returns string type for a message object of type '<Angles>"
  "arm_lib/Angles")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Angles)))
  "Returns string type for a message object of type 'Angles"
  "arm_lib/Angles")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Angles>)))
  "Returns md5sum for a message object of type '<Angles>"
  "5fe5f0b7cf47a023278ced6a6706ef7a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Angles)))
  "Returns md5sum for a message object of type 'Angles"
  "5fe5f0b7cf47a023278ced6a6706ef7a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Angles>)))
  "Returns full string definition for message of type '<Angles>"
  (cl:format cl:nil "float32 chassis_arm1~%float32 arm1_arm2~%float32 arm2_arm3~%float32 arm3_arm4~%~%# float32 arm4_x~%# float32 arm4_y~%# float32 arm4_z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Angles)))
  "Returns full string definition for message of type 'Angles"
  (cl:format cl:nil "float32 chassis_arm1~%float32 arm1_arm2~%float32 arm2_arm3~%float32 arm3_arm4~%~%# float32 arm4_x~%# float32 arm4_y~%# float32 arm4_z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Angles>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Angles>))
  "Converts a ROS message object to a list"
  (cl:list 'Angles
    (cl:cons ':chassis_arm1 (chassis_arm1 msg))
    (cl:cons ':arm1_arm2 (arm1_arm2 msg))
    (cl:cons ':arm2_arm3 (arm2_arm3 msg))
    (cl:cons ':arm3_arm4 (arm3_arm4 msg))
))
