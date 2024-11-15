// standard cpp headers
#include <chrono>
#include <functional>
#include <memory>
#include <string>

// ros2 dependencies 
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// namespace
using namespace std::chrono_literals;


// Create a publisher
class DemoPublisher : public rclcpp::Node {
  public:
    // the constructor names the node and initialices all the variables
    DemoPublisher() 
    : Node("demo_publisher"), count_(0) {
      publisher_ = this->create_publisher<std_msgs::msg::String>("yap", 10);                  // publishes to the yap topic
      timer_ = this->create_wall_timer(500ms, std::bind(&DemoPublisher::publish_data, this)); // will callback the publish data method every 500ms
    }

  private:
    // methods
    void publish_data() {
      auto message = std_msgs::msg::String();                                    // create a msg variable
      message.data = "Yapping in c++!: msg " + std::to_string(count_++);         // give it a value
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str()); // print it to the console
      publisher_->publish(message);                                              // publish the msg
    }

    // variables
    rclcpp::TimerBase::SharedPtr timer_;                             // calls back the publishing funtion
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // publishes a mesage to the topic
    size_t count_;                                                   // keeps count of mesages sent
};


// Main Loop 
int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);                        // initialize the node
  rclcpp::spin(std::make_shared<DemoPublisher>()); // process info on the node
  rclcpp::shutdown();                              // shutdown the node
  return 0;
}
