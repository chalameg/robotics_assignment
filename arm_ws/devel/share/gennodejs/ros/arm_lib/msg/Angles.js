// Auto-generated. Do not edit!

// (in-package arm_lib.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Angles {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.chassis_arm1 = null;
      this.arm1_arm2 = null;
      this.arm2_arm3 = null;
      this.arm3_arm4 = null;
    }
    else {
      if (initObj.hasOwnProperty('chassis_arm1')) {
        this.chassis_arm1 = initObj.chassis_arm1
      }
      else {
        this.chassis_arm1 = 0.0;
      }
      if (initObj.hasOwnProperty('arm1_arm2')) {
        this.arm1_arm2 = initObj.arm1_arm2
      }
      else {
        this.arm1_arm2 = 0.0;
      }
      if (initObj.hasOwnProperty('arm2_arm3')) {
        this.arm2_arm3 = initObj.arm2_arm3
      }
      else {
        this.arm2_arm3 = 0.0;
      }
      if (initObj.hasOwnProperty('arm3_arm4')) {
        this.arm3_arm4 = initObj.arm3_arm4
      }
      else {
        this.arm3_arm4 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Angles
    // Serialize message field [chassis_arm1]
    bufferOffset = _serializer.float32(obj.chassis_arm1, buffer, bufferOffset);
    // Serialize message field [arm1_arm2]
    bufferOffset = _serializer.float32(obj.arm1_arm2, buffer, bufferOffset);
    // Serialize message field [arm2_arm3]
    bufferOffset = _serializer.float32(obj.arm2_arm3, buffer, bufferOffset);
    // Serialize message field [arm3_arm4]
    bufferOffset = _serializer.float32(obj.arm3_arm4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Angles
    let len;
    let data = new Angles(null);
    // Deserialize message field [chassis_arm1]
    data.chassis_arm1 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [arm1_arm2]
    data.arm1_arm2 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [arm2_arm3]
    data.arm2_arm3 = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [arm3_arm4]
    data.arm3_arm4 = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'arm_lib/Angles';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5fe5f0b7cf47a023278ced6a6706ef7a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 chassis_arm1
    float32 arm1_arm2
    float32 arm2_arm3
    float32 arm3_arm4
    
    # float32 arm4_x
    # float32 arm4_y
    # float32 arm4_z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Angles(null);
    if (msg.chassis_arm1 !== undefined) {
      resolved.chassis_arm1 = msg.chassis_arm1;
    }
    else {
      resolved.chassis_arm1 = 0.0
    }

    if (msg.arm1_arm2 !== undefined) {
      resolved.arm1_arm2 = msg.arm1_arm2;
    }
    else {
      resolved.arm1_arm2 = 0.0
    }

    if (msg.arm2_arm3 !== undefined) {
      resolved.arm2_arm3 = msg.arm2_arm3;
    }
    else {
      resolved.arm2_arm3 = 0.0
    }

    if (msg.arm3_arm4 !== undefined) {
      resolved.arm3_arm4 = msg.arm3_arm4;
    }
    else {
      resolved.arm3_arm4 = 0.0
    }

    return resolved;
    }
};

module.exports = Angles;
