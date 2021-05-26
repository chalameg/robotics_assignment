#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"

namespace gazebo
{
	class ModelPush : public ModelPlugin
	{
	public:
		void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
		{

			// Make sure the ROS node for Gazebo has already been initialized
			if (!ros::isInitialized())
			{
				ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
								 << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
				return;
			}

			// Store the pointer to the model
			this->model = _parent;

			// // intiantiate the joint controller
			this->jointController = this->model->GetJointController();

			// // set your PID values
			this->pid = common::PID(31.1, 10.01, 10.03);

			// Listen to the update event. This event is broadcast every
			// simulation iteration.
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&ModelPush::OnUpdate, this));

			//create rosnode to publish current angle of joints
			ros::NodeHandle n;
			this->current_angles_pub = n.advertise<std_msgs::String>("current_angles_topic_two", 100);
		}

		// Called by the world update start event
	public:
		void OnUpdate()
		{

			SetJointAngle("chasis_arm1_joint", 30);
			SetJointAngle("arm1_arm2_joint", 30);
			SetJointAngle("arm2_arm3_joint", -30);
			SetJointAngle("arm3_arm4_joint", 30);

			
			double a1 = getJointPose("chasis_arm1_joint", 0);
			double a2 = getJointPose("arm1_arm2_joint", 0);
			double a3 = getJointPose("arm2_arm3_joint", 0);
			double a4 = getJointPose("arm3_arm4_joint", 0);

			std_msgs::String msg;
			std::stringstream ss;
			ss << "current angles of: "
			   << "chasis_arm1_joint = " << a1 << " "
			   << "arm1_arm2_joint = " << a2 << " "
			   << "arm2_arm3_joint = " << a3 << " "
			   << "arm3_arm4_joint = " << a4 << " ";
			msg.data = ss.str();

			// msg.data = "Current arm1_arm2_joint values: " + std::to_string(a1 * 180.0 / M_PI);
			this->current_angles_pub.publish(msg);

			std::cout << ss.str() << std::endl;
		}
	
	private:
		void SetJointAngle(std::string joint_name, float degree)
		{
			float rad = M_PI * degree / 180;
			std::string name = this->model->GetJoint(joint_name)->GetScopedName();
			this->jointController->SetPositionPID(name, pid);
			this->jointController->SetPositionTarget(name, rad);
		}

	// Get joint position by index.
	// 0 returns rotation accross X axis
	// 1 returns rotation accross Y axis
	// 2 returns rotation accross Z axis
	// If the Joint has only Z axis for rotation, 0 returns that value and 1 and 2 return nan
	private:
		float getJointPose(std::string joint_name, int index)
		{
			double a1 = physics::JointState(this->model->GetJoint(joint_name)).Position(index);
			return a1 * 180.0 / M_PI;
		}

	// a pointer that points to a model object
	private:
		physics::ModelPtr model;

		// 	// A joint controller object
		// 	// Takes PID value and apply angular velocity
		// 	//  or sets position of the angles
	private:
		physics::JointControllerPtr jointController;

	private:
		event::ConnectionPtr updateConnection;

		//  PID object
	private:
		common::PID pid;

	private:
		ros::Publisher current_angles_pub;
	};

	// private:
	// 	std::unique_ptr<ros::NodeHandle> rosNode;

	// private:
	// 	ros::Subscriber rosSub;

	// private:
	// 	ros::Subscriber linkStateSub;

	// private:
	// 	std::thread rosQueueThread, rosDataPublishThread;

	// private:
	// 	ros ::CallbackQueue rosQueue;

	// private:
	//   ros::Publisher data_pub;

	// Register this plugin with the simulator
	GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}