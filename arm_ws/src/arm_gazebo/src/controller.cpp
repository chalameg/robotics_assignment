#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <arm_lib/Angles.h>
#include <arm_lib/fk.h>
#include <arm_lib/ik.h>
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

			// // instiantiate the joint controller
			this->jointController = this->model->GetJointController();

			this->pid = common::PID(5.1, 4.01, 10.03);

			this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
			ros::SubscribeOptions so = ros::SubscribeOptions::create<arm_lib::Angles>(
				"/" + this->model->GetName() + "/pos_cmd",
				1,
				boost::bind(&ModelPush::OnRosMsg, this, _1),
				ros::VoidPtr(), &this->rosQueue);
			this->current_angles_pub = this->rosNode->advertise<arm_lib::Angles>("/current_angles", 1000);
			this->rosSub = this->rosNode->subscribe(so);

			// subscribe 
            this->rosNode1.reset(new ros::NodeHandle("gazebo_client1"));
            ros::SubscribeOptions so1 =
                ros::SubscribeOptions::create<std_msgs::String>(
                     "/catchrelease",
                        1,
                    boost::bind(&ModelPush::OnRosMsg1, this, _1),
                    ros::VoidPtr(), &this->rosQueue1);

            this->rosSub = this->rosNode->subscribe(so1);

			this->rosQueueThread = std::thread(std::bind(&ModelPush::QueueThread, this));
			this->rosQueueThread1 =
              std::thread(std::bind(&ModelPush::QueueThread1, this));

			this->rosDataPublishThread = std::thread(std::bind(&ModelPush::Publish, this));

			left_finger = this->model->GetJoint("palm_left_finger")->GetScopedName();
            right_finger = this->model->GetJoint("palm_right_finger")->GetScopedName();

			this->jointController->SetPositionPID(this->left_finger, this->pid);
            this->jointController->SetPositionPID(this->right_finger, this->pid);

			inverseKinematics();
			// Listen to the update event. This event is broadcast every
			// simulation iteration.
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&ModelPush::OnUpdate, this));

		}

	private:
		void inverseKinematics()
		{
			//call inverse kinematics service
			ros::ServiceClient client1 = this->rosNode->serviceClient<arm_lib::ik>("/ik");
			arm_lib::ik srv1;
			srv1.request.actuator_pose = {2,1,1};
			
			if(client1.call(srv1)){
	
				// std::cout << srv1.response.new_angles[1] << std::endl;
				angle[0] = srv1.response.new_angles[0];
				angle[1] = srv1.response.new_angles[1];
				angle[2] = srv1.response.new_angles[2];
				angle[3] = srv1.response.new_angles[3];
				// std::cout << "/fk is called." ;
			}
		}

	private:
		void Publish()
		{
			ros::Rate loop_rate(10);
			while (ros::ok())
			{
				
				//call forward kinematics and publish end effector pose
				arm_lib::Angles pos;
				pos.chassis_arm1 = getJointPose("chassis_arm1_joint", 0);
				pos.arm1_arm2 = getJointPose("arm1_arm2_joint", 0);
				pos.arm2_arm3  = getJointPose("arm2_arm3_joint", 0);
				pos.arm3_arm4 = getJointPose("arm3_arm4_joint", 0);
				
				ros::ServiceClient client = this->rosNode->serviceClient<arm_lib::fk>("/fk");
				arm_lib::fk srv;  
				srv.request.joint_angles = {pos.chassis_arm1, pos.arm1_arm2, pos.arm2_arm3, pos.arm3_arm4};
				srv.request.link_lengths = {0.05, 2.0, 1.0, 1.0, };
				if(client.call(srv)){
					pos.actuator_x = srv.response.actuator_pose[0];
					pos.actuator_y = srv.response.actuator_pose[1];
					pos.actuator_z = srv.response.actuator_pose[2];
				}
				this->current_angles_pub.publish(pos);

				std::cout << pos << std::endl;

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

		public: void OnRosMsg1(const std_msgs::String::ConstPtr& msg)
        {

            std::stringstream ss(msg->data.c_str());
            
            std::string s = ss.str(); 
            std::cout <<  s << std::endl;
            
            if(s.find("catch") != std::string::npos){
               ROS_INFO("value Equals catch"); 
               this->jointController->SetPositionTarget(this->left_finger, -0.52360);
               this->jointController->SetPositionTarget(this->right_finger, 0.52360);
            }else{
                if(s.find("release") != std::string::npos){
                  this->jointController->SetPositionTarget(this->left_finger, 0.6);
                  this->jointController->SetPositionTarget(this->right_finger, -0.6);
                }
            }

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
	private: void QueueThread1()
        {
			static const double timeout = 0.01;
			while (this->rosNode1->ok())
			{
				this->rosQueue1.callAvailable(ros::WallDuration(timeout));
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
		std::unique_ptr<ros::NodeHandle> rosNode1;

	private:
		ros::Subscriber rosSub;

	private:
		ros::Subscriber linkStateSub;

	private:
		std::thread rosQueueThread,rosQueueThread1, rosDataPublishThread;

	private:
		ros ::CallbackQueue rosQueue;
		ros::CallbackQueue rosQueue1;
		std::string right_finger;
        std::string left_finger;

	};
	// Register this plugin with the simulator
	GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}