#include <igl/triangle/triangulate.h>
#include <igl/writeOBJ.h>
#include <iostream>
#include <Eigen/Core>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: triangulate (input file name) (desired triangle area) (output file name)" << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs)
    {
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return -1;
    }

    std::vector<double> xs;
    std::vector<double> ys;
    while (ifs)
    {
        double x, y;
        ifs >> x >> y;
        if (ifs)
        {
            xs.push_back(x);
            ys.push_back(y);
        }
    }

    double area = strtod(argv[2], NULL);
    if (area <= 0.0)
    {
        std::cerr << "Must specify positive area" << std::endl;
        return -1;
    }

    int numpts = (int)xs.size();
    if (numpts < 3)
    {
        std::cerr << "File needs to contain at least 3 points" << std::endl;
        return -1;
    }

    Eigen::MatrixXd PV(numpts, 2);
    Eigen::MatrixXi PE(numpts, 2);
    for (int i = 0; i < numpts; i++)
    {
        PV(i, 0) = xs[i];
        PV(i, 1) = ys[i];
        PE(i, 0) = i;
        PE(i, 1) = ((i + 1) % numpts);
    }

    std::stringstream ss;
    ss << "-a" << std::fixed << area << "Djz";
    std::string flags = ss.str();
    Eigen::MatrixXd H(0, 2);
    Eigen::MatrixXd planeV;
    Eigen::MatrixXi F;
    igl::triangle::triangulate(PV, PE, H, flags, planeV, F);
    int tris = planeV.rows();
    Eigen::MatrixXd spaceV(tris, 3);
    for (int i = 0; i < tris; i++)
    {
        spaceV(i, 0) = planeV(i, 0);
        spaceV(i, 1) = planeV(i, 1);
        spaceV(i, 2) = 0;
    }
    igl::writeOBJ(argv[3], spaceV, F);

    int a;
    std::cin >> a;
}
