#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <arm_lib/Angles.h>
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"	
#include <thread>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>

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

			this->pid = common::PID(10.1, 4.01, 8.03);

			this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
			ros::SubscribeOptions so = ros::SubscribeOptions::create<arm_lib::Angles>(
				"/" + this->model->GetName() + "/pos_cmd",
				1,
				boost::bind(&ModelPush::OnRosMsg, this, _1),
				ros::VoidPtr(), &this->rosQueue);
			this->current_angles_pub = this->rosNode->advertise<std_msgs::String>("/current_angles", 1000);
			this->rosSub = this->rosNode->subscribe(so);

			this->rosQueueThread = std::thread(std::bind(&ModelPush::QueueThread, this));
			this->rosDataPublishThread = std::thread(std::bind(&ModelPush::Publish, this));

			// Listen to the update event. This event is broadcast every
			// simulation iteration.
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&ModelPush::OnUpdate, this));

		}


	private:
		void Publish()
		{
			ros::Rate loop_rate(10);
			while (ros::ok())
			{
				double a1 = getJointPose("chassis_arm1_joint", 0);
				double a2 = getJointPose("arm1_arm2_joint", 0);
				double a3 = getJointPose("arm2_arm3_joint", 0);
				double a4 = getJointPose("arm3_arm4_joint", 0);

				physics::LinkPtr arm4 = this->model->GetLink("arm4");
				physics::LinkState state = physics::LinkState(arm4);
				ignition::math::Vector3d pos = state.Pose().Pos();
				
				std_msgs::String msg;
				std::stringstream ss;
				ss << "arm_4 pose X: " << pos.X() << "\n"
				<< "arm_4 pose Y: " << pos.Y() << "\n"
				<< "arm_4 pose Z: " << pos.Z() << "\n"
				<< "current angles of: \n"
				<< "chassis_arm1_joint = " << a1 << "\n"
				<< "arm1_arm2_joint = " << a2 << "\n"
				<< "arm2_arm3_joint = " << a3 << "\n"
				<< "arm3_arm4_joint = " << a4 << "\n";
				msg.data = ss.str();

				this->current_angles_pub.publish(msg);

				std::cout << ss.str() << std::endl;

				ros::spinOnce();
				loop_rate.sleep();
			}
		}

		// Called by the world update start event
	public:
		void OnUpdate()
		{
			SetJointAngle("chassis_arm1_joint", angle[0]);
			SetJointAngle("arm1_arm2_joint", angle[1]);
			SetJointAngle("arm2_arm3_joint", angle[2]);
			SetJointAngle("arm3_arm4_joint", angle[3]);
			
		}
	public:
		void OnRosMsg(const arm_lib::Angles::ConstPtr &msg)
		{
			angle[0] = msg->chassis_arm1;
			angle[1] = msg->arm1_arm2;
			angle[2] = msg->arm2_arm3;
			angle[3] = msg->arm3_arm4;
		}

	public:
  		void QueueThread()
			{
				static const double timeout = 0.01;
				while (this->rosNode->ok())
				{
				this->rosQueue.callAvailable(ros::WallDuration(timeout));
				}
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

	private:
  		float angle[4] = {0, 0, 0, 0};

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

	private:
		std::unique_ptr<ros::NodeHandle> rosNode;

	private:
		ros::Subscriber rosSub;

	private:
		ros::Subscriber linkStateSub;

	private:
		std::thread rosQueueThread, rosDataPublishThread;

	private:
		ros ::CallbackQueue rosQueue;

	};
	// Register this plugin with the simulator
	GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}