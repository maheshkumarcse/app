#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    cv::VideoCapture cap(0); // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Camera not found." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Pulse Measurement", cv::WINDOW_NORMAL);

    std::vector<double> green_values;
    int frame_count = 0;
    int duration = 10; // Measurement duration in seconds

    double start_time = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

    while (true) {
        cap >> frame; // Read a new frame from the camera
        if (frame.empty()) {
            break;
        }

        // Extract the green channel values
        std::vector<cv::Mat> channels;
        cv::split(frame, channels);
        cv::Mat green_channel = channels[1];

        // Calculate the average green channel value
        double average_green = cv::mean(green_channel)[0];
        green_values.push_back(average_green);

        frame_count++;

        double current_time = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();
        if ((current_time - start_time) >= duration) {
            break;
        }

        cv::imshow("Pulse Measurement", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    double fps = static_cast<double>(frame_count) / (static_cast<double>(cv::getTickCount()) / cv::getTickFrequency() - start_time);
    
    // Find peaks in the pulse signal
    std::vector<double> diff_signal;
    for (size_t i = 1; i < green_values.size(); ++i) {
        diff_signal.push_back(green_values[i] - green_values[i - 1]);
    }

    int num_peaks = 0;
    for (size_t i = 1; i < diff_signal.size(); ++i) {
        if (diff_signal[i - 1] > 0 && diff_signal[i] < 0) {
            num_peaks++;
        }
    }

    double pulse_rate = static_cast<double>(num_peaks) / duration * 60.0;

    std::cout << "Pulse rate: " << pulse_rate << " BPM" << std::endl;

    return 0;
}
