#include "ros/ros.h"
#include "sensor_msgs/MagneticField.h"

int main(int argc, char** argv){

    ros::init(argc, argv, "mag_pub");
    ros::NodeHandle pnh("~");

    std::string frame_id;
    pnh.param<std::string>("frame_id",frame_id,"mag_frame");

    ros::Publisher mag_pub;
    mag_pub = pnh.advertise<sensor_msgs::MagneticField>("mag",1);

    int ct = 1;
    ros::Rate loop_rate(10);

    while(ros::ok()){

        sensor_msgs::MagneticField mag_msg;

        mag_msg.header.stamp = ros::Time::now();
        mag_msg.header.frame_id = frame_id;

        mag_msg.magnetic_field.x = ct;
        mag_msg.magnetic_field.y = ct;
        mag_msg.magnetic_field.z = ct;
        mag_pub.publish(mag_msg);

        ros::spinOnce();
        loop_rate.sleep();
        ct++;
        
    }

}