#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char** argv){

    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher ch_pub = n.advertise<std_msgs::String>("Chatter", 1000);

    ros::Rate loop_rate(1);

    while(ros::ok()){

        std_msgs::String msg;
        msg.data = "War Eagle";
        ROS_INFO("Hello");
        ch_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();

    }


}