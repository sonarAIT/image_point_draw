//(OpenCV4) g++ -std=c++11 dip08.cpp `pkg-config --cflags --libs opencv4`
//(OpenCV3) g++ dip08.cpp `pkg-config --cflags --libs opencv`
#include <iostream>  //入出力関連ヘッダ
#include <opencv2/opencv.hpp>  //OpenCV関連ヘッダ
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, const char* argv[])
{
    //①画像ファイルの読み込み
    //画像ファイル"ferarri.jpg"を読み込んで，画像データ"sourceImage"に格納
    cv::Mat sourceImage = cv::imread("lankershim.tif", cv::IMREAD_COLOR);
    if (sourceImage.data==0) {  //画像ファイルが読み込めなかった場合
        printf("File not found\n");
        exit(0);
    }
    printf("Width=%d, Height=%d\n", sourceImage.cols, sourceImage.rows);
    // resize image
//    const double sc = 1;
//    cv::resize(sourceImage, sourceImage, cv::Size(sourceImage.cols * sc, sourceImage.rows * sc));
    
    
    std::string filename = "US-101_01.txt";
    // input file
    std::ifstream ifs(filename);
    // read file
    std::string line;
    while (std::getline(ifs, line)) {
        // string split space
        std::stringstream ss(line);
        std::string word;
        std::vector<std::string> words;
        while (std::getline(ss, word, ' ')) {
            words.push_back(word);
        }

        std::string xStr = words[2];
        std::string yStr = words[3];
        xStr = xStr.substr(1, xStr.size() - 2);
        yStr = yStr.substr(0, yStr.size() - 1);
//        std::cout << xStr << "," << yStr << std::endl;
        
        double x = std::stod(xStr);
        double y = std::stod(yStr);

        cv::Point2d point(x, y);
        cv::circle(sourceImage, point, 10, cv::Scalar(0, 0, 255), -1);
    }

    //②画像を表示
    cv::namedWindow("sourceImage", cv::WINDOW_AUTOSIZE);
    cv::imshow("sourceImage", sourceImage);
    cv::waitKey(0);
    cv::imwrite("hoge.png", sourceImage);
    
    return 0;
}
