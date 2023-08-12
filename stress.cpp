//code for stress level
#include <iostream>
#include <string>

int main() {
    int stressScore = 0;
    
    std::cout << "Welcome to the Stress Level Assessment!" << std::endl;
    std::cout << "Answer the following questions using a scale of 1 to 5 (1 = Not at all, 5 = Very much)." << std::endl;
    
    std::string questions[] = {
        "How overwhelmed do you feel right now?",
        "How often do you experience difficulty relaxing?",
        "How often do you have trouble concentrating?",
        "How frequently do you feel irritable or angry?",
        "How often do you feel anxious or worried?"
    };
    
    for (const std::string &question : questions) {
        int response;
        do {
            std::cout << question << " (1-5): ";
            std::cin >> response;
        } while (response < 1 || response > 5);
        
        stressScore += response;
    }
    
    // Calculate an average stress score
    double averageStressScore = static_cast<double>(stressScore) / 5.0;
    
    std::cout << "Your average stress score is: " << averageStressScore << std::endl;
    
    if (averageStressScore <= 2.5) {
        std::cout << "You seem to be relatively calm." << std::endl;
    } else if (averageStressScore <= 3.5) {
        std::cout << "You may be experiencing moderate stress." << std::endl;
    } else {
        std::cout << "Your stress level appears to be high. Consider seeking support." << std::endl;
    }
    
    return 0;
}
