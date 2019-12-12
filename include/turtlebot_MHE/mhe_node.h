#ifndef MHE_NODE_H
#define MHE_NODE_H

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <aruco_localization/MarkerMeasurementArray.h>
#include "turtlebot_MHE/mhe.h"

class MHENode
{
public:
    MHENode();
    ~MHENode();

protected:
    void measCallback(const aruco_localization::MarkerMeasurementArrayConstPtr& msg);
    void odomCallback(const nav_msgs::OdometryConstPtr& msg);

private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;
    ros::Subscriber meas_sub_;
    ros::Subscriber odom_sub_;
//    ros::Publisher est_pub_;
    std::map<int, int> id2idx_;
    mhe::MHE estimator_;
    mhe::Meas z_cur_;
    mhe::Zidx z_idx_;
    mhe::Pose odom_;
};

#endif // MHE_NODE_H
