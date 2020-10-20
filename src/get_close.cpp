#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

geometry_msgs::Twist cmd_vel_message;
float velocity_gain_base = 0.1; //Was velocity_gain changed for bonus assignment
float velocity_gain_mult = 10;  //Base of 1 is standard speed
float velocity_gain = velocity_gain_base * velocity_gain_mult;
float angular_gain = 1.0;
turtlesim::Pose turtle1_pose;

void cbPose1(const turtlesim::Pose::ConstPtr& message)
{
    turtle1_pose = *message;
}

void cbPose2(const turtlesim::Pose::ConstPtr& message)
{
    double x_distance = turtle1_pose.x - message->x;
    double y_distance = turtle1_pose.y - message->y;
    double distance = hypot(x_distance, y_distance);

    double heading = atan2(y_distance, x_distance);
    double angular_difference = heading - message->theta;
    if (angular_difference > M_PI)
    {
        angular_difference = angular_difference - (2 * M_PI);
    }
    else if (angular_difference < (-M_PI))
    {
        angular_difference = angular_difference + (2 * M_PI);
    }
    cmd_vel_message.linear.x = velocity_gain * distance;
    cmd_vel_message.angular.z = angular_gain * angular_difference;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "get_close");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1);

    ros::Subscriber pose1_subscriber = n.subscribe("/turtle1/pose", 100, &cbPose1);
    ros::Subscriber pose2_subscriber = n.subscribe("/turtle2/pose", 100, &cbPose2);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        cmd_vel_pub.publish(cmd_vel_message);
        loop_rate.sleep();

        ros::spinOnce();
    }

    return 0;
}
