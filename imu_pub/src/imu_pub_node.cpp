#include <iostream>
#include <fstream>
#include <string>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/String.h"

using namespace std; // Dummy ya need to include this to read (its ok youre tired)

//#include "Mechanization.h" // Unsure about outputting Quaternian Data, Ask howard when back in town, for now just output read gyro and accel data


int main(int argc, char** argv){


    // Opening Input .txt File
    ifstream importData;
    importData.open("./src/imu_pub/src/hw3_data.txt");

    // ------ IMU Message (w/Data) Creation ----- //
    ros::init(argc,argv,"IMU_Gyro_and_Accel_Pub");
    ros::NodeHandle pnh ("~");

    std::string frame_id;
    pnh.param<std::string>("frame_id",frame_id,"IMU_Frame");

    ros::Publisher imu_pub;
    imu_pub = pnh.advertise<sensor_msgs::Imu>("IMU_data",1);

    ros::Rate loop_rate(10);

    // ----- Variable Creation ----- //
    double gyro[3];
    double accel[3];
    double mag[3];

    if(importData.is_open()){

        std::cout<<"CHECK: File is opened successfully!"<<std::endl;

        while(!importData.eof()&&ros::ok()){

            // ----- Read Data from .txt File ----- //
            importData >> accel[0] >> accel[1] >> accel[2]  // accelerometer data
                       >> gyro[0]  >> gyro[1]  >> gyro[2]   // gyroscope data
                       >> mag[0]   >> mag[1]   >> mag[2];   // magnometer data
            
            sensor_msgs::Imu imu_msg; // Verify name of IMU header file when you get to the lodge, this might need to change for ROS to run correctly (check via installed ROS toolkit)

            // ----- Message Header ----- //
            imu_msg.header.stamp = ros::Time::now();
            imu_msg.header.frame_id = frame_id;

            // ----- Message Body ----- //

                // --- Gyro Publihser Output --- //
                imu_msg.angular_velocity.x = *(gyro); 
                imu_msg.angular_velocity.y = *(gyro+1);
                imu_msg.angular_velocity.z = *(gyro+2);

                // --- Linear Accel Publihser Output --- //
                imu_msg.linear_acceleration.x = *(accel);
                imu_msg.linear_acceleration.y = *(accel+1);
                imu_msg.linear_acceleration.z = *(accel+2);

            // ----- Publish Compiled Message ----- //    
            imu_pub.publish(imu_msg);

            ros::spinOnce();
            loop_rate.sleep();

        }

        if(importData.eof()){

            std::cout<<"Congratulations, you have reached the end of the data file!"<<std::endl;

        }

    }

    else{

        std::cout<<"ERROR: Could Not Locate File!"<<std::endl;

    }
}
