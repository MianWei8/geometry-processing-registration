#include "random_points_on_mesh.h"
#include "math.h"
#include <igl/cumsum.h>
#include <igl/doublearea.h>

//Still need to finish this?
int binary_search(const Eigen::MatrixXd &V, double randVal)
{
    if (V.rows() == 1){
        return 0;
    }
    Eigen::MatrixXd Vhalf;
    
    int n = V.rows();
    
    if (randVal < V(ceil(n/2),0)){
        Vhalf.resize(floor(n/2),1);
        Vhalf = V.topRows(floor(n/2));
        return binary_search(Vhalf, randVal);
    }
    else{
        Vhalf.resize(ceil(n/2),1);
        Vhalf = V.bottomRows(ceil(n/2));
        return floor(n/2) + binary_search(Vhalf, randVal);
        
    }
}

void random_points_on_mesh(
  const int n,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & X)
{
  // REPLACE WITH YOUR CODE:
    X.resize(n,3);
    int size = V.rows(), curIndex;
    double alpha,beta, randVal, curSum;
    Eigen::MatrixXd A;
    A.resize(size,1);
    Eigen::RowVector3d u,newV,crossedV;
    curSum = 0;
    igl::doublearea(V,F,A);
    Eigen::MatrixXd C;
    C.resizeLike(A);
    igl::cumsum(A,2,C);
    C = C/C(C.rows() - 1);
    
    for(int i = 0;i<n;i++) {
        randVal = floor(rand()*size);
        alpha = rand();
        beta = rand();
        if (alpha + beta > 1) {
            alpha = 1 - alpha;
            beta = 1 - beta;
        }
        curIndex = binary_search(C, randVal);
        
        X.row(i) = (1 - (alpha + beta)) * V.row(F(curIndex,0)) + alpha * V.row(F(curIndex,1)) + beta * V.row(F(curIndex,2));
        //Need to find the current triangle
    }
}



