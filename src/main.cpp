#include <opencv2/opencv.hpp>
#include <torch/torch.h>
#include <iostream>

int main() {
    std::cout << "Hello, PyTorch(" << TORCH_VERSION << ") and OpenCV(" << CV_VERSION << ")" << std::endl;

    // Check if CUDA is available and set the device
    torch::Device device = (torch::cuda::is_available()) ? torch::kCUDA : torch::kCPU;
    std::cout << "CUDA " << ((device == torch::kCUDA) ? "is" : "is not") << "available" << std::endl;

    // Create a tensor and display it
    torch::Tensor tensor = torch::rand({2, 3}, device);
    std::cout << "Tensor on " << ((device == torch::kCUDA) ? "GPU" : "CPU") << ":" << std::endl;
    std::cout << tensor << std::endl;

    // Open the camera and display the feed
    std::cout << "Opening camera..." << std::endl;
    cv::VideoCapture cap(0);

    // Check if camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::cout << "Press ESC to exit" << std::endl;
    while (1) {
        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty()) {
            std::cerr << "Error capturing frame" << std::endl;
            break;
        }

        // Display the resulting frame
        cv::imshow("Camera", frame);

        // Press  ESC on keyboard to exit
        if (cv::waitKey(1) >= 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }

    // When everything done, release the video capture object
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
