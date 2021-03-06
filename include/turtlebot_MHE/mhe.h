#ifndef MHE_H
#define MHE_H

#include <Eigen/Core>
#include <vector>
#define TIME_HORIZON 5
#define NUM_LANDMARKS 9

namespace mhe
{

enum
{
    X = 0,
    Y = 1,
    THETA = 2,

    V = 0,
    W = 1,

    R = 0,
    PHI = 1,
};

typedef Eigen::Vector3d Pose;
typedef Eigen::Vector2d Input;
typedef Eigen::Matrix<double, 2, NUM_LANDMARKS> Meas;
typedef Eigen::Matrix<bool, TIME_HORIZON, NUM_LANDMARKS> Zidx;

class MHE
{
public:
    MHE();
    virtual ~MHE();
    void setParams(const Pose& mu0, const Pose& omega, const Pose& slew, double sig_r, double sig_phi);
    Pose propagateState(const Pose& state, const Input& u, double dt);
    void update(const Pose& mu, const Meas& z, const Zidx& idx, const Input& u, double dt);
    void optimize();
    void initializeLandmark(int index, const Eigen::Vector2d &lm);
    void writeFile();

private:
    std::vector<Pose> pose_hist_;
    std::vector<Meas> z_hist_;
    std::vector<Pose> odom_hist_;
    Zidx z_ind_;
    Meas lms_;
    Pose mu_;
    Eigen::Matrix2d R_inv_;
    Eigen::Matrix3d Omega_;
    Eigen::Matrix3d S_;
};

} // namespace mhe

#endif // MHE_H 

