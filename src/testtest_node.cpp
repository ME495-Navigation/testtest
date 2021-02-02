/// \file
/// \brief Test node that publishes


#include"ros/ros.h"
#include"std_msgs/Int32.h"

static std_msgs::Int32 to_pub{};

void callback(const std_msgs::Int32 & i)
{
    to_pub = i;
    ROS_INFO_STREAM("HELLO: " << i.data);
}

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "testest");
    ros::NodeHandle nh;
    const auto pub = nh.advertise<std_msgs::Int32>("myint", 1000);
    const auto sub = nh.subscribe("input", 10000, callback);
    ros::Rate r(10.0);
    while(ros::ok())
    {
        pub.publish(to_pub);
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
