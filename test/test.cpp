#include"catch_ros/catch.hpp"
#include"ros/ros.h"
#include"std_msgs/Int32.h"

static int called = false;
void callback(const std_msgs::Int32 & i)
{
    // if what we have published has not yet been received by the node under
    // test we will see a 0. This means the test has not really started yet
    if(i.data !=0 || called)
    {
        called = true;
        CHECK(i.data == 55);
    }
    else
    {
        CHECK(i.data == 0);
    }
}

TEST_CASE("pubsub", "[pubsub]")
{
    // this test case subscribes to a topic and checks the results
    ros::NodeHandle nh;
    const auto sub = nh.subscribe("myint", 1000, callback);

    // a latched publisher is used to account for the case that we publish
    // this message before the node under test can subscribe to the input topic
    const auto pub = nh.advertise<std_msgs::Int32>("input", 1000, true); 
    std_msgs::Int32 out;
    out.data = 55;
    pub.publish(out);
    ros::Rate r(100.0); //frequency is significantly higher then the expected publishing frequency
    for(int i = 0; ros::ok() && i != 200; ++i)
    {
        ros::spinOnce();
        r.sleep();
    }
    CHECK(called);
}

