#include <iostream>
#include <ros/ros.h>
#include <turtlesim/Pose.h>

void printPose(const turtlesim::Pose::ConstPtr& message)
{
    std::cout << "Turtle at [" << message->x << ", " << message->y << "]" << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "print_pose");

    ros::NodeHandle n;
    ros::Subscriber pose_subscriber = n.subscribe("/turtle1/pose", 100, &printPose);

    ros::spin();

    return 0;
}