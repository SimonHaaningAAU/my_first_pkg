#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "roundround");
    
    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

    geometry_msgs::Twist cmd_vel_message;

    /*if (cmd_vel_message.angular.z >= 1){
        cmd_vel_message.angular.z = cmd_vel_message.angular.z + 1;
    }
    else {*/
        cmd_vel_message.angular.z = 1.0;
    //}
    cmd_vel_message.linear.x = 1.0; //Base was 1.0 changing positively makes bigger circles

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        cmd_vel_pub.publish(cmd_vel_message);
        loop_rate.sleep();
    }

    return 0;
}