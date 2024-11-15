// cpp headers
#include <memory>

// ros2 dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

// create a subscriber to a topic
class DemoSubscriber : public rclcpp::Node {
  public:
    // the constructor initializes the node and creates a subscription
    DemoSubscriber()
    : Node("demo_subscriber") {
      subscription_ = this->create_subscription<std_msgs::msg::String>("yap", 10, std::bind(&DemoSubscriber::topic_callback, this, _1));
    }

  private:
    // 
    void topic_callback(const std_msgs::msg::String & msg) const {
      RCLCPP_INFO(this->get_logger(), "Its giving: '%s'", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};


// main loop
int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);                         // initializes the node
  rclcpp::spin(std::make_shared<DemoSubscriber>()); // process the data on the node
  rclcpp::shutdown();                               // shutsdown the node
  return 0;
}